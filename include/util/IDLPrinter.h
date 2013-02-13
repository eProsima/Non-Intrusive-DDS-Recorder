#ifndef _UTIL_IDLPRINTER_H_
#define _UTIL_IDLPRINTER_H_

#include <sstream>
#include <map>
#include <vector>

namespace eProsima
{
    class IDLPrinter : public std::ostringstream
    {
    public:

        IDLPrinter(){}

        IDLPrinter(IDLPrinter &&printer);

        bool addTypeName(std::string &&typeName);

        std::string str();

    private:

        std::vector<IDLPrinter> m_typePriters;
        std::map<std::string, std::vector<IDLPrinter>::iterator> m_typeNames;
    };
};

#endif _UTIL_IDLPRINTER_H_
