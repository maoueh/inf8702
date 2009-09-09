#include "application.h"
#include "command_line.h"
#include "console_logger.h"
#include "rendering_context.h"
#include "window.h"

//
//// Application Constructor/Destructor
//

Application::Application(CommandLine* commandLine) : 
    mCommandLine(commandLine), mWindow(NULL), mIsWindowed(WINDOWED_MODE), 
    mContinueApplication(TRUE), mLogger(new ConsoleLogger())
{
}

Application::~Application()
{
    delete mLogger;
    mLogger = NULL;

    delete mWindow;
    mWindow = NULL;
}

//
//// Application Members
//

void Application::initialize()
{
    if ( mCommandLine->hasMoreTokens() )
        consumeCommandLine();

    mWindow = new Window("INF8702", getName().c_str(), mIsWindowed);
    mWindow->setRenderingContext(new RenderingContext());

    mWindow->initialize(mIsWindowed);

    mWindow->addKeyboardListener(this);
    mWindow->addMouseListener(this);
    mWindow->addWindowListener(this);

    mWindow->show();
}

void Application::start()
{
    initialize();

   	while( mContinueApplication )
	{
        MSG message = {0, 0, 0};
        // Let the OS live a little..
		while( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

        process();
	}

    PostQuitMessage(0);
}

void Application::stop()
{
    mContinueApplication = FALSE;
}

void Application::consumeCommandLine()
{
    do {
        const CHAR* token = mCommandLine->getNextToken();

        if ( strcmp(token, "--windowed-mode") == MATCH )
        {
            mIsWindowed = true;
            break;
        }
    } while (mCommandLine->hasMoreTokens());
}

void Application::windowClosed(Window* window)
{
    stop();
}