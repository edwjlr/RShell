#ifndef PARSER_HPP
#define PARSER_HPP
#include "base.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include "executable.hpp"
#include "and.hpp"
#include "semicolon.hpp"
#include "or.hpp"
using namespace std;


// No reason for inherit class Base
class Parser
{
	private:
		std::string userInput;
	public:
		Parser(std::string userInput);
		void Parse();
        Base * parseToken( std::vector<char *> & inputTokens );
};
#endif
