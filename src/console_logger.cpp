#include "console_logger.h"

ConsoleLogger::ConsoleLogger() : Logger()
{

}

ConsoleLogger::~ConsoleLogger()
{

}

// Newline is automaticaly added at the end of each message
void ConsoleLogger::log(const CHAR* message)
{
    cout << message << endl;
}

// Newline is automaticaly added at the end of each message
// Warning : The resulting string is limited to 4096 characters
void ConsoleLogger::log(CHAR* format, ...)
{
	// Put variables into the string
	CHAR* arguments = (CHAR*) &format + sizeof(format);

	CHAR buffer[4096];
    vsprintf_s( buffer, 4096, format, arguments );

    cout << buffer << endl;
}