#include "../header/base.hpp"
#include "../header/executable.hpp"
#include<sys/wait.h> 
#include<unistd.h>
#include<iostream>
#include<string.h>
#include <cstring>

using namespace std;

Executable::Executable() { }

Executable::Executable(std::string userCommand , vector<char *> args )
{
	command = userCommand;
	argument = args;
}

bool Executable::executed()
{
    // convert vector<char *> argument to char *[] c_str_arg  so we can pass to execvp
	char * c_str_arg[argument.size()+2];
	int i = 1;
    // as space before argument so command execute properly
	c_str_arg[0] = " ";
	for( char * s: argument)
	{
		c_str_arg[i] = s;
		i++;
	}
    // assign null to the end argument to pass to execvp
	c_str_arg[argument.size()+1] = NULL;

    // convert std::string command to char []
	char c_str_cmd[command.length()];
	strcpy( c_str_cmd, command.c_str() );


	pid_t pid = fork();

	if (pid == -1 )
	{
		// check fork error
        perror("ERROR EXECUTING");
        exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		// child process
		if(execvp(c_str_cmd, c_str_arg ) == -1)
		{
			perror("ERROR EXECUTING");
			exit(0);
		}
	}
	else if(pid > 0)
	{
		// parent process
        int status;
        if(waitpid(pid, &status, 0) == -1){
            perror("WAITING FOR CHILD");
        }
        if(WEXITSTATUS(status) != 0) {
            return false;
        }
	}
	return true;
}
