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

struct DDS_DynamicData;

#ifdef __cplusplus

#include <string>

#include <sqlite3.h>

namespace eProsima
{
    class eProsimaLog;

    class DynamicDataDB
    {
        public:

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

            DynamicDataDB(eProsimaLog &log, sqlite3 *databaseH, std::string &tableName,
                    struct RTICdrTypeCode *typeCode);

            ~DynamicDataDB();

            bool storeDynamicData(unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int writerId, struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData);

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

        private:

            bool kindIsPrimitive(RTICdrTCKind kind);

            bool createInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode);
            bool processStructsInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode);
            bool processMembersInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *memberInfo, std::string &memberName);
            bool processPrimitiveInitialStatements(std::string &table_create, std::string &dynamicDataAdd,
                    struct RTICdrTypeCode *primitiveInfo, std::string &primitiveName);
            
            struct DDS_DynamicData* getMemberDynamicDataObject(RTICdrTypeCode *typecode,
                    struct DDS_DynamicData *dynamicData);
            bool processStructsStorage(struct RTICdrTypeCode *typeCode,
                    struct DDS_DynamicData *dynamicData, int &index);
            bool processMembersStorage(struct RTICdrTypeCode *memberInfo, std::string &memberName,
                    struct DDS_DynamicData *dynamicData, int &index);
            bool processPrimitiveStorage(struct RTICdrTypeCode *primitiveInfo, std::string &primitiveName,
                    struct DDS_DynamicData *primitiveData, int &index);

            eProsimaLog &m_log;

            bool m_ready;

            /// Handler of the database.
            sqlite3 *m_databaseH;

            std::string m_tableName;

            /// Sqlite3 statement used to add dynamic data.
            sqlite3_stmt *m_addStmt;

            static writePrimitiveInitialStatementsFunctions writePrimitiveInitialStatementsFunctionsMap[];
            static writePrimitiveStorageFunctions writePrimitiveStorageFunctionsMap[];
    };
}

#endif // __cplusplus

#endif // _DYNAMICDATADB_H_
