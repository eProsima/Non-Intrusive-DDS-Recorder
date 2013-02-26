#ifndef _DYNAMICDATADB_H_
#define _DYNAMICDATADB_H_

#ifdef __cplusplus

#include <string>
#include <list>
#include <stdint.h>

#include <sqlite3.h>
#include "RTPSPacketAnalyzer.h"

namespace eProsima
{
    class eProsimaLog;
    class Member;
    class TypeCode;
    class StructTypeCode;
    class ArrayTypeCode;
    class EnumTypeCode;
    class PrimitiveTypeCode;
    class SequenceTypeCode;
    class UnionTypeCode;
    class CDR;

    typedef struct arrayProcessInfo
    {
        uint32_t currentDimensionIndex;
        uint32_t currentDimensionProcess;
        uint32_t numberOfElements;
        int pointer;
        void *buffer;
        std::string arrayName;
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
                uint32_t _kind;
                bool (*_addToStream)(std::string &memberName, std::string &table_create,
                        std::string &dynamicDataAdd);
            } writePrimitiveInitialStatementsFunctions;

            typedef struct writePrimitiveStorageFunctions
            {
                uint32_t _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, CDR &cdr, int &index);
            } writePrimitiveStorageFunctions;

            typedef struct writeArrayPrimitiveFunctions
            {
                uint32_t _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, CDR &cdr,
                        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
                            
            } writeArrayPrimitiveFunctions;

            typedef struct writeSequencePrimitiveFunctions
            {
                uint32_t _kind;
                bool (*_addToStream)(sqlite3_stmt *stmt, int ref, CDR &cdr);
                            
            } writeSequencePrimitiveFunctions;

            static bool addOctetStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addShortStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addUShortStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addLongStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addULongStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addLongLongStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addULongLongStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addCharStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addStringStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addFloatStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addDoubleStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addBoolStorage(sqlite3_stmt *stmt, CDR &cdr, int &index);
            static bool addEnumStorage(sqlite3_stmt *stmt, const EnumTypeCode *enumTC, CDR &cdr, int &index, bool step);

            static bool addOctetArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addShortArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addUShortArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addLongArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addULongArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addLongLongArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addULongLongArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addCharArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addFloatArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addDoubleArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addBoolArrayStorage(sqlite3_stmt *stmt, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);
            static bool addEnumArrayStorage(sqlite3_stmt *stmt, const EnumTypeCode *enumTC, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);

            static bool addOctetSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addShortSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addUShortSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addLongSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addULongSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addLongLongSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addULongLongSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addCharSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addFloatSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addDoubleSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);
            static bool addEnumSequenceStorage(sqlite3_stmt *stmt, int ref, const EnumTypeCode *enumTC, CDR &cdr);
            static bool addBoolSequenceStorage(sqlite3_stmt *stmt, int ref, CDR &cdr);

            DynamicDataDB(eProsimaLog &log, sqlite3 *databaseH, std::string &tableName,
                    const TypeCode*typeCode);

            bool storeDynamicData(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId,
                    const TypeCode *typeCode, CDR &cdr);

            ~DynamicDataDB();

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
            static bool addEnumInitialStatements(std::string &memberName, std::string &table_create,
                    std::string &dynamicDataAdd);

        private:

            bool createInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const TypeCode *typeCode);

            bool processStructsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const StructTypeCode *structTC, std::string &suffix);

            bool processUnionsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const UnionTypeCode *unionTC, std::string &suffix);

            bool processMembersInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const Member *memberInfo, std::string &suffix);

            bool processArraysInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const ArrayTypeCode *typeCode, std::string &suffix);

            bool processDimensionsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const ArrayTypeCode *typeCode, std::string &suffix, uint32_t currentDimension);

            bool processArrayElementsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const ArrayTypeCode *typeCode);

            bool processArrayPrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const PrimitiveTypeCode *typeCode);

            bool processPrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const PrimitiveTypeCode *primitiveInfo, const std::string &primitiveName,
                    std::string &suffix);

            bool processSequencesInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const SequenceTypeCode *typeCode, std::string &suffix);

            bool processSequenceElementsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const SequenceTypeCode *typeCode, std::string &suffix);

            bool processSequencePrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    const PrimitiveTypeCode *typeCode, std::string &suffix);

            bool processStructsStorage(const StructTypeCode *typeCode, CDR &cdr,
                std::string &suffix, int &index, bool step);

            bool processUnionsStorage(const UnionTypeCode *typeCode, CDR &cdr,
                std::string &suffix, int &index, bool step);

            bool processMembersStorage(const Member *memberInfo, CDR &cdr, std::string &suffix,
                    int &index, bool step);

            bool processArraysStorage(const ArrayTypeCode *typeCode, CDR &cdr, std::string &suffix,
                    const std::string &memberName, int &index, bool step);

            bool processDimensionsStorage(sqlite3_stmt *stmt, const ArrayTypeCode *typeCode, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);

            bool processArrayElementsStorage(sqlite3_stmt *stmt, const ArrayTypeCode *typeCode,
                    CDR &cdr, arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);

            bool processArrayPrimitiveStorage(sqlite3_stmt *stmt, const PrimitiveTypeCode *typeCode, CDR &cdr,
                    arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension);

            bool processPrimitiveStorage(const PrimitiveTypeCode *primitiveInfo,
                    CDR &cdr, int &index, bool step);

            bool processSequencesStorage(const SequenceTypeCode *typeCode,
                    CDR &cdr, std::string &suffix,
                    const std::string &memberName, int &index, bool step);

            bool processSequenceElementsStorage(sqlite3_stmt *stmt, int ref, const SequenceTypeCode *typeCode, CDR &cdr);

            bool processSequencePrimitiveStorage(sqlite3_stmt *stmt, int ref, const PrimitiveTypeCode *typeCode, CDR &cdr);

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
