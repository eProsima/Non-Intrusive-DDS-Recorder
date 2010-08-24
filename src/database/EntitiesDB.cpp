#include "database/EntitiesDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_typeCode.h"

#include <string.h>

#define ENTITIES_TABLE "entities"
#define READER_TEXT "reader"
#define WRITER_TEXT "writer"

static const char* const CLASS_NAME = "EntitiesDB";
static const char* const ENTITY_ADD = "INSERT INTO " ENTITIES_TABLE " VALUES(?, ?, ?, ?, ?, ?, ?)";

using namespace eProsima;
using namespace std;

eEntity::eEntity(unsigned int hostId, unsigned int appId,
        unsigned int instanceId, unsigned int entityId,
        const char *topicName, const char *typeName) : m_hostId(hostId),
    m_appId(appId), m_instanceId(instanceId),
    m_entityId(entityId), m_topicName(topicName), m_typeName(typeName)
{
}

bool eEntity::equal(unsigned int hostId, unsigned int appId,
    unsigned int instanceId, unsigned int entityId)
{
    bool returnedValue = false;

    if(hostId == m_hostId &&
            appId == m_appId &&
            instanceId == m_instanceId &&
            entityId == m_entityId)
        returnedValue = true;

    return returnedValue;
}

std::string& eEntity::getTopicName()
{
    return m_topicName;
}

std::string& eEntity::getTypeName()
{
    return m_typeName;
}

EntitiesDB::EntitiesDB(eProsimaLog &log, sqlite3 *databaseH) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_addStmt(NULL)
{
    const char* const METHOD_NAME = "EntitiesDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='" ENTITIES_TABLE "'";
    const char* const TABLE_TRUNCATE = "DELETE FROM " ENTITIES_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " ENTITIES_TABLE " (host_id BIGINT UNSIGNED," \
                                      "app_id BIGINT UNSIGNED, instance_id BIGINT UNSIGNED, entity_id BIGINT UNSIGNED," \
                                      "type TEXT, topic_name TEXT, type_name TEXT," \
                                      "PRIMARY KEY(host_id, app_id, instance_id, entity_id))";
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
                    logError(m_log, "Cannot truncate the entities table");

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
                    logError(m_log, "Cannot create the entities table");

                sqlite3_finalize(stmt);
            }
        }
        else
        {
            logError(m_log, "Cannot execute check the entities table");
        }

        if(m_ready)
        {
            m_ready = false;

            if(sqlite3_prepare_v2(m_databaseH, ENTITY_ADD, strlen(ENTITY_ADD), &m_addStmt, NULL) == SQLITE_OK)
            {
                    m_ready = true;
            }
            else
                logError(m_log, "Cannot create add statement");
                
        }
    }
    else
    {
        logError(m_log, "Cannot check the entities table");
    }
}

EntitiesDB::~EntitiesDB()
{
    list<eEntity*>::iterator it;

    for(it = m_entities.begin(); it != m_entities.end(); it++)
    {
        delete *it;
    }

    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }
}

bool EntitiesDB::addEntity(const unsigned int hostId, const unsigned int appId,
        const unsigned int instanceId, const unsigned int entityId, int type,
        const char *topicName, const char *typeName)
{
    const char* const METHOD_NAME = "addTypeCode";
    bool returnedValue = false;

    if(m_ready)
    {
        if(findEntity(hostId, appId, instanceId, entityId) == NULL)
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_int64(m_addStmt, 1, hostId);
                sqlite3_bind_int64(m_addStmt, 2, appId);
                sqlite3_bind_int64(m_addStmt, 3, instanceId);
                sqlite3_bind_int64(m_addStmt, 4, entityId);
                if(type == 0)
                    sqlite3_bind_text(m_addStmt, 5, READER_TEXT, strlen(READER_TEXT), SQLITE_STATIC);
                else
                    sqlite3_bind_text(m_addStmt, 5, WRITER_TEXT, strlen(WRITER_TEXT), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, 6, topicName, strlen(topicName), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, 7, typeName, strlen(typeName), SQLITE_STATIC);

                if(sqlite3_step(m_addStmt) == SQLITE_DONE)
                {
                    m_entities.push_back(new eEntity(hostId, appId,
                                instanceId, entityId, topicName, typeName));
                    returnedValue = true;
                }
            }
            else
            {
                logError(m_log, "Cannot reset the add statement");
            }
        }
    }

    return returnedValue;
}

eEntity* EntitiesDB::findEntity(const unsigned int hostId, const unsigned int appId,
        const unsigned int instanceId, const unsigned int entityId)
{
    eEntity *returnedValue = NULL;
    list<eEntity*>::iterator it;

    for(it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if((*it)->equal(hostId, appId, instanceId, entityId))
        {
            returnedValue = (*it);
            break;
        }
    }

    return returnedValue;
}
