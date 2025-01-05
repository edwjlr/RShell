#include<iostream>
#include"../header/executable.hpp"
#include"../header/parser.hpp"
using namespace std;

int main(){
	while (1)
	{
		string userInput;
		cout << "$ ";
		getline(cin, userInput);
		if(userInput == "exit")
			break;
		Parser* run = new Parser(userInput);
		run->Parse();
	}

	return 0;
}
