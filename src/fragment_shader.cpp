#include "fragment_shader.h"

#include "application_manager.h"

FragmentShader::FragmentShader(const STRING& filename) : Shader(filename),
    mHandle(NULL)
{
    mHandle = glCreateShader(GL_FRAGMENT_SHADER); 
}

FragmentShader::~FragmentShader()
{
    glDeleteShader(mHandle);
}

void FragmentShader::load()
{
    const CHAR* sources[1] = { mSource.c_str() };
    glShaderSource(mHandle, 1, sources, NULL);
    glCompileShader(mHandle);

#ifdef DEBUG
    printLog();
#endif
}

UINT FragmentShader::getHandle()
{
    return mHandle;
}

void FragmentShader::printLog()
{
    ApplicationManager::get()->log("====== Fragment Shader Log (%s) ======", mFilename.c_str());

    INT logMessageLength = 0;
	glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &logMessageLength);

	if ( logMessageLength > 1 )
	{
        INT charactersWritten = 0;
		CHAR* logMessage = (CHAR*) malloc(logMessageLength);
		glGetShaderInfoLog(mHandle, logMessageLength, &charactersWritten, logMessage);

		ApplicationManager::get()->log(logMessage);
        ApplicationManager::get()->log(""); // Newline
		free(logMessage);
	} 
    else 
    {
        ApplicationManager::get()->log("Compilation Successful\n");
    }
}