#ifndef UTILS
#define UTILS

#include "common.h"

class Utils
{
public:
	template<typename T> static STRING toString(const T &value);

    static STRING& toLowerCase(STRING& value);
    static STRING& toUpperCase(STRING& value);

    static BOOL readFileContent(const STRING& filename, STRING& destination);
    static BOOL writeFileContent(const STRING& filename, const STRING& content);

	// Warning : The resulting string is limited to 4096 characters
	static STRING format(CHAR* format, ...);
};

#endif