#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "shader.h"

class VertexShader : public Shader
{
public:
    VertexShader(const STRING& filename);
    virtual ~VertexShader();

    virtual void load();
    virtual UINT getHandle();

    virtual void bindAttributes(UINT programHandle) = 0;

private:
    virtual void printLog();

    UINT mHandle; 
};

#endif