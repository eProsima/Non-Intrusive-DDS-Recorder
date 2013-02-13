#include "util/IDLPrinter.h"

using namespace eProsima;

IDLPrinter::IDLPrinter(IDLPrinter &&printer) : m_typeNames(std::move(printer.m_typeNames))
{
    int i = 0;
    ++i;
}

bool IDLPrinter::isTypePrinter(std::string &typeName)
{
    /*std::pair<std::map<std::string, std::vector<IDLPrinter>::iterator>::iterator, bool> ret = m_typeNames.insert(std::move(typeName));

    if(!ret.second)
    {
    }
    return ret.second;*/
    return false;
}

std::string IDLPrinter::str()
{
    this->clear();
    return "";
}