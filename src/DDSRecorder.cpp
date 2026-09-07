/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "DDSRecorder.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"
#include "log/eProsimaLog.h"
#include "database/MonitorDB.h"
#include "database/CaptureDB.h"
#include "database/TopicsDB.h"
#include "TypeStore.h"

#ifdef EPROSIMA_LINUX
#include <sys/time.h>
#endif // ifdef EPROSIMA_LINUX

#define ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER (0x000100c2)
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER (0x000003c7)
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER (0x000003c2)
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER (0x000004c7)
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER (0x000004c2)

#define RTPS_PID_END (0x0001)
#define RTPS_PID_TOPIC_NAME (0x0005)
#define RTPS_PID_TYPE_NAME (0x0007)
#define RTPS_PID_GUID (0x005A)
#define RTPS_PID_DURABILITY (0x001D)
#define RTPS_PID_RELIABILITY (0x001A)
#define RTPS_PID_OWNERSHIP (0x001F)

/*
 * The QoS kinds as they travel, from the RTPS specification. Fast DDS spells them the same way in
 * dds/core/policy/QosPolicies.hpp.
 */
#define RTPS_RELIABILITY_BEST_EFFORT (0x01)
#define RTPS_RELIABILITY_RELIABLE (0x02)
#define RTPS_DURABILITY_VOLATILE (0x00)
#define RTPS_DURABILITY_TRANSIENT_LOCAL (0x01)
#define RTPS_OWNERSHIP_SHARED (0x00)
#define RTPS_OWNERSHIP_EXCLUSIVE (0x01)

/*
 * The entityKind octet of an EntityId_t says whether the endpoint was created on a keyed topic,
 * which is the only place keyedness appears on the wire: no QoS parameter carries it, and it is a
 * property of the data type rather than of the endpoint.
 *
 * RTPS 2.5 clause 9.3.1.2 table 9.1 gives the kinds. The two most significant bits of the octet
 * say only whether the entity is user-defined ('00'), built-in ('11') or vendor-specific ('01'),
 * so a writer with key is 0x02 as a user entity and 0xc2 as a built-in one. The kind itself is the
 * low nibble, not the low six bits the clause mentions: Fast DDS ORs 0x60 into some
 * vendor-specific ids, making a keyed writer 0x62, and every kind in the table is distinct in the
 * nibble. Fast DDS masks 0x0F for the same reason in RTPSParticipantImpl.cpp.
 */
#define RTPS_ENTITY_KIND_MASK (0x0F)
#define RTPS_ENTITY_KIND_WRITER_WITH_KEY (0x02)
#define RTPS_ENTITY_KIND_WRITER_NO_KEY (0x03)
#define RTPS_ENTITY_KIND_READER_NO_KEY (0x04)
#define RTPS_ENTITY_KIND_READER_WITH_KEY (0x07)

using namespace eprosima::fastcdr;
using namespace eprosima;
using namespace std;

static const char* const CLASS_NAME = "DDSRecorder";

/// What the entityKind octet of an endpoint's EntityId_t says about the topic being keyed.
enum class Keyedness
{
    /// The kind is not one of the four endpoint kinds, so it says nothing.
    UNKNOWN,
    NO_KEY,
    WITH_KEY
};

/*
 * Reads the keyedness out of an entity id. The octet is the least significant byte of the four,
 * which is the order format_guid() prints them in.
 */
static Keyedness keyedness_of(
        uint32_t entityId)
{
    switch (entityId & RTPS_ENTITY_KIND_MASK)
    {
        case RTPS_ENTITY_KIND_WRITER_WITH_KEY:
        case RTPS_ENTITY_KIND_READER_WITH_KEY:
            return Keyedness::WITH_KEY;
        case RTPS_ENTITY_KIND_WRITER_NO_KEY:
        case RTPS_ENTITY_KIND_READER_NO_KEY:
            return Keyedness::NO_KEY;
        default:
            return Keyedness::UNKNOWN;
    }
}

