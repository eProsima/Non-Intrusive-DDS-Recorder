#include "database/EntitiesDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_typeCode.h"
#include "dds_c/dds_c_infrastructure.h"

#include <string.h>

#ifndef RTI_WIN32
#include <sys/time.h>
#endif

#define ENTITIES_TABLE "entities"
#define MESSAGES_TABLE "entities_topic_messages"
#define READER_TEXT "reader"
#define WRITER_TEXT "writer"

static const char* const CLASS_NAME = "EntitiesDB";
static const char* const ENTITY_ADD = "INSERT INTO " ENTITIES_TABLE " VALUES(?, ?, ?, ?, ?, ?, ?, ?)";
static const char* const MESSAGES_ADD = "INSERT INTO " MESSAGES_TABLE " VALUES(?, ?, ?, ?, ?, ?, ?, ?, "\
                                         "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

using namespace eProsima;
using namespace std;

eEntity::eEntity(unsigned int hostId, unsigned int appId,
        unsigned int instanceId, unsigned int entityId,
        const char *topicName, const char *typeName,
        bool existsTypecode) : m_hostId(hostId),
    m_appId(appId), m_instanceId(instanceId),
    m_entityId(entityId), m_topicName(topicName), m_typeName(typeName),
    m_existsTypecode(existsTypecode)
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

bool eEntity::getExistsTypecode()
{
    return m_existsTypecode;
}

void eEntity::setExistsTypecode(bool e)
{
    m_existsTypecode = e;
}

EntitiesDB::EntitiesDB(eProsimaLog &log, sqlite3 *databaseH) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_addStmt(NULL), m_addMsgStmt(NULL)
{
    const char* const METHOD_NAME = "EntitiesDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='" ENTITIES_TABLE "'";
    const char* const TABLE_TRUNCATE = "DELETE FROM " ENTITIES_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " ENTITIES_TABLE " (host_id BIGINT UNSIGNED," \
                                      "app_id BIGINT UNSIGNED, instance_id BIGINT UNSIGNED, entity_id BIGINT UNSIGNED," \
                                      "type TEXT, topic_name TEXT, type_name TEXT, exists_typecode TINYINT UNSIGNED," \
                                      "PRIMARY KEY(host_id, app_id, instance_id, entity_id))";
    const char* const TABLE_MESSAGES_CHECK = "SELECT name FROM sqlite_master WHERE name='" MESSAGES_TABLE "'";
    const char* const TABLE_MESSAGES_TRUNCATE = "DELETE FROM " MESSAGES_TABLE;
    const char* const TABLE_MESSAGES_CREATE = "CREATE TABLE " MESSAGES_TABLE \
        " (wireshark_timestamp_sec BIGINT, wireshark_timestamp_usec BIGINT UNSIGNED, " \
        "ip_src TEXT, ip_dst TEXT, " \
        "host_id BIGINT UNSIGNED, app_id BIGINT UNSIGNED, instance_id BIGINT UNSIGNED, " \
        "reader_id BIGINT UNSIGNED, writer_id BIGINT UNSIGNED, writer_seq_num BIGINT UNSIGNED, " \
        "sourcetimestamp_sec BIGINT, sourcetimestamp_nanosec BIGINT UNSIGNED, " \
        "dest_host_Id BIGINT UNSIGNED, dest_app_id BIGINT UNSIGNED, dest_instance_id BIGINT UNSIGNED, " \
        "entity_host_id BIGINT UNSIGNED, entity_app_id BIGINT UNSIGNED, entity_instance_id BIGINT UNSIGNED," \
        "entity_id BIGINT UNSIGNED, type TEXT, topic_name TEXT, type_name TEXT, exists_typecode TINYINT UNSIGNED)";
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
            else
                logError(m_log, "Cannot prepare statement to delete entities table");
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
            else
                logError(m_log, "Cannot prepare statement to create entities table");
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
                if(sqlite3_prepare_v2(m_databaseH, TABLE_MESSAGES_CHECK, strlen(TABLE_MESSAGES_CHECK), &stmt, NULL) == SQLITE_OK)
                {
                    ret = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);

                    if(ret == SQLITE_ROW)
                    {
                        if(sqlite3_prepare_v2(m_databaseH, TABLE_MESSAGES_TRUNCATE, strlen(TABLE_MESSAGES_TRUNCATE), &stmt, NULL) == SQLITE_OK)
                        {
                            if(sqlite3_step(stmt) == SQLITE_DONE)
                                m_ready = true;
                            else
                                logError(m_log, "Cannot truncate the entities messages table");

                            sqlite3_finalize(stmt);
                        }
                        else
                            logError(m_log, "Cannot prepare statement to delete entities table");
                    }
                    else if(ret == SQLITE_DONE)
                    {
                        if(sqlite3_prepare_v2(m_databaseH, TABLE_MESSAGES_CREATE, strlen(TABLE_MESSAGES_CREATE), &stmt, NULL) == SQLITE_OK)
                        {
                            if(sqlite3_step(stmt) == SQLITE_DONE)
                                m_ready = true;
                            else
                                logError(m_log, "Cannot create the entities messages table");

                            sqlite3_finalize(stmt);
                        }
                        else
                            logError(m_log, "Cannot prepare statement to create entities table");
                    }
                    else
                    {
                        logError(m_log, "Cannot execute check the entities messages table");
                    }

                    if(m_ready)
                    {
                        m_ready = false;

                        if(sqlite3_prepare_v2(m_databaseH, MESSAGES_ADD, strlen(MESSAGES_ADD), &m_addMsgStmt, NULL) == SQLITE_OK)
                        {
                            m_ready = true;
                        }
                        else
                            logError(m_log, "Cannot create add messages statement");

                    }
                }
                else
                {
                    logError(m_log, "Cannot check the entities message table");
                }
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

    for(it = m_entities_without.begin(); it != m_entities_without.end(); it++)
    {
        delete *it;
    }

    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }

    if(m_addMsgStmt != NULL)
    {
        sqlite3_finalize(m_addMsgStmt);
    }
}

