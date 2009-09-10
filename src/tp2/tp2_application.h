#ifndef TP2_APPLICATION_H
#define TP2_APPLICATION_H

#include "color.h"
#include "opengl_application.h"

class ShaderProgram;
class Window;

class Tp2Application : public OpenGlApplication
{
public:
    Tp2Application(CommandLine* commandLine);
    virtual ~Tp2Application();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    virtual void    keyPressed(Window* window, INT keyCode, INT repeat);

    virtual void    mousePressed(Window* window, INT button, INT x, INT y);
    virtual void    mouseDragged(Window* window, INT x, INT y);

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
    Color mFogColor;
    INT   mActiveColorComponent;

    FLOAT mRotationAngleX;
    FLOAT mRotationAngleY;
    FLOAT mRotationAngleZ;

    FLOAT mRotationFreqX;
    FLOAT mRotationFreqY;
    FLOAT mRotationFreqZ;

    FLOAT mAxisScaleFactor;
    BOOL mAutomaticRotation;

    BOOL mIsSpotLightOn;
    BOOL mIsDirectionalLightOn;
    BOOL mIsPointLightOn;

    FLOAT mFramerate;
};

#endif