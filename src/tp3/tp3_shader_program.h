#ifndef TP1_SHADER_PROGRAM_H
#define TP1_SHADER_PROGRAM_H

#include "fragment_shader.h"
#include "shader_program.h"
#include "vertex_shader.h"

//
/// Fragment Shader
//

class Tp3FragmentShader : public FragmentShader
{
public:
    Tp3FragmentShader() : FragmentShader("tp3_fragment_shader.glsl") { };
    virtual ~Tp3FragmentShader() { };

    virtual void bindOutputs(UINT programHandle);
};

//
/// Vertex Shader
//

class Tp3VertexShader : public VertexShader
{
public:
    Tp3VertexShader() : VertexShader("tp3_vertex_shader.glsl") { };
    virtual ~Tp3VertexShader() { };

    virtual void bindAttributes(UINT programHandle);
};

//
/// Shader Program
//

class Tp3ShaderProgram : public ShaderProgram
{
public:
    Tp3ShaderProgram(BOOL* isPointLightOn, BOOL* isSpotLightOn, BOOL* isDirectionalLightOn);
    virtual ~Tp3ShaderProgram();

    virtual void bindUniforms();

private:
    Tp3FragmentShader* mFragmentShader;
    Tp3VertexShader* mVertexShader;

    BOOL* mIsPointLightOn;
    BOOL* mIsSpotLightOn;
    BOOL* mIsDirectionalLightOn;
};

#endif