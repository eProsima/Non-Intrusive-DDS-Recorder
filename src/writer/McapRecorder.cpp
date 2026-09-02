/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/

/*
 * The MCAP output is optional: MCAP_SUPPORT is defined by CMake only when the vendored mcap
 * library and its lz4/zstd dependencies are available. This file is compiled either way and
 * provides the same class both times, so nothing else in the tool needs a conditional.
 */
#ifdef MCAP_SUPPORT

/*
 * The mcap library is header-only and its implementation must be compiled in exactly one
 * translation unit. This is that unit, which is also why no other file includes an mcap header.
 */
/* mcap/types.hpp uses the fixed-width integer types but includes only <cstddef>. */
#include <cstdint>

#define MCAP_IMPLEMENTATION
#include <mcap/writer.hpp>

#endif // ifdef MCAP_SUPPORT

#include <database/EntitiesDB.h>
#include <database/MonitorDB.h>
#include <log/eProsimaLog.h>
#include <writer/McapRecorder.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>

#ifdef EPROSIMA_LINUX
#include <sys/time.h>
#endif // ifdef EPROSIMA_LINUX

#ifdef MCAP_SUPPORT

/*
 * Encodings and metadata names are the ones *eProsima DDS Record & Replay* uses, taken from
 * ddsrecorder_participants (McapHandler.cpp and constants.hpp). They are the compatibility
 * contract with the tools that read its recordings, so they must match exactly.
 */
static const char* const SCHEMA_ENCODING = "omgidl";
static const char* const MESSAGE_ENCODING = "cdr";

static const char* const CHANNEL_QOS = "qos";
static const char* const CHANNEL_ROS2_TYPES = "ros2-types";
static const char* const CHANNEL_PARTITIONS = "partitions";

static const char* const METADATA_VERSION = "version";
static const char* const METADATA_VERSION_RELEASE = "release";
static const char* const METADATA_GUID = "messages_guid";
static const char* const METADATA_GUID_INDEX = "messages_guid_index";

/*
 * The recorder parses only the topic name, the type name, the TypeCode and the GUID out of the
 * discovery messages, so no QoS survives. Same four-key default the SQLite writer uses.
 */
static const char* const DEFAULT_QOS =
        "reliability: true\ndurability: false\nownership: false\nkeyed: false";

static const char* const NOT_ROS2 = "false";

/*
 * The profile is deliberately empty: "ros2" would claim a well-known profile this traffic does
 * not follow. Readers fall back to the channel message encoding, which is "cdr".
 */
static const char* const MCAP_PROFILE = "";

/*
 * Set from the CMake project version. src/version.cpp holds only #defines and exports no symbol,
 * and its value is stale, so it is not used.
 */
#ifndef DDSRECORDER_VERSION_STRING
#define DDSRECORDER_VERSION_STRING "unknown"
#endif // ifndef DDSRECORDER_VERSION_STRING

#endif // ifdef MCAP_SUPPORT

using namespace eprosima;
using namespace std;

static const char* const CLASS_NAME = "McapRecorder";

bool McapRecorder::is_supported()
{
#ifdef MCAP_SUPPORT
    return true;
#else
    return false;
#endif // ifdef MCAP_SUPPORT
}

#ifdef MCAP_SUPPORT

namespace eprosima {

/// A DDS Topic seen in the discovery traffic, before its MCAP records exist.
struct McapTopic
{
    string type_name;
    string idl;
    mcap::ChannelId channel_id{0};
    bool materialized{false};
};

struct McapRecorder::Impl
{
    Impl(
            eProsimaLog& log)
        : log_(log)
        , options_(MCAP_PROFILE)
    {
    }

    /**
     * \brief Writes the Schema and Channel records of a topic.
     *
     * Deferred until the topic has a sample, so that every discovery message seen so far had the
     * chance to supply the IDL: an MCAP record cannot be modified once written.
     */
    bool materialize_topic(
            const string& topicName,
            McapTopic& topic);

    /// Returns the endpoint with this Guid, or nullptr.
    eEntity* find_endpoint(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId);

    eProsimaLog& log_;

