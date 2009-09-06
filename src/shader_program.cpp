#include "shader_program.h"

#include "application_manager.h"
#include "fragment_shader.h"
#include "vertex_shader.h"

ShaderProgram::ShaderProgram() :
    mHandle(NULL), mFragmentShader(NULL), mVertexShader(NULL),
    mFragmentShaderHandle(NULL), mVertexShaderHandle(NULL),
    mIsLinked(FALSE)
{
    mHandle = glCreateProgram();
}

ShaderProgram::ShaderProgram(FragmentShader* fragmentShader, VertexShader* vertexShader) : 
    mHandle(NULL), mFragmentShader(NULL), mVertexShader(NULL),
    mFragmentShaderHandle(fragmentShader->getHandle()), mVertexShaderHandle(vertexShader->getHandle())
{
    mHandle = glCreateProgram();

    attachFragmentShader(fragmentShader);
    attachVertexShader(vertexShader);
}

ShaderProgram::~ShaderProgram()
{
    if ( mFragmentShader != NULL )
    {
        glDetachShader(mHandle, mFragmentShaderHandle);
        mFragmentShader = NULL;
        mFragmentShaderHandle = NULL;
    }

    if ( mVertexShaderHandle != NULL )
    {
        glDetachShader(mHandle,mVertexShaderHandle);
        mVertexShader = NULL;
        mVertexShaderHandle = NULL;
    }

    glDeleteProgram(mHandle);
}

void ShaderProgram::attachVertexShader(VertexShader* vertexShader)
{
    mVertexShader = vertexShader;
    mVertexShaderHandle = vertexShader->getHandle();

    glAttachShader(mHandle, mVertexShaderHandle);
}

void ShaderProgram::attachFragmentShader(FragmentShader* fragmentShader)
{
    mFragmentShader = fragmentShader;
    mFragmentShaderHandle = fragmentShader->getHandle();

    glAttachShader(mHandle, mFragmentShaderHandle);
}

void ShaderProgram::link()
{
    if ( mVertexShader != NULL )
        mVertexShader->bindAttributes(mHandle);
    if ( mFragmentShader != NULL )
        mFragmentShader->bindOutputs(mHandle);

    glLinkProgram(mHandle);

    INT isLinked = 0;
    glGetProgramiv(mHandle, GL_LINK_STATUS, &isLinked);
    mIsLinked = isLinked != 0;

#ifdef DEBUG
    printLog();
#endif
}

void ShaderProgram::use()
{
    assert(mIsLinked == TRUE && "Program not linked yet");

    glUseProgram(mHandle);
    bindUniforms();
}

INT ShaderProgram::getUniformLocation(const CHAR* uniformName)
{
	assert(mIsLinked == TRUE && "Program not linked yet");

	INT location = glGetUniformLocation(mHandle, uniformName);

	assert(location != -1 && "Location doesn't exist");
    //printRendererError();

    return location;
}

void ShaderProgram::printLog()
{
    ApplicationManager::get()->log("====== Shader Program Log ======");

    int logMessageLength = 0;
	glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &logMessageLength);

	if ( logMessageLength > 1 )
	{
        int charactersWritten = 0;
		CHAR* logMessage = (CHAR*) malloc(logMessageLength);
		glGetProgramInfoLog(mHandle, logMessageLength, &charactersWritten, logMessage);

		ApplicationManager::get()->log(logMessage);
        ApplicationManager::get()->log(""); // Newline
		free(logMessage);
	} 
    else 
    {
        ApplicationManager::get()->log("Linkage Successful\n");
    }
}