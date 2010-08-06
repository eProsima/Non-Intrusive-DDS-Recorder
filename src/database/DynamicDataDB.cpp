#include "database/DynamicDataDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "dds_c/dds_c_common.h"
#include "dds_c/dds_c_dynamicdata.h"

#include <string.h>

static const char* const CLASS_NAME = "DynamicDataDB";

using namespace eProsima;
using namespace std;

DynamicDataDB::writePrimitiveInitialStatementsFunctions DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap[] =
{
    {RTI_CDR_TK_OCTET, DynamicDataDB::addTinyIntInitialStatements},
    {RTI_CDR_TK_SHORT, DynamicDataDB::addShortInitialStatements},
    {RTI_CDR_TK_USHORT, DynamicDataDB::addUShortInitialStatements},
    {RTI_CDR_TK_LONG, DynamicDataDB::addIntInitialStatements},
    {RTI_CDR_TK_ULONG, DynamicDataDB::addUIntInitialStatements},
    {RTI_CDR_TK_LONGLONG, DynamicDataDB::addBigIntInitialStatements},
    {RTI_CDR_TK_ULONGLONG, DynamicDataDB::addUBigIntInitialStatements},
    {RTI_CDR_TK_CHAR, DynamicDataDB::addCharInitialStatements},
    {RTI_CDR_TK_STRING, DynamicDataDB::addTextInitialStatements},
    {RTI_CDR_TK_NULL, NULL}
};

DynamicDataDB::writePrimitiveStorageFunctions DynamicDataDB::writePrimitiveStorageFunctionsMap[] =
{
    {RTI_CDR_TK_OCTET, DynamicDataDB::addOctetStorage},
    {RTI_CDR_TK_SHORT, DynamicDataDB::addShortStorage},
    {RTI_CDR_TK_USHORT, DynamicDataDB::addUShortStorage},
    {RTI_CDR_TK_LONG, DynamicDataDB::addLongStorage},
    {RTI_CDR_TK_ULONG, DynamicDataDB::addULongStorage},
    {RTI_CDR_TK_LONGLONG, DynamicDataDB::addLongLongStorage},
    {RTI_CDR_TK_ULONGLONG, DynamicDataDB::addULongLongStorage},
    {RTI_CDR_TK_CHAR, DynamicDataDB::addCharStorage},
    {RTI_CDR_TK_STRING, DynamicDataDB::addStringStorage},
    {RTI_CDR_TK_NULL, NULL}
};

DynamicDataDB::DynamicDataDB(eProsimaLog &log, sqlite3 *databaseH, string &tableName,
        struct RTICdrTypeCode *typeCode) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_tableName(tableName), m_addStmt(NULL)
{
    const char* const METHOD_NAME = "DynamicDataDB";
    const char* const TABLE_CHECK_INIT = "SELECT name FROM sqlite_master WHERE name='";
    const char* const TABLE_DROP_INIT = "DROP TABLE ";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;
    string TABLE_CHECK, TABLE_DROP, TABLE_CREATE, DYNAMICDATA_ADD;

    TABLE_CHECK = TABLE_CHECK_INIT;
    TABLE_CHECK += m_tableName;
    TABLE_CHECK += "'";

    TABLE_DROP = TABLE_DROP_INIT;
    TABLE_DROP += m_tableName;

    if(sqlite3_prepare_v2(m_databaseH, TABLE_CHECK.c_str(), strlen(TABLE_CHECK.c_str()), &stmt, NULL) == SQLITE_OK)
    {
        ret = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(ret == SQLITE_ROW)
        {
            if(sqlite3_prepare_v2(m_databaseH, TABLE_DROP.c_str(), strlen(TABLE_DROP.c_str()), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) != SQLITE_DONE)
                    logError(m_log, "Cannot drop the %s table", m_tableName.c_str());

                sqlite3_finalize(stmt);
            }
        }

        if(createInitialStatements(TABLE_CREATE, DYNAMICDATA_ADD, typeCode))
        {
            if(sqlite3_prepare_v2(m_databaseH, TABLE_CREATE.c_str(), strlen(TABLE_CREATE.c_str()), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) == SQLITE_DONE)
                    m_ready = true;
                else
                    logError(m_log, "Cannot create the %s table", m_tableName.c_str());

                sqlite3_finalize(stmt);
            }
            else
            {
                logError(m_log, "Cannot prepare the creation statement for %s table", m_tableName.c_str());
            }
        }

        if(m_ready)
        {
            m_ready = false;

            if(sqlite3_prepare_v2(m_databaseH, DYNAMICDATA_ADD.c_str(), strlen(DYNAMICDATA_ADD.c_str()), &m_addStmt, NULL) == SQLITE_OK)
            {
                    m_ready = true;
            }
            else
                logError(m_log, "Cannot create add statement");
                
        }
    }
    else
    {
        logError(m_log, "Cannot check the %s table", m_tableName.c_str());
    }
}

DynamicDataDB::~DynamicDataDB()
{
    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }
}

