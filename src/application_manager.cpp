#include "application.h"
#include "application_manager.h"
#include "common.h"
#include "console_logger.h"

//
/// Statis Definitions
//

ApplicationManager* ApplicationManager::sInstance = NULL;

ApplicationManager* ApplicationManager::get()
{
    if ( sInstance == NULL )
        sInstance = new ApplicationManager();

    return sInstance;
}

void ApplicationManager::destroy()
{
    delete sInstance;
    sInstance = NULL;
}

void ApplicationManager::log(const CHAR* message)
{
    Application* application = get()->getApplication();
    if ( application != NULL )
        application->getLogger()->log(message);
}

void ApplicationManager::log(CHAR* format, ...)
{
    Application* application = get()->getApplication();
    if ( application != NULL )
        application->getLogger()->log(format, "TODO - COrrect ME");
}

ApplicationManager::ApplicationManager() : 
    mApplication(NULL)
{
}

ApplicationManager::~ApplicationManager()
{

}

void ApplicationManager::startApplication(Application* application)
{
    mApplication = application;
    application->start();
}

Application* ApplicationManager::getApplication()
{
    return mApplication;
}