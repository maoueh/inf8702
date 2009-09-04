#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <vector>

#include "common.h"

class CommandLine
{
public:
    CommandLine(STRING commandLine);
    CommandLine(INT argumentCount, const CHAR** arguments);

    INT getTokenCount();

    BOOL hasMoreTokens();
    const CHAR* getNextToken();

    void resetIterator();

private:
    int mCurrentPosition;
    vector<string> mTokens;

};

#endif