#ifndef TP1_APPLICATION_H
#define TP1_APPLICATION_H

#include "color.h"
#include "opengl_application.h"

class ShaderProgram;
class Window;

class Tp1Application : public OpenGlApplication
{
public:
    Tp1Application(CommandLine* commandLine);
    virtual ~Tp1Application();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    virtual void    keyPressed(Window* window, INT keyCode, INT repeat);

    virtual void    mousePressed(MouseEvent& event);
    virtual void    mouseDragged(MouseEvent& event);

    virtual void    draw();

private:
    void compileCubeList(FLOAT size);
    void compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);

    STRING mName;
    ShaderProgram* mShaderProgram;
    BOOL mIsShaderOn;

    INT mLastMouseX;
    INT mLastMouseY;

    UINT mCubeListId;
    UINT mQuadGridListId;

    Color mCubeColor;
    INT   mActiveColorComponent;

    FLOAT mRotationAngleX;
    FLOAT mRotationAngleY;
    FLOAT mRotationAngleZ;

    FLOAT mRotationFreqX;
    FLOAT mRotationFreqY;
    FLOAT mRotationFreqZ;

    FLOAT mAxisScaleFactor;
    BOOL mAutomaticRotation;

    FLOAT mFramerate;
};

#endif