DDSRecorder::DDSRecorder(
        eProsimaLog& log,
        string& database,
        bool queryable_mode,
        const TypeStore * type_store)
    : m_log(log)
    , m_databaseH(NULL)
    , type_store_(type_store)
{
    const char* const METHOD_NAME = "DDSRecorder";

    if (sqlite3_open(database.c_str(), &m_databaseH) == SQLITE_OK)
    {
        monitor_db_ = new MonitorDB(m_log, m_databaseH);

        if (monitor_db_ == NULL)
        {
            logError(m_log, "Cannot create object MonitorDB");
        }

        /*
         * The two schemas are no longer exclusive: '-queryable' keeps the *DDS Record & Replay*
         * tables and adds a table per DDS Topic beside them, so a recording made with it can
         * still be replayed.
         */
        if (queryable_mode)
        {
            topics_db_ = new TopicsDB(m_log, m_databaseH, type_store_);

            if (topics_db_ == NULL || !topics_db_->is_ready())
            {
                logError(m_log, "Cannot create object TopicsDB");
            }

            capture_db_ = new CaptureDB(m_log, m_databaseH);

            if (capture_db_ == NULL || !capture_db_->is_ready())
            {
                logError(m_log, "Cannot create object CaptureDB");
            }
        }
    }
    else
    {
        logError(m_log, "Cannot open the database file %s", database.c_str());
        sqlite3_close(m_databaseH);
        m_databaseH = NULL;
    }
}

DDSRecorder::~DDSRecorder()
{
    if (capture_db_ != NULL)
    {
        delete capture_db_;
    }
    if (topics_db_ != NULL)
    {
        delete topics_db_;
    }
    if (monitor_db_ != NULL)
    {
        delete monitor_db_;
    }
    if (m_databaseH != NULL)
    {
        sqlite3_close(m_databaseH);
    }
}

