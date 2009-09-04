#include "brick_shader_program.h"

//
/// Fragment Shader
//

void BrickFragmentShader::bindData(UINT programHandle)
{
    glBindFragDataLocation( programHandle, 0, "mFragmentColor" );
}

//
/// Vertex Shader
//

void BrickVertexShader::bindAttributes(UINT programHandle)
{
    glBindAttribLocation( programHandle, 1, "mModelCoordVertex" );
    glBindAttribLocation( programHandle, 2, "mModelCoordNormal" );
}

//
/// Shader Program
//

BrickShaderProgram::BrickShaderProgram() : ShaderProgram()
{
    mFragmentShader = new BrickFragmentShader();
    mVertexShader = new BrickVertexShader();
    
    mFragmentShader->load();
    mVertexShader->load();

    attachFragmentShader(mFragmentShader);
    attachVertexShader(mVertexShader);
}

BrickShaderProgram::~BrickShaderProgram()
{
    delete mFragmentShader;
    delete mVertexShader;
}

void BrickShaderProgram::bindVariables()
{
    glUniform3f(Utils::getUniformLocation(mHandle, "mBrickColor"), 1.0f, 0.3f, 0.2f);
    glUniform3f(Utils::getUniformLocation(mHandle, "mMortarColor"), 0.85f, 0.86f, 0.84f);
    glUniform2f(Utils::getUniformLocation(mHandle, "mBrickSize"), 0.30f, 0.15f);
    glUniform2f(Utils::getUniformLocation(mHandle, "mBrickProportion"), 0.90f, 0.85f);
    glUniform3f(Utils::getUniformLocation(mHandle, "mLightPosition"), 0.0f, 0.0f, 4.0f);
}