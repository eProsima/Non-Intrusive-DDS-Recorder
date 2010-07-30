#include "database/TypeCodeDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_stream.h"
#include "osapi/osapi_heap.h"

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

TypeCodeDB::TypeCodeDB(eProsimaLog &log, string &database) : m_log(log), m_databaseH(NULL)
{
    const char* const METHOD_NAME = "TypeCodeDB";

    if(sqlite3_open(database.c_str(), &m_databaseH) != SQLITE_OK)
    {
        logError(m_log, "Cannot open the database file %s\n", database.c_str());
        sqlite3_close(m_databaseH);
        m_databaseH = NULL;
    }
}

TypeCodeDB::~TypeCodeDB()
{
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); it != m_typecodes.end(); it++)
    {
        delete *it;
    }

    if(m_databaseH != NULL)
        sqlite3_close(m_databaseH);
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
