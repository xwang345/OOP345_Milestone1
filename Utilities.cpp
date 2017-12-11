#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "Utilities.h"

char Utilities::delimiter = 0;
std::ofstream Utilities::logFile;

Utilities::Utilities(): field_width(1){}

size_t Utilities::getFieldWidth() const {
	return field_width;
}

const std::string Utilities::nextToken(const std::string& s, size_t& a, bool& b) {
	std::string token;

	while (a < s.size()) {
		if (s.at(a) == delimiter) { a++;  break; }
		token += s.at(a);		
		a++;
	}

	while (*(token.begin()) == ' ') {
		token.erase(token.begin());
	}

	while (*(token.end() - 1) == ' ' ) {
		token.erase(token.end() - 1);
	}
	
	field_width = token.size();
	return std::move(token);
}

void Utilities::setDelimiter(const char d) {
	 delimiter = d;
}

void Utilities::setLogFile(const char* filename) {
	 if (!filename) {
		 throw std::string("Filename variable is empty");
	 }
	 
	 logFile.open(filename, logFile.out | logFile.trunc);
	 if (!logFile) throw std::string("Error opening file");
}


 std::ofstream& Utilities::getLogFile() {
	 return logFile;
}

