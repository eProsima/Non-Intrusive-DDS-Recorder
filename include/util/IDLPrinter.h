#ifndef _UTIL_IDLPRINTER_H_
#define _UTIL_IDLPRINTER_H_

#include <sstream>
#include <unordered_map>
#include <stdint.h>

namespace eProsima
{
    class IDLPrinter : public std::ostringstream
    {
    public:

        IDLPrinter();

		IDLPrinter(IDLPrinter &printer);

        IDLPrinter(IDLPrinter &&printer);

        bool isTypePrinterAndUp(const std::string &typeName);

        std::string str();

		bool addPrinter(std::string &&typeName, IDLPrinter &&printer);

		bool operator<(const IDLPrinter &printer) const;

		IDLPrinter& operator=(IDLPrinter &&printer);

    private:

        std::unordered_map<std::string, IDLPrinter> m_typePrinters;

		uint32_t m_priority;

		uint32_t m_currentGlobalPriority;
    };
};

#endif // _UTIL_IDLPRINTER_H_
