#include "application_manager.h"
#include "brick_shader_application.h"
#include "command_line.h"

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    ApplicationManager::get()->startApplication(new BrickShaderApplication(&commandLine));

    ApplicationManager::destroy();
    return 0;
}