void DDSRecorder::processDataCallback(
        void * user,
        const unsigned int npacket,
        const struct timeval & wts,
        std::string& ip_src,
        std::string& ip_dst,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSequenceNum,
        struct DDS_Time_t & sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        bool endianess,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataCallback";
    DDSRecorder * rtpsdumper = (DDSRecorder*)user;

    if (user != NULL)
    {
        rtpsdumper->processData(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId,
                readerId, writerId, writerSequenceNum, sourceTmp,
                destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    else
    {
        printError("Bad parameters");
    }
}

void DDSRecorder::processData(
        const unsigned int npacket,
        const struct timeval & wts,
        string& ip_src,
        string& ip_dst,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t & sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        bool endianess,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    // Data(w)
    if (writerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER ||
            readerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER)
    {
        processDataW(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // Data(r)
    else if (writerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER ||
            readerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER)
    {
        processDataR(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // It's not a Data(p)
    else if (writerId != ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER)
    {
        processDataNormal(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
}

void DDSRecorder::processDataW(
        const unsigned int npacket,
        const struct timeval & wts,
        std::string& ip_src,
        std::string& ip_dst,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t & sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        bool endianess,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";

    if (serializedData != NULL)
    {
        PublicationBuiltinTopic pubtopic;
        deserializePublicationBuiltinTopic(endianess, (char*)serializedData, serializedDataLen, pubtopic);

        if (nullptr != monitor_db_)
        {
            /*
             * The schema stores the samples as CDR, so the data type is needed only to describe
             * the type for the user. Its one source is the file given with '-idl'; when that file
             * did not declare it, the type is recorded without a description.
             */
            MonitorDB::TopicQos qos;
            qos.reliable = pubtopic.reliable;
            qos.transient_local = pubtopic.transient_local;
            qos.exclusive_ownership = pubtopic.exclusive_ownership;

            /*
             * The endpoint's own entity id states whether its topic is keyed, and that is what the
             * system really did, so it is preferred. Only when the kind is none of the four
             * endpoint kinds does the data type read from '-idl' have to answer instead, and
             * without that file the topic is recorded as unkeyed.
             */
            Keyedness keyedness = keyedness_of(pubtopic.guid.objectId);

            qos.keyed = (Keyedness::UNKNOWN != keyedness)
                    ? (Keyedness::WITH_KEY == keyedness)
                    : ((type_store_ != nullptr) && type_store_->is_keyed(pubtopic.type_name));

            monitor_db_->add_topic(pubtopic.topic_name, pubtopic.type_name,
                    (type_store_ != nullptr) ? type_store_->idl_for(pubtopic.type_name) : string(),
                    qos, true);
            monitor_db_->add_endpoint(pubtopic.guid.hostId, pubtopic.guid.appId,
                    pubtopic.guid.instanceId, pubtopic.guid.objectId,
                    pubtopic.topic_name, pubtopic.type_name);
        }

        if (topics_db_ != NULL)
        {
            topics_db_->add_topic(pubtopic.topic_name, pubtopic.type_name);
        }

        if (capture_db_ != NULL)
        {
            capture_db_->add_discovery(npacket, wts, ip_src, ip_dst, sourceTmp,
                    destHostId, destAppId, destInstanceId,
                    pubtopic.guid.hostId, pubtopic.guid.appId, pubtopic.guid.instanceId,
                    pubtopic.guid.objectId, true, pubtopic.topic_name, pubtopic.type_name);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void DDSRecorder::processDataR(
        const unsigned int npacket,
        const struct timeval & wts,
        std::string& ip_src,
        std::string& ip_dst,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t & sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        bool endianess,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataR";

    if (serializedData != NULL)
    {
        SubscriptionBuiltinTopic subtopic;
        deserializeSubscriptionBuiltinTopic(endianess, (char*)serializedData, serializedDataLen, subtopic);

        if (monitor_db_ != NULL)
        {
            /*
             * The schema stores the samples as CDR, so the data type is needed only to describe
             * the type for the user. Its one source is the file given with '-idl'; when that file
             * did not declare it, the type is recorded without a description.
             */
            MonitorDB::TopicQos qos;
            qos.reliable = subtopic.reliable;
            qos.transient_local = subtopic.transient_local;
            qos.exclusive_ownership = subtopic.exclusive_ownership;

            /*
             * The endpoint's own entity id states whether its topic is keyed, and that is what the
             * system really did, so it is preferred. Only when the kind is none of the four
             * endpoint kinds does the data type read from '-idl' have to answer instead, and
             * without that file the topic is recorded as unkeyed.
             */
            Keyedness keyedness = keyedness_of(subtopic.guid.objectId);

            qos.keyed = (Keyedness::UNKNOWN != keyedness)
                    ? (Keyedness::WITH_KEY == keyedness)
                    : ((type_store_ != nullptr) && type_store_->is_keyed(subtopic.type_name));

            monitor_db_->add_topic(subtopic.topic_name, subtopic.type_name,
                    (type_store_ != nullptr) ? type_store_->idl_for(subtopic.type_name) : string(),
                    qos, false);
            monitor_db_->add_endpoint(subtopic.guid.hostId, subtopic.guid.appId,
                    subtopic.guid.instanceId, subtopic.guid.objectId,
                    subtopic.topic_name, subtopic.type_name);
        }

        if (topics_db_ != NULL)
        {
            topics_db_->add_topic(subtopic.topic_name, subtopic.type_name);
        }

        if (capture_db_ != NULL)
        {
            capture_db_->add_discovery(npacket, wts, ip_src, ip_dst, sourceTmp,
                    destHostId, destAppId, destInstanceId,
                    subtopic.guid.hostId, subtopic.guid.appId, subtopic.guid.instanceId,
                    subtopic.guid.objectId, false, subtopic.topic_name, subtopic.type_name);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void DDSRecorder::processDataNormal(
        const unsigned int npacket,
        const struct timeval & wts,
        string& ip_src,
        string& ip_dst,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t & sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        bool endianess,
        const char * serializedData,
        unsigned int serializedDataLen)
{
    MonitorDB::StoredMessage stored;

    monitor_db_->add_message(wts, hostId, appId, instanceId, readerId, writerId,
            writerSeqNum, sourceTmp, serializedData, serializedDataLen, &stored);

    /*
     * Only a sample that Messages actually took gets a data row. A duplicate, seen twice because
     * it travelled both as multicast and as unicast, would collide on the same key here too.
     */
    if (topics_db_ != NULL && stored.stored)
    {
        topics_db_->store(stored.topic_name, stored.type_name, stored.writer_guid,
                stored.sequence_number, serializedData, serializedDataLen);
    }

    /*
     * Every packet that carried an attributable sample gets a row, duplicates included: unlike
     * Messages, this is a record of what the capture saw rather than of what was published.
     */
    if (capture_db_ != NULL && stored.resolved)
    {
        capture_db_->add_message_capture(npacket, wts, ip_src, ip_dst,
                destHostId, destAppId, destInstanceId, stored.writer_guid,
                stored.sequence_number);
    }
}

bool DDSRecorder::deserializePublicationBuiltinTopic(
        bool endianess,
        char* serializedData,
        unsigned int serializedDataLength,
        DDSRecorder::PublicationBuiltinTopic& pubtopic)
{
    const char* const METHOD_NAME = "deserializePublicationBuiltinTopic";
    bool returnedValue = true;

    if (serializedData != NULL)
    {
        Cdr::Endianness _endianess = endianess ? Cdr::LITTLE_ENDIANNESS : Cdr::BIG_ENDIANNESS;
        FastBuffer buffer((char*)serializedData, serializedDataLength);
        Cdr cdr(buffer, _endianess, CdrVersion::XCDRv1);

        cdr.read_encapsulation();

        if (cdr.get_encoding_flag() == EncodingAlgorithmFlag::PL_CDR)
        {
            uint16_t parameterId, parameterLength;

            try
            {
                cdr >> parameterId;
                cdr >> parameterLength;

                while (parameterId != RTPS_PID_END)
                {
                    Cdr::state currentState = cdr.get_state();

                    switch (parameterId)
                    {
                        case RTPS_PID_GUID:
                            cdr.deserialize(pubtopic.guid.hostId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(pubtopic.guid.appId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(pubtopic.guid.instanceId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(pubtopic.guid.objectId, Cdr::BIG_ENDIANNESS);
                            break;
                        case RTPS_PID_TOPIC_NAME:
                            cdr >> pubtopic.topic_name;
                            break;
                        case RTPS_PID_TYPE_NAME:
                            cdr >> pubtopic.type_name;
                            break;
                        case RTPS_PID_RELIABILITY:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            pubtopic.reliable = (RTPS_RELIABILITY_RELIABLE == kind);
                            break;
                        }
                        case RTPS_PID_DURABILITY:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            /*
                             * The column is a bool that the replayer reads back as either VOLATILE
                             * or TRANSIENT_LOCAL, so TRANSIENT and PERSISTENT cannot be told apart
                             * from TRANSIENT_LOCAL. They are all recorded as durable, which keeps
                             * late joiner delivery on replay; VOLATILE would lose it.
                             */
                            pubtopic.transient_local = (kind >= RTPS_DURABILITY_TRANSIENT_LOCAL);
                            break;
                        }
                        case RTPS_PID_OWNERSHIP:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            pubtopic.exclusive_ownership = (RTPS_OWNERSHIP_EXCLUSIVE == kind);
                            break;
                        }
                        default:
                            break;
                    }

                    cdr.set_state(currentState);
                    cdr.jump(parameterLength);

                    cdr >> parameterId;
                    cdr >> parameterLength;
                }
            }
            catch (exception::Exception& ex)
            {
                logError(m_log, "Exception: ", ex.what());
                returnedValue = false;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DDSRecorder::deserializeSubscriptionBuiltinTopic(
        bool endianess,
        char* serializedData,
        unsigned int serializedDataLength,
        DDSRecorder::SubscriptionBuiltinTopic& subtopic)
{
    const char* const METHOD_NAME = "deserializeSubscriptionBuiltinTopic";
    bool returnedValue = true;

    if (serializedData != NULL)
    {
        Cdr::Endianness _endianess = endianess ? Cdr::LITTLE_ENDIANNESS : Cdr::BIG_ENDIANNESS;
        FastBuffer buffer((char*)serializedData, serializedDataLength);
        Cdr cdr(buffer, _endianess, CdrVersion::XCDRv1);

        cdr.read_encapsulation();

        if (cdr.get_encoding_flag() == EncodingAlgorithmFlag::PL_CDR)
        {
            uint16_t parameterId, parameterLength;

            try
            {
                cdr >> parameterId;
                cdr >> parameterLength;

                while (parameterId != RTPS_PID_END)
                {
                    Cdr::state currentState = cdr.get_state();

                    switch (parameterId)
                    {
                        case RTPS_PID_GUID:
                            cdr.deserialize(subtopic.guid.hostId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(subtopic.guid.appId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(subtopic.guid.instanceId, Cdr::BIG_ENDIANNESS);
                            cdr.deserialize(subtopic.guid.objectId, Cdr::BIG_ENDIANNESS);
                            break;
                        case RTPS_PID_TOPIC_NAME:
                            cdr >> subtopic.topic_name;
                            break;
                        case RTPS_PID_TYPE_NAME:
                            cdr >> subtopic.type_name;
                            break;
                        case RTPS_PID_RELIABILITY:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            subtopic.reliable = (RTPS_RELIABILITY_RELIABLE == kind);
                            break;
                        }
                        case RTPS_PID_DURABILITY:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            /*
                             * The column is a bool that the replayer reads back as either VOLATILE
                             * or TRANSIENT_LOCAL, so TRANSIENT and PERSISTENT cannot be told apart
                             * from TRANSIENT_LOCAL. They are all recorded as durable, which keeps
                             * late joiner delivery on replay; VOLATILE would lose it.
                             */
                            subtopic.transient_local = (kind >= RTPS_DURABILITY_TRANSIENT_LOCAL);
                            break;
                        }
                        case RTPS_PID_OWNERSHIP:
                        {
                            uint32_t kind = 0;
                            cdr >> kind;
                            subtopic.exclusive_ownership = (RTPS_OWNERSHIP_EXCLUSIVE == kind);
                            break;
                        }
                        default:
                            break;
                    }

                    cdr.set_state(currentState);
                    cdr.jump(parameterLength);

                    cdr >> parameterId;
                    cdr >> parameterLength;
                }
            }
            catch (exception::Exception& ex)
            {
                logError(m_log, "Exception: ", ex.what());
                returnedValue = false;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}
