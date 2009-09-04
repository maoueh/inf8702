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

    static void log(const CHAR* message);
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