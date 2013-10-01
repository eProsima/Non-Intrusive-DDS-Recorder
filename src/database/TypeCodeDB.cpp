#include "database/TypeCodeDB.h"
#include "database/DynamicDataDB.h"
#include "util/IDLPrinter.h"
#include "cdr/StructTypeCode.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <string.h>

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif

#define TYPECODE_TABLE "_topics"

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "TypeCodeDB";
static const char* const TYPECODE_ADD = "INSERT INTO " TYPECODE_TABLE " VALUES(?, ?, ?)";

eTypeCode::eTypeCode(std::string &topicName, std::string &typeName,
        TypeCode *typeCode, DynamicDataDB *dynamicDB) :
    m_topicName(topicName), m_typeName(typeName), m_typeCode(typeCode),
    m_dynamicDB(dynamicDB)
{
}

eTypeCode::~eTypeCode()
{
    delete m_typeCode;

    if(m_dynamicDB != NULL)
        delete m_dynamicDB;
}

bool eTypeCode::equal(std::string &topicName, std::string &typeName, bool &error)
{
    bool returnedValue = false;

    if(m_topicName == topicName)
    {
        if(m_typeName == typeName)
            returnedValue = true;
        else
            error = true;
    }

    return returnedValue;
}

TypeCode* eTypeCode::getCdrTypecode()
{
    return m_typeCode;
}

DynamicDataDB* eTypeCode::getDynamicDataDB()
{
    return m_dynamicDB;
}

TypeCodeDB::TypeCodeDB(eProsimaLog &log, sqlite3 *databaseH, int tcMaxSize) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_addStmt(NULL)
#ifdef DDS_USE
    , m_buffer(NULL), m_tcMaxSize(tcMaxSize)
#endif
{
    const char* const METHOD_NAME = "TypeCodeDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='" TYPECODE_TABLE "'";
    const char* const TABLE_TRUNCATE = "DELETE FROM " TYPECODE_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " TYPECODE_TABLE " (topic_name VARCHAR(255)," \
                                      "type_name VARCHAR(255), typecode TEXT)";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;

    if(SQLITE_PREPARE(m_databaseH, TABLE_CHECK, (int)strlen(TABLE_CHECK), &stmt, NULL) == SQLITE_OK)
    {
        ret = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(ret == SQLITE_ROW)
        {
            if(SQLITE_PREPARE(m_databaseH, TABLE_TRUNCATE, (int)strlen(TABLE_TRUNCATE), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) == SQLITE_DONE)
                    m_ready = true;
                else
                    logError(m_log, "Cannot truncate the typecodes table");

                sqlite3_finalize(stmt);
            }
        }
        else if(ret == SQLITE_DONE)
        {
            if(SQLITE_PREPARE(m_databaseH, TABLE_CREATE, (int)strlen(TABLE_CREATE), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) == SQLITE_DONE)
                    m_ready = true;
                else
                    logError(m_log, "Cannot create the typecodes table");

                sqlite3_finalize(stmt);
            }
        }
        else
        {
            logError(m_log, "Cannot execute check the typecodes table");
        }

        if(m_ready)
        {
            m_ready = false;

            if(SQLITE_PREPARE(m_databaseH, TYPECODE_ADD, (int)strlen(TYPECODE_ADD), &m_addStmt, NULL) == SQLITE_OK)
            {
#ifdef DDS_USE
                m_buffer = (char*)calloc(m_tcMaxSize, sizeof(char));

                if(m_buffer != NULL)
#endif
                    m_ready = true;
            }
            else
                logError(m_log, "Cannot create add statement");
                
        }
    }
    else
    {
        logError(m_log, "Cannot check the typecodes table");
    }
}

TypeCodeDB::~TypeCodeDB()
{
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); it != m_typecodes.end(); it++)
    {
        delete *it;
    }

#ifdef DDS_USE
    if(m_buffer != NULL)
    {
        free(m_buffer);
    }
#endif

    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }
}

bool TypeCodeDB::addTypecode(std::string &topicName, std::string &typeName, TypeCode *typeCode)
{
    const char* const METHOD_NAME = "addTypeCode";
    DynamicDataDB *dynamicDB;
    string dynamicTableName;
    bool error = false;

    if(m_ready)
    {
        if(findTypecode(topicName, typeName, error) == NULL && !error)
        {
            // Create the dynamic data database.
            dynamicTableName = topicName;
            DynamicDataDB::eraseSpacesInTableName(dynamicTableName);
            dynamicDB = new DynamicDataDB(m_log, m_databaseH, dynamicTableName, typeCode);

            if(dynamicDB != NULL)
            {
                if(sqlite3_reset(m_addStmt) == SQLITE_OK)
                {
                    sqlite3_bind_text(m_addStmt, 1, topicName.c_str(), (int)topicName.length(), SQLITE_STATIC);
                    sqlite3_bind_text(m_addStmt, 2, typeName.c_str(), (int)typeName.length(), SQLITE_STATIC);
                    string txtTypeCode = getPrintIDL(typeCode);
                    sqlite3_bind_text(m_addStmt, 3, txtTypeCode.c_str(), (int)txtTypeCode.length(), SQLITE_STATIC);

                    if(sqlite3_step(m_addStmt) == SQLITE_DONE)
                    {
                        m_typecodes.push_back(new eTypeCode(topicName, typeName, typeCode, dynamicDB));
                        return true;
                    }
                    else
                    {
                        logError(m_log, "Cannot step the add statement");
                    }
                }
                else
                {
                    logError(m_log, "Cannot reset the add statement");
                }

                delete dynamicDB;
            }
            else
            {
                logError(m_log, "Cannot create the DynamicDataDB to topic %s", topicName.c_str());
            }
        }
        else
        {
            if(error)
                logError(m_log, "Discovered two Topics with the same topic name (%s) but different type name.", topicName.c_str());
        }
    }

    return false;
}

eTypeCode* TypeCodeDB::findTypecode(std::string &topicName, std::string &typeName, bool &error)
{
    eTypeCode *returnedValue = NULL;
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); !error && it != m_typecodes.end(); it++)
    {
        if((*it)->equal(topicName, typeName, error))
        {
            returnedValue = (*it);
            break;
        }
    }

    return returnedValue;
}

std::string TypeCodeDB::getPrintIDL(const TypeCode *typeCode)
{
    IDLPrinter txtStream;

    txtStream << typeCode;

    return txtStream.str();
}
