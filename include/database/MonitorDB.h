/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _MONITORDB_H_
#define _MONITORDB_H_

#ifdef __cplusplus

#include <string>
#include <list>

#include <sqlite3.h>
#include "RTPSPacketAnalyzer.h"
#include "database/Endpoint.h"

namespace eprosima {
class eProsimaLog;

/**
 * \brief Writes the recorded traffic using the *DDS Record & Replay* schema.
 *
 * This is the alternative to the default schema, selected with the '-monitor' command line
 * argument. Instead of one table per DDS Topic with one column per data type member, it
 * writes the fixed Types/Topics/Messages layout that *DDS Record & Replay* produces and the
 * *DDS Monitor* reads.
 *
 * The sample is stored as the untouched CDR payload, so this writer never needs the data
 * type of a topic. That is what allows a topic whose data type is not in the '-idl' file, or
 * which has no '-idl' file at all, to be recorded anyway.
 */
class MonitorDB
{
public:

    /**
     * \brief Constructor.
     *
     * Creates the six tables of the schema, dropping them first if the database file
     * already contains them, and seeds the single empty partition.
     *
     * \param log Log object used to log errors.
     * \param databaseH Handler of an already opened database. Cannot be NULL.
     */
    MonitorDB(
            eProsimaLog& log,
            sqlite3 * databaseH);

    ~MonitorDB();

    /**
     * \brief This function adds a DDS Topic and its data type.
     *
     * Repeated announcements of the same topic are ignored, so this can be called for
     * every discovery message.
     *
     * \param topicName Name of the DDS Topic.
     * \param typeName Name of the DDS Topic data type.
     * \param idl The data type rendered as IDL, or an empty string when the data type is
     * not known. Stored in the 'idl' column, rendered from the file given with '-idl'.
     * It is there for the user to read; nothing in this tool parses it back.
     * \return True value is returned if the topic was added or was already present.
     */
    bool add_topic(
            std::string& topicName,
            std::string& typeName,
            const std::string& idl);

    /**
     * \brief This function registers an endpoint so its samples can be attributed.
     *
     * A sample only carries the GuidPrefix of its participant and the entity id of its
     * writer, so the topic and the type name have to be recovered from the discovery
     * traffic.
     *
     * \param hostId GuidPrefix of the participant that owns the endpoint.
     * \param appId GuidPrefix of the participant that owns the endpoint.
     * \param instanceId GuidPrefix of the participant that owns the endpoint.
     * \param entityId Entity id of the endpoint inside its participant.
     * \param topicName Name of the DDS Topic the endpoint serves.
     * \param typeName Name of the DDS Topic data type.
     * \return True value is returned if the endpoint was registered.
     */
    bool add_endpoint(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId,
            std::string& topicName,
            std::string& typeName);

    /**
     * \brief What add_message() resolved about a sample, for a caller that has to write it
     * somewhere else too.
     *
     * The topic and the type are recovered from the discovery traffic and the writer GUID is
     * rendered here, so a caller writing the '-queryable' data tables would otherwise have to
     * repeat both.
     */
    typedef struct StoredMessage
    {
        std::string writer_guid;
        unsigned long long sequence_number = 0;
        std::string topic_name;
        std::string type_name;
        /**
         * False when the sample was a duplicate and Messages already held it. A caller keyed on
         * (writer_guid, sequence_number) must not write it a second time.
         */
        bool stored = false;
        /**
         * False when the sample could not be attributed to any announced endpoint, in which case
         * none of the fields above mean anything and Messages holds no row for it either.
         */
        bool resolved = false;
    } StoredMessage;

    /**
     * \brief This function stores a user sample as a row of the Messages table.
     *
     * The payload is stored verbatim, encapsulation header included, so no data type is
     * needed. A sample whose endpoint was never announced cannot be attributed to a
     * topic and is discarded.
     *
     * Because (writer_guid, sequence_number) is the primary key of Messages, a sample
     * that appears more than once in the capture, for instance because it was seen both
     * as multicast and as unicast, is stored once and counted as a duplicate.
     *
     * \return True value is returned if the sample was stored or was a duplicate. False
     * is returned on error, and when the endpoint is unknown.
     */
    bool add_message(
            const struct timeval & wts,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t & sourceTmp,
            const char * serializedData,
            unsigned int serializedDataLen,
            StoredMessage * stored = nullptr);

    /// Number of rows written into the Messages table.
    unsigned int getMessageCount();

    /// Number of samples discarded because they were already stored.
    unsigned int getDuplicateCount();

    /**
     * \brief Renders a GUID the way Fast DDS writes it: '<prefix>|<entity>'.
     *
     * The prefix is twelve zero padded hexadecimal bytes; the entity id is four
     * hexadecimal bytes that are not zero padded, for example
     * 'c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3'.
     */
    static std::string format_guid(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId);

    /**
     * \brief Renders a GuidPrefix on its own, the twelve zero padded hexadecimal bytes without
     * the entity id that format_guid() appends.
     *
     * Returns an empty string for the all zero prefix, which is what a packet carrying no
     * INFO_DST submessage leaves behind and means "every participant" rather than a real one.
     */
    static std::string format_guid_prefix(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId);

    /**
     * \brief Renders a timestamp as 'YYYY-MM-DD HH:MM:SS.nnnnnnnnn' in UTC.
     *
     * The DDS Monitor applies its time window as a lexicographic comparison over this
     * text, so the fixed width and the zero padding are what keep range queries
     * chronologically correct.
     */
    static std::string format_timestamp(
            long long seconds,
            unsigned long long nanos);

    /**
     * \brief Converts an RTPS Time_t fraction into nanoseconds.
     *
     * The fraction is in units of 2^-32 seconds. Note that the value carried in
     * DDS_Time_t::nanoseconds is this raw fraction and not a count of nanoseconds.
     */
    static unsigned int fraction_to_nanosec(
            unsigned int fraction);

private:

    /// Creates the tables of the schema. Returns true on success.
    bool create_schema();

    /// Runs a statement that returns no rows. Returns true on success.
    bool execute(
            const char * statement);

    Endpoint* find_endpoint(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId);

    eProsimaLog& log_;

    bool ready_{false};

    /// Handler of the database.
    sqlite3 * database_{nullptr};

    sqlite3_stmt * add_type_stmt_{nullptr};

    /**
     * Fills in Types.idl for a type that was first announced before the '-idl' file was
     * consulted for it. Guarded on the column being empty, so the first description wins
     * and repeated announcements cost nothing.
     */
    sqlite3_stmt * updatte_type_stmt_{nullptr};

    sqlite3_stmt * add_topic_stmt_{nullptr};
    sqlite3_stmt * add_topic_parttition_stmt_{nullptr};
    sqlite3_stmt * add_message_stmt_{nullptr};
    sqlite3_stmt * add_message_partitition_stmt{nullptr};

    /// Endpoints seen in the discovery traffic, used to attribute samples to a topic.
    std::list<Endpoint*> m_endpoints;

    unsigned int message_count{0};

    unsigned int duplicate_count_{0};

    /// Whether the warning about samples with an unknown endpoint was already logged.
    bool unknown_endpoint_warned_{false};
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _MONITORDB_H_
