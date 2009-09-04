#ifndef BRICK_SHADER_PROGRAM
#define BRICK_SHADER_PROGRAM

#include "fragment_shader.h"
#include "shader_program.h"
#include "vertex_shader.h"

//
/// Fragment Shader
//

class BrickFragmentShader : public FragmentShader
{
public:
    BrickFragmentShader() : FragmentShader("brick_fragment_shader.glsl") { };
    virtual ~BrickFragmentShader() { };

    virtual void bindOutputs(UINT programHandle);
};

//
/// Vertex Shader
//

class BrickVertexShader : public VertexShader
{
public:
    BrickVertexShader() : VertexShader("brick_vertex_shader.glsl") { };
    virtual ~BrickVertexShader() { };

    virtual void bindAttributes(UINT programHandle);
};

//
/// Shader Program
//

class BrickShaderProgram : public ShaderProgram
{
public:
    BrickShaderProgram();
    virtual ~BrickShaderProgram();

    virtual void bindUniforms();

private:
    BrickFragmentShader* mFragmentShader;
    BrickVertexShader* mVertexShader;
};

#endif