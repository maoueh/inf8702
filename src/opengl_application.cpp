#include "command_line.h"
#include "logger.h"
#include "opengl_application.h"
#include "window.h"

OpenGlApplication::OpenGlApplication(CommandLine* commandLine) : Application(commandLine),
    mCameraTheta(DEG2RAD(270.0f)), mCameraPhi(DEG2RAD(90.0f)), mCameraRho(30.0f),
    mCameraX(0.0), mCameraY(0.0), mCameraZ(0.0)
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

void OpenGlApplication::updateCamera()
{
   mCameraX = mCameraRho * cos(mCameraTheta) * sin(mCameraPhi);
   mCameraY = mCameraRho * sin(mCameraTheta) * sin(mCameraPhi);
   mCameraZ = mCameraRho * cos(mCameraPhi);

   gluLookAt(mCameraX, mCameraY, mCameraZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void OpenGlApplication::updateProjection()
{
    FLOAT height = (FLOAT) mWindow->getWidth();
    if ( height != 0 )
        gluPerspective(60.0, (FLOAT) mWindow->getWidth() / height, 0.1, 300.0);
}

void OpenGlApplication::updateWorld()
{

}