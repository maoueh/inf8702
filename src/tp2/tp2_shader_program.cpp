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

Tp2ShaderProgram::Tp2ShaderProgram(BOOL* isPointLightOn, BOOL* isSpotLightOn, 
                                   BOOL* isDirectionalLightOn) : ShaderProgram(),
    mIsPointLightOn(isPointLightOn),             mIsSpotLightOn(isSpotLightOn), 
    mIsDirectionalLightOn(isDirectionalLightOn)
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
    // TODO getUniformLocation should cache uniform location
    glUniform1i(getUniformLocation("texUnit0"), 0);
    glUniform1i(getUniformLocation("texUnit1"), 1);
    glUniform1i(getUniformLocation("texUnit2"), 2);

    glUniform1i(getUniformLocation("uIsPointLightOn"), *mIsPointLightOn);
    glUniform1i(getUniformLocation("uIsSpotLightOn"), *mIsSpotLightOn);
    glUniform1i(getUniformLocation("uIsDirectionalLightOn"), *mIsDirectionalLightOn);
}