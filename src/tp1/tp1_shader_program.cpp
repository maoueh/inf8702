#include "tp1_shader_program.h"

//
/// Fragment Shader
//

void Tp1FragmentShader::bindData(UINT programHandle)
{
    //glBindFragDataLocation( programHandle, 0, "mFragmentColor" );
}

//
/// Vertex Shader
//

void Tp1VertexShader::bindAttributes(UINT programHandle)
{
  /*  glBindAttribLocation( programHandle, 1, "mModelCoordVertex" );
    glBindAttribLocation( programHandle, 2, "mModelCoordNormal" );*/
}

//
/// Shader Program
//

Tp1ShaderProgram::Tp1ShaderProgram() : ShaderProgram()
{
    mFragmentShader = new Tp1FragmentShader();
    mVertexShader = new Tp1VertexShader();
    
    mFragmentShader->load();
    mVertexShader->load();

    attachFragmentShader(mFragmentShader);
    attachVertexShader(mVertexShader);
}

Tp1ShaderProgram::~Tp1ShaderProgram()
{
    delete mFragmentShader;
    delete mVertexShader;
}

void Tp1ShaderProgram::bindVariables()
{
   /* glUniform3f(Utils::getUniformLocation(mHandle, "mBrickColor"), 1.0f, 0.3f, 0.2f);
    glUniform3f(Utils::getUniformLocation(mHandle, "mMortarColor"), 0.85f, 0.86f, 0.84f);
    glUniform2f(Utils::getUniformLocation(mHandle, "mBrickSize"), 0.30f, 0.15f);
    glUniform2f(Utils::getUniformLocation(mHandle, "mBrickProportion"), 0.90f, 0.85f);
    glUniform3f(Utils::getUniformLocation(mHandle, "mLightPosition"), 0.0f, 0.0f, 4.0f);*/
}