    mcap::McapWriter writer_;
    mcap::McapWriterOptions options_;

    bool open_{false};
    bool closed_{false};

    /// Topics seen in discovery, keyed by topic name.
    map<string, McapTopic> topics_;

    /// Schema ids already written, keyed by type name.
    map<string, mcap::SchemaId> schemas_;

    /// Endpoints seen in discovery, used to attribute a sample to a topic.
    list<eEntity*> endpoints_;

    /// (writer Guid, RTPS sequence number) pairs already stored.
    set<pair<string, unsigned long long>> stored_;

    /**
     * MCAP has no field for the publishing DataWriter, so the GUID is recovered in two hops, as
     * DDS Record & Replay does it: the message sequence number gives an index, and the index
     * gives the GUID string. The indirection keeps the record small when many messages share a
     * writer.
     */
    mcap::KeyValueMap guid_by_sequence_;
    mcap::KeyValueMap guid_by_index_;
    map<string, string> index_by_guid_;

    /**
     * A single counter across the whole file, not per channel. That is what makes
     * guid_by_sequence_, which is keyed by the sequence number alone, unambiguous; a per-channel
     * counter would let two channels collide in it.
     */
    uint32_t sequence_{0};

    unsigned int message_count_{0};
    unsigned int duplicate_count_{0};
    bool unknown_endpoint_warned_{false};
};

} // namespace eprosima

/// Renders a timestamp as nanoseconds since the epoch, which is what MCAP stores.
static mcap::Timestamp to_nanosec(
        long long seconds,
        unsigned long long nanos)
{
    return (mcap::Timestamp)(((unsigned long long)seconds) * 1000000000ULL + nanos);
}

bool McapRecorder::Impl::materialize_topic(
        const string& topicName,
        McapTopic& topic)
{
    const char* const METHOD_NAME = "materialize_topic";

    if (topic.materialized)
    {
        return true;
    }

    auto schema_it = schemas_.find(topic.type_name);

    if (schemas_.end() == schema_it)
    {
        // Empty schema data means the type was never described, which is legal MCAP.
        mcap::Schema schema(topic.type_name, SCHEMA_ENCODING, topic.idl);
        writer_.addSchema(schema);
        schema_it = schemas_.insert(make_pair(topic.type_name, schema.id)).first;
    }

    mcap::KeyValueMap metadata;
    metadata[CHANNEL_QOS] = DEFAULT_QOS;
    metadata[CHANNEL_ROS2_TYPES] = NOT_ROS2;
    // No partition information survives the discovery parsing.
    metadata[CHANNEL_PARTITIONS] = "";

    mcap::Channel channel(topicName, MESSAGE_ENCODING, schema_it->second, metadata);
    writer_.addChannel(channel);

    topic.channel_id = channel.id;
    topic.materialized = true;

    logInfo(log_, "Created MCAP channel for topic %s with type %s", topicName.c_str(),
            topic.type_name.c_str());

    return true;
}

eEntity* McapRecorder::Impl::find_endpoint(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId)
{
    for (auto entity : endpoints_)
    {
        if (entity->equal(hostId, appId, instanceId, entityId))
        {
            return entity;
        }
    }

    return nullptr;
}

McapRecorder::McapRecorder(
        eProsimaLog& log,
        const std::string& filename)
{
    const char* const METHOD_NAME = "McapRecorder";

    impl_ = new Impl(log);

    const mcap::Status status = impl_->writer_.open(filename, impl_->options_);

    if (!status.ok())
    {
        logError(impl_->log_, "Cannot create the MCAP file %s: %s", filename.c_str(),
                status.message.c_str());
        return;
    }

    impl_->open_ = true;
}

McapRecorder::~McapRecorder()
{
    if (nullptr != impl_)
    {
        close();

        for (auto entity : impl_->endpoints_)
        {
            delete entity;
        }

        delete impl_;
    }
}

bool McapRecorder::is_open()
{
    return (nullptr != impl_) && impl_->open_;
}

