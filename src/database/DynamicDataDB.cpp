#include "database/DynamicDataDB.h"
#include "log/eProsimaLog.h"
#include "fastcdr/exceptions/Exception.h"
#include "cdr/StructTypeCode.h"
#include "cdr/ArrayTypeCode.h"
#include "cdr/EnumTypeCode.h"
#include "cdr/SequenceTypeCode.h"
#include "cdr/UnionTypeCode.h"
#include "cdr/PrimitiveTypeCode.h"

#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif

static const char* const CLASS_NAME = "DynamicDataDB";

using namespace eprosima::fastcdr;
using namespace eprosima;
using namespace std;

DynamicDataDB::DynamicDataDB(eProsimaLog &log, sqlite3 *databaseH, string &tableName,
        const TypeCode *typeCode) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_tableName(tableName), m_addStmt(NULL)
{
    const char* const METHOD_NAME = "DynamicDataDB";
    const char* const TABLE_CHECK_INIT = "SELECT name FROM sqlite_master WHERE name='";
    const char* const TABLE_DROP_INIT = "DROP TABLE ";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;
    string TABLE_CHECK, TABLE_DROP, TABLE_CREATE, DYNAMICDATA_ADD;

    // Erase '::' from m_tableName.
    std::replace(m_tableName.begin(), m_tableName.end(), ':', '_');
    // Erase '.' from m_tableName;
    std::replace(m_tableName.begin(), m_tableName.end(), '.', '_');
    // Erase '-' from m_tableName;
    std::replace(m_tableName.begin(), m_tableName.end(), '-', '_');

    TABLE_CHECK = TABLE_CHECK_INIT;
    TABLE_CHECK.append(m_tableName);
    TABLE_CHECK += '\'';

    TABLE_DROP = TABLE_DROP_INIT;
    TABLE_DROP += m_tableName;

    if(SQLITE_PREPARE(m_databaseH, TABLE_CHECK.c_str(), (int)TABLE_CHECK.length(), &stmt, NULL) == SQLITE_OK)
    {
        ret = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(ret == SQLITE_ROW)
        {
            if(SQLITE_PREPARE(m_databaseH, TABLE_DROP.c_str(), (int)TABLE_DROP.length(), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) != SQLITE_DONE)
                    logError(m_log, "Cannot drop the %s table", m_tableName.c_str());

                sqlite3_finalize(stmt);
            }
        }

        if(createInitialStatements(TABLE_CREATE, DYNAMICDATA_ADD, typeCode))
        {
            if(SQLITE_PREPARE(m_databaseH, TABLE_CREATE.c_str(), (int)TABLE_CREATE.length(), &stmt, NULL) == SQLITE_OK)
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
        else
        {
            logError(m_log, "Cannot create initial statement for %s table", m_tableName.c_str());
        }

        //printf("%s\n", TABLE_CREATE.c_str());
        //printf("%s\n", DYNAMICDATA_ADD.c_str());

        if(m_ready)
        {
            m_ready = false;

            if(SQLITE_PREPARE(m_databaseH, DYNAMICDATA_ADD.c_str(), (int)DYNAMICDATA_ADD.length(), &m_addStmt, NULL) == SQLITE_OK)
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
    size_t foundHere = 0;
    // Erase spaces.
    while((foundHere = tableName.find(' ', lookHere)) != string::npos)
    {
        tableName.replace(foundHere, 1, 1, '_');
        lookHere = foundHere + 1;
    }
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

DynamicDataDB::writePrimitiveInitialStatementsFunctions DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap[] =
{
    {TypeCode::KIND_OCTET, DynamicDataDB::addTinyIntInitialStatements},
    {TypeCode::KIND_SHORT, DynamicDataDB::addShortInitialStatements},
    {TypeCode::KIND_USHORT, DynamicDataDB::addUShortInitialStatements},
    {TypeCode::KIND_LONG, DynamicDataDB::addIntInitialStatements},
    {TypeCode::KIND_ULONG, DynamicDataDB::addUIntInitialStatements},
    {TypeCode::KIND_LONGLONG, DynamicDataDB::addBigIntInitialStatements},
    {TypeCode::KIND_ULONGLONG, DynamicDataDB::addUBigIntInitialStatements},
    {TypeCode::KIND_CHAR, DynamicDataDB::addCharInitialStatements},
    {TypeCode::KIND_STRING, DynamicDataDB::addTextInitialStatements},
    {TypeCode::KIND_FLOAT, DynamicDataDB::addFloatInitialStatements},
    {TypeCode::KIND_DOUBLE, DynamicDataDB::addDoubleInitialStatements},
    {TypeCode::KIND_BOOLEAN, DynamicDataDB::addTinyIntInitialStatements},
    {TypeCode::KIND_NULL, NULL}
};

DynamicDataDB::writePrimitiveStorageFunctions DynamicDataDB::writePrimitiveStorageFunctionsMap[] =
{
    {TypeCode::KIND_OCTET, DynamicDataDB::addOctetStorage},
    {TypeCode::KIND_SHORT, DynamicDataDB::addShortStorage},
    {TypeCode::KIND_USHORT, DynamicDataDB::addUShortStorage},
    {TypeCode::KIND_LONG, DynamicDataDB::addLongStorage},
    {TypeCode::KIND_ULONG, DynamicDataDB::addULongStorage},
    {TypeCode::KIND_LONGLONG, DynamicDataDB::addLongLongStorage},
    {TypeCode::KIND_ULONGLONG, DynamicDataDB::addULongLongStorage},
    {TypeCode::KIND_CHAR, DynamicDataDB::addCharStorage},
    {TypeCode::KIND_STRING, DynamicDataDB::addStringStorage},
    {TypeCode::KIND_FLOAT, DynamicDataDB::addFloatStorage},
    {TypeCode::KIND_DOUBLE, DynamicDataDB::addDoubleStorage},
    {TypeCode::KIND_BOOLEAN, DynamicDataDB::addBoolStorage},
    {TypeCode::KIND_NULL, NULL}
};

DynamicDataDB::writeArrayPrimitiveFunctions DynamicDataDB::writeArrayPrimitiveFunctionsMap[] =
{
    {TypeCode::KIND_OCTET, DynamicDataDB::addOctetArrayStorage},
    {TypeCode::KIND_SHORT, DynamicDataDB::addShortArrayStorage},
    {TypeCode::KIND_USHORT, DynamicDataDB::addUShortArrayStorage},
    {TypeCode::KIND_LONG, DynamicDataDB::addLongArrayStorage},
    {TypeCode::KIND_ULONG, DynamicDataDB::addULongArrayStorage},
    {TypeCode::KIND_LONGLONG, DynamicDataDB::addLongLongArrayStorage},
    {TypeCode::KIND_ULONGLONG, DynamicDataDB::addULongLongArrayStorage},
    {TypeCode::KIND_CHAR, DynamicDataDB::addCharArrayStorage},
    {TypeCode::KIND_FLOAT, DynamicDataDB::addFloatArrayStorage},
    {TypeCode::KIND_DOUBLE, DynamicDataDB::addDoubleArrayStorage},
    {TypeCode::KIND_BOOLEAN, DynamicDataDB::addBoolArrayStorage},
    {TypeCode::KIND_NULL, NULL}
};

DynamicDataDB::writeSequencePrimitiveFunctions DynamicDataDB::writeSequencePrimitiveFunctionsMap[] =
{
    {TypeCode::KIND_OCTET, DynamicDataDB::addOctetSequenceStorage},
    {TypeCode::KIND_SHORT, DynamicDataDB::addShortSequenceStorage},
    {TypeCode::KIND_USHORT, DynamicDataDB::addUShortSequenceStorage},
    {TypeCode::KIND_LONG, DynamicDataDB::addLongSequenceStorage},
    {TypeCode::KIND_ULONG, DynamicDataDB::addULongSequenceStorage},
    {TypeCode::KIND_LONGLONG, DynamicDataDB::addLongLongSequenceStorage},
    {TypeCode::KIND_ULONGLONG, DynamicDataDB::addULongLongSequenceStorage},
    {TypeCode::KIND_CHAR, DynamicDataDB::addCharSequenceStorage},
    {TypeCode::KIND_FLOAT, DynamicDataDB::addFloatSequenceStorage},
    {TypeCode::KIND_DOUBLE, DynamicDataDB::addDoubleSequenceStorage},
    {TypeCode::KIND_BOOLEAN, DynamicDataDB::addBoolSequenceStorage},
    {TypeCode::KIND_NULL, NULL}
};

bool DynamicDataDB::createInitialStatements(string &table_create, string &dynamicDataAdd,
        const TypeCode *typeCode)
{
    bool returnedValue = false;
    string suffix = "";

    table_create = "CREATE TABLE ";
    table_create += m_tableName;
    table_create += " (message_id INT, sniffer_timestamp_sec INT, sniffer_timestamp_usec INT, " \
                     "ip_src VARCHAR(15), ip_dst VARCHAR(15), " \
                     "src_rtps_host_id UNSIGNED INT, src_rtps_app_id UNSIGNED INT, src_rtps_instance_id UNSIGNED INT, " \
                     "src_timestamp_sec INT, src_timestamp_nanosec INT, " \
                     "dst_rtps_host_id UNSIGNED INT, dst_rtps_app_id UNSIGNED INT, dst_rtps_instance_id UNSIGNED INT";

    dynamicDataAdd = "INSERT INTO ";
    dynamicDataAdd += m_tableName;
    dynamicDataAdd += " VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?";

    if(typeCode->getKind() == TypeCode::KIND_STRUCT)
        returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, dynamic_cast<const StructTypeCode*>(typeCode), suffix);

    table_create += ", PRIMARY KEY(message_id))";
    dynamicDataAdd += ")";

    return returnedValue;
}

bool DynamicDataDB::processStructsInitialStatements(string &table_create, string &dynamicDataAdd,
        const StructTypeCode *structTC, string &suffix)
{
    const char* const METHOD_NAME = "processStructsInitialStatements";
    bool returnedValue = false;

    if(structTC != NULL)
    {
        returnedValue = true;
        for(uint32_t count = 0; returnedValue && (count < structTC->getMemberCount()); ++count)
        {
            const Member *memberInfo = structTC->getMember(count);

            if(memberInfo != NULL)
            {
                returnedValue = processMembersInitialStatements(table_create, dynamicDataAdd,
                        memberInfo, suffix);
            }
            else
            {
                logError(m_log, "Cannot obtain info about member %d", count);
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processUnionsInitialStatements(string &table_create, string &dynamicDataAdd,
        const UnionTypeCode *unionTC, string &suffix)
{
    const char* const METHOD_NAME = "processUnionsInitialStatements";
    bool returnedValue = false;
    string smemberName;
    string newSuffix = suffix;

    if(unionTC != NULL)
    {
        newSuffix += "discriminator";
        table_create += ", ";
        table_create += newSuffix;
        table_create += " INT";
        dynamicDataAdd += ", ?";

        returnedValue = true;
        for(uint32_t count = 0; returnedValue && (count < unionTC->getMemberCount()); count ++)
        {
            const Member *memberInfo = unionTC->getMember(count);

            if(memberInfo != NULL)
            {
                returnedValue = processMembersInitialStatements(table_create, dynamicDataAdd,
                        memberInfo, suffix);
            }
            else
            {
                logError(m_log, "Cannot obtain info about member %d", count);
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersInitialStatements(string &table_create, string &dynamicDataAdd,
        const Member *memberInfo, string &suffix)
{
    const char* const METHOD_NAME = "processMembersInitialStatements";
    bool returnedValue = false;
    string newSuffix;

    if(memberInfo != NULL)
    {
        const TypeCode *mTypeCode = memberInfo->getTypeCode();

        if(mTypeCode != NULL)
        {
            if(mTypeCode->getKind() == TypeCode::KIND_STRUCT)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                newSuffix += "_";
                returnedValue = processStructsInitialStatements(table_create, dynamicDataAdd, dynamic_cast<const StructTypeCode*>(mTypeCode), newSuffix);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_UNION)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                newSuffix += "_";
                returnedValue = processUnionsInitialStatements(table_create, dynamicDataAdd, dynamic_cast<const UnionTypeCode*>(mTypeCode), newSuffix);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_ARRAY)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                returnedValue = processArraysInitialStatements(table_create, dynamicDataAdd, dynamic_cast<const ArrayTypeCode*>(mTypeCode), newSuffix);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_SEQUENCE)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                returnedValue = processSequencesInitialStatements(table_create, dynamicDataAdd, dynamic_cast<const SequenceTypeCode*>(mTypeCode), newSuffix);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_ENUM)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                returnedValue = addEnumInitialStatements(newSuffix, table_create, dynamicDataAdd);
            }
            else if(TypeCode::kindIsPrimitive(mTypeCode->getKind()))
            {
                returnedValue = processPrimitiveInitialStatements(table_create, dynamicDataAdd,
                        dynamic_cast<const PrimitiveTypeCode*>(mTypeCode), memberInfo->getName(), suffix);
            }
            else
            {
                logError(m_log, "The kind %d is not recognize", mTypeCode->getKind());
            }
        }
        else
        {
            logError(m_log, "The member %s cannot contains a typecode", memberInfo->getName().c_str());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveInitialStatements(string &table_create, string &dynamicDataAdd,
        const PrimitiveTypeCode *primitiveInfo, const string &primitiveName, string &suffix)
{
    bool returnedValue = false;
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    string newName;

    if(primitiveInfo != NULL)
    {
        while(writePrimitiveInitialStatementsFunctionsPointer->_kind != TypeCode::KIND_NULL)
        {
            if(primitiveInfo->getKind() == writePrimitiveInitialStatementsFunctionsPointer->_kind)
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

bool DynamicDataDB::processArraysInitialStatements(string &table_create, string &dynamicDataAdd,
        const ArrayTypeCode *typeCode, string &suffix)
{
    // suffix contains the name of the new table.
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArraysInitialStatements";
    string TABLE_CREATE = "CREATE TABLE ";
    string TABLE_INSERT = "INSERT INTO ";
    string TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='";
    string TABLE_DROP = "DROP TABLE ";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;

    if(typeCode != NULL)
    {
        TABLE_CREATE += m_tableName;
        TABLE_CREATE += "_";
        TABLE_CREATE += suffix;
        TABLE_CREATE += " (";
        TABLE_CREATE += suffix;
        TABLE_CREATE += "_id INT";
        TABLE_INSERT += m_tableName;
        TABLE_INSERT += "_";
        TABLE_INSERT += suffix;
        TABLE_INSERT += " VALUES(?";
        TABLE_CHECK += m_tableName;
        TABLE_CHECK += "_";
        TABLE_CHECK += suffix;
        TABLE_CHECK += "'";
        TABLE_DROP += m_tableName;
        TABLE_DROP += "_";
        TABLE_DROP += suffix;

        if(processDimensionsInitialStatements(TABLE_CREATE, TABLE_INSERT, typeCode,
                    suffix, 0))
        {
            TABLE_CREATE += ")";
            TABLE_INSERT += ")";

            //printf("%s\n", TABLE_CREATE.c_str());
            //printf("%s\n", TABLE_INSERT.c_str());

            if(SQLITE_PREPARE(m_databaseH, TABLE_CHECK.c_str(), (int)TABLE_CHECK.length(), &stmt, NULL) == SQLITE_OK)
            {
                ret = sqlite3_step(stmt);
                sqlite3_finalize(stmt);

                if(ret == SQLITE_ROW)
                {
                    if(SQLITE_PREPARE(m_databaseH, TABLE_DROP.c_str(), (int)TABLE_DROP.length(), &stmt, NULL) == SQLITE_OK)
                    {
                        if(sqlite3_step(stmt) != SQLITE_DONE)
                            logError(m_log, "Cannot drop the %s table", m_tableName.c_str());

                        sqlite3_finalize(stmt);
                    }
                }

                if(SQLITE_PREPARE(m_databaseH, TABLE_CREATE.c_str(), (int)TABLE_CREATE.length(), &stmt, NULL) == SQLITE_OK)
                {
                    if(sqlite3_step(stmt) == SQLITE_DONE)
                    {
                        sqlite3_finalize(stmt);

                        if(SQLITE_PREPARE(m_databaseH, TABLE_INSERT.c_str(), (int)TABLE_INSERT.length(), &stmt, NULL) == SQLITE_OK)
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

        table_create += ", ";
        table_create += suffix;
        table_create += "_id";
        table_create += " INT";
        dynamicDataAdd += ", ?";
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processDimensionsInitialStatements(string &table_create, string &dynamicDataAdd,
        const ArrayTypeCode *typeCode, string &suffix, uint32_t currentDimension)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processDimensionsInitialStatements";
    ostringstream field;

    if(typeCode != NULL)
    {
        field << "index_" << currentDimension;

        table_create += ", ";
        table_create += field.str();
        table_create += " INT";
        dynamicDataAdd += ", ?";

        if(currentDimension == typeCode->getDimensionCount() -1)
        {
            returnedValue = processArrayElementsInitialStatements(table_create, dynamicDataAdd,
                    typeCode);
        }
        else
        {
            returnedValue = processDimensionsInitialStatements(table_create, dynamicDataAdd,
                    typeCode, suffix, currentDimension + 1);
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayElementsInitialStatements(string &table_create, string &dynamicDataAdd,
        const ArrayTypeCode *typeCode)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArrayElementsInitialStatements";
    const TypeCode *elementType = NULL;

    if(typeCode != NULL)
    {
        elementType = typeCode->getContentTypeCode();

        if(elementType != NULL)
        {
            if(elementType->getKind() == TypeCode::KIND_ENUM)
            {
                std::string value = "value";
                returnedValue = addEnumInitialStatements(value, table_create, dynamicDataAdd);
            }
            else if(TypeCode::kindIsPrimitive(elementType->getKind()))
            {
                returnedValue = processArrayPrimitiveInitialStatements(table_create,
                        dynamicDataAdd, dynamic_cast<const PrimitiveTypeCode*>(elementType));
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
        const PrimitiveTypeCode *typeCode)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processArrayPrimitiveInitialStatements";
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    string value = "value";

    if(typeCode != NULL)
    {
        while(writePrimitiveInitialStatementsFunctionsPointer->_kind != TypeCode::KIND_NULL)
        {
            if(typeCode->getKind() == writePrimitiveInitialStatementsFunctionsPointer->_kind)
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
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencesInitialStatements(string &table_create, string &dynamicDataAdd,
        const SequenceTypeCode *typeCode, string &suffix)
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
        TABLE_CREATE += m_tableName;
        TABLE_CREATE += "_";
        TABLE_CREATE += suffix;
        TABLE_CREATE += " (";
        TABLE_CREATE += suffix;
        TABLE_CREATE += "_id INT, index_0 INT";
        TABLE_INSERT += m_tableName;
        TABLE_INSERT += "_";
        TABLE_INSERT += suffix;
        TABLE_INSERT += " VALUES(?, ?";
        TABLE_CHECK += m_tableName;
        TABLE_CHECK += "_";
        TABLE_CHECK += suffix;
        TABLE_CHECK += "'";
        TABLE_DROP += m_tableName;
        TABLE_DROP += "_";
        TABLE_DROP += suffix;

        if(processSequenceElementsInitialStatements(TABLE_CREATE, TABLE_INSERT, typeCode,
                    newSuffix))
        {
            TABLE_CREATE += ")";
            TABLE_INSERT += ")";

            //printf("%s\n", TABLE_CREATE.c_str());
            //printf("%s\n", TABLE_INSERT.c_str());

            if(SQLITE_PREPARE(m_databaseH, TABLE_CHECK.c_str(), (int)TABLE_CHECK.length(), &stmt, NULL) == SQLITE_OK)
            {
                ret = sqlite3_step(stmt);
                sqlite3_finalize(stmt);

                if(ret == SQLITE_ROW)
                {
                    if(SQLITE_PREPARE(m_databaseH, TABLE_DROP.c_str(), (int)TABLE_DROP.length(), &stmt, NULL) == SQLITE_OK)
                    {
                        if(sqlite3_step(stmt) != SQLITE_DONE)
                            logError(m_log, "Cannot drop the %s table", m_tableName.c_str());

                        sqlite3_finalize(stmt);
                    }
                }

                if(SQLITE_PREPARE(m_databaseH, TABLE_CREATE.c_str(), (int)TABLE_CREATE.length(), &stmt, NULL) == SQLITE_OK)
                {
                    if(sqlite3_step(stmt) == SQLITE_DONE)
                    {
                        sqlite3_finalize(stmt);

                        if(SQLITE_PREPARE(m_databaseH, TABLE_INSERT.c_str(), (int)TABLE_INSERT.length(), &stmt, NULL) == SQLITE_OK)
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
        table_create += "_id";
        table_create += " INT";
        dynamicDataAdd += ", ?";
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequenceElementsInitialStatements(string &table_create, string &dynamicDataAdd,
        const SequenceTypeCode *typeCode, string &suffix)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processSequenceElementsInitialStatements";
    const TypeCode *elementType = NULL;

    if(typeCode != NULL)
    {
        elementType = typeCode->getContentTypeCode();

        if(elementType != NULL)
        {
            if(elementType->getKind() == TypeCode::KIND_ENUM)
            {
                //returnedValue = addEnumInitialStatements(value, table_create, dynamicDataAdd);
            }
            else if(TypeCode::kindIsPrimitive(elementType->getKind()))
            {
                returnedValue = processSequencePrimitiveInitialStatements(table_create,
                        dynamicDataAdd, dynamic_cast<const PrimitiveTypeCode*>(elementType), suffix);
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
        const PrimitiveTypeCode *typeCode, string &suffix)
{
    bool returnedValue = false;
    const char* const METHOD_NAME = "processSequencePrimitiveInitialStatements";
    writePrimitiveInitialStatementsFunctions *writePrimitiveInitialStatementsFunctionsPointer =
        DynamicDataDB::writePrimitiveInitialStatementsFunctionsMap;
    bool (*addToStream)(string &memberName, string &table_create,
            string &dynamicDataAdd) = NULL;
    string value = "value";

    if(typeCode != NULL)
    {
        while(writePrimitiveInitialStatementsFunctionsPointer->_kind != TypeCode::KIND_NULL)
        {
            if(typeCode->getKind() == writePrimitiveInitialStatementsFunctionsPointer->_kind)
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
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processStructsStorage(const StructTypeCode *typeCode, Cdr &cdr,
        std::string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processStructsStorage";
    bool returnedValue = true;
    uint32_t membersNumber = 0, count = 0;
    const Member *memberInfo = NULL;

    if(typeCode != NULL)
    {
        // Get memberCount;
        membersNumber = typeCode->getMemberCount();

        for(; returnedValue && (count < membersNumber); count ++)
        {
            memberInfo = typeCode->getMember(count);

            if(memberInfo != NULL)
            {
                returnedValue = processMembersStorage(memberInfo, cdr,
                        suffix, index, step);
            }
            else
            {
                logError(m_log, "Cannot obtain info about member %d", count);
            }
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processUnionsStorage(const UnionTypeCode *typeCode, Cdr &cdr,
        std::string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processUnionsStorage";
    bool returnedValue = false;
    uint32_t membersNumber, memberMatch = 0;
    int32_t discriminator;
    bool discriminatorMatch = false;
    const UnionMember *memberInfo = NULL;

    if(typeCode != NULL)
    {
        try
        {
            cdr >> discriminator;

            membersNumber = typeCode->getMemberCount();
            sqlite3_bind_int(m_addStmt, index++, discriminator);

            // Search selected by discriminator.
            if(!step)
            {
                for(uint32_t count = 0; count < membersNumber; count ++)
                {
                    memberInfo = dynamic_cast<const UnionMember*>(typeCode->getMember(count));

                    if(memberInfo != NULL)
                    {
                        for(uint32_t lCount = 0; !discriminatorMatch && (lCount < memberInfo->getLabelCount()); ++lCount)
                        {
                            if(discriminator == memberInfo->getLabel(lCount))
                            {
                                discriminatorMatch = true;
                                memberMatch = count;
                            }
                        }
                    }
                    else
                    {
                        logError(m_log, "Cannot obtain info about member %d", count);
                    }
                }

                if(!discriminatorMatch)
                {
                    discriminatorMatch = true;
                    memberMatch = typeCode->getDefaultIndex();
                }
            }

            returnedValue = true;
            for(uint32_t count = 0; returnedValue && (count < membersNumber); count ++)
            {
                memberInfo = dynamic_cast<const UnionMember*>(typeCode->getMember(count));

                if(memberInfo != NULL)
                {
                    returnedValue = processMembersStorage(static_cast<const Member*>(memberInfo), cdr,
                            suffix, index, !discriminatorMatch || !(count == memberMatch));
                }
                else
                {
                    logError(m_log, "Cannot obtain info about member %d", count);
                }
            }
        }
        catch(exception::Exception &ex)
        {
            logError(m_log, "Exception: ", ex.what());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::storeDynamicData(const unsigned int npacket, const struct timeval &wts, string &ip_src, string &ip_dst,
        unsigned int hostId, unsigned int appId, unsigned int instanceId,
        unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId,
        const TypeCode *typeCode, Cdr &cdr)
{
    const char* const METHOD_NAME = "storeDynamicData";
    bool returnedValue = false;
    int index = 1;
    string suffix = "";

    if(m_ready)
    {
        if(typeCode != NULL)
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_int(m_addStmt, index++, npacket);
                sqlite3_bind_int(m_addStmt, index++, wts.tv_sec);
                sqlite3_bind_int(m_addStmt, index++, wts.tv_usec);
                sqlite3_bind_text(m_addStmt, index++, ip_src.c_str(), (int)ip_src.length(), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, index++, ip_dst.c_str(), (int)ip_dst.length(), SQLITE_STATIC);
                sqlite3_bind_int64(m_addStmt, index++, hostId);
                sqlite3_bind_int64(m_addStmt, index++, appId);
                sqlite3_bind_int64(m_addStmt, index++, instanceId);
                sqlite3_bind_int(m_addStmt, index++, sourceTmp.seconds);
                sqlite3_bind_int(m_addStmt, index++, sourceTmp.nanoseconds);

                if(destHostId != 0 || destAppId != 0 ||
                        destInstanceId != 0)
                {
                    sqlite3_bind_int64(m_addStmt, index++, destHostId);
                    sqlite3_bind_int64(m_addStmt, index++, destAppId);
                    sqlite3_bind_int64(m_addStmt, index++, destInstanceId);
                }
                else
                {
                    sqlite3_bind_null(m_addStmt, index++);
                    sqlite3_bind_null(m_addStmt, index++);
                    sqlite3_bind_null(m_addStmt, index++);
                }

                if(typeCode->getKind() == TypeCode::KIND_STRUCT)
                {
                    const StructTypeCode *structTypeCode = dynamic_cast<const StructTypeCode*>(typeCode);
                    returnedValue = processStructsStorage(structTypeCode, cdr, suffix, index, false);
                }

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
        else
        {
            logError(m_log, "Bad parameters");
        }
    }

    return returnedValue;
}

bool DynamicDataDB::processMembersStorage(const Member *memberInfo, Cdr &cdr,
        string &suffix, int &index, bool step)
{
    const char* const METHOD_NAME = "processMembersStorage";
    bool returnedValue = false;
    string newSuffix;

    if(memberInfo != NULL)
    {
        const TypeCode *mTypeCode = memberInfo->getTypeCode();

        if(mTypeCode != NULL)
        {
            if(mTypeCode->getKind() == TypeCode::KIND_STRUCT)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                newSuffix += "_";
                returnedValue = processStructsStorage(dynamic_cast<const StructTypeCode*>(mTypeCode), cdr,
                        newSuffix, index, step);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_UNION)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                newSuffix += "_";
                returnedValue = processUnionsStorage(dynamic_cast<const UnionTypeCode*>(mTypeCode), cdr,
                        newSuffix, index, step);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_ARRAY)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                returnedValue = processArraysStorage(dynamic_cast<const ArrayTypeCode*>(mTypeCode), cdr, newSuffix, memberInfo->getName(), index, step);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_SEQUENCE)
            {
                newSuffix = suffix;
                newSuffix += memberInfo->getName();
                returnedValue = processSequencesStorage(dynamic_cast<const SequenceTypeCode*>(mTypeCode), cdr, newSuffix, memberInfo->getName(), index, step);
            }
            else if(mTypeCode->getKind() == TypeCode::KIND_ENUM)
            {
                returnedValue = addEnumStorage(m_addStmt, dynamic_cast<const EnumTypeCode*>(mTypeCode), cdr, index, step);
            }
            else if(TypeCode::kindIsPrimitive(mTypeCode->getKind()))
            {
                returnedValue = processPrimitiveStorage(dynamic_cast<const PrimitiveTypeCode*>(mTypeCode), cdr, index, step);
            }
            else
            {
                logError(m_log, "The kind %d is not recognize", mTypeCode->getKind());
            }
        }
        else
        {
            logError(m_log, "The member %s cannot contains a typecode", memberInfo->getName().c_str());
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processPrimitiveStorage(const PrimitiveTypeCode *primitiveInfo,
        Cdr &cdr, int &index, bool step)
{
    bool returnedValue = false;

    if(!step)
    {
        writePrimitiveStorageFunctions *writePrimitiveStorageFunctionsPointer =
            DynamicDataDB::writePrimitiveStorageFunctionsMap;
        bool (*addToStream)(sqlite3_stmt *stmt, Cdr &cdr, int & index) = NULL;

        while(writePrimitiveStorageFunctionsPointer->_kind != TypeCode::KIND_NULL)
        {
            if(primitiveInfo->getKind() == writePrimitiveStorageFunctionsPointer->_kind)
            {
                addToStream = writePrimitiveStorageFunctionsPointer->_addToStream;
                break;
            }
            writePrimitiveStorageFunctionsPointer++;
        }

        if(addToStream != NULL)
        {
            returnedValue = addToStream(m_addStmt, cdr, index);
        }
    }
    else
    {
        sqlite3_bind_null(m_addStmt, index++);
        returnedValue = true;
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addOctetStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        uint8_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addShortStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addShortStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        int16_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addUShortStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addUShortStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        uint16_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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


bool DynamicDataDB::addLongStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addLongStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        int32_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addULongStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addULongStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        uint32_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addLongLongStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addLongLongStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        int64_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int64(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addULongLongStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addULongLongStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        uint64_t value;
        try
        {
            cdr >> value;
            sqlite3_bind_int64(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addCharStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addCharStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        char value = 0;
        try
        {
            cdr >> value;
            sqlite3_bind_text(stmt, index++, &value, 1, SQLITE_STATIC);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get the char field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addStringStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addStringStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        std::string value;

        try
        {
            cdr >> value;
            sqlite3_bind_text(stmt, index++, value.c_str(), (int)value.length(), SQLITE_TRANSIENT);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get the string field");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addFloatStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addFloatStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        float value;
        try
        {
            cdr >> value;
            sqlite3_bind_double(stmt, index++, (double)value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addDoubleStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addDoubleStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        double value;
        try
        {
            cdr >> value;
            sqlite3_bind_double(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addBoolStorage(sqlite3_stmt *stmt, Cdr &cdr, int &index)
{
    const char* const METHOD_NAME = "addBoolStorage";
    bool returnedValue = false;

    if(stmt != NULL)
    {
        uint8_t value;

        try
        {
            cdr >> value;
            sqlite3_bind_int(stmt, index++, value);
            returnedValue = true;
        }
        catch(exception::Exception &ex)
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

bool DynamicDataDB::addEnumStorage(sqlite3_stmt *stmt, const EnumTypeCode *enumTC, Cdr &cdr, int &index, bool step)
{
    const char* const METHOD_NAME = "addEnumStorage";
    bool returnedValue = false;

    if(stmt != NULL && enumTC != NULL)
    {
        if(!step)
        {
            int32_t ordinal;

            try
            {
                cdr >> ordinal;
                const EnumMember *member = enumTC->getMemberWithOrdinal(ordinal);

                if(member != NULL)
                {
                    sqlite3_bind_text(stmt, index++, member->getName().c_str(), (int)member->getName().length(), SQLITE_STATIC);
                    returnedValue = true;
                }
                else
                {
                    printError("Cannot find ordinal of the enumerator");
                }
            }
            catch(exception::Exception &ex)
            {
                printError("Cannot get the ordinal of the enumerator");
            }
        }
        else
        {
            sqlite3_bind_null(stmt, index++);
            returnedValue = true;
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArraysStorage(const ArrayTypeCode *typeCode, Cdr &cdr, string &suffix,
        const string &memberName, int &index, bool step)
{
    const char* const METHOD_NAME = "processArraysStorage";
    bool returnedValue = false;
    list<arrayNode*>::iterator it;
    arrayNode *aNode = NULL;
    arrayProcessInfo arrayProcessingInfo;

    if(typeCode != NULL)
    {
        arrayProcessingInfo.pointer = 0;
        arrayProcessingInfo.buffer = 0;
        arrayProcessingInfo.numberOfElements = 0;
        arrayProcessingInfo.currentDimensionProcess = 0;
        arrayProcessingInfo.arrayName = memberName;

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

                        if(processDimensionsStorage(aNode->m_stmt, typeCode, cdr,
                                    &arrayProcessingInfo, 0))
                        {
                            sqlite3_bind_int(m_addStmt, index++, aNode->m_ref++);
                            returnedValue = true;
                        }

                        if(arrayProcessingInfo.buffer != NULL)
                            free(arrayProcessingInfo.buffer);
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
        const ArrayTypeCode *typeCode, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "processDimensionsStorage";
    bool returnedValue = false;
    uint32_t dimensionIndex;

    if(stmt != NULL && typeCode != NULL &&
            arrayProcessingInfo != NULL)
    {
        dimensionIndex = typeCode->getDimension(currentDimension);

        if(currentDimension == arrayProcessingInfo->currentDimensionProcess)
        {
            if(arrayProcessingInfo->numberOfElements != 0)
                arrayProcessingInfo->numberOfElements *= dimensionIndex;
            else
                arrayProcessingInfo->numberOfElements = dimensionIndex;
            arrayProcessingInfo->currentDimensionProcess++;
        }

        if(currentDimension == typeCode->getDimensionCount() - 1)
        {
            arrayProcessingInfo->currentDimensionIndex = dimensionIndex;
            returnedValue = processArrayElementsStorage(stmt, typeCode, cdr,
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
                    returnedValue = processDimensionsStorage(stmt, typeCode, cdr,
                            arrayProcessingInfo, currentDimension + 1);
                }
                else
                {
                    logError(m_log, "Cannot reset statement from array %s", arrayProcessingInfo->arrayName.c_str());
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

bool DynamicDataDB::processArrayElementsStorage(sqlite3_stmt *stmt, const ArrayTypeCode* typeCode, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "processArrayElementsStorage";
    bool returnedValue = false;
    const TypeCode *elementType = NULL;

    if(stmt != NULL &&  typeCode != NULL && arrayProcessingInfo != NULL)
    {
        elementType = typeCode->getContentTypeCode();

        if(elementType != NULL)
        {
            if(elementType->getKind() == TypeCode::KIND_ENUM)
            {
                returnedValue = addEnumArrayStorage(stmt, dynamic_cast<const EnumTypeCode*>(elementType), cdr,
                        arrayProcessingInfo, currentDimension);
            }
            else if(TypeCode::kindIsPrimitive(elementType->getKind()))
            {
                returnedValue = processArrayPrimitiveStorage(stmt, dynamic_cast<const PrimitiveTypeCode*>(elementType), cdr,
                        arrayProcessingInfo, currentDimension);
            }
        }
        else
        {
            logError(m_log, "Cannot get the content typecode");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processArrayPrimitiveStorage(sqlite3_stmt *stmt, const PrimitiveTypeCode *typeCode, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    bool returnedValue = false;
    writeArrayPrimitiveFunctions *writeArrayPrimitiveFunctionsPointer =
        DynamicDataDB::writeArrayPrimitiveFunctionsMap;
    bool (*addToStream)(sqlite3_stmt *stmt, Cdr &cdr, arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension) = NULL;

    while(writeArrayPrimitiveFunctionsPointer->_kind != TypeCode::KIND_NULL)
    {
        if(typeCode->getKind() == writeArrayPrimitiveFunctionsPointer->_kind)
        {
            addToStream = writeArrayPrimitiveFunctionsPointer->_addToStream;
            break;
        }

        writeArrayPrimitiveFunctionsPointer++;
    }

    if(addToStream != NULL)
    {
        returnedValue = addToStream(stmt, cdr, arrayProcessingInfo, currentDimension);
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addOctetArrayStorage";
    bool returnedValue = false;
    uint8_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (uint8_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (uint8_t*)calloc(sizeof(uint8_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(uint8_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addShortArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addShortArrayStorage";
    bool returnedValue = false;
    int16_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (int16_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (int16_t*)calloc(sizeof(int16_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(int16_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addUShortArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addUShortArrayStorage";
    bool returnedValue = false;
    uint16_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (uint16_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (uint16_t*)calloc(sizeof(uint16_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(uint16_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addLongArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addLongArrayStorage";
    bool returnedValue = false;
    int32_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (int32_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (int32_t*)calloc(sizeof(int32_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(int32_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addULongArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addULongArrayStorage";
    bool returnedValue = false;
    uint32_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (uint32_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (uint32_t*)calloc(sizeof(uint32_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(uint32_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addLongLongArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addLongLongArrayStorage";
    bool returnedValue = false;
    int64_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (int64_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (int64_t*)calloc(sizeof(int64_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(int64_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addULongLongArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addULongLongArrayStorage";
    bool returnedValue = false;
    uint64_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (uint64_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (uint64_t*)calloc(sizeof(uint64_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(uint64_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addCharArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addCharArrayStorage";
    bool returnedValue = false;
    char *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (char*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (char*)calloc(sizeof(char)*arrayProcessingInfo->numberOfElements,
                    sizeof(char));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addFloatArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addFloatArrayStorage";
    bool returnedValue = false;
    float *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (float*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (float*)calloc(sizeof(float)*arrayProcessingInfo->numberOfElements, sizeof(float));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addDoubleArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addDoubleArrayStorage";
    bool returnedValue = false;
    double *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (double*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (double*)calloc(sizeof(double)*arrayProcessingInfo->numberOfElements, sizeof(double));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addBoolArrayStorage(sqlite3_stmt *stmt, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addBoolArrayStorage";
    bool returnedValue = false;
    uint8_t *auxPointerBuffer = NULL;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = reinterpret_cast<uint8_t*>(arrayProcessingInfo->buffer);

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (uint8_t*)calloc(sizeof(uint8_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(uint8_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
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

bool DynamicDataDB::addEnumArrayStorage(sqlite3_stmt *stmt, const EnumTypeCode *enumTC, Cdr &cdr,
        arrayProcessInfo *arrayProcessingInfo, uint32_t currentDimension)
{
    const char* const METHOD_NAME = "addEnumArrayStorage";
    bool returnedValue = false;
    int32_t *auxPointerBuffer = NULL;
    string label;

    if(stmt != NULL && arrayProcessingInfo != NULL)
    {
        auxPointerBuffer = (int32_t*)arrayProcessingInfo->buffer;

        if(auxPointerBuffer == NULL)
        {
            auxPointerBuffer = (int32_t*)calloc(sizeof(int32_t)*arrayProcessingInfo->numberOfElements,
                    sizeof(int32_t));

            if(auxPointerBuffer != NULL)
            {
                cdr.deserializeArray(auxPointerBuffer, arrayProcessingInfo->numberOfElements);
                arrayProcessingInfo->buffer = (void*)auxPointerBuffer;
            }
        }

        if(auxPointerBuffer != NULL)
        {
            for(unsigned int count = arrayProcessingInfo->pointer; count < (arrayProcessingInfo->pointer +
                        arrayProcessingInfo->currentDimensionIndex); count++)
            {
                const EnumMember *member = enumTC->getMemberWithOrdinal(auxPointerBuffer[count]);

                if(member != NULL)
                {
                    if(sqlite3_reset(stmt) == SQLITE_OK)
                    {
                        sqlite3_bind_int(stmt, currentDimension + 2, count - arrayProcessingInfo->pointer);
                        sqlite3_bind_text(stmt, currentDimension + 3, member->getName().c_str(), (int)member->getName().length(), SQLITE_STATIC); // +1 saltando campo de referencia.

                        if(sqlite3_step(stmt) != SQLITE_DONE)
                            printError("Cannot step the statement");
                    }
                    else
                        printError("Cannot reset the statement");
                }
                else
                {
                    printError("Cannot find ordinal of the enumerator");
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

bool DynamicDataDB::processSequencesStorage(const SequenceTypeCode *typeCode,
        Cdr &cdr, string &suffix,
        const string &memberName, int &index, bool step)
{
    const char* const METHOD_NAME = "processSequencesStorage";
    bool returnedValue = false;
    list<arrayNode*>::iterator it;
    arrayNode *aNode = NULL;

    if(typeCode != NULL)
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
                    if(processSequenceElementsStorage(aNode->m_stmt, aNode->m_ref, typeCode, cdr))
                    {
                        sqlite3_bind_int(m_addStmt, index++, aNode->m_ref++);
                        returnedValue = true;
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

bool DynamicDataDB::processSequenceElementsStorage(sqlite3_stmt *stmt, int ref, const SequenceTypeCode *typeCode, Cdr &cdr)
{
    const char* const METHOD_NAME = "processSequenceElementsStorage";
    bool returnedValue = false;
    const TypeCode *elementType = NULL;

    if(stmt != NULL && typeCode != NULL)
    {
        elementType = typeCode->getContentTypeCode();

        if(elementType != NULL)
        {
            if(elementType->getKind() == TypeCode::KIND_ENUM)
            {
                addEnumSequenceStorage(stmt, ref, dynamic_cast<const EnumTypeCode*>(elementType), cdr);
            }
            else if(TypeCode::kindIsPrimitive(elementType->getKind()))
            {
                returnedValue = processSequencePrimitiveStorage(stmt, ref, dynamic_cast<const PrimitiveTypeCode*>(elementType), cdr);
            }
        }
        else
        {
            logError(m_log, "Cannot get the content typecode");
        }
    }
    else
    {
        logError(m_log, "Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::processSequencePrimitiveStorage(sqlite3_stmt *stmt, int ref,
        const PrimitiveTypeCode *typeCode, Cdr &cdr)
{
    bool returnedValue = false;
    writeSequencePrimitiveFunctions *writeSequencePrimitiveFunctionsPointer =
        DynamicDataDB::writeSequencePrimitiveFunctionsMap;
    bool (*addToStream)(sqlite3_stmt *stmt, int ref, Cdr &cdr) = NULL;

    while(writeSequencePrimitiveFunctionsPointer->_kind != TypeCode::KIND_NULL)
    {
        if(typeCode->getKind() == writeSequencePrimitiveFunctionsPointer->_kind)
        {
            addToStream = writeSequencePrimitiveFunctionsPointer->_addToStream;
            break;
        }

        writeSequencePrimitiveFunctionsPointer++;
    }

    if(addToStream != NULL)
    {
        returnedValue = addToStream(stmt, ref, cdr);
    }

    return returnedValue;
}

bool DynamicDataDB::addOctetSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addOctetSequenceStorage";
    bool returnedValue = false;
    std::vector<uint8_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get octet sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addShortSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addShortSequenceStorage";
    bool returnedValue = false;
    std::vector<int16_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get short sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addUShortSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addUShortSequenceStorage";
    bool returnedValue = false;
    std::vector<uint16_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count <  values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get unsigned short sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addLongSequenceStorage";
    bool returnedValue = false;
    std::vector<int32_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get long sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addULongSequenceStorage";
    bool returnedValue = false;
    std::vector<uint32_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get unsigned long sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addLongLongSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addLongLongSequenceStorage";
    bool returnedValue = false;
    std::vector<int64_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int64(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get long long sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addULongLongSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addULongLongSequenceStorage";
    bool returnedValue = false;
    std::vector<uint64_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int64(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get unsigned long long sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addCharSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addCharSequenceStorage";
    bool returnedValue = false;
    std::vector<char> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_text(stmt, 3, &(values[count]), 1, SQLITE_STATIC);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get char sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addFloatSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addFloatSequenceStorage";
    bool returnedValue = false;
    std::vector<float> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_double(stmt, 3, (double)(values[count]));

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get float sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addDoubleSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addDoubleSequenceStorage";
    bool returnedValue = false;
    std::vector<double> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_double(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get double sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addEnumSequenceStorage(sqlite3_stmt *stmt, int ref, const EnumTypeCode *enumTC, Cdr &cdr)
{
    const char* const METHOD_NAME = "addEnumSequenceStorage";
    bool returnedValue = false;
    std::vector<int32_t> ordinals;


    if(stmt != NULL && enumTC != NULL)
    {
        try
        {
            cdr >> ordinals;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < ordinals.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    const EnumMember *member = enumTC->getMemberWithOrdinal(ordinals[count]);

                    if(member != NULL)
                    {
                        sqlite3_bind_int(stmt, 1, ref);
                        sqlite3_bind_int(stmt, 2, count);
                        sqlite3_bind_text(stmt, 3, member->getName().c_str(), (int)member->getName().length(), SQLITE_STATIC);

                        if(sqlite3_step(stmt) != SQLITE_DONE)
                        {
                            printError("Cannot step the statement");
                            returnedValue = false;
                        }
                    }
                }
                else
                {
                    printError("Cannot reset statement");
                    returnedValue = false;
                }
            }
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get enum sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

bool DynamicDataDB::addBoolSequenceStorage(sqlite3_stmt *stmt, int ref, Cdr &cdr)
{
    const char* const METHOD_NAME = "addBoolSequenceStorage";
    bool returnedValue = false;
    std::vector<uint8_t> values;

    if(stmt != NULL)
    {
        try
        {
            cdr >> values;

            returnedValue = true;
            for(unsigned int count = 0; (returnedValue) && (count < values.size()); count++)
            {
                if(sqlite3_reset(stmt) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, ref);
                    sqlite3_bind_int(stmt, 2, count);
                    sqlite3_bind_int(stmt, 3, values[count]);

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
        }
        catch(exception::Exception &ex)
        {
            printError("Cannot get bool sequence values");
        }
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}
