#pragma once

#include <string>

class DetailedException
{
private:
	const int m_line;
	const char* m_file;
	const std::string m_what;
public:
	DetailedException(std::string details, const int line, const char* file);
	std::string details();
	std::string what();
};