bool McapRecorder::add_topic(
        std::string& topicName,
        std::string& typeName,
        const std::string& idl)
{
    const char* const METHOD_NAME = "add_topic";

    if (!is_open())
    {
        logError(impl_->log_, "The MCAP file is not open");
        return false;
    }

    if (topicName.empty() || typeName.empty())
    {
        logInfo(impl_->log_, "Ignoring a discovered topic with no topic name or no type name");
        return false;
    }

    McapTopic& topic = impl_->topics_[topicName];

    if (topic.materialized)
    {
        // The Schema and Channel records are already written and cannot be changed.
        return true;
    }

    topic.type_name = typeName;

    // The first description wins, so an announcement without a TypeCode never erases one.
    if (topic.idl.empty())
    {
        topic.idl = idl;
    }

    return true;
}

bool McapRecorder::add_endpoint(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId,
        std::string& topicName,
        std::string& typeName)
{
    const char* const METHOD_NAME = "add_endpoint";

    if (!is_open())
    {
        logError(impl_->log_, "The MCAP file is not open");
        return false;
    }

    if (nullptr == impl_->find_endpoint(hostId, appId, instanceId, entityId))
    {
        impl_->endpoints_.push_back(new eEntity(hostId, appId, instanceId, entityId,
                topicName, typeName, false));
    }

    return true;
}

bool McapRecorder::add_message(
        const struct timeval& wts,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t& sourceTmp,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "add_message";

    if (!is_open())
    {
        logError(impl_->log_, "The MCAP file is not open");
        return false;
    }

    if (nullptr == serializedData || 0 == serializedDataLen)
    {
        logError(impl_->log_, "Bad parameters");
        return false;
    }

    /*
     * Either entity id identifies the topic; the writer is preferred because the sample is
     * attributed to it.
     */
    eEntity* endpoint = impl_->find_endpoint(hostId, appId, instanceId, writerId);

    if (nullptr == endpoint)
    {
        endpoint = impl_->find_endpoint(hostId, appId, instanceId, readerId);
    }

    if (nullptr == endpoint)
    {
        if (!impl_->unknown_endpoint_warned_)
        {
            logInfo(impl_->log_, "Discarding samples whose endpoint was not announced in the "
                    "capture, starting with (%u, %u, %u, %u): their topic is unknown",
                    hostId, appId, instanceId, writerId);
            impl_->unknown_endpoint_warned_ = true;
        }

        return false;
    }

    const string writer_guid = MonitorDB::format_guid(hostId, appId, instanceId, writerId);

    /*
     * Unlike the SQLite schema, where the primary key removes them for free, duplicates have to
     * be recognized here: the same sample is captured more than once when it is seen both as
     * multicast and as unicast, or when the writer repairs it.
     */
    if (!impl_->stored_.insert(make_pair(writer_guid, writerSeqNum)).second)
    {
        ++impl_->duplicate_count_;
        return true;
    }

    auto topic_it = impl_->topics_.find(endpoint->getTopicName());

    if (impl_->topics_.end() == topic_it)
    {
        // The endpoint is known but its topic is not, which add_endpoint should have prevented.
        logError(impl_->log_, "No MCAP channel for topic %s",
                endpoint->getTopicName().c_str());
        return false;
    }

    if (!impl_->materialize_topic(topic_it->first, topic_it->second))
    {
        return false;
    }

    mcap::Message message;
    message.channelId = topic_it->second.channel_id;
    message.sequence = impl_->sequence_;
    message.logTime = to_nanosec(wts.tv_sec, (unsigned long long)wts.tv_usec * 1000ULL);
    message.publishTime = to_nanosec(sourceTmp.seconds,
                    MonitorDB::fraction_to_nanosec(sourceTmp.nanoseconds));
    message.dataSize = serializedDataLen;
    message.data = reinterpret_cast<const std::byte*>(serializedData);

    const mcap::Status status = impl_->writer_.write(message);

    if (!status.ok())
    {
        logError(impl_->log_, "Cannot write the MCAP message: %s", status.message.c_str());
        return false;
    }

    // Record which writer produced this sequence number, through the shared index.
    auto index_it = impl_->index_by_guid_.find(writer_guid);

    if (impl_->index_by_guid_.end() == index_it)
    {
        const string index = to_string(impl_->index_by_guid_.size());

        impl_->guid_by_index_[index] = writer_guid;
        index_it = impl_->index_by_guid_.insert(make_pair(writer_guid, index)).first;
    }

    impl_->guid_by_sequence_[to_string(impl_->sequence_)] = index_it->second;

    ++impl_->sequence_;
    ++impl_->message_count_;

    return true;
}

