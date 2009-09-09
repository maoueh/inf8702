#include "application_manager.h"
#include "tp2_application.h"
#include "command_line.h"

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    ApplicationManager::get()->startApplication(new Tp2Application(&commandLine));

    ApplicationManager::destroy();
    return 0;
}
