#include "RTPSdump.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "disc/disc_builtin.h"
#include "cdr/cdr_stream.h"
#include "pres/pres_typePlugin.h"
#include "dds_c/dds_c_typecode.h"

#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER 0x000003c7
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER 0x000003c2
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER 0x000004c7
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER 0x000004c2

#define TYPECODE_MAX_SERIALIZED_LENGTH 2048

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

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "RTPSdump";

RTPSdump::RTPSdump(eProsimaLog &log, string &database) : m_log(log), m_typecodeDB(m_log, database)
{
}

void RTPSdump::processDataCallback(void *user, unsigned int readerId,
        unsigned int writerId, const char *serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataCallback";
    RTPSdump *rtpsdumper = (RTPSdump*)user;

    if(user != NULL)
    {
        rtpsdumper->processData(readerId, writerId, serializedData,
                serializedDataLen);
    }
    else
    {
        printError("Bad parameters");
    }
}

void RTPSdump::processData(unsigned int readerId,
                    unsigned int writerId, const char *serializedData,
                    unsigned int serializedDataLen)
{
    // Data(w)
    if(readerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER &&
            writerId == ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER)
    {
        processDataW(serializedData, serializedDataLen);
    }
    else if(readerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER &&
            writerId == ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER)
    {
        processDataR(serializedData, serializedDataLen);
    }
}

void RTPSdump::processDataW(const char *serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";
    struct DISCBuiltinTopicPublicationData topic = DISC_BUILTIN_TOPIC_PUBLICATION_DATA_INITIALIZE;
    struct DISCBuiltinTopicPublicationDataPluginEndpointData * epd = NULL;
    struct DISCBuiltinTopicPublicationDataPool *pool = NULL;
    struct REDAFastBufferPoolProperty poolProperty = REDA_FAST_BUFFER_POOL_PROPERTY_DEFAULT;
    struct RTICdrTypeCode *typeCode = NULL;
    RTICdrStream stream;

    if(serializedData != NULL)
    {
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
                    pool->_typeCodeMaximumSerializedLength = TYPECODE_MAX_SERIALIZED_LENGTH;
                    pool->_locatorFilterSeqMaximumLength = 0;
                    pool->_locatorFilterExpMaximumLength = 0;

                    pool->_typeCodePool = REDAFastBufferPool_new(
                            (TYPECODE_MAX_SERIALIZED_LENGTH * RTI_CDR_CHAR_SIZE),
                            RTI_CDR_LONG_ALIGN, &poolProperty);

                    if(pool->_typeCodePool != NULL)
                    {
                        RTICdrStream_init(&stream);
                        RTICdrStream_set(&stream, (char*)serializedData, serializedDataLen);

                        if(DISCBuiltinTopicPublicationDataPlugin_deserialize(epd, &topic, &stream,
                                    RTI_FALSE, RTI_TRUE, NULL) == RTI_TRUE)
                        {
                            RTIOsapiHeap_allocateBufferNotAligned((char**)&typeCode, RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));

                            if(typeCode != NULL)
                            {
                                RTICdrTypeCode_initialize_stream(typeCode,
                                        RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                if(RTICdrTypeCode_copy_stream(typeCode, topic.parameter->typeCode) == RTI_TRUE)
                                {
                                    // Add typecode.
                                    if(m_typecodeDB.addTypecode(topic.parameter->topic, topic.parameter->typeName,
                                                typeCode))
                                    {
                                        RTICdrTypeCode_print_IDL(typeCode, 0);
                                    }
                                    else
                                    {
                                        RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                    }
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
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void RTPSdump::processDataR(const char *serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";
    struct DISCBuiltinTopicSubscriptionData topic = DISC_BUILTIN_TOPIC_SUBSCRIPTION_DATA_INITIALIZE;
    struct DISCBuiltinTopicSubscriptionDataPluginEndpointData * epd = NULL;
    struct DISCBuiltinTopicSubscriptionDataPool *pool = NULL;
    struct REDAFastBufferPoolProperty poolProperty = REDA_FAST_BUFFER_POOL_PROPERTY_DEFAULT;
    struct RTICdrTypeCode *typeCode = NULL;
    RTICdrStream stream;

    if(serializedData != NULL)
    {
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
                    pool->_typeCodeMaximumSerializedLength = TYPECODE_MAX_SERIALIZED_LENGTH;
                    pool->_userDataMaximumLength = 0;
                    pool->_groupDataMaximumLength = 0;
                    pool->_topicDataMaximumLength = 0;
                    pool->_partitionMaximumNameCount = 0;
                    pool->_partitionMaximumCumulativeLength = 0;
                    pool->_contentFilterPropertyMaxSerializedLength = 0;

                    pool->_typeCodePool = REDAFastBufferPool_new(
                            (TYPECODE_MAX_SERIALIZED_LENGTH * RTI_CDR_CHAR_SIZE),
                            RTI_CDR_LONG_ALIGN, &poolProperty);

                    if(pool->_typeCodePool != NULL)
                    {
                        RTICdrStream_init(&stream);
                        RTICdrStream_set(&stream, (char*)serializedData, serializedDataLen);

                        if(DISCBuiltinTopicSubscriptionDataPlugin_deserialize(epd, &topic, &stream,
                                    RTI_FALSE, RTI_TRUE, NULL) == RTI_TRUE)
                        {
                            RTIOsapiHeap_allocateBufferNotAligned((char**)&typeCode, RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));

                            if(typeCode != NULL)
                            {
                                RTICdrTypeCode_initialize_stream(typeCode,
                                        RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                if(RTICdrTypeCode_copy_stream(typeCode, topic.parameter->typeCode) == RTI_TRUE)
                                {
                                    // Add typecode.
                                    if(m_typecodeDB.addTypecode(topic.parameter->topic, topic.parameter->typeName,
                                                typeCode))
                                    {
                                        RTICdrTypeCode_print_IDL(typeCode, 0);
                                    }
                                    else
                                    {
                                        RTIOsapiHeap_freeBufferNotAligned(typeCode);
                                    }
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
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}
