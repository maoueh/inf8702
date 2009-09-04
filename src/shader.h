#ifndef SHADER
#define SHADER

#include "common.h"

class Shader
{
public:
    Shader(const STRING& filename);
    virtual ~Shader();

    virtual void load() = 0;
    virtual UINT getHandle() = 0;

    inline const STRING& getFilename();
    inline const STRING& getSource();

protected:
    STRING mFilename;
    STRING mSource;

private:
    virtual void printLog() = 0;

    void readSource();
};

#include "shader.inl"

#endif