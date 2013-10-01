#include "DDSRecorder.h"
#include "cpp/Cdr.h"
#include "cpp/exceptions/Exception.h"
#include "eProsima_cpp/eProsimaLog.h"
#include "database/TypeCodeDB.h"
#include "database/EntitiesDB.h"
#include "database/DynamicDataDB.h"
#include "cdr/TypeCode.h"

#ifdef EPROSIMA_LINUX
#include <sys/time.h>
#endif

#define ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER (0x000100c2)
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER (0x000003c7)
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER (0x000003c2)
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER (0x000004c7)
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER (0x000004c2)

#define RTPS_PID_END (0x0001)
#define RTPS_PID_TOPIC_NAME (0x0005)
#define RTPS_PID_TYPE_NAME (0x0007)
#define RTPS_PID_TYPECODE (0x8004)
#define RTPS_PID_GUID (0x005A)

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "DDSRecorder";

DDSRecorder::DDSRecorder(eProsimaLog &log, string &database, int tcMaxSize) : m_log(log), m_databaseH(NULL),
    m_typecodeDB(NULL), m_entitiesDB(NULL), m_tcMaxSize(tcMaxSize)
{
    const char* const METHOD_NAME = "DDSRecorder";

    if(sqlite3_open(database.c_str(), &m_databaseH) == SQLITE_OK)
    {
        m_typecodeDB = new TypeCodeDB(m_log, m_databaseH, tcMaxSize);

        if(m_typecodeDB != NULL)
        {
            m_entitiesDB = new EntitiesDB(m_log, m_databaseH);

            if(m_entitiesDB == NULL)
            {
                logError(m_log, "Cannot create object EntitiesDB");
            }
        }
        else
        {
            logError(m_log, "Cannot create object TypeCodeDB");
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
    if(m_typecodeDB != NULL)
        delete m_typecodeDB;
    if(m_entitiesDB != NULL)
        delete m_entitiesDB;
    if(m_databaseH != NULL)
        sqlite3_close(m_databaseH);
}

void DDSRecorder::processDataCallback(void *user, const unsigned int npacket, const struct timeval &wts,
        std::string &ip_src, std::string &ip_dst, unsigned int hostId,
        unsigned int appId, unsigned int instanceId, unsigned int readerId,
        unsigned int writerId, unsigned long long writerSequenceNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId, bool endianess,
        const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataCallback";
    DDSRecorder *rtpsdumper = (DDSRecorder*)user;

    if(user != NULL)
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

void DDSRecorder::processData(const unsigned int npacket, const struct timeval &wts, string &ip_src, string &ip_dst,
        unsigned int hostId, unsigned int appId,
        unsigned int instanceId, unsigned int readerId,
        unsigned int writerId, unsigned long long writerSeqNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId, bool endianess,
        const char *serializedData, unsigned int serializedDataLen)
{
    // Data(w)
    if(writerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER ||
            readerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER)
    {
        processDataW(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // Data(r)
    else if(writerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER ||
            readerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER)
    {
        processDataR(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // It's not a Data(p)
    else if(writerId != ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER)
    {
        processDataNormal(npacket, wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
}

void DDSRecorder::processDataW(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";

    if(serializedData != NULL)
    {
        PublicationBuiltinTopic pubtopic;
        deserializePublicationBuiltinTopic(endianess, (char*)serializedData, serializedDataLen, pubtopic);

        if(pubtopic.typeCode != NULL)
        {
            TypeCode *typeCode = TypeCode::deserializeTypeCode(pubtopic.typeCode, pubtopic.typeCodeLength);

            if(typeCode != NULL)
            {
                // Add typecode.
                if(m_typecodeDB == NULL ||
                    m_typecodeDB->addTypecode(pubtopic.topic_name, pubtopic.type_name,
                            typeCode) == false)
                {
                    delete typeCode;
                }

                // Add entity.
                if(m_entitiesDB != NULL)
                    m_entitiesDB->addEntity(npacket, wts, ip_src, ip_dst, hostId,
                            appId, instanceId, readerId, writerId, writerSeqNum,
                            sourceTmp, destHostId, destAppId, destInstanceId, pubtopic.guid.hostId,
                            pubtopic.guid.appId, pubtopic.guid.instanceId,
                            pubtopic.guid.objectId, 1, pubtopic.topic_name, pubtopic.type_name, true);
            }
            else
            {
                logError(m_log, "Cannot deserialize the typecode");
            }
        }
        else
        {
            logInfo(m_log, "the datawriter of topic %s doesn't send the typecode", pubtopic.topic_name.c_str());

            if(m_entitiesDB != NULL)
                m_entitiesDB->addEntity(npacket, wts, ip_src, ip_dst, hostId,
                        appId, instanceId, readerId, writerId, writerSeqNum,
                        sourceTmp, destHostId, destAppId, destInstanceId, pubtopic.guid.hostId,
                        pubtopic.guid.appId, pubtopic.guid.instanceId,
                        pubtopic.guid.objectId, 1, pubtopic.topic_name, pubtopic.type_name, false);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void DDSRecorder::processDataR(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataR";

    if(serializedData != NULL)
    {
        SubscriptionBuiltinTopic subtopic;
        deserializeSubscriptionBuiltinTopic(endianess, (char*)serializedData, serializedDataLen, subtopic);

        if(subtopic.typeCode != NULL)
        {
            TypeCode *typeCode = TypeCode::deserializeTypeCode(subtopic.typeCode, subtopic.typeCodeLength);

            if(typeCode != NULL)
            {
                // Add typecode.
                if(m_typecodeDB == NULL ||
                    m_typecodeDB->addTypecode(subtopic.topic_name, subtopic.type_name,
                            typeCode) == false)
                {
                    delete typeCode;
                }

                // Add entity.
                if(m_entitiesDB != NULL)
                    m_entitiesDB->addEntity(npacket, wts, ip_src, ip_dst, hostId,
                            appId, instanceId, readerId, writerId, writerSeqNum,
                            sourceTmp, destHostId, destAppId, destInstanceId, subtopic.guid.hostId,
                            subtopic.guid.appId, subtopic.guid.instanceId,
                            subtopic.guid.objectId, 0, subtopic.topic_name, subtopic.type_name, true);
            }
            else
            {
                logError(m_log, "Cannot deserialize the typecode");
            }
        }
        else
        {
            logInfo(m_log, "the datareader of topic %s doesn't send the typecode", subtopic.topic_name.c_str());

            if(m_entitiesDB != NULL)
                m_entitiesDB->addEntity(npacket, wts, ip_src, ip_dst, hostId,
                        appId, instanceId, readerId, writerId, writerSeqNum,
                        sourceTmp, destHostId, destAppId, destInstanceId, subtopic.guid.hostId,
                        subtopic.guid.appId, subtopic.guid.instanceId,
                        subtopic.guid.objectId, 0, subtopic.topic_name, subtopic.type_name, false);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void DDSRecorder::processDataNormal(const unsigned int npacket, const struct timeval &wts, string &ip_src, string &ip_dst,
        unsigned int hostId, unsigned int appId, unsigned int instanceId,
        unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId, bool endianess,
        const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataNormal";
    eEntity *entity = NULL;
    eTypeCode *typecode = NULL;
    DynamicDataDB *dynamicDB = NULL;
    bool error = false;

    // Check the writer or reader has associated a typecode.
    if((entity = m_entitiesDB->findEntity(hostId, appId,
                    instanceId, writerId)) != NULL ||
            (entity = m_entitiesDB->findEntity(hostId, appId,
                                               instanceId, readerId)) != NULL)
    {
        if((typecode = m_typecodeDB->findTypecode(entity->getTopicName(),
                        entity->getTypeName(), error)) != NULL && !error)
        {
            Cdr::Endianness _endianess = endianess ? Cdr::LITTLE_ENDIANNESS : Cdr::BIG_ENDIANNESS;
            FastBuffer buffer((char*)serializedData, serializedDataLen);
            Cdr cdr(buffer, _endianess, Cdr::DDS_CDR);
            
            cdr.read_encapsulation();

            if(cdr.getDDSCdrPlFlag() == Cdr::DDS_CDR_WITHOUT_PL)
            {
				// It is necessary reset the alignment in the CDR buffer.
				cdr.resetAlignment();
                dynamicDB = typecode->getDynamicDataDB();
                        
                if(dynamicDB != NULL)
                {
                    if(!dynamicDB->storeDynamicData(npacket, wts, ip_src, ip_dst, hostId,
                                appId, instanceId, readerId, writerId, writerSeqNum,
                                sourceTmp, destHostId, destAppId, destInstanceId,
                                typecode->getCdrTypecode(), cdr))
                    {
                        logError(m_log, "Cannot stores the dynamic data in database");
                    }
                }
            }
        }
        else
        {
            logError(m_log, "Cannot find the typecode from topic %s", entity->getTopicName().c_str());
        }
    }
    else
    {
        logError(m_log, "Cannot find entity in database: (%u, %u, %u, %u) or " \
                "(%u, %u, %u, %u)", hostId, appId, instanceId, writerId,
                hostId, appId, instanceId, readerId);
    }

}


bool DDSRecorder::deserializePublicationBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, DDSRecorder::PublicationBuiltinTopic &pubtopic)
{
    const char* const METHOD_NAME = "deserializePublicationBuiltinTopic";
    bool returnedValue = true;

    if(serializedData != NULL)
    {
        Cdr::Endianness _endianess = endianess ? Cdr::LITTLE_ENDIANNESS : Cdr::BIG_ENDIANNESS;
        FastBuffer buffer((char*)serializedData, serializedDataLength);
        Cdr cdr(buffer, _endianess, Cdr::DDS_CDR);

        cdr.read_encapsulation();

        if(cdr.getDDSCdrPlFlag() == Cdr::DDS_CDR_WITH_PL)
        {
            uint16_t parameterId, parameterLength;

            try
            {
                cdr >> parameterId;
                cdr >> parameterLength;

                while(parameterId != RTPS_PID_END)
                {
                    Cdr::state currentState = cdr.getState();

                    switch(parameterId)
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
                        case RTPS_PID_TYPECODE:
                            pubtopic.typeCode = cdr.getCurrentPosition();
                            pubtopic.typeCodeLength = parameterLength;
                            break;
                        default:
                            break;
                    }

                    cdr.setState(currentState);
                    cdr.jump(parameterLength);

                    cdr >> parameterId;
                    cdr >> parameterLength;
                }
            }
            catch(eProsima::Exception &ex)
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

bool DDSRecorder::deserializeSubscriptionBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, DDSRecorder::SubscriptionBuiltinTopic &subtopic)
{
    const char* const METHOD_NAME = "deserializeSubscriptionBuiltinTopic";
    bool returnedValue = true;

    if(serializedData != NULL)
    {
        Cdr::Endianness _endianess = endianess ? Cdr::LITTLE_ENDIANNESS : Cdr::BIG_ENDIANNESS;
        FastBuffer buffer((char*)serializedData, serializedDataLength);
        Cdr cdr(buffer, _endianess, Cdr::DDS_CDR);

        cdr.read_encapsulation();
        
        if(cdr.getDDSCdrPlFlag() == Cdr::DDS_CDR_WITH_PL)
        {
            uint16_t parameterId, parameterLength;

            try
            {
                cdr >> parameterId;
                cdr >> parameterLength;

                while(parameterId != RTPS_PID_END)
                {
                    Cdr::state currentState = cdr.getState();

                    switch(parameterId)
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
                        case RTPS_PID_TYPECODE:
                            subtopic.typeCode = cdr.getCurrentPosition();
                            subtopic.typeCodeLength = parameterLength;
                            break;
                        default:
                            break;
                    }

                    cdr.setState(currentState);
                    cdr.jump(parameterLength);

                    cdr >> parameterId;
                    cdr >> parameterLength;
                }
            }
            catch(eProsima::Exception &ex)
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
