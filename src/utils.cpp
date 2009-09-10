#include "utils.h"

#include <fstream>
#include <sstream>

template<typename T> STRING Utils::toString(const T &value)
{
	ostringstream stream;
	stream << value;

	return stream.str();		
}

STRING& Utils::toLowerCase(STRING& value)
{
    for (UINT i = 0; i < value.length(); ++i)
        value[i] = tolower(value[i]);

    return value;
}

STRING& Utils::toUpperCase(STRING& value)
{
    for (UINT i = 0; i < value.length(); ++i)
        value[i] = toupper(value[i]);

    return value;
}

// Warning : The resulting string is limited to 4096 characters
STRING Utils::format(CHAR* stringFormat, ...)
{	
	// Put variables into the string
	CHAR* arguments = (CHAR*) &stringFormat + sizeof(stringFormat);

	CHAR buffer[4096];
    vsprintf_s( (CHAR*) buffer, 4096, stringFormat, arguments );

	return STRING( buffer );
}

BOOL Utils::readFileContent(const STRING& filename, STRING& destination)
{
    ifstream file( filename.c_str() );
    if ( file.is_open() )
    {
        destination.clear();

        string line;
        while ( !file.eof() )
        {
            getline( file, line );
            destination.append(line);
            destination.append("\n");
        }

        file.close();
        return TRUE;
    }

    return FALSE;
}

BOOL Utils::writeFileContent(const STRING& filename, const STRING& content)
{
    ofstream file( filename.c_str() );
    if ( file.is_open() )
    {
        file << content;

        file.close();
        return TRUE;
    }

    return FALSE;
}