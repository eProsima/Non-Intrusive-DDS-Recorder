/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "util/IDLPrinter.h"
#include <algorithm>
#include <vector>

using namespace eprosima;

bool eprosima::IDLPrinter_cmp(IDLPrinter *printer1, IDLPrinter *printer2)
{
	return printer1->m_priority < printer2->m_priority;
}

IDLPrinter::IDLPrinter() : m_priority(0), m_currentGlobalPriority(0)
{
}

IDLPrinter::IDLPrinter(IDLPrinter &printer) : m_typePrinters(std::move(printer.m_typePrinters)),
	m_priority(printer.m_currentGlobalPriority), m_currentGlobalPriority(++printer.m_currentGlobalPriority)
{
}

IDLPrinter::IDLPrinter(IDLPrinter &&printer) : m_typePrinters(std::move(printer.m_typePrinters)),
	m_priority(printer.m_priority), m_currentGlobalPriority(printer.m_currentGlobalPriority)
{
    m_out << printer.m_out.str();
}

IDLPrinter::~IDLPrinter()
{
    std::unordered_map<std::string, IDLPrinter*>::iterator it = m_typePrinters.begin();

    while(it != m_typePrinters.end())
    {
        delete (*it).second;
        it = m_typePrinters.erase(it);
    }
}

IDLPrinter& IDLPrinter::operator=(IDLPrinter &&printer)
{
	this->m_priority = printer.m_priority;
	this->m_currentGlobalPriority = printer.m_currentGlobalPriority;
	std::swap(this->m_typePrinters, printer.m_typePrinters); 
    m_out << printer.m_out.str();
	return *this;
}

bool IDLPrinter::isTypePrinterAndUp(const std::string &typeName)
{
	bool returnedValue = false;
	std::unordered_map<std::string, IDLPrinter*>::iterator it = m_typePrinters.find(typeName);

	if(it != m_typePrinters.end())
	{
		(*it).second->m_priority = m_currentGlobalPriority++;
		returnedValue = true;
	}

	return returnedValue;
}

std::string IDLPrinter::str()
{
	m_out.str("");
	m_out.clear();
	std::vector<IDLPrinter*> vec;

	for(std::unordered_map<std::string, IDLPrinter*>::iterator it = m_typePrinters.begin(); it != m_typePrinters.end(); ++it)
	{
		vec.push_back(std::move((*it).second));
	}
	std::sort(vec.begin(), vec.end(), IDLPrinter_cmp);

	for(std::vector<IDLPrinter*>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
	{
		m_out << (*it)->m_out.str();
	}

    return m_out.str();
}

bool IDLPrinter::addPrinter(std::string &&typeName, IDLPrinter *printer)
{
	this->m_currentGlobalPriority = printer->m_currentGlobalPriority;
	std::swap(this->m_typePrinters, printer->m_typePrinters);
	std::pair<std::string, IDLPrinter*> pair(std::move(typeName), printer);
	std::pair<std::unordered_map<std::string, IDLPrinter*>::iterator, bool> ret = this->m_typePrinters.insert(std::move(pair));

	return true;
}

std::ostringstream& IDLPrinter::getOut() 
{
    return m_out;
}
