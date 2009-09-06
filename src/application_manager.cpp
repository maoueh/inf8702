#include "application.h"
#include "application_manager.h"
#include "common.h"
#include "console_logger.h"

//
/// Static Definitions
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

// A newline is automaticaly added at the end of each message
void ApplicationManager::log(const CHAR* message)
{
    Application* application = get()->getApplication();
    if ( application != NULL )
        application->getLogger()->log(message);
}

// A newline is automaticaly added at the end of each message
// Warning : The resulting string is limited to 4096 characters
void ApplicationManager::log(CHAR* format, ...)
{
    Application* application = get()->getApplication();
    if ( application != NULL )
    {
        // Put variables into the string
	    CHAR* arguments = (CHAR*) &format + sizeof(format);

	    CHAR buffer[4096];
        vsprintf_s( buffer, 4096, format, arguments );

        application->getLogger()->log(buffer);
    }
}

//
/// Class Definitions
//

ApplicationManager::ApplicationManager() : 
    mApplication(NULL)
{
}

ApplicationManager::~ApplicationManager()
{
    delete mApplication;
    mApplication = NULL;
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