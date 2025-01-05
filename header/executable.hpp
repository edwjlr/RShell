#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP
#pragma once
#include "base.hpp"
#include <string>
#include <vector>
using namespace std;

class Executable : public Base {
	public:
        // command will hold actual command
		std::string command;
        // vector will hold arguments to command
		vector<char *> argument;

		Executable();
		Executable(std::string, vector<char  *> args );
	virtual bool executed();
};

#endif
