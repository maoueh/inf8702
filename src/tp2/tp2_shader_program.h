#ifndef TP1_SHADER_PROGRAM_H
#define TP1_SHADER_PROGRAM_H

#include "fragment_shader.h"
#include "shader_program.h"
#include "vertex_shader.h"

//
/// Fragment Shader
//

class Tp2FragmentShader : public FragmentShader
{
public:
    Tp2FragmentShader() : FragmentShader("tp2_fragment_shader.glsl") { };
    virtual ~Tp2FragmentShader() { };

    virtual void bindOutputs(UINT programHandle);
};

//
/// Vertex Shader
//

class Tp2VertexShader : public VertexShader
{
public:
    Tp2VertexShader() : VertexShader("tp2_vertex_shader.glsl") { };
    virtual ~Tp2VertexShader() { };

    virtual void bindAttributes(UINT programHandle);
};

//
/// Shader Program
//

class Tp2ShaderProgram : public ShaderProgram
{
public:
    Tp2ShaderProgram(BOOL* isPointLightOn, BOOL* isSpotLightOn, BOOL* isDirectionalLightOn);
    virtual ~Tp2ShaderProgram();

    virtual void bindUniforms();

private:
    Tp2FragmentShader* mFragmentShader;
    Tp2VertexShader* mVertexShader;

    BOOL* mIsPointLightOn;
    BOOL* mIsSpotLightOn;
    BOOL* mIsDirectionalLightOn;
};

#endif