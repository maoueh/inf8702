#include "tp2_shader_program.h"

//
/// Fragment Shader
//

void Tp2FragmentShader::bindOutputs(UINT programHandle)
{

}

//
/// Vertex Shader
//

void Tp2VertexShader::bindAttributes(UINT programHandle)
{

}

//
/// Shader Program
//

Tp2ShaderProgram::Tp2ShaderProgram() : ShaderProgram()
{
    mFragmentShader = new Tp2FragmentShader();
    mVertexShader = new Tp2VertexShader();
    
    mFragmentShader->load();
    mVertexShader->load();

    attachFragmentShader(mFragmentShader);
    attachVertexShader(mVertexShader);
}

Tp2ShaderProgram::~Tp2ShaderProgram()
{
    delete mFragmentShader;
    delete mVertexShader;
}

void Tp2ShaderProgram::bindUniforms()
{
    /*glUniform1f(getUniformLocation("uRedComponent"), 1.0f);
    glUniform1f(getUniformLocation("uGreenComponent"), 0.0f);
    glUniform1f(getUniformLocation("uBlueComponent"), 0.0f);*/
}