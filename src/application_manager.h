#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "common.h"

class Application;
class Logger;

class ApplicationManager
{
public:
    static ApplicationManager* get();
    static void destroy();

    // A newline is automaticaly added at the end of each message
    static void log(const CHAR* message);

    // A newline is automaticaly added at the end of each message
    // Warning : The resulting string is limited to 4096 characters
    static void log(CHAR* format, ...);

    Application* getApplication();

    void startApplication(Application* application);

private:
    static ApplicationManager* sInstance;

    // Class cannot be instantiated outside
    ApplicationManager();
    ApplicationManager(const ApplicationManager& other);
    ApplicationManager& operator=(const ApplicationManager& rightSide);
    ~ApplicationManager();

    Application* mApplication;
};

#endif