void DynamicDataDB::eraseSpacesInTableName(string &tableName)
{
    size_t lookHere = 0;
    size_t foundHere;
    // Erase spaces.
    while((foundHere = tableName.find(" ")) !=
            string::npos)
    {
        tableName.replace(foundHere, 1, "_");
        lookHere = foundHere + 1;
    }
}

bool DynamicDataDB::kindIsPrimitive(RTICdrTCKind kind)
{
    if((kind == RTI_CDR_TK_STRUCT) ||
            (kind == RTI_CDR_TK_ARRAY) ||
            (kind == RTI_CDR_TK_SEQUENCE) ||
            (kind == RTI_CDR_TK_UNION) ||
            (kind == RTI_CDR_TK_ALIAS) ||
            (kind == RTI_CDR_TK_VALUE) ||
            (kind == RTI_CDR_TK_SPARSE))
        return false;
    return true;
}

bool DynamicDataDB::createInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode)
{
    bool returnedValue = false;

    table_create = "CREATE TABLE ";
    table_create += m_tableName;
    table_create += " (host_id INT, app_id INT, instance_id INT, entity_id INT";

    dynamicDataAdd = "INSERT INTO ";
    dynamicDataAdd += m_tableName;
    dynamicDataAdd += " VALUES(?, ?, ?, ?";

    returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, typeCode);

    table_create += ")";
    dynamicDataAdd += ")";

    return returnedValue;
}

