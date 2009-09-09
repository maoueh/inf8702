#include "command_line.h"
#include "logger.h"
#include "opengl_application.h"
#include "window.h"

OpenGlApplication::OpenGlApplication(CommandLine* commandLine) : Application(commandLine),
    mCameraTheta(DEG2RAD(270.0f)), mCameraPhi(DEG2RAD(90.0f)), mCameraRho(30.0f),
    mCameraX(0.0), mCameraY(0.0), mCameraZ(0.0), mIsPerspective(TRUE)
{

}

OpenGlApplication::~OpenGlApplication()
{

}

void OpenGlApplication::initialize()
{
    Application::initialize();

    glewInit();
    if ( !glewIsSupported("GL_VERSION_2_0") ) 
    {
	    mLogger->log("OpenGL version 2.0 or above required");
        exit(1);
    }

    glShadeModel(GL_SMOOTH);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGlApplication::process()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    updateWorld();
    updateCamera();

    draw(); 

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    updateProjection();

    mWindow->swapBuffers();
}

void OpenGlApplication::keyPressed(Window* window, INT keyCode, INT repeat)
{
   switch(keyCode) 
   {
      case VK_ESCAPE : // Fall Through
      case VK_Q :
		stop();
        break;
      case VK_P :
         mIsPerspective = !mIsPerspective;
         break;
      case VK_MINUS :  // Fall Through
      case VK_MINUS_2 :
         // The camera goes backward
         mCameraRho += 2.0f;
         break;
      case VK_PLUS : // Fall Through
      case VK_PLUS_2 :
         // The camera goes foward
         mCameraRho -= 2.0f;
         if (mCameraRho <= 1.0f)
            mCameraRho = 1.0f;
         break;
      case VK_RIGHT :
         mCameraTheta += DEG2RAD(2.0f);
         break;
      case VK_LEFT :
         mCameraTheta -= DEG2RAD(2.0f);
         break;
      case VK_UP :
         mCameraPhi -= DEG2RAD(2.0f);
         break;
      case VK_DOWN :
         mCameraPhi += DEG2RAD(2.0f);
         break;
   }
}

void OpenGlApplication::windowResized(Window* window, INT width, INT height)
{
    updateViewport();
}

void OpenGlApplication::updateCamera()
{
   mCameraX = mCameraRho * cos(mCameraTheta) * sin(mCameraPhi);
   mCameraY = mCameraRho * sin(mCameraTheta) * sin(mCameraPhi);
   mCameraZ = mCameraRho * cos(mCameraPhi);

   gluLookAt(mCameraX, mCameraY, mCameraZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void OpenGlApplication::updateProjection()
{
    FLOAT height = (FLOAT) mWindow->getHeight();
    if (mIsPerspective)
    {
        if ( height != 0 )
            gluPerspective(60.0, (FLOAT) mWindow->getWidth() / height, 0.1, 300.0);
    } 
    else
    {
        FLOAT width = (FLOAT) mWindow->getWidth();
        if ( width <= height && width != 0.0 ) 
            glOrtho(-10.0, 10.0, -10.0 * height / width, 10.0 * height / width, 0.01, 300.0);
        else if ( height != 0.0 )
            glOrtho(-10.0 * width / height, 10.0 * width / height, -10.0, 10.0, 0.01, 300.0);
    }
}

void OpenGlApplication::updateViewport()
{
    glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
    draw();
}


void OpenGlApplication::updateWorld()
{

}