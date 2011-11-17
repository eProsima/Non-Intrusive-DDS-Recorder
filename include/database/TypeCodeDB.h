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
    class DynamicDataDB;

    class eTypeCode
    {
        public:

            eTypeCode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode, DynamicDataDB *dynamicDB);

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

            /**
             * \brief This function return the typecode.
             *
             * \return Return the CdrTypeCode. Don't free this pointer.
             */
            RTICdrTypeCode* getCdrTypecode();

            DynamicDataDB* getDynamicDataDB();

        private:

            std::string m_topicName;
            std::string m_typeName;
            struct RTICdrTypeCode *m_typeCode;
            DynamicDataDB *m_dynamicDB;
    };

    class TypeCodeDB
    {
        public:

            TypeCodeDB(eProsimaLog &log, sqlite3 *databaseH, int tcMaxSize);

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

            /**
             * \brief This function searchs a typecode in the database.
             *
             * \param topicName Pointer to the topic's name. Cannot be NULL.
             * \param typeName Pointer to the type's name. Cannot be NULL.
             * \return Return the pointer to the eTypeCode structure if this was found.
             * In other case NULL pointer is returned. Don't free this pointer.
             */
            eTypeCode* findTypecode(const char *topicName, const char *typeName);

        private:

            char *getPrintIDL(RTICdrTypeCode *typeCode);

            std::list<eTypeCode*> m_typecodes;

            eProsimaLog &m_log;

            bool m_ready;

            /// Handler of the database.
            sqlite3 *m_databaseH;

            /// Sqlite3 statement used to add typecodes.
            sqlite3_stmt *m_addStmt;

            /// Buffer used in function getPrintID()
            char *m_buffer;

            int m_tcMaxSize;
    };
}

#endif

#endif // _TYPECODEDB_H_
