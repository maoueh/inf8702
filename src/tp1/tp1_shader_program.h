#ifndef TP1_SHADER_PROGRAM_H
#define TP1_SHADER_PROGRAM_H

#include "fragment_shader.h"
#include "shader_program.h"
#include "vertex_shader.h"

//
/// Fragment Shader
//

class Tp1FragmentShader : public FragmentShader
{
public:
    Tp1FragmentShader() : FragmentShader("tp1_fragment_shader.glsl") { };
    virtual ~Tp1FragmentShader() { };

    virtual void bindOutputs(UINT programHandle);
};

//
/// Vertex Shader
//

class Tp1VertexShader : public VertexShader
{
public:
    Tp1VertexShader() : VertexShader("tp1_vertex_shader.glsl") { };
    virtual ~Tp1VertexShader() { };

    virtual void bindAttributes(UINT programHandle);
};

//
/// Shader Program
//

class Tp1ShaderProgram : public ShaderProgram
{
public:
    Tp1ShaderProgram();
    virtual ~Tp1ShaderProgram();

    virtual void bindUniforms();

private:
    Tp1FragmentShader* mFragmentShader;
    Tp1VertexShader* mVertexShader;
};

#endif