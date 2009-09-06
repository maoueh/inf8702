#include "application_manager.h"
#include "tp1_application.h"
#include "command_line.h"

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    ApplicationManager::get()->startApplication(new Tp1Application(&commandLine));

    ApplicationManager::destroy();
    return 0;
}
