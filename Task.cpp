#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include "Task.h"
#include "Utilities.h"

size_t Task::field_width = 1;

//Default constructor
Task::Task(const std::string& taskRecord): slots("1"){
	pNextTask[Quality::passed] = 0;
	pNextTask[Quality::redirect] = 0;

	Utilities u;
	std::vector<std::string> tokens;
	std::string token;
	bool more = true; //are there any tokens left?
	size_t pos = 0; //starting position of string search
	while (more)
	{
		token = u.nextToken(taskRecord, pos, more);
		if (pos == taskRecord.size()) { more = false; }
		tokens.emplace_back(token);
		field_width = (tokens.size() == 1 && u.getFieldWidth() > field_width) ? u.getFieldWidth() : field_width;
		
	}

	name = tokens.at(0);
	if (tokens.size() >= 2) {
		slots = tokens.at(1);
		if (tokens.size() >= 3) {
			nextTask[Quality::passed] = tokens.at(2);
			if (tokens.size() == 4) {
				nextTask[Quality::redirect] = tokens.at(3);
			}
		}
	}
	tokens.clear();

}

bool Task::validate(const Task& t) {
	unsigned empty = 0;
	for (unsigned nT = 0; nT < 2; nT++) {
		if (nextTask[nT].empty()) {
			empty++;
			if (empty == 2) { return true; }
			continue;
		}
		if (nextTask[nT] == t.name) {
			pNextTask[nT] = &t;
		}
	}

	for (unsigned rT = 0; rT < 2; rT++) {
		if (!nextTask[rT].empty() && !pNextTask[rT]) {
			return false;
		}
	}

	return true;
}

const std::string& Task::getName() const {
	return name;
}

unsigned int Task::getSlots()const {
	return std::stoul(slots);
}

const Task* Task::getNextTask(Quality quality)const {
	std::string err;
	if (pNextTask[quality] == 0) {
		err = "*** Validate [" + nextTask[quality] + "] @ [" + name + "] ***";
		throw err;
	}
	return pNextTask[quality];
}

void Task::display(std::ostream& os) const {
	
	std::string unvalidated = "*** to be validated ***";
	os << std::left << "Task Name   " << " : " << std::setw(field_width + 2) << "[" + name + "]" << " [" + slots + "]" << std::endl;

	std::string next[] = { "Continue to", "Redirect to" };
	for (int t = 0; t < 2; t++){
		if(!nextTask[t].empty()){
			os << " " << std::right << next[t] << " : " << std::left << std::setw(field_width+2) << "[" + nextTask[t] + "]";
			if (pNextTask[t] == 0) { 
				os << " " + unvalidated; 
			} 
			os << std::endl;
		}
	}
}

size_t Task::getFieldWidth() {
	return field_width;
}

bool operator==(const Task& tl, const Task& tr) {

	return true;
}


