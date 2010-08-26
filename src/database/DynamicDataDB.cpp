#include "database/DynamicDataDB.h"
#include "eProsima_c/eProsimaMacros.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "dds_c/dds_c_common.h"
#include "dds_c/dds_c_dynamicdata.h"
#include "osapi/osapi_heap.h"

#include <string.h>
#include <stdlib.h>

#ifndef RTI_WIN32
#include <sys/time.h>
#endif

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
    {RTI_CDR_TK_FLOAT, DynamicDataDB::addFloatInitialStatements},
    {RTI_CDR_TK_DOUBLE, DynamicDataDB::addDoubleInitialStatements},
    {RTI_CDR_TK_ENUM, DynamicDataDB::addEnumInitialStatements},
    {RTI_CDR_TK_BOOLEAN, DynamicDataDB::addTinyIntInitialStatements},
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
    {RTI_CDR_TK_FLOAT, DynamicDataDB::addFloatStorage},
    {RTI_CDR_TK_DOUBLE, DynamicDataDB::addDoubleStorage},
    {RTI_CDR_TK_ENUM, DynamicDataDB::addEnumStorage},
    {RTI_CDR_TK_BOOLEAN, DynamicDataDB::addBoolStorage},
    {RTI_CDR_TK_NULL, NULL}
};

DynamicDataDB::writeArrayPrimitiveFunctions DynamicDataDB::writeArrayPrimitiveFunctionsMap[] =
{
    {RTI_CDR_TK_OCTET, DynamicDataDB::addOctetArrayStorage},
    {RTI_CDR_TK_SHORT, DynamicDataDB::addShortArrayStorage},
    {RTI_CDR_TK_USHORT, DynamicDataDB::addUShortArrayStorage},
    {RTI_CDR_TK_LONG, DynamicDataDB::addLongArrayStorage},
    {RTI_CDR_TK_ULONG, DynamicDataDB::addULongArrayStorage},
    {RTI_CDR_TK_LONGLONG, DynamicDataDB::addLongLongArrayStorage},
    {RTI_CDR_TK_ULONGLONG, DynamicDataDB::addULongLongArrayStorage},
    {RTI_CDR_TK_CHAR, DynamicDataDB::addCharArrayStorage},
    {RTI_CDR_TK_FLOAT, DynamicDataDB::addFloatArrayStorage},
    {RTI_CDR_TK_DOUBLE, DynamicDataDB::addDoubleArrayStorage},
    {RTI_CDR_TK_ENUM, DynamicDataDB::addEnumArrayStorage},
    {RTI_CDR_TK_BOOLEAN, DynamicDataDB::addBoolArrayStorage},
    {RTI_CDR_TK_NULL, NULL}
};

DynamicDataDB::writeSequencePrimitiveFunctions DynamicDataDB::writeSequencePrimitiveFunctionsMap[] =
{
    {RTI_CDR_TK_OCTET, DynamicDataDB::addOctetSequenceStorage},
    {RTI_CDR_TK_SHORT, DynamicDataDB::addShortSequenceStorage},
    {RTI_CDR_TK_USHORT, DynamicDataDB::addUShortSequenceStorage},
    {RTI_CDR_TK_LONG, DynamicDataDB::addLongSequenceStorage},
    {RTI_CDR_TK_ULONG, DynamicDataDB::addULongSequenceStorage},
    {RTI_CDR_TK_LONGLONG, DynamicDataDB::addLongLongSequenceStorage},
    {RTI_CDR_TK_ULONGLONG, DynamicDataDB::addULongLongSequenceStorage},
    {RTI_CDR_TK_CHAR, DynamicDataDB::addCharSequenceStorage},
    {RTI_CDR_TK_FLOAT, DynamicDataDB::addFloatSequenceStorage},
    {RTI_CDR_TK_DOUBLE, DynamicDataDB::addDoubleSequenceStorage},
    {RTI_CDR_TK_ENUM, DynamicDataDB::addEnumSequenceStorage},
    {RTI_CDR_TK_BOOLEAN, DynamicDataDB::addBoolSequenceStorage},
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

        printf("%s\n", TABLE_CREATE.c_str());
        printf("%s\n", DYNAMICDATA_ADD.c_str());

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
    list<arrayNode*>::iterator ait;

    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }

    for(ait = m_arrays.begin(); ait != m_arrays.end(); ait++)
        delete (*ait);
    for(ait = m_sequences.begin(); ait != m_sequences.end(); ait++)
        delete (*ait);
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
    string suffix = "";

    table_create = "CREATE TABLE ";
    table_create += m_tableName;
    table_create += " (wireshark_sourcetimestamp_sec BIGINT, wireshark_sourcetimestamp_msec BIGINT UNSIGNED, " \
                     "ip_src TEXT, ip_dst TEXT, " \
                     "host_id BIGINT UNSIGNED, app_id BIGINT UNSIGNED, instance_id BIGINT UNSIGNED, " \
                     "reader_id BIGINT UNSIGNED, writer_id BIGINT UNSIGNED, writer_seq_num BIGINT UNSIGNED," \
                     "sourcetimestamp_sec BIGINT, sourcetimestamp_nanosec BIGINT UNSIGNED";

    dynamicDataAdd = "INSERT INTO ";
    dynamicDataAdd += m_tableName;
    dynamicDataAdd += " VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?";

    returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, typeCode, suffix);

    table_create += ")";
    dynamicDataAdd += ")";

    return returnedValue;
}

bool DynamicDataDB::processStructsInitialStatements(string &table_create, string &dynamicDataAdd,
                    struct RTICdrTypeCode *typeCode, string &suffix)
{
    const char* const METHOD_NAME = "processStructsInitialStatements";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    const char *memberName = NULL;
    string smemberName;