void McapRecorder::close()
{
    const char* const METHOD_NAME = "close";

    if (nullptr == impl_ || !impl_->open_ || impl_->closed_)
    {
        return;
    }

    impl_->closed_ = true;

    /*
     * Give a channel to the topics that never carried a sample, so the file lists everything the
     * discovery traffic announced, as the SQLite Topics table would.
     */
    for (auto& topic : impl_->topics_)
    {
        impl_->materialize_topic(topic.first, topic.second);
    }

    mcap::Metadata version;
    version.name = METADATA_VERSION;
    version.metadata[METADATA_VERSION_RELEASE] = DDSRECORDER_VERSION_STRING;

    if (!impl_->writer_.write(version).ok())
    {
        logError(impl_->log_, "Cannot write the MCAP version metadata");
    }

    mcap::Metadata guids;
    guids.name = METADATA_GUID;
    guids.metadata = impl_->guid_by_sequence_;

    if (!impl_->writer_.write(guids).ok())
    {
        logError(impl_->log_, "Cannot write the MCAP %s metadata", METADATA_GUID);
    }

    mcap::Metadata index;
    index.name = METADATA_GUID_INDEX;
    index.metadata = impl_->guid_by_index_;

    if (!impl_->writer_.write(index).ok())
    {
        logError(impl_->log_, "Cannot write the MCAP %s metadata", METADATA_GUID_INDEX);
    }

    impl_->writer_.close();
}

unsigned int McapRecorder::getMessageCount()
{
    return (nullptr != impl_) ? impl_->message_count_ : 0;
}

unsigned int McapRecorder::getDuplicateCount()
{
    return (nullptr != impl_) ? impl_->duplicate_count_ : 0;
}

#else // ifdef MCAP_SUPPORT

/*
 * The disabled build. The class keeps its interface so that DDSRecorder and main() need no
 * conditional compilation; every operation simply refuses.
 */

McapRecorder::McapRecorder(
        eProsimaLog& log,
        const std::string& filename)
{
    const char* const METHOD_NAME = "McapRecorder";

    logError(log, "Cannot write %s: this build has no MCAP support. Rebuild with "
            "-DMCAP_SUPPORT=ON", filename.c_str());
}

McapRecorder::~McapRecorder()
{
}

bool McapRecorder::is_open()
{
    return false;
}

bool McapRecorder::add_topic(
        std::string& topicName,
        std::string& typeName,
        const std::string& idl)
{
    static_cast<void>(topicName);
    static_cast<void>(typeName);
    static_cast<void>(idl);
    return false;
}

bool McapRecorder::add_endpoint(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId,
        std::string& topicName,
        std::string& typeName)
{
    static_cast<void>(hostId);
    static_cast<void>(appId);
    static_cast<void>(instanceId);
    static_cast<void>(entityId);
    static_cast<void>(topicName);
    static_cast<void>(typeName);
    return false;
}

bool McapRecorder::add_message(
        const struct timeval& wts,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t& sourceTmp,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    static_cast<void>(wts);
    static_cast<void>(hostId);
    static_cast<void>(appId);
    static_cast<void>(instanceId);
    static_cast<void>(readerId);
    static_cast<void>(writerId);
    static_cast<void>(writerSeqNum);
    static_cast<void>(sourceTmp);
    static_cast<void>(serializedData);
    static_cast<void>(serializedDataLen);
    return false;
}

void McapRecorder::close()
{
}

unsigned int McapRecorder::getMessageCount()
{
    return 0;
}

unsigned int McapRecorder::getDuplicateCount()
{
    return 0;
}

#endif // ifdef MCAP_SUPPORT
