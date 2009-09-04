#ifndef APPLICATION
#define APPLICATION

#include "common.h"

class CommandLine;
class Window;
class Logger;

class Application
{
public:
    Application(CommandLine* commandLine);
    virtual ~Application();

    void start();

    inline Logger* getLogger();

    // System Dependent Methods
    void consumeMessage(UINT message);

    inline void setInstance(HINSTANCE instance);
    inline void setWindowProcedure(WNDPROC windowProcedure);

protected:
    Application(const Application&);
    Application& operator=(const Application& rightSide);

    virtual void    consumeCommandLine();
    virtual void    initialize();

    virtual void    process() = 0;
    virtual STRING& getName() = 0;

    CommandLine* mCommandLine;
    BOOL         mIsWindowed;
    BOOL         mContinueGameLoop;
    Window*      mWindow;
    Logger*      mLogger;

private:
    // System Dependent Members
    WNDPROC   mWindowProcedure;
    HINSTANCE mInstance;

};

#include "application.inl"

#endif