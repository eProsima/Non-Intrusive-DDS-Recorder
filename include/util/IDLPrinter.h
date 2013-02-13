#ifndef _UTIL_IDLPRINTER_H_
#define _UTIL_IDLPRINTER_H_

#include <sstream>
#include <unordered_map>

namespace eProsima
{
    class IDLPrinter : public std::ostringstream
    {
    public:

        IDLPrinter(){}

        IDLPrinter(IDLPrinter &&printer);

        bool isTypePrinter(std::string &typeName);

        std::string str();

    private:

        std::unordered_map<std::string, IDLPrinter> m_typePrinters;
    };
};

#endif _UTIL_IDLPRINTER_H_
