#include "RTPSdump.h"
#include "eProsima_cpp/eProsimaLog.h"
#include "database/TypeCodeDB.h"
#include "database/EntitiesDB.h"
#include "database/DynamicDataDB.h"
#include "cdr/TypeCode.h"

#include "disc/disc_builtin.h"
#include "cdr/cdr_stream.h"
#include "pres/pres_typePlugin.h"
#include "dds_c/dds_c_typecode.h"
#include "dds_c/dds_c_dynamicdata.h"
#include "CdrBuffer.h"
#include "Cdr.h"

#ifndef RTI_WIN32
#include <sys/time.h>
#endif

using namespace eProsima;

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

/* RTI types */
struct DISCBuiltinTopicPublicationDataPluginEndpointData
{
    struct PRESTypePluginDefaultEndpointData * defaultEndPluginData;
    struct DISCBuiltinTopicPublicationDataPool * pool;
};
struct DISCBuiltinTopicSubscriptionDataPluginEndpointData {
    struct PRESTypePluginDefaultEndpointData * defaultEndPluginData;
    struct DISCBuiltinTopicSubscriptionDataPool * pool;
};

extern "C" RTIBool DDS_DynamicDataTypePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    DDS_DynamicData *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample,
    void *endpoint_plugin_qos);

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "RTPSdump";

