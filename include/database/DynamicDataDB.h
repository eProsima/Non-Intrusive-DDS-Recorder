#ifndef _DYNAMICDATADB_H_
#define _DYNAMICDATADB_H_

/*
 * Ñapa para que me compile. Corrige un error en las
 * macros de RTI.
 */
#include "cdr/cdr_stream.h"
#define RTI_PRECONDITION_TEST
#include "cdr/cdr_typeCode.h"
#undef RTI_PRECONDITION_TEST
#include "dds_c/dds_c_common.h"

struct DDS_DynamicData;
struct DDS_Time_t;
struct timeval;

#ifdef __cplusplus

#include <string>
#include <list>

#include <sqlite3.h>

namespace eProsima
{
    class eProsimaLog;

    typedef struct arrayProcessInfo
    {
        RTICdrUnsignedLong numberOfDimensions;
        RTICdrTCKind elementKind;
        RTICdrUnsignedLong currentDimensionIndex;
        RTICdrUnsignedLong currentDimensionProcess;
        DDS_UnsignedLong numberOfElements;
        int pointer;
        void *buffer;
        RTICdrTypeCode *elementType;
        const char *arrayName;
    } arrayProcessInfo;

    class DynamicDataDB
    {
        public:

            typedef struct arrayNode
            {
                std::string m_tableName;
                int m_ref;
                sqlite3_stmt *m_stmt;

                arrayNode() : m_ref(1), m_stmt(NULL)
                {
                }

                arrayNode(std::string &tableName, sqlite3_stmt *stmt)
                    : m_tableName(tableName), m_ref(1), m_stmt(stmt)
                {
                }

                ~arrayNode()
                {
                    if(m_stmt != NULL)
                    {
                        sqlite3_finalize(m_stmt);
                    }
                }
            } arrayNode;

            typedef struct writePrimitiveInitialStatementsFunctions
            {
                RTICdrTCKind _kind;
                bool (*_addToStream)(std::string &memberName, std::string &table_create,
                        std::string &dynamicDataAdd);
            } writePrimitiveInitialStatementsFunctions;

            typedef struct writePrimitiveStorageFunctions
            {
                RTICdrTCKind _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                        std::string &name, int &index);
            } writePrimitiveStorageFunctions;

            typedef struct writeArrayPrimitiveFunctions
            {
                RTICdrTCKind _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
                            
            } writeArrayPrimitiveFunctions;

            typedef struct writeSequencePrimitiveFunctions
            {
                RTICdrTCKind _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, int ref,
                        std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
                            
            } writeSequencePrimitiveFunctions;

            DynamicDataDB(eProsimaLog &log, sqlite3 *databaseH, std::string &tableName,
                    struct RTICdrTypeCode *typeCode);

            ~DynamicDataDB();

            bool storeDynamicData(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, struct RTICdrTypeCode *typeCode, struct DDS_DynamicData *dynamicData);

            static void eraseSpacesInTableName(std::string &tableName);

            static bool addTinyIntInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addShortInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addUShortInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addIntInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addUIntInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addBigIntInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addUBigIntInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addCharInitialStatements(std::string &memberName, std::string &table_create, std::string &dynamicDataAdd);
            static bool addTextInitialStatements(std::string &memberName, std::string &table_create, std::string &dynamicDataAdd);
            static bool addFloatInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);
            static bool addDoubleInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);

            static bool addOctetStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addShortStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addUShortStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addULongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addLongLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addULongLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addCharStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addStringStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addFloatStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);
            static bool addDoubleStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    std::string &name, int &index);

            static bool addOctetArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addShortArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addUShortArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addULongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addLongLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addULongLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addCharArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addFloatArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            static bool addDoubleArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);

            static bool addOctetSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addShortSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addUShortSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addLongSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addULongSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addLongLongSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addULongLongSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addCharSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addFloatSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);
            static bool addDoubleSequenceStorage(sqlite3_stmt *stmt, int ref, std::string &memberName, struct DDS_DynamicData *dynamicDataObject);

        private:

            bool kindIsPrimitive(RTICdrTCKind kind);

            bool createInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode);
            bool processStructsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processUnionsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processArraysInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processSequencesInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processMembersInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *memberInfo, std::string &memberName, std::string &suffix);
            bool processDimensionsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix, RTICdrUnsignedLong dimensionCount,
                    RTICdrUnsignedLong currentDimension);
            bool processArrayElementsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode);
            bool processArrayPrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode);
            bool processSequenceElementsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processSequencePrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, std::string &suffix);
            bool processPrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *primitiveInfo, std::string &primitiveName,
                    std::string &suffix);
            
            struct DDS_DynamicData* getMemberDynamicDataObject(RTICdrTypeCode *memberTypecode,
                    std::string &memberName, struct DDS_DynamicData *parentDynamicData);
            bool processStructsStorage(struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData, std::string &suffix,
                    int &index, bool step);
            bool processUnionsStorage(struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData, std::string &suffix,
                    int &index, bool step);
            bool processMembersStorage(struct RTICdrTypeCode *memberInfo, std::string &memberName,
                    struct DDS_DynamicData *dynamicData, std::string &suffix,
                    int &index, bool step);
            bool processArraysStorage(struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData, std::string &suffix,
                    std::string &memberName, int &index, bool step);
            bool processDimensionsStorage(sqlite3_stmt *stmt, struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            bool processArrayElementsStorage(sqlite3_stmt *stmt,
                    struct DDS_DynamicData *dynamicData, arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            bool processArrayPrimitiveStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicData,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension);
            bool processSequencesStorage(struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData, std::string &suffix,
                    std::string &memberName, int &index, bool step);
            bool processSequenceElementsStorage(sqlite3_stmt *stmt, int ref, std::string &memberName,
                    RTICdrTCKind elementKind, struct DDS_DynamicData *dynamicData);
            bool processSequencePrimitiveStorage(sqlite3_stmt *stmt, int ref, std::string &memberName,
                    RTICdrTCKind elementKind, struct DDS_DynamicData *dynamicData);
            bool processPrimitiveStorage(struct RTICdrTypeCode *primitiveInfo, std::string &primitiveName,
                    struct DDS_DynamicData *primitiveData, int &index, bool step);

            eProsimaLog &m_log;

            bool m_ready;

            /// Handler of the database.
            sqlite3 *m_databaseH;

            std::string m_tableName;

            /// Sqlite3 statement used to add dynamic data.
            sqlite3_stmt *m_addStmt;

            std::list<arrayNode*> m_arrays;
            std::list<arrayNode*> m_sequences;

            static writePrimitiveInitialStatementsFunctions writePrimitiveInitialStatementsFunctionsMap[];
            static writePrimitiveStorageFunctions writePrimitiveStorageFunctionsMap[];
            static writeArrayPrimitiveFunctions writeArrayPrimitiveFunctionsMap[];
            static writeSequencePrimitiveFunctions writeSequencePrimitiveFunctionsMap[];
    };
}

#endif // __cplusplus

#endif // _DYNAMICDATADB_H_
