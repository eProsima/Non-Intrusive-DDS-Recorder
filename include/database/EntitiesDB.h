#ifndef _ENTITIESDB_H_
#define _ENTITIESDB_H_

#ifdef __cplusplus

#include <string>
#include <list>

#include <sqlite3.h>

namespace eProsima
{
    class eProsimaLog;

    class eEntity
    {
        public:

            eEntity(unsigned int hostId, unsigned int appId,
                    unsigned int instanceId, unsigned int entityId,
                    const char *topicName, const char *typeName);

            /**
             * \brief This function returns if the entity is the same.
             *
             * \param guidPrefix prefix of the entity.
             * \param entityId entity identifier
             * \return True if they're equal or false in other case.
             */
            bool equal(unsigned int hostId, unsigned int appId,
                    unsigned int instanceId, unsigned int entityId);

            std::string& getTopicName();
            std::string& getTypeName();

        private:

            unsigned int m_hostId;
            unsigned int m_appId;
            unsigned int m_instanceId;
            unsigned int m_entityId;
            std::string m_topicName;
            std::string m_typeName;
    };

    class EntitiesDB
    {
        public:

            EntitiesDB(eProsimaLog &log, sqlite3 *databaseH);

            ~EntitiesDB();

            bool addEntity(const unsigned int hostId, const unsigned int appId,
                    const unsigned int instanceId, const unsigned int entityId,
                    const char *topicName, const char *typeName);

            eEntity* findEntity(const unsigned int hostId, const unsigned int appId,
                    const unsigned int instanceId, const unsigned int entityId);

        private:

            std::list<eEntity*> m_entities;

            eProsimaLog &m_log;

            bool m_ready;

            /// Handler of the database.
            sqlite3 *m_databaseH;

            /// Sqlite3 statement used to add typecodes.
            sqlite3_stmt *m_addStmt;
    };
}

#endif

#endif // _ENTITIESDB_H_