RTPSdump::RTPSdump(eProsimaLog &log, string &database, int tcMaxSize) : m_log(log), m_databaseH(NULL),
    m_typecodeDB(NULL), m_entitiesDB(NULL), m_tcMaxSize(tcMaxSize)
{
    const char* const METHOD_NAME = "RTPSdump";

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

RTPSdump::~RTPSdump()
{
    if(m_typecodeDB != NULL)
        delete m_typecodeDB;
    if(m_entitiesDB != NULL)
        delete m_entitiesDB;
    if(m_databaseH != NULL)
        sqlite3_close(m_databaseH);
}

void RTPSdump::processDataCallback(void *user, const struct timeval &wts,
        string &ip_src, string &ip_dst, unsigned int hostId,
        unsigned int appId, unsigned int instanceId, unsigned int readerId,
        unsigned int writerId, unsigned long long writerSequenceNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId, bool endianess,
        const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataCallback";
    RTPSdump *rtpsdumper = (RTPSdump*)user;

    if(user != NULL)
    {
        rtpsdumper->processData(wts, ip_src, ip_dst, hostId, appId, instanceId,
                readerId, writerId, writerSequenceNum, sourceTmp,
                destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    else
    {
        printError("Bad parameters");
    }
}

void RTPSdump::processData(const struct timeval &wts, string &ip_src, string &ip_dst,
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
        processDataW(wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // Data(r)
    else if(writerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER ||
            readerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER)
    {
        processDataR(wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
    // It's not a Data(p)
    else if(writerId != ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER)
    {
        processDataNormal(wts, ip_src, ip_dst, hostId, appId, instanceId, readerId, writerId,
                writerSeqNum, sourceTmp, destHostId, destAppId, destInstanceId, endianess,
                serializedData, serializedDataLen);
    }
}

void RTPSdump::processDataW(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";

    if(serializedData != NULL)
    {
#ifndef DDS_USE
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
                    m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
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
                m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                        appId, instanceId, readerId, writerId, writerSeqNum,
                        sourceTmp, destHostId, destAppId, destInstanceId, pubtopic.guid.hostId,
                        pubtopic.guid.appId, pubtopic.guid.instanceId,
                        pubtopic.guid.objectId, 1, pubtopic.topic_name, pubtopic.type_name, false);
        }
#else
        struct DISCBuiltinTopicPublicationData topic = DISC_BUILTIN_TOPIC_PUBLICATION_DATA_INITIALIZE;
        struct DISCBuiltinTopicPublicationDataPluginEndpointData * epd = NULL;
        struct DISCBuiltinTopicPublicationDataPool *pool = NULL;
        struct REDAFastBufferPoolProperty poolProperty = REDA_FAST_BUFFER_POOL_PROPERTY_DEFAULT;
        struct RTICdrTypeCode *typeCode = NULL;
        RTICdrStream stream;
        
        if(DISCBuiltinTopicPublicationDataPluginSupport_initializeData_ex(&topic, RTI_TRUE) == RTI_TRUE)
        {
            RTIOsapiHeap_allocateStructure(&epd, struct DISCBuiltinTopicPublicationDataPluginEndpointData);

            if(epd != NULL)
            {
                RTIOsapiHeap_allocateStructure(&pool, struct DISCBuiltinTopicPublicationDataPool);
                if(pool != NULL)
                {
                    epd->pool = pool;
                    pool->_propertyListMaximumLength = 0;
                    pool->_propertyStringMaximumLength = 0;
                    pool->_userDataMaximumLength = 0;
                    pool->_groupDataMaximumLength = 0;
                    pool->_topicDataMaximumLength = 0;
                    pool->_partitionMaximumNameCount = 0;
                    pool->_partitionMaximumCumulativeLength = 0;
                    pool->_propertyMaximumSerializedLength = 0;
                    pool->_typeCodeMaximumSerializedLength = m_tcMaxSize;
                    pool->_locatorFilterSeqMaximumLength = 0;
                    pool->_locatorFilterExpMaximumLength = 0;

                    pool->_typeCodePool = REDAFastBufferPool_new(
                            (m_tcMaxSize * RTI_CDR_CHAR_SIZE),
                            RTI_CDR_LONG_ALIGN, &poolProperty);

                    if(pool->_typeCodePool != NULL)
                    {
                        RTICdrStream_init(&stream);
                        RTICdrStream_set(&stream, (char*)serializedData, serializedDataLen);

                        if(DISCBuiltinTopicPublicationDataPlugin_deserialize(epd, &topic, &stream,
                                    RTI_TRUE, RTI_TRUE, NULL) == RTI_TRUE)
                        {
                            if(topic.parameter->typeCode != NULL)
                            {
                                CDRBuffer buffer((char*)topic.parameter->typeCode, RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                CDR cdr(buffer, CDR::DDS_CDR);

                                //
                                RTIOsapiHeap_allocateBufferNotAligned((char**)&typeCode, RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));

                                if(typeCode != NULL)
                                {
                                    RTICdrTypeCode_initialize_stream(typeCode,
                                            RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                    if(RTICdrTypeCode_copy_stream(typeCode, topic.parameter->typeCode) == RTI_TRUE)
                                    {
                                        // Add typecode.
                                        if(m_typecodeDB == NULL ||
                                                m_typecodeDB->addTypecode(topic.parameter->topic, topic.parameter->typeName,
                                                    typeCode) == false)
                                        {
                                            RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                        }

                                        // Add entity.
                                        if(m_entitiesDB != NULL)
                                            m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                                                    appId, instanceId, readerId, writerId, writerSeqNum,
                                                    sourceTmp, destHostId, destAppId, destInstanceId, topic.guid.prefix.hostId,
                                                    topic.guid.prefix.appId, topic.guid.prefix.instanceId,
                                                    topic.guid.objectId, 1, topic.parameter->topic, topic.parameter->typeName, true);
                                    }
                                    else
                                    {
                                        RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                        logError(m_log, "Cannot copy typecode");
                                    }
                                }
                                else
                                {
                                    logError(m_log, "Cannot allocate DDS_TypeCode");
                                }

                                //
                            }
                            else
                            {
                                logInfo(m_log, "the datawriter of topic %s doesn't send the typecode", topic.parameter->topic);

                                if(m_entitiesDB != NULL)
                                    m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                                            appId, instanceId, readerId, writerId, writerSeqNum,
                                            sourceTmp, destHostId, destAppId, destInstanceId, topic.guid.prefix.hostId,
                                            topic.guid.prefix.appId, topic.guid.prefix.instanceId,
                                            topic.guid.objectId, 1, topic.parameter->topic, topic.parameter->typeName, false);
                            }
                        }
                        else
                        {
                            logError(m_log, "Cannot deserialized DataW");
                        }

                        REDAFastBufferPool_delete(pool->_typeCodePool);
                    }
                    else
                    {
                        logError(m_log, "Cannot allocate typecode pool");
                    }

                    RTIOsapiHeap_freeStructure(pool);
                }
                else
                {
                    logError(m_log, "Cannot allocate DISCBuiltinTopicPublicationDataPool");
                }

                RTIOsapiHeap_freeStructure(epd);
            }
            else
            {

                logError(m_log, "Cannot allocate DISCBuiltinTopicPublicationDataPluginEndpointData");
            }

            DISCBuiltinTopicPublicationDataPluginSupport_finalizeData_ex(&topic, RTI_TRUE);
        }
        else
        {
            logError(m_log, "Cannot initialized DISCBuiltinTopicPublicationData");
        }
#endif
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void RTPSdump::processDataR(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataR";

    if(serializedData != NULL)
    {
#ifndef DDS_USE
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
                    m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
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
                m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                        appId, instanceId, readerId, writerId, writerSeqNum,
                        sourceTmp, destHostId, destAppId, destInstanceId, subtopic.guid.hostId,
                        subtopic.guid.appId, subtopic.guid.instanceId,
                        subtopic.guid.objectId, 0, subtopic.topic_name, subtopic.type_name, false);
        }
#else
        struct DISCBuiltinTopicSubscriptionData topic = DISC_BUILTIN_TOPIC_SUBSCRIPTION_DATA_INITIALIZE;
        struct DISCBuiltinTopicSubscriptionDataPluginEndpointData * epd = NULL;
        struct DISCBuiltinTopicSubscriptionDataPool *pool = NULL;
        struct REDAFastBufferPoolProperty poolProperty = REDA_FAST_BUFFER_POOL_PROPERTY_DEFAULT;
        struct RTICdrTypeCode *typeCode = NULL;
        RTICdrStream stream;

        if(DISCBuiltinTopicSubscriptionDataPluginSupport_initializeData_ex(&topic, RTI_TRUE) == RTI_TRUE)
        {
            RTIOsapiHeap_allocateStructure(&epd, struct DISCBuiltinTopicSubscriptionDataPluginEndpointData);

            if(epd != NULL)
            {
                RTIOsapiHeap_allocateStructure(&pool, struct DISCBuiltinTopicSubscriptionDataPool);
                if(pool != NULL)
                {
                    epd->pool = pool;
                    pool->_propertyListMaximumLength = 0;
                    pool->_propertyStringMaximumLength = 0;
                    pool->_propertyMaximumSerializedLength = 0;
                    pool->_typeCodeMaximumSerializedLength = m_tcMaxSize;
                    pool->_userDataMaximumLength = 0;
                    pool->_groupDataMaximumLength = 0;
                    pool->_topicDataMaximumLength = 0;
                    pool->_partitionMaximumNameCount = 0;
                    pool->_partitionMaximumCumulativeLength = 0;
                    pool->_contentFilterPropertyMaxSerializedLength = 0;

                    pool->_typeCodePool = REDAFastBufferPool_new(
                            (m_tcMaxSize * RTI_CDR_CHAR_SIZE),
                            RTI_CDR_LONG_ALIGN, &poolProperty);

                    if(pool->_typeCodePool != NULL)
                    {
                        RTICdrStream_init(&stream);
                        RTICdrStream_set(&stream, (char*)serializedData, serializedDataLen);

                        if(DISCBuiltinTopicSubscriptionDataPlugin_deserialize(epd, &topic, &stream,
                                    RTI_TRUE, RTI_TRUE, NULL) == RTI_TRUE)
                        {
                            if(topic.parameter->typeCode != NULL)
                            {
                                RTIOsapiHeap_allocateBufferNotAligned((char**)&typeCode, RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));

                                if(typeCode != NULL)
                                {
                                    RTICdrTypeCode_initialize_stream(typeCode,
                                            RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                    if(RTICdrTypeCode_copy_stream(typeCode, topic.parameter->typeCode) == RTI_TRUE)
                                    {
                                        // Add typecode.
                                        if(m_typecodeDB == NULL ||
                                                m_typecodeDB->addTypecode(topic.parameter->topic, topic.parameter->typeName,
                                                    typeCode) == false)
                                        {
                                            RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                        }

                                        // Add entity.
                                        if(m_entitiesDB != NULL)
                                            m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                                                    appId, instanceId, readerId, writerId, writerSeqNum,
                                                    sourceTmp, destHostId, destAppId, destInstanceId, topic.guid.prefix.hostId,
                                                    topic.guid.prefix.appId, topic.guid.prefix.instanceId,
                                                    topic.guid.objectId, 0, topic.parameter->topic, topic.parameter->typeName, true);
                                    }
                                    else
                                    {
                                        RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                        logError(m_log, "Cannot copy typecode");
                                    }
                                }
                                else
                                {
                                    logError(m_log, "Cannot allocate DDS_TypeCode");
                                }
                            }
                            else
                            {
                                logInfo(m_log, "the datareader of topic %s doesn't send the typecode", topic.parameter->topic);

                                if(m_entitiesDB != NULL)
                                    m_entitiesDB->addEntity(wts, ip_src, ip_dst, hostId,
                                            appId, instanceId, readerId, writerId, writerSeqNum,
                                            sourceTmp, destHostId, destAppId, destInstanceId, topic.guid.prefix.hostId,
                                            topic.guid.prefix.appId, topic.guid.prefix.instanceId,
                                            topic.guid.objectId, 0, topic.parameter->topic, topic.parameter->typeName, false);
                            }
                        }
                        else
                        {
                            logError(m_log, "Cannot deserialized DataR");
                        }

                        REDAFastBufferPool_delete(pool->_typeCodePool);
                    }
                    else
                    {
                        logError(m_log, "Cannot allocate typecode pool");
                    }

                    RTIOsapiHeap_freeStructure(pool);
                }
                else
                {
                    logError(m_log, "Cannot allocate DISCBuiltinTopicSubscriptionDataPool");
                }

                RTIOsapiHeap_freeStructure(epd);
            }
            else
            {

                logError(m_log, "Cannot allocate DISCBuiltinTopicSubscriptionDataPluginEndpointData");
            }

            DISCBuiltinTopicSubscriptionDataPluginSupport_finalizeData_ex(&topic, RTI_TRUE);
        }
        else
        {
            logError(m_log, "Cannot initialized DISCBuiltinTopicSubscriptionData");
        }
#endif
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void RTPSdump::processDataNormal(const struct timeval &wts, string &ip_src, string &ip_dst,
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

    // Check the writer or reader has associated a typecode.
    if((entity = m_entitiesDB->findEntity(hostId, appId,
                    instanceId, writerId)) != NULL ||
            (entity = m_entitiesDB->findEntity(hostId, appId,
                                               instanceId, readerId)) != NULL)
    {
#ifndef DDS_USE
        if((typecode = m_typecodeDB->findTypecode(entity->getTopicName(),
                        entity->getTypeName())) != NULL)
        {
            CDRBuffer::Endianess _endianess = endianess ? CDRBuffer::LITTLE_ENDIAN : CDRBuffer::BIG_ENDIAN;
            CDRBuffer buffer((char*)serializedData, serializedDataLen, _endianess);
            CDR cdr(buffer, CDR::DDS_CDR);
            
            if(cdr.read_encapsulation() && cdr.getDDSCdrPlFlag() == CDR::DDS_CDR_WITHOUT_PL)
            {
				// It is necessary reset the alignment in the CDR buffer.
				cdr.resetAlignment();
                dynamicDB = typecode->getDynamicDataDB();
                        
                if(dynamicDB != NULL)
                {
                    if(!dynamicDB->storeDynamicData(wts, ip_src, ip_dst, hostId,
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
#else
        struct DDS_DynamicDataTypeSupport *typeSupport = NULL;
        struct DDS_DynamicDataTypeProperty_t typeProp = DDS_DynamicDataTypeProperty_t_INITIALIZER;
        struct DDS_DynamicData *dynamicData = NULL;
        RTICdrStream stream;

        if((typecode = m_typecodeDB->findTypecode(entity->getTopicName().c_str(),
                        entity->getTypeName().c_str())) != NULL)
        {
            typeSupport = DDS_DynamicDataTypeSupport_new((struct DDS_TypeCode*)typecode->getCdrTypecode(), &typeProp);

            if(typeSupport != NULL)
            {
                dynamicData = DDS_DynamicDataTypeSupport_create_data(typeSupport);

                if(dynamicData != NULL)
                {
                    RTICdrStream_init(&stream);
                    RTICdrStream_set(&stream, (char*)serializedData, serializedDataLen);

                    if(DDS_DynamicDataTypePlugin_deserialize(NULL, dynamicData, 
                            &stream, RTI_TRUE, RTI_TRUE, NULL) == RTI_TRUE)
                    {
                        dynamicDB = typecode->getDynamicDataDB();
                        
                        if(dynamicDB != NULL)
                        {
                            if(!dynamicDB->storeDynamicData(wts, ip_src, ip_dst, hostId,
                                        appId, instanceId, readerId, writerId, writerSeqNum,
                                        sourceTmp, destHostId, destAppId, destInstanceId,
                                        typecode->getCdrTypecode(), dynamicData))
                            {
                                logError(m_log, "Cannot stores the dynamic data in database");
                            }
                        }
                    }
                    else
                    {
                        logError(m_log, "Cannot deserialize the DynamicData");
                    }

                    DDS_DynamicDataTypeSupport_delete_data(typeSupport, dynamicData);
                }
                else
                {
                    logError(m_log, "Cannot create the DynamicData");
                }

                DDS_DynamicDataTypeSupport_delete(typeSupport);
            }
            else
            {
                logError(m_log, "Cannot create the DynamicDataTypeSupport");
            }
        }
        else
        {
            logError(m_log, "Cannot find the typecode from topic %s", entity->getTopicName().c_str());
        }
#endif
    }
    else
    {
        logError(m_log, "Cannot find entity in database: (%u, %u, %u, %u) or " \
                "(%u, %u, %u, %u)", hostId, appId, instanceId, writerId,
                hostId, appId, instanceId, readerId);
    }

}


bool RTPSdump::deserializePublicationBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, RTPSdump::PublicationBuiltinTopic &pubtopic)
{
    const char* const METHOD_NAME = "deserializePublicationBuiltinTopic";
    bool returnedValue = false;

    if(serializedData != NULL)
    {
        CDRBuffer::Endianess _endianess = endianess ? CDRBuffer::LITTLE_ENDIAN : CDRBuffer::BIG_ENDIAN;
        CDRBuffer buffer((char*)serializedData, serializedDataLength, _endianess);
        CDR cdr(buffer, CDR::DDS_CDR);

        if(cdr.read_encapsulation() && cdr.getDDSCdrPlFlag() == CDR::DDS_CDR_WITH_PL)
        {
            uint16_t parameterId, parameterLength;

            returnedValue = cdr >> parameterId;
            returnedValue &= cdr >> parameterLength;

            while(returnedValue && parameterId != RTPS_PID_END)
            {
                CDRBuffer::State currentState = cdr.getState();

                switch(parameterId)
                {
                case RTPS_PID_GUID:
                    returnedValue &= cdr.deserialize(pubtopic.guid.hostId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(pubtopic.guid.appId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(pubtopic.guid.instanceId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(pubtopic.guid.objectId, CDRBuffer::BIG_ENDIAN);
                    break;
                case RTPS_PID_TOPIC_NAME:
                    returnedValue &= cdr >> pubtopic.topic_name;
                    break;
                case RTPS_PID_TYPE_NAME:
                    returnedValue &= cdr >> pubtopic.type_name;
                    break;
                case RTPS_PID_TYPECODE:
                    pubtopic.typeCode = cdr.getCurrentPosition();
                    pubtopic.typeCodeLength = parameterLength;
                    break;
                default:
                    break;
                }

                cdr.setState(currentState);
                returnedValue &= cdr.jump(parameterLength);

                returnedValue &= cdr >> parameterId;
                returnedValue &= cdr >> parameterLength;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool RTPSdump::deserializeSubscriptionBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, RTPSdump::SubscriptionBuiltinTopic &subtopic)
{
    const char* const METHOD_NAME = "deserializeSubscriptionBuiltinTopic";
    bool returnedValue = false;

    if(serializedData != NULL)
    {
        CDRBuffer::Endianess _endianess = endianess ? CDRBuffer::LITTLE_ENDIAN : CDRBuffer::BIG_ENDIAN;
        CDRBuffer buffer((char*)serializedData, serializedDataLength, _endianess);
        CDR cdr(buffer, CDR::DDS_CDR);

        if(cdr.read_encapsulation() && cdr.getDDSCdrPlFlag() == CDR::DDS_CDR_WITH_PL)
        {
            uint16_t parameterId, parameterLength;

            returnedValue = cdr >> parameterId;
            returnedValue &= cdr >> parameterLength;

            while(returnedValue && parameterId != RTPS_PID_END)
            {
                CDRBuffer::State currentState = cdr.getState();

                switch(parameterId)
                {
                case RTPS_PID_GUID:
                    returnedValue &= cdr.deserialize(subtopic.guid.hostId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(subtopic.guid.appId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(subtopic.guid.instanceId, CDRBuffer::BIG_ENDIAN);
                    returnedValue &= cdr.deserialize(subtopic.guid.objectId, CDRBuffer::BIG_ENDIAN);
                    break;
                case RTPS_PID_TOPIC_NAME:
                    returnedValue &= cdr >> subtopic.topic_name;
                    break;
                case RTPS_PID_TYPE_NAME:
                    returnedValue &= cdr >> subtopic.type_name;
                    break;
                case RTPS_PID_TYPECODE:
                    subtopic.typeCode = cdr.getCurrentPosition();
                    subtopic.typeCodeLength = parameterLength;
                    break;
                default:
                    break;
                }

                cdr.setState(currentState);
                returnedValue &= cdr.jump(parameterLength);

                returnedValue &= cdr >> parameterId;
                returnedValue &= cdr >> parameterLength;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}