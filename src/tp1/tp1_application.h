#ifndef TP1_APPLICATION_H
#define TP1_APPLICATION_H

#include "opengl_application.h"

class ShaderProgram;

class Tp1Application : public OpenGlApplication
{
public:
    Tp1Application(CommandLine* commandLine);
    virtual ~Tp1Application();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    void draw();

private:
    void compileCubeList(FLOAT size);
    void compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);

    ShaderProgram* mShaderProgram;

    STRING mName;
    UINT mCubeListId;
    UINT mQuadGridListId;

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