bool EntitiesDB::addEntity(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
        unsigned int hostId, unsigned int appId, unsigned int instanceId,
        unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
        struct DDS_Time_t &sourceTmp, unsigned int destHostId,
        unsigned int destAppId, unsigned int destInstanceId,const unsigned int entity_hostId, const unsigned int entity_appId,
        const unsigned int entity_instanceId, const unsigned int entityId, int type,
        const char *topicName, const char *typeName, bool existsTypecode)
{
    const char* const METHOD_NAME = "addEntity";
    bool returnedValue = false;
    eEntity *entity = NULL;

    if(m_ready)
    {
        if((entity = findEntity(entity_hostId, entity_appId, entity_instanceId, entityId)) == NULL)
        {
            if(sqlite3_reset(m_addStmt) == SQLITE_OK)
            {
                sqlite3_bind_int64(m_addStmt, 1, entity_hostId);
                sqlite3_bind_int64(m_addStmt, 2, entity_appId);
                sqlite3_bind_int64(m_addStmt, 3, entity_instanceId);
                sqlite3_bind_int64(m_addStmt, 4, entityId);
                if(type == 0)
                    sqlite3_bind_text(m_addStmt, 5, READER_TEXT, strlen(READER_TEXT), SQLITE_STATIC);
                else
                    sqlite3_bind_text(m_addStmt, 5, WRITER_TEXT, strlen(WRITER_TEXT), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, 6, topicName, strlen(topicName), SQLITE_STATIC);
                sqlite3_bind_text(m_addStmt, 7, typeName, strlen(typeName), SQLITE_STATIC);
                if(existsTypecode)
                    sqlite3_bind_int(m_addStmt, 8, 1);
                else
                    sqlite3_bind_int(m_addStmt, 8, 0);

                if(sqlite3_step(m_addStmt) == SQLITE_DONE)
                {
                    m_entities.push_back(new eEntity(entity_hostId, entity_appId,
                                entity_instanceId, entityId, topicName, typeName, existsTypecode));
                    returnedValue = true;
                }
            }
            else
            {
                logError(m_log, "Cannot reset the add statement");
            }
        }
        else
        {
            if(existsTypecode && ! entity->getExistsTypecode())
            {
                entity->setExistsTypecode(true);
                logInfo(m_log, "the datawriter of topic %s sends the typecode", topicName);
            }
            returnedValue = true;
        }

        if(returnedValue)
        {
            returnedValue = false;
            if(sqlite3_reset(m_addMsgStmt) == SQLITE_OK)
            {
                sqlite3_bind_int64(m_addMsgStmt, 1, wts.tv_sec);
                sqlite3_bind_int64(m_addMsgStmt, 2, wts.tv_usec);
                sqlite3_bind_text(m_addMsgStmt, 3, ip_src.c_str(), ip_src.length(), SQLITE_STATIC);
                sqlite3_bind_text(m_addMsgStmt, 4, ip_dst.c_str(), ip_dst.length(), SQLITE_STATIC);
                sqlite3_bind_int64(m_addMsgStmt, 5, hostId);
                sqlite3_bind_int64(m_addMsgStmt, 6, appId);
                sqlite3_bind_int64(m_addMsgStmt, 7, instanceId);
                sqlite3_bind_int64(m_addMsgStmt, 8, readerId);
                sqlite3_bind_int64(m_addMsgStmt, 9, writerId);
                sqlite3_bind_int64(m_addMsgStmt, 10, writerSeqNum);
                sqlite3_bind_int64(m_addMsgStmt, 11, sourceTmp.sec);
                sqlite3_bind_int64(m_addMsgStmt, 12, sourceTmp.nanosec);

                if(destHostId != 0 || destAppId != 0 ||
                        destInstanceId != 0)
                {
                    sqlite3_bind_int64(m_addMsgStmt, 13, destHostId);
                    sqlite3_bind_int64(m_addMsgStmt, 14, destAppId);
                    sqlite3_bind_int64(m_addMsgStmt, 15, destInstanceId);
                }
                else
                {
                    sqlite3_bind_null(m_addMsgStmt, 13);
                    sqlite3_bind_null(m_addMsgStmt, 14);
                    sqlite3_bind_null(m_addMsgStmt, 15);
                }

                sqlite3_bind_int64(m_addMsgStmt, 16, entity_hostId);
                sqlite3_bind_int64(m_addMsgStmt, 17, entity_appId);
                sqlite3_bind_int64(m_addMsgStmt, 18, entity_instanceId);
                sqlite3_bind_int64(m_addMsgStmt, 19, entityId);
                if(type == 0)
                    sqlite3_bind_text(m_addMsgStmt, 20, READER_TEXT, strlen(READER_TEXT), SQLITE_STATIC);
                else
                    sqlite3_bind_text(m_addMsgStmt, 20, WRITER_TEXT, strlen(WRITER_TEXT), SQLITE_STATIC);
                sqlite3_bind_text(m_addMsgStmt, 21, topicName, strlen(topicName), SQLITE_STATIC);
                sqlite3_bind_text(m_addMsgStmt, 22, typeName, strlen(typeName), SQLITE_STATIC);
                if(existsTypecode)
                    sqlite3_bind_int(m_addMsgStmt, 23, 1);
                else
                    sqlite3_bind_int(m_addMsgStmt, 23, 0);

                if(sqlite3_step(m_addMsgStmt) == SQLITE_DONE)
                {
                    returnedValue = true;
                }
            }
            else
            {
                logError(m_log, "Cannot reset the add messages statement");
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