    if(typeCode != NULL)
    {
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
                                memberInfo, smemberName, suffix);
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
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processUnionsInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix)
{
    const char* const METHOD_NAME = "processUnionsInitialStatements";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    const char *memberName = NULL;
    string smemberName;
    string newSuffix = suffix;

    if(typeCode != NULL)
    {
        if(RTICdrTypeCode_get_member_count(typeCode, &membersNumber) == RTI_TRUE)
        {
            newSuffix += "_discriminator";
            table_create += ", ";
            table_create += newSuffix;
            table_create += " INT";
            dynamicDataAdd += ", ?";

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
                                memberInfo, smemberName, suffix);
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
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArraysInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix)
{
    // suffix contains the name of the new table.
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArraysInitialStatements";
    string TABLE_CREATE = "CREATE TABLE ";
    string TABLE_INSERT = "INSERT INTO ";
    string TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='";
    string TABLE_DROP = "DROP TABLE ";
    RTICdrUnsignedLong dimensionCount;
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;

    if(typeCode != NULL)
    {
        TABLE_CREATE += suffix;
        TABLE_CREATE += " (ref INT";
        TABLE_INSERT += suffix;
        TABLE_INSERT += " VALUES(?";
        TABLE_CHECK += suffix;
        TABLE_CHECK += "'";
        TABLE_DROP += suffix;

        if(RTICdrTypeCode_get_array_dimension_count(typeCode, &dimensionCount) == RTI_TRUE)
        {
            if(processDimensionsInitialStatements(TABLE_CREATE, TABLE_INSERT, typeCode,
                        suffix, dimensionCount, 0))
            {
                TABLE_CREATE += ")";
                TABLE_INSERT += ")";

                printf("%s\n", TABLE_CREATE.c_str());
                printf("%s\n", TABLE_INSERT.c_str());

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

                    if(sqlite3_prepare_v2(m_databaseH, TABLE_CREATE.c_str(), strlen(TABLE_CREATE.c_str()), &stmt, NULL) == SQLITE_OK)
                    {
                        if(sqlite3_step(stmt) == SQLITE_DONE)
                        {
                            sqlite3_finalize(stmt);

                            if(sqlite3_prepare_v2(m_databaseH, TABLE_INSERT.c_str(), strlen(TABLE_INSERT.c_str()), &stmt, NULL) == SQLITE_OK)
                            {
                                m_arrays.push_back(new arrayNode(suffix, stmt));
                                returnedValue = true;
                            }
                            else
                            {
                                logError(m_log, "Cannot prepare statement to insert in array table %s", suffix.c_str());
                            }
                        }
                        else
                        {
                            sqlite3_finalize(stmt);
                            logError(m_log, "Cannot create the %s table", m_tableName.c_str());
                        }

                    }
                    else
                    {
                        logError(m_log, "Cannot prepare statement to create array table %s", suffix.c_str());
                    }
                }
                else
                {
                    logError(m_log, "Cannot check the %s table", m_tableName.c_str());
                }
            }
        }

        table_create += ", ";
        table_create += suffix;
        table_create += " INT";
        dynamicDataAdd += ", ?";
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencesInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix)
{
    // suffix contains the name of the new table.
    bool returnedValue = false;
    const char* const METHOD_NAME = "processSequencesInitialStatements";
    string TABLE_CREATE = "CREATE TABLE ";
    string TABLE_INSERT = "INSERT INTO ";
    string TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='";
    string TABLE_DROP = "DROP TABLE ";
    sqlite3_stmt *stmt = NULL;
    string newSuffix = suffix;
    int ret = SQLITE_ERROR;

    if(typeCode != NULL)
    {
        TABLE_CREATE += suffix;
        TABLE_CREATE += " (ref INT, indice INT";
        TABLE_INSERT += suffix;
        TABLE_INSERT += " VALUES(?, ?";
        TABLE_CHECK += suffix;
        TABLE_CHECK += "'";
        TABLE_DROP += suffix;

        if(processSequenceElementsInitialStatements(TABLE_CREATE, TABLE_INSERT, typeCode,
                    newSuffix))
        {
            TABLE_CREATE += ")";
            TABLE_INSERT += ")";

            printf("%s\n", TABLE_CREATE.c_str());
            printf("%s\n", TABLE_INSERT.c_str());

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

                if(sqlite3_prepare_v2(m_databaseH, TABLE_CREATE.c_str(), strlen(TABLE_CREATE.c_str()), &stmt, NULL) == SQLITE_OK)
                {
                    if(sqlite3_step(stmt) == SQLITE_DONE)
                    {
                        sqlite3_finalize(stmt);

                        if(sqlite3_prepare_v2(m_databaseH, TABLE_INSERT.c_str(), strlen(TABLE_INSERT.c_str()), &stmt, NULL) == SQLITE_OK)
                        {
                            m_sequences.push_back(new arrayNode(suffix, stmt));
                            returnedValue = true;
                        }
                        else
                        {
                            logError(m_log, "Cannot prepare statement to insert in array table %s", suffix.c_str());
                        }
                    }
                    else
                    {
                        sqlite3_finalize(stmt);
                        logError(m_log, "Cannot create the %s table", m_tableName.c_str());
                    }

                }
                else
                {
                    logError(m_log, "Cannot prepare statement to create array table %s", suffix.c_str());
                }
            }
            else
            {
                logError(m_log, "Cannot check the %s table", m_tableName.c_str());
            }
        }

        table_create += ", ";
        table_create += suffix;
        table_create += " INT";
        dynamicDataAdd += ", ?";
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *memberInfo, string &memberName, string &suffix)
{
    const char* const METHOD_NAME = "processMembersInitialStatements";
    bool returnedValue = false;
    RTICdrTCKind kind;
    string newSuffix;

    if(RTICdrTypeCode_get_kind(memberInfo, &kind) == RTI_TRUE)
    {
        if(kind == RTI_CDR_TK_STRUCT)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            newSuffix += "__";
            returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, memberInfo, newSuffix);
        }
        else if(kind == RTI_CDR_TK_UNION)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            newSuffix += "__";
            returnedValue = processUnionsInitialStatements(table_create, dynamicDataAdd, memberInfo, newSuffix);
        }
        else if(kind == RTI_CDR_TK_ARRAY)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            returnedValue = processArraysInitialStatements(table_create, dynamicDataAdd, memberInfo, newSuffix);
        }
        else if(kind == RTI_CDR_TK_SEQUENCE)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            returnedValue = processSequencesInitialStatements(table_create, dynamicDataAdd, memberInfo, newSuffix);
        }
        else if(kindIsPrimitive(kind))
        {
            returnedValue = processPrimitiveInitialStatements(table_create, dynamicDataAdd,
                    memberInfo, memberName, suffix);
        }
        else
        {
            logError(m_log, "The kind %d is not recognize", kind);
        }
    }

    return returnedValue;
}

