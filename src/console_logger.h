#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "logger.h"

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger();
    virtual ~ConsoleLogger();

    // A newline is automaticaly added at the end of each message
    virtual void log(const CHAR* message);

    // A newline is automaticaly added at the end of each message
    // Warning : The resulting string is limited to 4096 characters
    virtual void log(CHAR* format, ...);
};

#endif