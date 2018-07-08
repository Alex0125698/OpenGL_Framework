#include "DetailedException.h"

DetailedException::DetailedException(std::string details, const int line, const char* file)
	: m_line(line), m_file(file), m_what(details.c_str())
{
}

std::string DetailedException::details()
{
	std::string s = "Error thrown in file: ";
	s += m_file;
	s += "\non line: ";
	s += std::to_string(m_line) + "\n";
	return s;
}

std::string DetailedException::what()
{
	return m_what;
}
