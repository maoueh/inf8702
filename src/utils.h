#ifndef UTILS
#define UTILS

#include "common.h"

class Utils
{
public:
	template<typename T> static STRING toString(const T &value);

    static BOOL readFileContent(const STRING& filename, STRING& destination);
    static BOOL writeFileContent(const STRING& filename, const STRING& content);

	// Warning : The resulting string is limited to 4096 characters
	static STRING format(CHAR* format, ...);

    static INT getUniformLocation(UINT programHandle, const CHAR* name);
};

#endif