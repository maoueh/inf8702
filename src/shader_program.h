#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "common.h"

class FragmentShader;
class VertexShader;

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(FragmentShader* fragmentShader, VertexShader* vertexShader);
    virtual ~ShaderProgram();

    void attachVertexShader(VertexShader* vertexShader);
    void attachFragmentShader(FragmentShader* fragmentShader);

    void link();
    void use();

    virtual void bindVariables() = 0;

protected:
    UINT mHandle;
    UINT mFragmentShaderHandle;
    UINT mVertexShaderHandle;
    BOOL mIsLinked;

    FragmentShader* mFragmentShader;
    VertexShader* mVertexShader;

private:
    void printLog();
};

#endif