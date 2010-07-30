#ifndef _TYPECODEDB_H_
#define _TYPECODEDB_H_

struct RTICdrTypeCode;

#ifdef __cplusplus

#include <string>
#include <list>

#include <sqlite3.h>

namespace eProsima
{
    class eProsimaLog;

    class eTypeCode
    {
        public:

            eTypeCode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode);

            ~eTypeCode();

            /**
             * \brief This function returns if the typecode is equal using
             * topic's name and type's name.
             *
             * \param topicName The topic's name. Cannot be NULL.
             * \param typeName The type's name. Cannot be NULL.
             * \return True if they're equal or false in other case.
             */
            bool equal(const char *topicName, const char *typeName);

        private:

            std::string m_topicName;
            std::string m_typeName;
            struct RTICdrTypeCode *m_typeCode;
    };

    class TypeCodeDB
    {
        public:

            TypeCodeDB(eProsimaLog &log, std::string &database);

            ~TypeCodeDB();

            /**
             * \brief This function adds a typecode in the database.
             *
             * \param topicName Pointer to the topic's name. Cannot be NULL.
             * \param typeName Pointer to the type's name. Cannot be NULL.
             * \param typeCode Pointer to the buffer where is the typecode. Cannot be NULL.
             * \return True value is returned if the typecode was added. False is returned
             * if the typecode is already in the database and it wasn't added.
             */
            bool addTypecode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode);

        private:

            std::list<eTypeCode*> m_typecodes;

            eProsimaLog &m_log;

            /// Handler of the database.
            sqlite3 *m_databaseH;
    };
}

#endif

#endif // _TYPECODEDB_H_
