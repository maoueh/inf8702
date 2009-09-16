#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include "application.h"

class CommandLine;

class OpenGlApplication : public Application
{
public:
    OpenGlApplication(CommandLine* commandLine);
    virtual ~OpenGlApplication();

protected:
    OpenGlApplication(const Application&);
    OpenGlApplication& operator=(const OpenGlApplication& rightSide);

    virtual void    initialize();

    virtual void    process();
    virtual STRING& getName() = 0;

    virtual void    keyPressed(Window* window, int keyCode, int repeat);

    virtual void    windowResized(WindowEvent& event);

    virtual void    draw() = 0;
    virtual void    updateCamera();
    virtual void    updateProjection();
    virtual void    updateViewport();
    virtual void    updateWorld();
    virtual void    idle(); // TODO Default behavior not implemented right now

    // A value of -1 is considered as infinite (or non-blocked) framerate
    void setFramerate(INT framerate);

    BOOL  mIsPerspective;

    INT   mFramerate;

    // TODO Encapsulate
    FLOAT mCameraTheta;
    FLOAT mCameraRho;
    FLOAT mCameraPhi;

    FLOAT mCameraX;
    FLOAT mCameraY;
    FLOAT mCameraZ;

};

#endif