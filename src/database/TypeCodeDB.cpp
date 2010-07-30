#include "database/TypeCodeDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_stream.h"
#include "osapi/osapi_heap.h"

#define TYPECODE_TABLE "typecodes"

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "TypeCodeDB";

eTypeCode::eTypeCode(const char *topicName, const char *typeName,
        struct RTICdrTypeCode *typeCode) : m_topicName(topicName),
    m_typeName(typeName), m_typeCode(typeCode)
{
}

eTypeCode::~eTypeCode()
{
    RTIOsapiHeap_freeBufferNotAligned(m_typeCode);
}

bool eTypeCode::equal(const char *topicName, const char *typeName)
{
    const char* const METHOD_NAME = "equal";
    bool returnedValue = false;

    if(topicName != NULL && typeName != NULL)
    {
        if(strcmp(m_topicName.c_str(), topicName) == 0 &&
                strcmp(m_typeName.c_str(), typeName) == 0)
            returnedValue = true;
    }
    else
    {
        printError("Bad parameters");
    }

    return returnedValue;
}

TypeCodeDB::TypeCodeDB(eProsimaLog &log, sqlite3 *databaseH) : m_log(log), m_databaseH(databaseH)
{
    const char* const METHOD_NAME = "TypeCodeDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name=\"" TYPECODE_TABLE "\"";
    const char* const TABLE_TRUNCATE = "DELETE FROM " TYPECODE_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " TYPECODE_TABLE "(topic_name VARCHAR(50)," \
                                      "type_name VARCHAR(50), typecode VARCHAR(2048)," \
                                      "PRIMARY KEY(topic_name, type_name))";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;

    if(sqlite3_prepare_v2(m_databaseH, TABLE_CHECK, strlen(TABLE_CHECK), &stmt, NULL) == SQLITE_OK)
    {
        ret = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(ret == SQLITE_ROW)
        {
            if(sqlite3_prepare_v2(m_databaseH, TABLE_TRUNCATE, strlen(TABLE_TRUNCATE), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) != SQLITE_DONE)
                    logError(m_log, "Cannot truncate the typecodes table");

                sqlite3_finalize(stmt);
            }
        }
        else if(ret == SQLITE_DONE)
        {
            if(sqlite3_prepare_v2(m_databaseH, TABLE_CREATE, strlen(TABLE_CREATE), &stmt, NULL) == SQLITE_OK)
            {
                if(sqlite3_step(stmt) != SQLITE_DONE)
                    logError(m_log, "Cannot create the typecodes table");

                sqlite3_finalize(stmt);
            }
        }
        else
        {
            logError(m_log, "Cannot execute check the typecodes table");
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
}

bool TypeCodeDB::addTypecode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode)
{
    bool returnedValue = false;
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); it != m_typecodes.end(); it++)
    {
        if((*it)->equal(topicName, typeName))
            break;
    }

    if(it == m_typecodes.end())
    {
        m_typecodes.push_back(new eTypeCode(topicName, typeName, typeCode));
        returnedValue = true;
    }

    return returnedValue;
}
