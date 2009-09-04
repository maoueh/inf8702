#include "command_line.h"

CommandLine::CommandLine(STRING commandLine) :
    mCurrentPosition(-1), mTokens()
{
    char* nextToken = NULL;
    char* token = strtok_s((CHAR*) commandLine.c_str(), " ", &nextToken);
	while (token != NULL) {
        mTokens.push_back(STRING(token));
		token = strtok_s(NULL, " ", &nextToken);
	}
}

CommandLine::CommandLine(INT argumentCount, const CHAR** arguments) : 
    mCurrentPosition(-1), mTokens()
{
    for ( int i = 0; i < argumentCount; ++i )
    {
        mTokens.push_back(STRING(arguments[i]));
    }
}

INT CommandLine::getTokenCount()
{
    return (INT) mTokens.size();
}

BOOL CommandLine::hasMoreTokens()
{
    return (INT) mTokens.size() > (mCurrentPosition + 1);
}

const CHAR* CommandLine::getNextToken()
{
    return mTokens[++mCurrentPosition].c_str();
}

void CommandLine::resetIterator()
{
    mCurrentPosition = -1;
}