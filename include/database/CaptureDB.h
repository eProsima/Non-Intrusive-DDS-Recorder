/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CAPTUREDB_H_
#define _CAPTUREDB_H_

#ifdef __cplusplus

#include <string>

#include <sqlite3.h>
#include "RTPSPacketAnalyzer.h"

namespace eprosima {
class eProsimaLog;

/**
 * \brief Records what the capture reveals that the *DDS Record & Replay* schema has no column for.
 *
 * That schema describes a recording as a DDS system would see it, so a sample is a
 * (writer_guid, sequence_number) with a topic and two timestamps, and nothing says which packet
 * carried it or between which addresses. A capture knows all of that, and it is most of the
 * reason to sniff rather than subscribe, so it is kept here rather than added to Messages: the
 * *DDS Record & Replay* tables stay byte for byte what the DDS Monitor expects.
 *
 * There is a second gain in keeping it apart. A sample seen twice, because it travelled both as
 * multicast and as unicast or because the writer repaired it, is one row of Messages but two
 * packets. Messages counts the second as a duplicate and drops it; here it is a row of its own,
 * so the repetition the capture witnessed is not lost.
 */
class CaptureDB
{
public:

    /**
     * \brief Constructor. Creates the three tables, dropping them first if already present.
     *
     * \param log Log object used to log errors.
     * \param databaseH Handler of an already opened database. Cannot be NULL.
     */
    CaptureDB(
            eProsimaLog& log,
            sqlite3 * databaseH);

    ~CaptureDB();

    /// Whether the tables were created. When false, the other methods do nothing.
    bool is_ready() const;

    /**
     * \brief Records an endpoint and the announcement that introduced it.
     *
     * Repeated announcements add a row to DiscoveryMessages, since each is a packet the capture
     * really saw, but leave the single Endpoints row alone.
     *
     * \param npacket Ordinal of the packet inside the capture file.
     * \param wts Timestamp the sniffer gave the packet.
     * \param ip_src Source IPv4 address of the packet.
     * \param ip_dst Destination IPv4 address of the packet.
     * \param sourceTmp Source timestamp carried by the RTPS INFO_TS submessage.
     * \param destHostId GuidPrefix of the destination participant, 0 when there was no INFO_DST.
     * \param destAppId GuidPrefix of the destination participant.
     * \param destInstanceId GuidPrefix of the destination participant.
     * \param hostId GuidPrefix of the participant that owns the announced endpoint.
     * \param appId GuidPrefix of the participant that owns the announced endpoint.
     * \param instanceId GuidPrefix of the participant that owns the announced endpoint.
     * \param entityId Entity id of the announced endpoint.
     * \param is_writer True when the announced endpoint is a DataWriter.
     * \param topicName Name of the DDS Topic the endpoint serves.
     * \param typeName Name of the DDS Topic data type.
     * \return True value is returned if the announcement was recorded.
     */
    bool add_discovery(
            unsigned int npacket,
            const struct timeval & wts,
            const std::string& ip_src,
            const std::string& ip_dst,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId,
            bool is_writer,
            const std::string& topicName,
            const std::string& typeName);

    /**
     * \brief Records the packet that carried a user sample.
     *
     * \param npacket Ordinal of the packet inside the capture file.
     * \param wts Timestamp the sniffer gave the packet.
     * \param ip_src Source IPv4 address of the packet.
     * \param ip_dst Destination IPv4 address of the packet.
     * \param destHostId GuidPrefix of the destination participant, 0 when there was no INFO_DST.
     * \param destAppId GuidPrefix of the destination participant.
     * \param destInstanceId GuidPrefix of the destination participant.
     * \param writer_guid GUID of the writer, as Messages.writer_guid spells it.
     * \param sequence_number Sequence number of the sample.
     * \return True value is returned if the packet was recorded.
     */
    bool add_message_capture(
            unsigned int npacket,
            const struct timeval & wts,
            const std::string& ip_src,
            const std::string& ip_dst,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            const std::string& writer_guid,
            unsigned long long sequence_number);

    /// Number of rows written into MessagesCapture.
    unsigned int get_capture_count() const;

private:

    /// Creates the tables of the schema. Returns true on success.
    bool create_schema();

    /// Runs a statement that returns no rows. Returns true on success.
    bool execute(
            const char * statement);

    eProsimaLog& log_;

    sqlite3 * database_{nullptr};

    sqlite3_stmt * add_endpoint_stmt_{nullptr};

    sqlite3_stmt * add_discovery_stmt_{nullptr};

    sqlite3_stmt * add_capture_stmt_{nullptr};

    unsigned int capture_count_{0};

    bool ready_{false};
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _CAPTUREDB_H_
