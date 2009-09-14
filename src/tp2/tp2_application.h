#ifndef TP2_APPLICATION_H
#define TP2_APPLICATION_H

#include "color.h"
#include "opengl_application.h"

class ShaderProgram;
class TextureUnit;
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

    virtual void    updateWorld();

private:
    void initializeTextures();
    void applyTextures();
    void deactivateTextures();

    void compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal);

    void updateLights();

    STRING mName;
    ShaderProgram* mShaderProgram;
    BOOL mIsShaderOn;

    INT mLastMouseX;
    INT mLastMouseY;

    TextureUnit* m3dLabsTextureUnit;
    TextureUnit* mRustTextureUnit;
    TextureUnit* mStonewallTextureUnit;

    UINT mQuadGridListId;

    Color mCubeColor;
    Color mFogColor;
    INT   mActiveColorComponent;

    FLOAT mPointLightPosition[4];
    Color mPointLightAmbient;
    Color mPointLightDiffuse;
    Color mPointLightSpecular;
    Color mPointLightEmission;

    Color mSpotLightAmbient;
    Color mSpotLightDiffuse;
    Color mSpotLightSpecular;
    Color mSpotLightEmission;

    FLOAT mDirectionalLightPosition[4];
    Color mDirectionalLightAmbient;
    Color mDirectionalLightDiffuse;
    Color mDirectionalLightSpecular;
    Color mDirectionalLightEmission;

    Color mMaterialAmbient;
    Color mMaterialDiffuse;
    Color mMaterialSpecular;
    Color mMaterialEmission;
    FLOAT mMaterialShininess[1];

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
};

#endif