#ifndef _UTIL_IDLPRINTER_H_
#define _UTIL_IDLPRINTER_H_

#include <sstream>
#include <unordered_map>
#include <stdint.h>

namespace eProsima
{
    class IDLPrinter
    {
    public:

        IDLPrinter();

		IDLPrinter(IDLPrinter &printer);

        IDLPrinter(IDLPrinter &&printer);

        bool isTypePrinterAndUp(const std::string &typeName);

        std::string str();

		bool addPrinter(std::string &&typeName, IDLPrinter *printer);

		bool operator<(const IDLPrinter &printer) const;

		IDLPrinter& operator=(IDLPrinter &&printer);

        std::ostringstream& getOut();

    private:

        std::unordered_map<std::string, IDLPrinter*> m_typePrinters;

        std::ostringstream m_out;

		uint32_t m_priority;

		uint32_t m_currentGlobalPriority;
    };
};

#endif // _UTIL_IDLPRINTER_H_