bool DynamicDataDB::processDimensionsInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix, RTICdrUnsignedLong dimensionCount,
        RTICdrUnsignedLong currentDimension)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processDimensionsInitialStatements";
    RTICdrUnsignedLong dimensionIndex;
    string field;
    char number[50];

    if(typeCode != NULL)
    {
        if(RTICdrTypeCode_get_array_dimension(typeCode, currentDimension, &dimensionIndex) == RTI_TRUE)
        {
            field = "indice_";
            SNPRINTF(number, 50, "%d", currentDimension);
            field += number;

            table_create += ", ";
            table_create += field;
            table_create += " INT";
            dynamicDataAdd += ", ?";

            if(currentDimension == dimensionCount -1)
            {
                returnedValue = processArrayElementsInitialStatements(table_create, dynamicDataAdd,
                        typeCode);
            }
            else
            {
                returnedValue = processDimensionsInitialStatements(table_create, dynamicDataAdd,
                        typeCode, suffix, dimensionCount, currentDimension + 1);
            }
        }
        else
        {
            logError(m_log, "Cannot get the array dimension of %s", suffix.c_str());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayElementsInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArrayElementsInitialStatements";
    RTICdrTypeCode *elementType = NULL;
    RTICdrTCKind elementKind;

    if(typeCode != NULL)
    {
        elementType = RTICdrTypeCode_get_content_type(typeCode);

        if(elementType != NULL)
        {
            if(RTICdrTypeCode_get_kind(elementType, &elementKind) == RTI_TRUE)
            {
                if(kindIsPrimitive(elementKind))
                {
                    returnedValue = processArrayPrimitiveInitialStatements(table_create,
                            dynamicDataAdd, elementType);
                }
            }
        }
        else
        {
            logError(m_log, "Cannot obtain the element type");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayPrimitiveInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArrayPrimitiveInitialStatements";
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    RTICdrTCKind kind;
    string value = "value";

    if(typeCode != NULL)
    {
        if(RTICdrTypeCode_get_kind(typeCode, &kind) == RTI_TRUE)
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
            {
                returnedValue = addToStream(value, table_create, dynamicDataAdd);
                returnedValue = true;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequenceElementsInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processSequenceElementsInitialStatements";
    RTICdrTypeCode *elementType = NULL;
    RTICdrTCKind elementKind;

    if(typeCode != NULL)
    {
        elementType = RTICdrTypeCode_get_content_type(typeCode);

        if(elementType != NULL)
        {
            if(RTICdrTypeCode_get_kind(elementType, &elementKind) == RTI_TRUE)
            {
                if(kindIsPrimitive(elementKind))
                {
                    returnedValue = processSequencePrimitiveInitialStatements(table_create,
                            dynamicDataAdd, elementType, suffix);
                }
            }
        }
        else
        {
            logError(m_log, "Cannot obtain the element type");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencePrimitiveInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *typeCode, string &suffix)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processSequencePrimitiveInitialStatements";
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    RTICdrTCKind kind;
    string value = "value";

    if(typeCode != NULL)
    {
        if(RTICdrTypeCode_get_kind(typeCode, &kind) == RTI_TRUE)
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
            {
                returnedValue = addToStream(value, table_create, dynamicDataAdd);
                returnedValue = true;
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveInitialStatements(string &table_create, string &dynamicDataAdd,
        struct RTICdrTypeCode *primitiveInfo, string &primitiveName, string &suffix)
{
    bool returnedValue = false;
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    RTICdrTCKind kind;
    string newName;

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
        {
            newName = suffix;
            newName += primitiveName;
            returnedValue = addToStream(newName, table_create, dynamicDataAdd);
        }
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
    table_create += " SMALLINT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addUShortInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " SMALLINT UNSIGNED";
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
    table_create += " INT UNSIGNED ";
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
    table_create += " BIGINT UNSIGNED ";
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

bool DynamicDataDB::addFloatInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " FLOAT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::addDoubleInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " DOUBLE";
    dynamicDataAdd += ", ?";
    return true;
}
bool DynamicDataDB::addEnumInitialStatements(string &memberName, string &table_create,
        string &dynamicDataAdd)
{
    table_create += ", ";
    table_create += memberName;
    table_create += " TEXT";
    dynamicDataAdd += ", ?";
    return true;
}

bool DynamicDataDB::storeDynamicData(const struct timeval &wts, string &ip_src, string &ip_dst,
        unsigned int hostId, unsigned int appId, unsigned int instanceId,
        unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
        struct DDS_Time_t &sourceTmp, struct RTICdrTypeCode *typeCode, struct DDS_DynamicData *dynamicData)
{
    const char* const METHOD_NAME = "storeDynamicData";
    bool returnedValue = false;
    int index = 1;
    string suffix = "";

    if(dynamicData != NULL &&
            typeCode != NULL)
    {
        if(m_ready)
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_int64(m_addStmt, index++, wts.tv_sec);
                sqlite3_bind_int64(m_addStmt, index++, wts.tv_usec);
                sqlite3_bind_text(m_addStmt, index++, ip_src.c_str(), ip_src.length(), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, index++, ip_dst.c_str(), ip_dst.length(), SQLITE_STATIC);
                sqlite3_bind_int64(m_addStmt, index++, hostId);
                sqlite3_bind_int64(m_addStmt, index++, appId);
                sqlite3_bind_int64(m_addStmt, index++, instanceId);
                sqlite3_bind_int64(m_addStmt, index++, readerId);
                sqlite3_bind_int64(m_addStmt, index++, writerId);
                sqlite3_bind_int64(m_addStmt, index++, writerSeqNum);
                sqlite3_bind_int64(m_addStmt, index++, sourceTmp.sec);
                sqlite3_bind_int64(m_addStmt, index++, sourceTmp.nanosec);

                returnedValue = processStructsStorage(typeCode, dynamicData, suffix, index, false);

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

struct DDS_DynamicData* DynamicDataDB::getMemberDynamicDataObject(RTICdrTypeCode *memberTypecode,
        string &memberName, struct DDS_DynamicData *parentDynamicData)
{
    const char* const METHOD_NAME = "getMemberDynamicDataObject";
    struct DDS_DynamicData *memberDynamicDataObject = NULL;

    if(parentDynamicData != NULL &&
            memberTypecode != NULL)
    {
        memberDynamicDataObject = DDS_DynamicData_new((const DDS_TypeCode*)memberTypecode, &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);

        if(memberDynamicDataObject != NULL)
        {
            if(DDS_DynamicData_get_complex_member(parentDynamicData, memberDynamicDataObject,
                        memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) != DDS_RETCODE_OK)
            {
                DDS_DynamicData_delete(memberDynamicDataObject);
                memberDynamicDataObject = NULL;
                logError(m_log, "Cannot get the complex member %s", memberName.c_str());
            }
        }
        else
        {
            logError(m_log, "Cannot create a dynamicdata structure");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return memberDynamicDataObject;
}

bool DynamicDataDB::processStructsStorage(struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData, string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processStructsStorage";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    const char *memberName = NULL;
    string smemberName;

    if(typeCode != NULL && (dynamicData != NULL || step))
    {
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
                                suffix, index, step);
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
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processUnionsStorage(struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData, string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processUnionsStorage";
    bool returnedValue = false;
    DDS_UnsignedLong membersNumber;
    struct RTICdrTypeCode *memberInfo;
    struct DDS_DynamicDataMemberInfo disInfo;
    const char *memberName = NULL;
    string smemberName;
    RTICdrLong label;

    if(typeCode != NULL && dynamicData != NULL)
    {
        if(DDS_DynamicData_get_member_info_by_index(dynamicData, &disInfo, 0) == DDS_RETCODE_OK)
        {
            if(RTICdrTypeCode_get_member_count(typeCode, &membersNumber) == RTI_TRUE)
            {
                sqlite3_bind_int(m_addStmt, index++, disInfo.member_id);
                returnedValue = true;
                for(DDS_UnsignedLong count = 0; returnedValue && (count < membersNumber); count ++)
                {
                    bool newStep = true;

                    memberInfo = RTICdrTypeCode_get_member_type(typeCode, count);

                    if(memberInfo != NULL)
                    {
                        memberName = RTICdrTypeCode_get_member_name(typeCode, count);
                        if(memberName != NULL)
                        {
                            smemberName = memberName;

                            if(RTICdrTypeCode_get_member_label(typeCode, count, 0, &label) == RTI_TRUE)
                            {
                                if(!step)
                                {
                                    if(label == disInfo.member_id)
                                    {
                                        newStep = false;
                                    }
                                    else
                                    {
                                        RTICdrTypeCode_get_default_index(typeCode, &label);

                                        if(disInfo.member_id == -1 &&
                                                label == count)
                                        {
                                            newStep = false;
                                        }
                                    }
                                }

                                returnedValue = processMembersStorage(memberInfo, smemberName, dynamicData,
                                        suffix, index, newStep);
                            }
                            else
                            {
                                logError(m_log, "Cannot obtain union label");
                            }
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
        }
        else
        {
            logError(m_log, "Cannot obtain member info from DynamicData");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersStorage(struct RTICdrTypeCode *memberInfo, string &memberName,
        struct DDS_DynamicData *dynamicData, string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processMembersStorage";
    bool returnedValue = false;
    struct DDS_DynamicData *memberDynamicDataObject = NULL;
    RTICdrTCKind kind;
    string newSuffix;

    if(RTICdrTypeCode_get_kind(memberInfo, &kind) == RTI_TRUE)
    {
        if(kind == RTI_CDR_TK_STRUCT)
        {
            if(!step)
                memberDynamicDataObject = getMemberDynamicDataObject(memberInfo,
                        memberName, dynamicData);

            if((memberDynamicDataObject != NULL) || (step))
            {
                newSuffix = suffix;
                newSuffix += memberName;
                newSuffix += "__";
                returnedValue = processStructsStorage(memberInfo, memberDynamicDataObject,
                        newSuffix, index, step);
                if(memberDynamicDataObject != NULL)
                    DDS_DynamicData_delete(memberDynamicDataObject);
            }
        }
        else if(kind == RTI_CDR_TK_UNION)
        {
            memberDynamicDataObject = getMemberDynamicDataObject(memberInfo,
                    memberName, dynamicData);

            if(memberDynamicDataObject != NULL)
            {
                newSuffix = suffix;
                newSuffix += memberName;
                newSuffix += "__";
                returnedValue = processUnionsStorage(memberInfo, memberDynamicDataObject,
                        newSuffix, index, step);
                DDS_DynamicData_delete(memberDynamicDataObject);
            }
        }
        else if(kind == RTI_CDR_TK_ARRAY)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            returnedValue = processArraysStorage(memberInfo, dynamicData, newSuffix, memberName, index, step);
        }
        else if(kind == RTI_CDR_TK_SEQUENCE)
        {
            newSuffix = suffix;
            newSuffix += memberName;
            returnedValue = processSequencesStorage(memberInfo, dynamicData, newSuffix, memberName, index, step);
        }
        else if(kindIsPrimitive(kind))
        {
            returnedValue = processPrimitiveStorage(memberInfo, memberName, dynamicData, index, step);
        }
        else
        {
            logError(m_log, "The kind %d is not recognize", kind);
        }
    }

    return returnedValue;
}

bool DynamicDataDB::processArraysStorage(struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData, string &suffix,
        string &memberName, int &index, bool step)
{
    const char* const METHOD_NAME = "processArraysStorage";
    bool returnedValue = false;
    list<arrayNode*>::iterator it;
    arrayNode *aNode = NULL;
    arrayProcessInfo arrayProcessingInfo;

    if(typeCode != NULL && (dynamicData != NULL || step))
    {
        arrayProcessingInfo.pointer = 0;
        arrayProcessingInfo.buffer = 0;
        arrayProcessingInfo.numberOfElements = 0;
        arrayProcessingInfo.currentDimensionProcess = 0;
        arrayProcessingInfo.arrayName = memberName.c_str();

        // Search array statement.
        for(it = m_arrays.begin(); it != m_arrays.end(); it++)
        {
            if(suffix.compare((*it)->m_tableName) == 0)
            {
                aNode = (*it);
                break;
            }
        }

        if(it != m_arrays.end())
        {
            if(aNode != NULL && aNode->m_stmt != NULL)
            {
                if(!step)

                {
                    if(sqlite3_reset(aNode->m_stmt) == SQLITE_OK)
                    {
                        sqlite3_bind_int(aNode->m_stmt, 1, aNode->m_ref);
                        arrayProcessingInfo.elementType = RTICdrTypeCode_get_content_type(typeCode);

                        if(arrayProcessingInfo.elementType != NULL)
                        {
                            if(RTICdrTypeCode_get_kind(arrayProcessingInfo.elementType, &arrayProcessingInfo.elementKind) == RTI_TRUE)
                            {
                                if(RTICdrTypeCode_get_array_dimension_count(typeCode, &arrayProcessingInfo.numberOfDimensions) == RTI_TRUE)
                                {
                                    if(processDimensionsStorage(aNode->m_stmt, typeCode, dynamicData,
                                                &arrayProcessingInfo, 0))
                                    {
                                        sqlite3_bind_int(m_addStmt, index++, aNode->m_ref++);
                                        returnedValue = true;
                                    }

                                    if(arrayProcessingInfo.buffer != NULL)
                                        RTIOsapiHeap_freeBuffer(arrayProcessingInfo.buffer);
                                }
                                else
                                {
                                    logError(m_log, "Cannot get the dimension count from array %s",
                                            suffix.c_str());
                                }
                            }
                            else
                            {
                                logError(m_log, "Cannot reset statement for array %s", suffix.c_str());
                            }
                        }
                        else
                        {
                            logError(m_log, "Cannot obtain the element type");
                        }
                    }
                    else
                    {
                        logError(m_log, "Cannot reset the statement");
                    }
                }
                else
                {
                    sqlite3_bind_null(m_addStmt, index++);
                    returnedValue = true;
                }
            }
            else
            {
                logError(m_log, "Bad array statement for %s", suffix.c_str());
            }
        }
        else
        {
            logError(m_log, "Cannot find the array statement of %s", suffix.c_str());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processDimensionsStorage(sqlite3_stmt *stmt,
        struct RTICdrTypeCode *typeCode, struct DDS_DynamicData *dynamicData,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "processDimensionsStorage";
    bool returnedValue = false;
    RTICdrUnsignedLong dimensionIndex;

    if(stmt != NULL && typeCode != NULL && dynamicData != NULL &&
            arrayProcessingInfo != NULL)
    {
        if(RTICdrTypeCode_get_array_dimension(typeCode, currentDimension, &dimensionIndex) == RTI_TRUE)
        {
            if(currentDimension == arrayProcessingInfo->currentDimensionProcess)
            {
                if(arrayProcessingInfo->numberOfElements != 0)
                    arrayProcessingInfo->numberOfElements *= dimensionIndex;
                else
                    arrayProcessingInfo->numberOfElements = dimensionIndex;
                arrayProcessingInfo->currentDimensionProcess++;
            }

            if(currentDimension == arrayProcessingInfo->numberOfDimensions - 1)
            {
                arrayProcessingInfo->currentDimensionIndex = dimensionIndex;
                returnedValue = processArrayElementsStorage(stmt, dynamicData,
                        arrayProcessingInfo, currentDimension);
            }
            else
            {
                returnedValue = true;
                for(unsigned int count = 0; (returnedValue) && (count < dimensionIndex); count++)
                {
                    if(sqlite3_reset(stmt) == SQLITE_OK)
                    {
                        sqlite3_bind_int(stmt, currentDimension + 2, count);
                        returnedValue = processDimensionsStorage(stmt, typeCode, dynamicData,
                                arrayProcessingInfo, currentDimension + 1);
                    }
                    else
                    {
                        logError(m_log, "Cannot reset statement from array %s", arrayProcessingInfo->arrayName);
                    }
                }
            }
        }
        else
        {
            logError(m_log, "Cannot get the array dimension");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayElementsStorage(sqlite3_stmt *stmt,
        struct DDS_DynamicData *dynamicData, arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "processArrayElementsStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicData != NULL
            && arrayProcessingInfo != NULL)
    {
        if(kindIsPrimitive(arrayProcessingInfo->elementKind))
        {
            returnedValue = processArrayPrimitiveStorage(stmt,
                    dynamicData, arrayProcessingInfo, currentDimension);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayPrimitiveStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicData,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    bool returnedValue = false;
    writeArrayPrimitiveFunctions *writeArrayPrimitiveFunctionsPointer =
        DynamicDataDB::writeArrayPrimitiveFunctionsMap;
    bool (*addToStream)(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
            arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension) = NULL;

    while(writeArrayPrimitiveFunctionsPointer->_kind != RTI_CDR_TK_NULL)
    {
        if(arrayProcessingInfo->elementKind == writeArrayPrimitiveFunctionsPointer->_kind)
        {
            addToStream = writeArrayPrimitiveFunctionsPointer->_addToStream;
            break;
        }

        writeArrayPrimitiveFunctionsPointer++;
    }

    if(addToStream != NULL)
    {
        returnedValue = addToStream(stmt, dynamicData, arrayProcessingInfo, currentDimension);
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencesStorage(struct RTICdrTypeCode *typeCode,
        struct DDS_DynamicData *dynamicData, string &suffix,
        string &memberName, int &index, bool step)
{
    const char* const METHOD_NAME = "processSequencesStorage";
    bool returnedValue = false;
    list<arrayNode*>::iterator it;
    arrayNode *aNode = NULL;
    RTICdrTypeCode *elementType = NULL;
    RTICdrTCKind elementKind;

    if(typeCode != NULL && (dynamicData != NULL || step))
    {
        // Search array statement.
        for(it = m_sequences.begin(); it != m_sequences.end(); it++)
        {
            if(suffix.compare((*it)->m_tableName) == 0)
            {
                aNode = (*it);
                break;
            }
        }

        if(it != m_sequences.end())
        {
            if(aNode != NULL && aNode->m_stmt != NULL)
            {
                if(!step)

                {
                    elementType = RTICdrTypeCode_get_content_type(typeCode);

                    if(elementType != NULL)
                    {
                        if(RTICdrTypeCode_get_kind(elementType, &elementKind) == RTI_TRUE)
                        {
                            if(processSequenceElementsStorage(aNode->m_stmt, aNode->m_ref, memberName,
                                        elementKind, dynamicData))
                            {
                                sqlite3_bind_int(m_addStmt, index++, aNode->m_ref++);
                                returnedValue = true;
                            }
                        }
                    }
                    else
                    {
                        logError(m_log, "Cannot obtain the element type");
                    }
                }
                else
                {
                    sqlite3_bind_null(m_addStmt, index++);
                    returnedValue = true;
                }
            }
            else
            {
                logError(m_log, "Bad array statement for %s", suffix.c_str());
            }
        }
        else
        {
            logError(m_log, "Cannot find the array statement of %s", suffix.c_str());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequenceElementsStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        RTICdrTCKind elementKind, struct DDS_DynamicData *dynamicData)
{
    const char* const METHOD_NAME = "processSequenceElementsStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicData != NULL)
    {
        if(kindIsPrimitive(elementKind))
        {
            returnedValue = processSequencePrimitiveStorage(stmt, ref, memberName,
                    elementKind,
                    dynamicData);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencePrimitiveStorage(sqlite3_stmt *stmt, int ref,
        string &memberName, RTICdrTCKind elementKind,
        struct DDS_DynamicData *dynamicData)
{
    bool returnedValue = false;
    writeSequencePrimitiveFunctions *writeSequencePrimitiveFunctionsPointer =
        DynamicDataDB::writeSequencePrimitiveFunctionsMap;
    bool (*addToStream)(sqlite3_stmt *stmt, int ref,
            string &memberName, struct DDS_DynamicData *dynamicDataObject) = NULL;

    while(writeSequencePrimitiveFunctionsPointer->_kind != RTI_CDR_TK_NULL)
    {
        if(elementKind == writeSequencePrimitiveFunctionsPointer->_kind)
        {
            addToStream = writeSequencePrimitiveFunctionsPointer->_addToStream;
            break;
        }

        writeSequencePrimitiveFunctionsPointer++;
    }

    if(addToStream != NULL)
    {
        returnedValue = addToStream(stmt, ref, memberName, dynamicData);
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveStorage(struct RTICdrTypeCode *primitiveInfo, string &primitiveName,
        struct DDS_DynamicData *primitiveData, int &index, bool step)
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
        {
            if(!step)
                returnedValue = addToStream(m_addStmt, primitiveData, primitiveName, index);
            else
            {
                sqlite3_bind_null(m_addStmt, index++);
                returnedValue = true;
            }
        }
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
    const char* const METHOD_NAME = "addCharStorage";
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

        if(value != NULL)
        {
            sqlite3_bind_text(stmt, index++, value, stringLength, SQLITE_TRANSIENT);
            DDS_String_free(value);
            returnedValue = true;
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addFloatStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addFloatStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Float value;
        if(DDS_DynamicData_get_float(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_double(stmt, index++, (double)value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the float field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addDoubleStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addDoubleStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Double value;
        if(DDS_DynamicData_get_double(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_double(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the double field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addEnumStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addEnumStorage";
    bool returnedValue = false;
    DDS_TypeCode *enumTypeCode = NULL;
    DDS_Long ordinal;
    DDS_UnsignedLong eindex;
    DDS_ExceptionCode_t exception = DDS_NO_EXCEPTION_CODE;
    const char *label;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_DynamicData_get_long(dynamicDataObject, &ordinal, (char*)name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

        if(DDS_DynamicData_get_member_type(dynamicDataObject, (const DDS_TypeCode**)&enumTypeCode, name.c_str(),
                    DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            eindex = DDS_TypeCode_find_member_by_label(enumTypeCode, ordinal, &exception);

            if(exception == DDS_NO_EXCEPTION_CODE)
            {
                label = DDS_TypeCode_member_name(enumTypeCode, eindex, &exception);

                if(exception == DDS_NO_EXCEPTION_CODE)
                {
                    sqlite3_bind_text(stmt, index++, label, strlen(label), SQLITE_STATIC);
                    returnedValue = true;
                }
            }
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addBoolStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        string &name, int &index)
{
    const char* const METHOD_NAME = "addBoolStorage";
    bool returnedValue = false;

    if(stmt != NULL && dynamicDataObject != NULL && !name.empty())
    {
        DDS_Boolean value;

        if(DDS_DynamicData_get_boolean(dynamicDataObject, &value,
                name.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
        {
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        else
        {
            printError("Cannot get the boolean field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addOctetArrayStorage";
    bool returnedValue = false;
    DDS_Octet *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Octet*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Octet)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Octet));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_octet_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addShortArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addShortArrayStorage";
    bool returnedValue = false;
    DDS_Short *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Short*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Short)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Short));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_short_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addUShortArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addUShortArrayStorage";
    bool returnedValue = false;
    DDS_UnsignedShort *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_UnsignedShort*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_UnsignedShort)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_UnsignedShort));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_ushort_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
                    arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addLongArrayStorage";
    bool returnedValue = false;
    DDS_Long *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Long*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Long)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Long));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_long_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addULongArrayStorage";
    bool returnedValue = false;
    DDS_UnsignedLong *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_UnsignedLong*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_UnsignedLong)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_UnsignedLong));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_ulong_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addLongLongArrayStorage";
    bool returnedValue = false;
    DDS_LongLong *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_LongLong*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_LongLong)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_LongLong));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_longlong_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int64(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongLongArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addULongLongArrayStorage";
    bool returnedValue = false;
    DDS_UnsignedLongLong *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_UnsignedLongLong*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_UnsignedLongLong)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_UnsignedLongLong));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_ulonglong_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int64(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addCharArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addCharArrayStorage";
    bool returnedValue = false;
    DDS_Char *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Char*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Char)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Char));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_char_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_text(stmt, currentDimension + 3, &(auxPointerBuffer[count]), 1, SQLITE_STATIC); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addFloatArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addFloatArrayStorage";
    bool returnedValue = false;
    DDS_Float *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Float*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Float)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Float));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_float_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_double(stmt, currentDimension + 3, (double)auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addDoubleArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addDoubleArrayStorage";
    bool returnedValue = false;
    DDS_Double *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Double*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Double)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Double));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_double_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_double(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addEnumArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
 arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addEnumArrayStorage";
    bool returnedValue = false;
    DDS_Long *auxPointerBuffer = NULL;
    DDS_UnsignedLong eindex, length;
    DDS_ExceptionCode_t exception = DDS_NO_EXCEPTION_CODE;
    string label;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Long*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Long)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Long));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_long_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName, DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                eindex = DDS_TypeCode_find_member_by_label((struct DDS_TypeCode*)arrayProcessingInfo->elementType,
                        auxPointerBuffer[count], &exception);

                if(exception == DDS_NO_EXCEPTION_CODE)
                {
                    label = DDS_TypeCode_member_name((struct DDS_TypeCode*)arrayProcessingInfo->elementType, eindex, &exception);

                    if(exception == DDS_NO_EXCEPTION_CODE)
                    {
                        if(sqlite3_reset(stmt) == SQLITE_OK)
                        {
                            sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                            sqlite3_bind_text(stmt, currentDimension + 3, label.c_str(), label.length(), SQLITE_STATIC); // +1 saltando campo de referencia.

                            if(sqlite3_step(stmt) != SQLITE_DONE)
                                printError("Cannot step the statement");
                        }
                        else
                            printError("Cannot reset the statement");
                    }
                }
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addBoolArrayStorage(sqlite3_stmt *stmt, struct DDS_DynamicData *dynamicDataObject,
        arrayProcessInfo *arrayProcessingInfo, RTICdrUnsignedLong currentDimension)
{
    const char* const METHOD_NAME = "addBoolArrayStorage";
    bool returnedValue = false;
    DDS_Boolean *auxPointerBuffer = NULL;
    DDS_UnsignedLong length;

    if(stmt != NULL && dynamicDataObject != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (DDS_Boolean*)arrayProcessingInfo->buffer;
        
        if(auxPointerBuffer == NULL)
        {
            RTIOsapiHeap_allocateBufferAligned((void**)&auxPointerBuffer, sizeof(DDS_Boolean)*arrayProcessingInfo->numberOfElements,
                    sizeof(DDS_Boolean));

            if(auxPointerBuffer != NULL)
            {
                length = arrayProcessingInfo->numberOfElements;
                DDS_DynamicData_get_boolean_array(dynamicDataObject, auxPointerBuffer, &length, arrayProcessingInfo->arrayName,
                        DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                    sqlite3_bind_int(stmt, currentDimension + 3, auxPointerBuffer[count]); // +1 saltando campo de referencia.

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                        printError("Cannot step the statement");
                }
                else
                    printError("Cannot reset the statement");
            }
            arrayProcessingInfo->pointer += arrayProcessingInfo->currentDimensionIndex;
            returnedValue = true;
        }
        else
        {
            printError("Cannot allocate buffer");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addOctetSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_OctetSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_OctetSeq_initialize(&values);
            DDS_OctetSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_octet_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_OctetSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_OctetSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addShortSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addShortSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_ShortSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_ShortSeq_initialize(&values);
            DDS_ShortSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_short_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_ShortSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_ShortSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addUShortSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addUShortSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_UnsignedShortSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_UnsignedShortSeq_initialize(&values);
            DDS_UnsignedShortSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_ushort_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_UnsignedShortSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_UnsignedShortSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addLongSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_LongSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_LongSeq_initialize(&values);
            DDS_LongSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_long_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_LongSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_LongSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addULongSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_UnsignedLongSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_UnsignedLongSeq_initialize(&values);
            DDS_UnsignedLongSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_ulong_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_UnsignedLongSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_UnsignedLongSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongLongSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addLongLongSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_LongLongSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_LongLongSeq_initialize(&values);
            DDS_LongLongSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_longlong_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int64(stmt, 3, *DDS_LongLongSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_LongLongSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongLongSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addULongLongSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_UnsignedLongLongSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_UnsignedLongLongSeq_initialize(&values);
            DDS_UnsignedLongLongSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_ulonglong_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int64(stmt, 3, *DDS_UnsignedLongLongSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_UnsignedLongLongSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addCharSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addCharSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_CharSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_CharSeq_initialize(&values);
            DDS_CharSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_char_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_text(stmt, 3, DDS_CharSeq_get_reference(&values, count), 1, SQLITE_STATIC);

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_CharSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addFloatSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addFloatSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_FloatSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_FloatSeq_initialize(&values);
            DDS_FloatSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_float_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_double(stmt, 3, (double)(*DDS_FloatSeq_get_reference(&values, count)));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_FloatSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addDoubleSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addDoubleSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_DoubleSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_DoubleSeq_initialize(&values);
            DDS_DoubleSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_double_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_double(stmt, 3, *DDS_DoubleSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_DoubleSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addEnumSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addEnumSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_LongSeq ordinals;
    DDS_Long eindex;
    DDS_TypeCode *sequenceTypeCode = NULL, *enumTypeCode = NULL;
    DDS_ExceptionCode_t exception = DDS_NO_EXCEPTION_CODE;
    string label;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            if(DDS_DynamicData_get_member_type(dynamicDataObject, (const struct DDS_TypeCode**)&sequenceTypeCode,
                        memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED) == DDS_RETCODE_OK)
            {
                enumTypeCode = DDS_TypeCode_content_type(sequenceTypeCode, &exception);

                if(exception == DDS_NO_EXCEPTION_CODE)
                {
                    DDS_LongSeq_initialize(&ordinals);
                    DDS_LongSeq_ensure_length(&ordinals, memberInfo.element_count, memberInfo.element_count);
                    DDS_DynamicData_get_long_seq(dynamicDataObject, &ordinals, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

                    returnedValue = true;
                    for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
                    {
                        if(sqlite3_reset(stmt) == SQLITE_OK)
                        {
                            DDS_UnsignedLong ordinal = *DDS_LongSeq_get_reference(&ordinals, count);
                            eindex = DDS_TypeCode_find_member_by_label(enumTypeCode, ordinal, &exception);

                                if(exception == DDS_NO_EXCEPTION_CODE)
                                {
                                    label = DDS_TypeCode_member_name(enumTypeCode, eindex, &exception);

                                    if(exception == DDS_NO_EXCEPTION_CODE)
                                    {
                                        sqlite3_bind_int(stmt, 1, ref);
                                        sqlite3_bind_int(stmt, 2, count);
                                        sqlite3_bind_text(stmt, 3, label.c_str(), label.length(), SQLITE_STATIC);

                                        if(sqlite3_step(stmt) != SQLITE_DONE)
                                        {
                                            printError("Cannot step the statement");
                                            returnedValue = false;
                                        }
                                    }
                                }
                        }
                        else
                        {
                            printError("Cannot reset statement");
                            returnedValue = false;
                        }
                    }

                    DDS_LongSeq_finalize(&ordinals);
                }
            }
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addBoolSequenceStorage(sqlite3_stmt *stmt, int ref, string &memberName,
        struct DDS_DynamicData *dynamicDataObject)
{
    const char* const METHOD_NAME = "addBoolSequenceStorage";
    bool returnedValue = false;
    DDS_DynamicDataMemberInfo memberInfo;
    struct DDS_BooleanSeq values;

    if(stmt != NULL && dynamicDataObject != NULL)
    {
        if(DDS_DynamicData_get_member_info(dynamicDataObject, &memberInfo, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED)
                == DDS_RETCODE_OK)
        {
            DDS_BooleanSeq_initialize(&values);
            DDS_BooleanSeq_ensure_length(&values, memberInfo.element_count, memberInfo.element_count);
            DDS_DynamicData_get_boolean_seq(dynamicDataObject, &values, memberName.c_str(), DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < memberInfo.element_count); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, *DDS_BooleanSeq_get_reference(&values, count));

                    if(sqlite3_step(stmt) != SQLITE_DONE)
                    {
                        printError("Cannot step the statement");
                        returnedValue = false;
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }

            DDS_BooleanSeq_finalize(&values);
        }
        else
        {
            printError("Cannot get member info");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}
