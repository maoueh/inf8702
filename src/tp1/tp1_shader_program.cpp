#include "tp1_shader_program.h"

//
/// Fragment Shader
//

void Tp1FragmentShader::bindOutputs(UINT programHandle)
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

void Tp1ShaderProgram::bindUniforms()
{
    glUniform1f(getUniformLocation("uRedComponent"), 1.0f);
    glUniform1f(getUniformLocation("uGreenComponent"), 0.0f);
    glUniform1f(getUniformLocation("uBlueComponent"), 0.0f);
}