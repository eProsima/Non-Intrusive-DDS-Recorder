#ifndef _UTIL_IDLPRINTER_H_
#define _UTIL_IDLPRINTER_H_

#include <sstream>
#include <unordered_map>
#include <stdint.h>

namespace eprosima
{
    class IDLPrinter
    {
    public:

        IDLPrinter();

		IDLPrinter(IDLPrinter &printer);

        IDLPrinter(IDLPrinter &&printer);

        virtual ~IDLPrinter();

        bool isTypePrinterAndUp(const std::string &typeName);

        std::string str();

		bool addPrinter(std::string &&typeName, IDLPrinter *printer);

		IDLPrinter& operator=(IDLPrinter &&printer);

        std::ostringstream& getOut();

        friend bool IDLPrinter_cmp(IDLPrinter *printer1, IDLPrinter *printer2);

    private:

        std::unordered_map<std::string, IDLPrinter*> m_typePrinters;

        std::ostringstream m_out;

		uint32_t m_priority;

		uint32_t m_currentGlobalPriority;
    };

    bool IDLPrinter_cmp(IDLPrinter *printer1, IDLPrinter *printer2);
};

#endif // _UTIL_IDLPRINTER_H_
