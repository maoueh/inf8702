#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include "shader.h"

class FragmentShader : public Shader
{
public:
    FragmentShader(const STRING& filename);
    virtual ~FragmentShader();

    virtual void load();
    virtual UINT getHandle();

    virtual void bindOutputs(UINT programHandle) = 0;

private:
    virtual void printLog();

    UINT mHandle; 
};

#endif