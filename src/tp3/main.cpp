#include "application_manager.h"
#include "command_line.h"
#include "tp3_application.h"

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    ApplicationManager::get()->startApplication(new Tp3Application(&commandLine));

    ApplicationManager::destroy();
    return 0;
}
