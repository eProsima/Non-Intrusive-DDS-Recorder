#include "RTPSdump.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "disc/disc_builtin.h"
#include "cdr/cdr_stream_impl.h"
#include "pres/pres_typePlugin_impl.h"
#include "dds_c/dds_c_typecode.h"

#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER 0x000003c7
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER 0x000003c2

#define TYPECODE_MAX_SERIALIZED_LENGTH 2048

/* RTI types */
struct DISCBuiltinTopicPublicationDataPluginEndpointData
{
    struct PRESTypePluginDefaultEndpointData * defaultEndPluginData;
    struct DISCBuiltinTopicPublicationDataPool * pool;
};

using namespace eProsima;

static const char* const CLASS_NAME = "RTPSdump";

RTPSdump::RTPSdump(eProsimaLog &log) : m_log(log)
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
}

void RTPSdump::processDataW(const char *serializedData,
        unsigned int serializedDataLen)
{
    const char* const METHOD_NAME = "processDataW";
    struct DISCBuiltinTopicPublicationData topic = DISC_BUILTIN_TOPIC_PUBLICATION_DATA_INITIALIZE;
    struct DISCBuiltinTopicPublicationDataPluginEndpointData * epd = NULL;
    struct DISCBuiltinTopicPublicationDataPool *pool = NULL;
    struct REDAFastBufferPoolProperty poolProperty = REDA_FAST_BUFFER_POOL_PROPERTY_DEFAULT;
    struct DDS_TypeCode *typeCode = NULL;
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
                            RTIOsapiHeap_allocateStructure(&typeCode, struct DDS_TypeCode);

                            if(typeCode != NULL)
                            {
                                RTICdrTypeCode_initialize_stream(&typeCode->_data,
                                        RTICdrTypeCode_get_stream_length(topic.parameter->typeCode));
                                if(RTICdrTypeCode_copy_stream(&typeCode->_data, topic.parameter->typeCode) == RTI_TRUE)
                                {
                                    // TODO
                                }
                                else
                                {
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
