#include "brick_shader_application.h"
#include "brick_shader_program.h"
#include "logger.h"

BrickShaderApplication::BrickShaderApplication(CommandLine* commandLine) : Application(commandLine),
    mName("Brick Shader")
{

}

BrickShaderApplication::~BrickShaderApplication()
{

}

void BrickShaderApplication::initialize()
{
    Application::initialize();

    BrickShaderProgram* brickShaderProgram = new BrickShaderProgram();
    //brickShaderProgram->use();
}

void BrickShaderApplication::process()
{
}