#include "../header/parser.hpp"
using namespace std;


// define tokens recognised by rshell
#define T_OPEN_PARENTHESIS "("
#define T_CLOSE_PARENTHESIS ")"
#define T_OR "||"
#define T_AND "&&"
#define T_SEMICOLON ";"
#define T_QUOTE "\""

Parser::Parser(std::string userInput)
{
	this->userInput = userInput;
}


// helper function to get tokens from inside vector of tokens, will check bounds
// and ensure tokens are removed and will return null if vector is empty
char * getNextToken( std::vector<char *> & inputTokens )
{
    char * token = NULL ;
    if( inputTokens.size() > 0 )
    {
        token = inputTokens.front();
        inputTokens.erase( inputTokens.begin() );
    }
    return  token;
}


// parse input string, deligate construction of command to parseToken functions
void Parser::Parse()
{
    std::string newInput = "";

    // parse string and insert spaces were appropraite
    for(unsigned long i = 0; i < this->userInput.size(); i++)
    {
        if (this->userInput.at(i) == '#')
        {
            if(i == 0)
            {
                return;
            }
            newInput.push_back(this->userInput.at(i) );
        }
        else if (this->userInput.at(i) == ';'){
            newInput.push_back(' ');
            newInput.push_back(this->userInput.at(i) );
        }
            // handle strings inside double quotation
        else if (this->userInput.at(i) == '"'){
            // push space before and after " so when we later split each will be a token
            newInput.push_back(' ');
            newInput.push_back(this->userInput.at(i) );
            newInput.push_back(' ');
        }
        else if( this->userInput.at(i) == ')' || this->userInput.at(i) == '(' )
        {
            // push space before and after )( so when we later split each will be a token
            newInput.push_back(' ');
            newInput.push_back(this->userInput.at(i) );
            newInput.push_back(' ');
        }
        else
        {
            newInput.push_back(this->userInput.at(i) );
        }
    }


    // vector will hold tokens and strings
    std::vector<char *> inputTokens;

    // split newInput at space
    char * stringA = const_cast<char *>(newInput.c_str());

    // copy token to inputTokens vector
    char *token = strtok(stringA," ");
    while( token )
    {
        inputTokens.push_back( token );
        token = strtok(NULL, " ");
    }

    // call parseToken to construct commands from inputToken
    Base * exe = parseToken( inputTokens );
    // execute returned command
    exe->executed();

    // return void
    return;
}


Base * Parser::parseToken( std::vector<char *> & inputTokens )
{
    std::vector<Base *> commandObjects;
    
    vector<int> connectors;
    vector<char*> commands;

    // get next token
    char * token = getNextToken( inputTokens );

    // while token is not null
    while (token)
    {
        if( strcmp(token, T_SEMICOLON) == 0 )
        {
            connectors.push_back(0);

            token = getNextToken( inputTokens );
        }
        else if( strcmp(token, T_AND) == 0 )
        {
            connectors.push_back(1);

            token = getNextToken( inputTokens );
        }
        else if( strcmp(token, T_OR) == 0 )
        {
            connectors.push_back(2);

            token = getNextToken( inputTokens );
        }
        else if( strcmp(token, T_OPEN_PARENTHESIS) == 0 )
        {
            // parse command inside parenthesis
            // call parseToken to construct commands from inputToken
            Base * command = parseToken( inputTokens );
            commandObjects.push_back(command);

            // get next token, expect )
            token = getNextToken( inputTokens );
        }
        else if( strcmp(token, T_CLOSE_PARENTHESIS) == 0 )
        {
            // found close parenthesis token, break and return to original caller
            break;
        }
        else
        {
            // create command
            std::string * cmd;
            // check is command is inside double quote
            if( strcmp(token, T_QUOTE) == 0 )
            {
                // get string inside quote
                token = getNextToken( inputTokens );
                cmd = new string(token);
                // discard closing quote
                token = getNextToken( inputTokens );
            }
            else
            {
                // command is not inside quote
                cmd = new string(token);
            }


            // create vector to hold arguments to command
            vector<char *> arg;

            token = getNextToken( inputTokens );

            // continue reading arguments while we have not read connectors token
            while ( token &&
                    (strcmp(token, T_OR) != 0) &&
                    (strcmp(token, T_AND) != 0) &&
                    (strcmp(token, T_SEMICOLON) != 0) &&
                    (strcmp(token, T_OPEN_PARENTHESIS) != 0) &&
                    (strcmp(token, T_CLOSE_PARENTHESIS) != 0) )
            {
                // while reading arguments of command, check if argument is inside double quotation
                if( strcmp(token, T_QUOTE) == 0 )
                {
                    // if argument is inside quotation, append the following tokens as a single string
                    // until we hit the closing quotation mark.

                    // create temporal quote_arg to hold string inside quotation
                    std::string quote_arg("");
                    // ignore the opening "

                    token = getNextToken( inputTokens );

                    while( token )
                    {
                        quote_arg += token;
                        quote_arg += " ";

                        token = getNextToken( inputTokens );

                        if( strcmp(token, T_QUOTE) == 0 )
                            break;
                    }
                    // remove " "
                    quote_arg.pop_back();

                    // copy std::string to char [] or char *, allocate memory for char array using malloc
                    char * c_str_arg = (char *)malloc( quote_arg.size() );
                    strcpy( c_str_arg, quote_arg.c_str() );

                    // push the retrieve string inside double quotation to arg
                    arg.push_back( c_str_arg );

                    token = getNextToken( inputTokens );

                } else
                {
                    // push token to arg
                    arg.push_back( token );

                    token = getNextToken( inputTokens );
                }
            }

            // create executable for command and argument.
            Base * command = new Executable( *cmd , arg );
            commandObjects.push_back( command );
        }
    }
    
    Base * commandOne;
    Base * commandTwo;

    // if there are connectors, then create them.
    if( connectors.size() > 0 )
    {
        int commandsIndex = 0;
        for( int i = 0; i < connectors.size(); i++ )
        {
            // get the first two commands
            commandOne = commandObjects.at( 0 );
            commandTwo = commandObjects.at( 1 );
            if( connectors[i] == 0 )
            {
                Base * connector = new Semicolon ( commandOne, commandTwo );

                // del or erase the first two command
                commandObjects.erase( commandObjects.begin() );
                commandObjects.erase( commandObjects.begin() );

                // insert connector command to the beginning of commandObjects.
                commandObjects.insert( commandObjects.begin(), connector );
            } else if( connectors[i] == 1 )
            {
                Base * connector = new And ( commandOne, commandTwo );

                // del or erase the first two command
                commandObjects.erase( commandObjects.begin() );
                commandObjects.erase( commandObjects.begin() );

                // insert connector command to the beginning of commandObjects.
                commandObjects.insert( commandObjects.begin(), connector );
            } else if( connectors[i] == 2 )
            {
                Base * connector = new Or ( commandOne, commandTwo );

                // del or erase the first two command
                commandObjects.erase( commandObjects.begin() );
                commandObjects.erase( commandObjects.begin() );

                // insert connector command to the beginning of commandObjects.
                commandObjects.insert( commandObjects.begin(), connector );
            }
        }
    }

    return commandObjects.at( 0 );
}
