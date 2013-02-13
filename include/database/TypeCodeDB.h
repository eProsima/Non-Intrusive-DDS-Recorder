#ifndef _TYPECODEDB_H_
#define _TYPECODEDB_H_

#ifndef RICARDO
struct RTICdrTypeCode;
#endif

#ifdef __cplusplus

#include <string>
#include <list>

#include <sqlite3.h>

namespace eProsima
{
    class eProsimaLog;
    class DynamicDataDB;
    class TypeCode;

    class eTypeCode
    {
        public:
#ifdef RICARDO
            eTypeCode(std::string &topicName, std::string &typeName,
                    TypeCode *typeCode, DynamicDataDB *dynamicDB);
#else
            eTypeCode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode, DynamicDataDB *dynamicDB);
#endif

            ~eTypeCode();

            /**
             * \brief This function returns if the typecode is equal using
             * topic's name and type's name.
             *
             * \param topicName The topic's name. Cannot be NULL.
             * \param typeName The type's name. Cannot be NULL.
             * \return True if they're equal or false in other case.
             */
            bool equal(std::string &topicName, std::string &typeName);
            // TODO Quitar.
            bool equal(const char *topicName, const char *typeName);

            /**
             * \brief This function return the typecode.
             *
             * \return Return the CdrTypeCode. Don't free this pointer.
             */
#ifdef RICARDO
            TypeCode* getCdrTypecode();
#else
            RTICdrTypeCode* getCdrTypecode();
#endif

            DynamicDataDB* getDynamicDataDB();

        private:

            std::string m_topicName;
            std::string m_typeName;
#ifdef RICARDO
            TypeCode *m_typeCode;
#else
            struct RTICdrTypeCode *m_typeCode;
#endif
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
#ifdef RICARDO
            bool addTypecode(std::string &topicName, std::string &typeName,
                    TypeCode *typeCode);
#else
            bool addTypecode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode);
#endif

            /**
             * \brief This function searchs a typecode in the database.
             *
             * \param topicName Pointer to the topic's name. Cannot be NULL.
             * \param typeName Pointer to the type's name. Cannot be NULL.
             * \return Return the pointer to the eTypeCode structure if this was found.
             * In other case NULL pointer is returned. Don't free this pointer.
             */
#ifdef RICARDO
            eTypeCode* findTypecode(std::string &topicName, std::string &typeName);
#else
            eTypeCode* findTypecode(const char *topicName, const char *typeName);
#endif

        private:

#ifdef RICARDO
            std::string getPrintIDL(const TypeCode *typeCode);
#else
            char *getPrintIDL(RTICdrTypeCode *typeCode);
#endif

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
