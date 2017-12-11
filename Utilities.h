#pragma once

#include <string>
#include <fstream>

class Utilities {
	size_t field_width;           // maximum field width needed 
	static char delimiter;        // field delimiter character
	static std::ofstream logFile; // log file
public:
	Utilities();
	size_t getFieldWidth() const;
	const std::string nextToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char);
	static void setLogFile(const char*);
	static std::ofstream& getLogFile();
};