bool DynamicDataDB::processStructsInitialStatements(string &table_create, string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode)
{
    const char* const METHOD_NAME = "processStructsInitialStatements";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    const char *memberName = NULL;
    string smemberName;

    if(RTICdrTypeCode_get_member_count(typeCode, &membersNumber) == RTI_TRUE)
    {
        returnedValue = true;
        for(DDS_UnsignedLong count = 0; returnedValue && (count < membersNumber); count ++)
        {
            memberInfo = RTICdrTypeCode_get_member_type(typeCode, count);

            if(memberInfo != NULL)
            {
                memberName = RTICdrTypeCode_get_member_name(typeCode, count);

                if(memberName != NULL)
                {
                    smemberName = memberName;
                    returnedValue = processMembersInitialStatements(table_create, dynamicDataAdd,
                            memberInfo, smemberName);
                }
                else
                {
                    logError(m_log, "Cannot obtain name of member %d", count);
                }
            }
            else
            {
                logError(m_log, "Cannot obtain info about member %d", count);
            }
        }
    }
    else
    {
        logError(m_log, "Cannot obtain number of member of the struct");
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *memberInfo, string &memberName)
{
    const char* const METHOD_NAME = "processMembersInitialStatements";
    bool returnedValue = false;
    RTICdrTCKind kind;

    if(RTICdrTypeCode_get_kind(memberInfo, &kind) == RTI_TRUE)
    {
        if(kind == RTI_CDR_TK_STRUCT)
        {
            returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, memberInfo);
        }
        else if(kind == RTI_CDR_TK_UNION)
        {
        }
        else if(kindIsPrimitive(kind))
        {
            returnedValue = processPrimitiveInitialStatements(table_create, dynamicDataAdd,
                    memberInfo, memberName);
        }
        else
        {
            logError(m_log, "The kind %d is not recognize", kind);
        }
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *primitiveInfo, string &primitiveName)
{
    bool returnedValue = false;
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    RTICdrTCKind kind;

    if(RTICdrTypeCode_get_kind(primitiveInfo, &kind) == RTI_TRUE)
    {
        while(writePrimitiveInitialStatementsFunctionsPointer->_kind != RTI_CDR_TK_NULL)
        {
            if(kind == writePrimitiveInitialStatementsFunctionsPointer->_kind)
            {
                addToStream = writePrimitiveInitialStatementsFunctionsPointer->_addToStream;
                break;
            }
            writePrimitiveInitialStatementsFunctionsPointer++;
        }

        if(addToStream != NULL)
            returnedValue = addToStream(primitiveName, table_create, dynamicDataAdd);
    }

    return returnedValue;
}

bool DynamicDataDB::addTinyIntInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " TINYINT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addShortInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " SHORT INT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addUShortInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " UNSINGED SHORT INT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addIntInitialStatements(string &memberName, string &table_create, string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " INT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addUIntInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " UNSIGNED INT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addBigIntInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " BIGINT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addUBigIntInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " UNSIGNED BIGINT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addCharInitialStatements(string &memberName, string &table_create, string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " CHARACTER(1)";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addTextInitialStatements(string &memberName, string &table_create, string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " TEXT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::storeDynamicData(unsigned int hostId, unsigned int appId, unsigned int instanceId,
        unsigned int writerId, struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData)
{
    const char* const METHOD_NAME = "storeDynamicData";
    bool returnedValue = false;
    int index = 1;

    if(dynamicData != NULL &&
            typeCode != NULL)
    {
        if(m_ready)
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_int(m_addStmt, index++, hostId);
                sqlite3_bind_int(m_addStmt, index++, appId);
                sqlite3_bind_int(m_addStmt, index++, instanceId);
                sqlite3_bind_int(m_addStmt, index++, writerId);

                returnedValue = processStructsStorage(typeCode, dynamicData, index);

                if(returnedValue)
                {
                    if(sqlite3_step(m_addStmt) != SQLITE_DONE)
                    {
                        returnedValue = false;
                        logError(m_log, "Cannot store in database");
                    }
                }
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

struct DDS_DynamicData* DynamicDataDB::getMemberDynamicDataObject(RTICdrTypeCode *typecode,
        struct DDS_DynamicData *dynamicData)
{
    //TODO
    return NULL;
}

bool DynamicDataDB::processStructsStorage(struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData, int &index)
{
    const char* const METHOD_NAME = "processStructsStorage";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    const char *memberName = NULL;
    string smemberName;

    if(RTICdrTypeCode_get_member_count(typeCode, &membersNumber) == RTI_TRUE)
    {
        returnedValue = true;
        for(DDS_UnsignedLong count = 0; returnedValue && (count < membersNumber); count ++)
        {
            memberInfo = RTICdrTypeCode_get_member_type(typeCode, count);

            if(memberInfo != NULL)
            {
                memberName = RTICdrTypeCode_get_member_name(typeCode, count);
                if(memberName != NULL)
                {
                    smemberName = memberName;
                    returnedValue = processMembersStorage(memberInfo, smemberName, dynamicData,
                            index);
                }
                else
                {
                    logError(m_log, "Cannot obtain name of member %d", count);
                }
            }
            else
            {
                logError(m_log, "Cannot obtain info about member %d", count);
            }
        }
    }
    else
    {
        logError(m_log, "Cannot obtain number of member of the struct");
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersStorage(struct RTICdrTypeCode *memberInfo, string &memberName,
        struct DDS_DynamicData *dynamicData, int &index)
{
    const char* const METHOD_NAME = "processMembersStorage";
    bool returnedValue = false;
    struct DDS_DynamicData *memberDynamicDataObject = NULL;
    RTICdrTCKind kind;

    if(RTICdrTypeCode_get_kind(memberInfo, &kind) == RTI_TRUE)
    {
        if(kind == RTI_CDR_TK_STRUCT)
        {
            //returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, memberInfo);
        }
        else if(kind == RTI_CDR_TK_UNION)
        {
        }
        else if(kindIsPrimitive(kind))
        {
            returnedValue = processPrimitiveStorage(memberInfo, memberName, dynamicData, index);
        }
        else
        {
            logError(m_log, "The kind %d is not recognize", kind);
        }
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveStorage(struct RTICdrTypeCode *primitiveInfo, string &primitiveName,
        struct DDS_DynamicData *primitiveData, int &index)
{
    bool returnedValue = false;
    writePrimitiveStorageFunctions *writePrimitiveStorageFunctionsPointer =
        DynamicDataDB::writePrimitiveStorageFunctionsMap;
    bool (*addToStream)(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
            string &name, int & index) = NULL;
    RTICdrTCKind kind;

    if(RTICdrTypeCode_get_kind(primitiveInfo, &kind) == RTI_TRUE)
    {
        while(writePrimitiveStorageFunctionsPointer->_kind != RTI_CDR_TK_NULL)
        {
            if(kind == writePrimitiveStorageFunctionsPointer->_kind)
            {
                addToStream = writePrimitiveStorageFunctionsPointer->_addToStream;
                break;
            }
            writePrimitiveStorageFunctionsPointer++;
        }

        if(addToStream != NULL)
            returnedValue = addToStream(m_addStmt, primitiveData, primitiveName, index);
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addOctetStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Octet value;
        if(DDS_DynamicData_get_octet(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the octet field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addShortStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addShortStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Short value;
        if(DDS_DynamicData_get_short(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the short field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addUShortStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addUShortStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_UnsignedShort value;
        if(DDS_DynamicData_get_ushort(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the ushort field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}


bool DynamicDataDB::addLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addLongStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Long value;
        if(DDS_DynamicData_get_long(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the long field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addULongStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_UnsignedLong value;
        if(DDS_DynamicData_get_ulong(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the ulong field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addLongLongStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_LongLong value;
        if(DDS_DynamicData_get_longlong(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            printf("%lld\n", value);
            sqlite3_bind_int64(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the longlong field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongLongStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addULongLongStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_UnsignedLongLong value;
        if(DDS_DynamicData_get_ulonglong(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int64(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the ulonglong field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addCharStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addStringStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Char value = NULL;
        DDS_DynamicData_get_char(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
        sqlite3_bind_text(stmt, index++, &value, 1, SQLITE_STATIC);
        returnedValue = true;
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addStringStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addStringStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Char *value = NULL;
        DDS_UnsignedLong stringLength;
        DDS_DynamicData_get_string(dynamicDataObject, &value, &stringLength,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
        sqlite3_bind_text(stmt, index++, value, stringLength, SQLITE_STATIC);
        returnedValue = true;
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}
