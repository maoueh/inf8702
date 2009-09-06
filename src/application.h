#ifndef APPLICATION
#define APPLICATION

#include "common.h"
#include "keyboard_listener.h"
#include "mouse_listener.h"
#include "window_listener.h"

class CommandLine;
class Window;
class Logger;

class Application : public KeyboardListener, MouseListener, WindowListener
{
public:
    Application(CommandLine* commandLine);
    virtual ~Application();

    void start();
    void stop();

    inline Logger* getLogger();

    virtual void   keyDown(Window* window, INT keyCode, INT repeat);
    virtual void   keyUp(Window* window, INT keyCode);

    virtual void   mousePressed(Window* window, INT button);
    virtual void   mouseReleased(Window* window, INT button);
    virtual void   mouseDoubleClicked(Window* window, INT button);

    virtual void   mouseMoved(Window* window);
    virtual void   mouseDragged(Window* window);

    virtual void   mouseWheel(Window* window);

    virtual void   windowClosed(Window* window);

protected:
    Application(const Application&);
    Application& operator=(const Application& rightSide);

    virtual void    consumeCommandLine();
    virtual void    initialize();

    virtual void    process() = 0;
    virtual STRING& getName() = 0;

    CommandLine* mCommandLine;
    BOOL         mIsWindowed;
    BOOL         mContinueApplication;
    Logger*      mLogger;
    Window*      mWindow;

};

#include "application.inl"

#endif