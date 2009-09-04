#include "application_manager.h"
#include "brick_shader_application.h"
#include "command_line.h"

//
//// Definitions
//

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParameter, LPARAM lParameter);

//
//// Variables
//

ApplicationManager* gApplicationManager = NULL;

int main(int argumentCount, const CHAR** arguments)
{
    // "" is the command line
    CommandLine commandLine(argumentCount, arguments);
    Application* application = new BrickShaderApplication(&commandLine);
    application->setWindowProcedure(WindowProcedure);

    gApplicationManager = ApplicationManager::get();
    gApplicationManager->startApplication(application);

    delete application;

    return 0;
}

//int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, INT commanShow) 
//{
//    gApplication = new BrickShaderApplication(commandLine);
//    gApplication->setWindowProcedure(WindowProcedure);
//
//    gApplication->start();
//
//    delete gApplication;	
//}


LRESULT WINAPI WindowProcedure(HWND windowHandle, UINT messageId, WPARAM wParameter, LPARAM lParameter)
{
    gApplicationManager->getApplication()->consumeMessage(messageId);
    return DefWindowProc( windowHandle, messageId, wParameter, lParameter );
}

