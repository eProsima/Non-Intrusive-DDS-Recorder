#include "database/TypeCodeDB.h"
#include "database/DynamicDataDB.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "cdr/cdr_stream.h"
#include "cdr/cdr_typeCode.h"
#include "osapi/osapi_heap.h"

#ifdef RTI_WIN32
#include <windows.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>

#define DUP _dup
#define DUP2 _dup2
#define CLOSE _close
#define READ _read
#define FILENO _fileno

#else
#define DUP dup
#define DUP2 dup2
#define CLOSE close
#define READ read
#define FILENO fileno
#endif

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif

#define TYPECODE_TABLE "typecodes"

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "TypeCodeDB";
static const char* const TYPECODE_ADD = "INSERT INTO " TYPECODE_TABLE " VALUES(?, ?, ?)";

eTypeCode::eTypeCode(const char *topicName, const char *typeName,
        struct RTICdrTypeCode *typeCode, DynamicDataDB *dynamicDB) :
    m_topicName(topicName), m_typeName(typeName), m_typeCode(typeCode),
    m_dynamicDB(dynamicDB)
{
}

eTypeCode::~eTypeCode()
{
    RTIOsapiHeap_freeBufferNotAligned(m_typeCode);

    if(m_dynamicDB != NULL)
        delete m_dynamicDB;
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

RTICdrTypeCode* eTypeCode::getCdrTypecode()
{
    return m_typeCode;
}

DynamicDataDB* eTypeCode::getDynamicDataDB()
{
    return m_dynamicDB;
}

TypeCodeDB::TypeCodeDB(eProsimaLog &log, sqlite3 *databaseH, int tcMaxSize) : m_log(log), m_ready(false),
    m_databaseH(databaseH), m_addStmt(NULL), m_buffer(NULL), m_tcMaxSize(tcMaxSize)
{
    const char* const METHOD_NAME = "TypeCodeDB";
    const char* const TABLE_CHECK = "SELECT name FROM sqlite_master WHERE name='" TYPECODE_TABLE "'";
    const char* const TABLE_TRUNCATE = "DELETE FROM " TYPECODE_TABLE;
    const char* const TABLE_CREATE = "CREATE TABLE " TYPECODE_TABLE " (topic_name TEXT," \
                                      "type_name TEXT, typecode TEXT)";
    sqlite3_stmt *stmt = NULL;
    int ret = SQLITE_ERROR;

    if(SQLITE_PREPARE(m_databaseH, TABLE_CHECK, strlen(TABLE_CHECK), &stmt, NULL) == SQLITE_OK)
    {
        ret = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(ret == SQLITE_ROW)
        {
            if(SQLITE_PREPARE(m_databaseH, TABLE_TRUNCATE, strlen(TABLE_TRUNCATE), &stmt, NULL) == SQLITE_OK)
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
            if(SQLITE_PREPARE(m_databaseH, TABLE_CREATE, strlen(TABLE_CREATE), &stmt, NULL) == SQLITE_OK)
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

            if(SQLITE_PREPARE(m_databaseH, TYPECODE_ADD, strlen(TYPECODE_ADD), &m_addStmt, NULL) == SQLITE_OK)
            {
                m_buffer = (char*)calloc(m_tcMaxSize, sizeof(char));

                if(m_buffer != NULL)
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

    if(m_buffer != NULL)
    {
        free(m_buffer);
    }

    if(m_addStmt != NULL)
    {
        sqlite3_finalize(m_addStmt);
    }
}

bool TypeCodeDB::addTypecode(const char *topicName, const char *typeName,
                    struct RTICdrTypeCode *typeCode)
{
    const char* const METHOD_NAME = "addTypeCode";
    char *buffer = NULL;
    DynamicDataDB *dynamicDB;
    string dynamicTableName;

    if(m_ready)
    {
        if(findTypecode(topicName, typeName) == NULL)
        {
            // Create the dynamic data database.
            dynamicTableName = topicName;
            dynamicTableName += "__";
            dynamicTableName += typeName;
            DynamicDataDB::eraseSpacesInTableName(dynamicTableName);
            dynamicDB = new DynamicDataDB(m_log, m_databaseH, dynamicTableName, typeCode);

            if(dynamicDB != NULL)
            {
                if(sqlite3_reset(m_addStmt) == SQLITE_OK)
                {
                    sqlite3_bind_text(m_addStmt, 1, topicName, strlen(topicName), SQLITE_STATIC);
                    sqlite3_bind_text(m_addStmt, 2, typeName, strlen(typeName), SQLITE_STATIC);
                    buffer = getPrintIDL(typeCode);
                    if(buffer != NULL)
                        sqlite3_bind_text(m_addStmt, 3, buffer, strlen(buffer), SQLITE_STATIC);

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
                logError(m_log, "Cannot create the DynamicDataDB to topic %s", topicName);
            }
        }
    }

    return false;
}

eTypeCode* TypeCodeDB::findTypecode(const char *topicName, const char *typeName)
{
    eTypeCode *returnedValue = NULL;
    list<eTypeCode*>::iterator it;

    for(it = m_typecodes.begin(); it != m_typecodes.end(); it++)
    {
        if((*it)->equal(topicName, typeName))
        {
            returnedValue = (*it);
            break;
        }
    }

    return returnedValue;
}

char* TypeCodeDB::getPrintIDL(RTICdrTypeCode *typeCode)
{
/* Win32 example
	HANDLE oldStdout;
	HANDLE pipefds[2] = {NULL, NULL};
	int hConHandle;
	unsigned long readLen = 0;
	*/

    int oldStdout;
    int pipefds[2];
	fpos_t pos;
	int readLen = 0;
    char *returnedValue = NULL;

    if(typeCode != NULL)
    {
/* Win32 example
        // Save STDOUT
		fflush(stdout);
        oldStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);

		// Create a pipe for the child process's STDOUT. 
		if(CreatePipe(&pipefds[0], &pipefds[1], NULL, 0) != 0)
		{
			// redirect stdout, stdout now writes into the pipe
			if (::SetStdHandle(STD_OUTPUT_HANDLE, pipefds[1]) != 0)
			{
				// new stdout handle
				HANDLE lStdHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);

				if(INVALID_HANDLE_VALUE != lStdHandle)
				{

					hConHandle = ::_open_osfhandle((intptr_t)lStdHandle, _O_TEXT);
					FILE *fp = ::_fdopen(hConHandle, "w");

					if(fp)
					{
						// replace stdout with pipe file handle
						*stdout = *fp;

						// unbuffered stdout
						::setvbuf(stdout, NULL, _IONBF, 0);

						hConHandle = ::_open_osfhandle((intptr_t)pipefds[0], _O_TEXT);
						
						if (hConHandle != 1)
						{
							RTICdrTypeCode_print_IDL(typeCode, 0);
							fflush(stdout);
							if(ReadFile(pipefds[0], m_buffer, m_tcMaxSize, &readLen, NULL)
								&& readLen)
							{
								returnedValue = m_buffer;
							}

							hConHandle = -1;
						}
					}
				}
			}

			// restore stdout
			SetStdHandle(STD_OUTPUT_HANDLE, oldStdout);
			CloseHandle(pipefds[0]);
			CloseHandle(pipefds[1]);
		}

		CloseHandle (oldStdout);
*/

        // Save STDOUT
        fflush(stdout);
        fgetpos(stdout, &pos);
        oldStdout = DUP(FILENO(stdout));

        // Redirect to pipe.       
#ifdef RTI_WIN32
		_pipe(pipefds, m_tcMaxSize, O_TEXT);
#else
		pipe(pipefds);
        
#endif
		DUP2(pipefds[1], FILENO(stdout));

        RTICdrTypeCode_print_IDL(typeCode, 0);
        fflush(stdout);

        // TODO Mejorar usando select o poll para comprobar.
		if((readLen = READ(pipefds[0], m_buffer, m_tcMaxSize)) > 0)
        {
           returnedValue = m_buffer;
        }

        CLOSE(pipefds[0]);
        CLOSE(pipefds[1]);

        // Restore STDOUT
        DUP2(oldStdout, FILENO(stdout));
        clearerr(stdout);
        fsetpos(stdout, &pos);
    }

    return returnedValue;
}

/*char* TypeCodeDB::getPrintIDL(RTICdrTypeCode *typeCode)
{

}*/
