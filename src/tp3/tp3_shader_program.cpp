#include "tp3_shader_program.h"

//
/// Fragment Shader
//

void Tp3FragmentShader::bindOutputs(UINT programHandle)
{

}

//
/// Vertex Shader
//

void Tp3VertexShader::bindAttributes(UINT programHandle)
{

}

//
/// Shader Program
//

Tp3ShaderProgram::Tp3ShaderProgram(BOOL* isPointLightOn, BOOL* isSpotLightOn, 
                                   BOOL* isDirectionalLightOn) : ShaderProgram(),
    mIsPointLightOn(isPointLightOn),             mIsSpotLightOn(isSpotLightOn), 
    mIsDirectionalLightOn(isDirectionalLightOn)
{
    mFragmentShader = new Tp3FragmentShader();
    mVertexShader = new Tp3VertexShader();
    
    mFragmentShader->load();
    mVertexShader->load();

    attachFragmentShader(mFragmentShader);
    attachVertexShader(mVertexShader);
}

Tp3ShaderProgram::~Tp3ShaderProgram()
{
    delete mFragmentShader;
    delete mVertexShader;
}

void Tp3ShaderProgram::bindUniforms()
{
    // TODO getUniformLocation should cache uniform location
    glUniform1i(getUniformLocation("texUnit0"), 0);
    glUniform1i(getUniformLocation("texUnit1"), 1);
    glUniform1i(getUniformLocation("texUnit2"), 2);

    glUniform1i(getUniformLocation("uIsPointLightOn"), *mIsPointLightOn);
    glUniform1i(getUniformLocation("uIsSpotLightOn"), *mIsSpotLightOn);
    glUniform1i(getUniformLocation("uIsDirectionalLightOn"), *mIsDirectionalLightOn);
}