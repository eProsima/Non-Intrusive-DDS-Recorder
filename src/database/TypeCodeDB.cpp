#include "database/TypeCodeDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_stream.h"
#include "cdr/cdr_typeCode.h"
#include "osapi/osapi_heap.h"

#define TYPECODE_TABLE "typecodes"

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "TypeCodeDB";
static const char* const TYPECODE_ADD = "INSERT INTO " TYPECODE_TABLE " VALUES(?, ?, ?)";

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

TypeCodeDB::TypeCodeDB(eProsimaLog &log, sqlite3 *databaseH) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_addStmt(NULL)
{
    const char* const METHOD_NAME = "TypeCodeDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='" TYPECODE_TABLE "'";
    const char* const TABLE_TRUNCATE = "DELETE FROM " TYPECODE_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " TYPECODE_TABLE " (topic_name VARCHAR(50)," \
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
                if(sqlite3_step(stmt) == SQLITE_DONE)
                    m_ready = true;
                else
                    logError(m_log, "Cannot truncate the typecodes table");

                sqlite3_finalize(stmt);
            }
        }
        else if(ret == SQLITE_DONE)
        {
            if(sqlite3_prepare_v2(m_databaseH, TABLE_CREATE, strlen(TABLE_CREATE), &stmt, NULL) == SQLITE_OK)
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

            if(sqlite3_prepare_v2(m_databaseH, TYPECODE_ADD, strlen(TYPECODE_ADD), &stmt, NULL) == SQLITE_OK)
                m_ready = true;
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
}

bool TypeCodeDB::addTypecode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode)
{
    const char* const METHOD_NAME = "addTypeCode";
    bool returnedValue = false;

    if(m_ready)
    {
        if(!findTypecode(topicName, typeName))
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_text(m_addStmt, 1, topicName, strlen(topicName), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, 2, typeName, strlen(typeName), SQLITE_STATIC);
                //sqlite3_bind_text(m_addStmt, 3, typeCode, strlen(typeCode), SQLITE_STATIC);
                getPrintIDL(typeCode);

                m_typecodes.push_back(new eTypeCode(topicName, typeName, typeCode));
                returnedValue = true;
            }
            else
            {
                logError(m_log, "Cannot reset the add statement");
            }
        }
    }

    return returnedValue;
}

bool TypeCodeDB::findTypecode(const char *topicName, const char *typeName)
{
    bool returnedValue = false;
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); it != m_typecodes.end(); it++)
    {
        if((*it)->equal(topicName, typeName))
            break;
    }

    if(it != m_typecodes.end())
        returnedValue = true;

    return returnedValue;
}

char* TypeCodeDB::getPrintIDL(RTICdrTypeCode *typeCode)
{
    int fd;
    fpos_t pos;

    if(typeCode != NULL)
    {
        fgetpos(stdout, &pos);
        fd = dup(fileno(stdout));
        freopen("tmp_file", "w", stdout);
        RTICdrTypeCode_print_IDL(typeCode, 0);
        fflush(stdout);
        dup2(fd, fileno(stdout));
        close(fd);
        clearerr(stdout);
        fsetpos(stdout, &pos);
    }
}
