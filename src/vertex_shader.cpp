#include "vertex_shader.h"

#include "application_manager.h"

VertexShader::VertexShader(const STRING& filename) : Shader(filename),
    mHandle(NULL)
{
    mHandle = glCreateShader(GL_VERTEX_SHADER);
}

VertexShader::~VertexShader()
{
    glDeleteShader(mHandle);
}

void VertexShader::load()
{
    const CHAR* sources[1] = { mSource.c_str() };
    glShaderSource(mHandle, 1, sources, NULL);
    glCompileShader(mHandle);

#ifdef DEBUG
    printLog();
#endif
}

UINT VertexShader::getHandle()
{
    return mHandle;
}

void VertexShader::printLog()
{
    ApplicationManager::get()->log("====== Vertex Shader Log ======");

    INT logMessageLength = 0;
	glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &logMessageLength);

	if ( logMessageLength > 1 )
	{
        INT charactersWritten = 0;
		CHAR* logMessage = (CHAR*) malloc(logMessageLength);
		glGetShaderInfoLog(mHandle, logMessageLength, &charactersWritten, logMessage);

		ApplicationManager::get()->log(logMessage);
		free(logMessage);
	} 
    else 
    {
        ApplicationManager::get()->log("Compilation Successful\n");
    }
}