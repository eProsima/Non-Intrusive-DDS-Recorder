/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _MCAPRECORDER_H_
#define _MCAPRECORDER_H_

#ifdef __cplusplus

#include <string>

#include "RTPSPacketAnalyzer.h"
#include "database/TypeDescription.h"

namespace eprosima {
class eProsimaLog;

/**
 * \brief Writes the recorded traffic as an MCAP file.
 *
 * This is the output selected with the '-mcap' command line argument, and it replaces the
 * SQLite database entirely: no database file is created.
 *
 * The samples are stored as their untouched CDR payload, exactly as MonitorDB does, so this
 * writer never needs the data type of a topic either. What type information is available, from
 * the file given with '-idl', which is its only source, is written twice: as the IDL text of the
 * MCAP Schema record of the type, and as the XTypes description of every type in the
 * 'dynamic_types' attachment, which is where *DDS Record & Replay* keeps the types of an MCAP
 * recording and where its replayer looks for them.
 *
 * The layout follows what *eProsima DDS Record & Replay* writes, so that the result can be read
 * by the tools that consume its recordings. In particular MCAP has no field for the GUID of the
 * publishing DataWriter, so the GUID is recovered through two metadata records the way that
 * implementation does it; see the implementation for the details.
 *
 * No mcap header is included here on purpose. The library is header-only and sizeable, only this
 * class needs it, and its implementation has to be compiled in exactly one translation unit, so
 * every mcap type is kept inside McapRecorder.cpp.
 *
 * The MCAP output is optional at build time, through the MCAP_SUPPORT CMake option. When it is
 * not built, this class still exists with the same interface but does nothing: the constructor
 * reports why, is_open() returns false and the rest are no-ops. Ask is_supported() to find out,
 * which is what lets the callers stay free of conditional compilation.
 */
class McapRecorder
{
public:

    /**
     * \brief Constructor.
     *
     * Creates the file, truncating it if it already exists.
     *
     * \param log Log object used to log errors.
     * \param filename Name of the MCAP file to write.
     */
    McapRecorder(
            eProsimaLog& log,
            const std::string& filename);

    /**
     * \brief Destructor. Closes the file if close() was not called.
     */
    ~McapRecorder();

    /// Not copyable: it owns a file being written.
    McapRecorder(
            const McapRecorder&) = delete;
    McapRecorder& operator =(
            const McapRecorder&) = delete;

    /**
     * \brief Whether this build has the MCAP output compiled in.
     *
     * Decided by the MCAP_SUPPORT CMake option. When false, constructing a McapRecorder always
     * fails, so a caller should check this before offering '-mcap' at all.
     */
    static bool is_supported();

    /**
     * \brief This function returns whether the file was created successfully.
     */
    bool is_open();

    /**
     * \brief This function registers a DDS Topic and its data type.
     *
     * The MCAP Schema and Channel records are not written here: they are materialized when the
     * topic gets its first sample, so that a later discovery message still has the chance to
     * supply the IDL. MCAP records cannot be modified once written.
     *
     * Repeated announcements of the same topic are harmless.
     *
     * The XTypes description of the data type is kept for the 'dynamic_types' attachment, which
     * is written when the file is closed. A type described by no '-idl' file contributes nothing
     * to it, and one that is built from other types contributes those as well.
     *
     * \param topicName Name of the DDS Topic.
     * \param typeName Name of the DDS Topic data type.
     * \param type What is known about the data type, all of it read from the file given with
     * '-idl'. Every member is empty when that file did not declare it.
     * \return True value is returned if the topic was registered.
     */
    bool add_topic(
            std::string& topicName,
            std::string& typeName,
            const TypeDescription& type);

    /**
     * \brief This function registers an endpoint so its samples can be attributed.
     *
     * A sample only carries the GuidPrefix of its participant and the entity ids of its writer
     * and of the destination reader, so the topic and the type name have to be recovered from
     * the discovery traffic.
     *
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
     * \brief This function stores a user sample as an MCAP message.
     *
     * The payload is stored verbatim, encapsulation header included, so no data type is needed.
     * A sample whose endpoint was never announced cannot be attributed to a topic and is
     * discarded.
     *
     * A sample whose (writer Guid, RTPS sequence number) was already stored is a duplicate, for
     * instance because the packet was seen both as multicast and as unicast, and is counted
     * rather than written again.
     *
     * \return True value is returned if the sample was stored or was a duplicate. False is
     * returned on error, and when the endpoint is unknown.
     */
    bool add_message(
            const struct timeval& wts,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t& sourceTmp,
            const char * serializedData,
            unsigned int serializedDataLen);

    /**
     * \brief This function writes the attachment and the metadata records, and closes the file.
     *
     * Calling it more than once is harmless. The destructor calls it, so an interrupted run
     * still leaves a readable file.
     */
    void close();

    /// Number of messages written into the file.
    unsigned int getMessageCount();

    /// Number of samples discarded because they were already stored.
    unsigned int getDuplicateCount();

private:

    /// Holds everything that needs the mcap library.
    struct Impl;

    Impl * impl_{nullptr};
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _MCAPRECORDER_H_
