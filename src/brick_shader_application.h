#ifndef BRICK_SHADER_APPLICATION
#define BRICK_SHADER_APPLICATION

#include "application.h"

class BrickShaderApplication : public Application
{
public:
    BrickShaderApplication(CommandLine* commandLine);
    virtual ~BrickShaderApplication();

protected:
    virtual void    initialize();
    virtual void    process();
    virtual STRING& getName() { return mName; }

private:
    STRING mName;

};

#endif