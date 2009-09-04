#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

class Logger
{
public:
    virtual ~Logger() { }

    virtual void log(const CHAR* message) = 0;
    // Warning : The resulting string is limited to 4096 characters
    virtual void log(CHAR* format, ...) = 0;
};

#endif