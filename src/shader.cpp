#include "shader.h"

//
//// Constructor/Destructor
//

Shader::Shader(const STRING& filename) :
    mFilename(filename), mSource()
{
    readSource();
}

Shader::~Shader()
{
}

void Shader::readSource()
{
    Utils::readFileContent(mFilename, mSource);
}