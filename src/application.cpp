#include "application.h"
#include "command_line.h"
#include "console_logger.h"
#include "rendering_context.h"
#include "window.h"

//
//// Constructor/Destructor
//

Application::Application(CommandLine* commandLine) : 
    mCommandLine(commandLine), mWindow(NULL), mIsWindowed(WINDOWED_MODE), mContinueGameLoop(TRUE),
    mLogger(new ConsoleLogger()), mWindowProcedure(NULL)
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
//// Members
//

void Application::initialize()
{
    assert(mWindowProcedure != NULL && "forgot setWindowProcedure(..) ?");

    if ( mCommandLine->hasMoreTokens() )
        consumeCommandLine();

    mWindow = new Window("INF8702", getName().c_str(), mIsWindowed);
    mWindow->setRenderingContext(new RenderingContext());

    mWindow->initialize(mWindowProcedure, mIsWindowed);

    mWindow->show();
}

void Application::start()
{
    initialize();

   	while( mContinueGameLoop )
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
}

void Application::consumeMessage(UINT messageId)
{
	switch(messageId)
	{
	  case WM_DESTROY:
      {
			mContinueGameLoop = FALSE;
			PostQuitMessage(0);
            break;
      }
	}
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