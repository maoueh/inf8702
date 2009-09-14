#include "tp3_application.h"
#include "tp3_shader_program.h"

#include "color.h"
#include "logger.h"
#include "texture_unit.h"
#include "window.h"

#define FOG_DELTA 10.0f

Tp3Application::Tp3Application(CommandLine* commandLine) : OpenGlApplication(commandLine),
    mName("Tp3 - INF8702"),  
    mRotationAngleX(0.0f),    mRotationAngleY(0.0f),       mRotationAngleZ(0.0f),
    mRotationFreqX(0.15f),    mRotationFreqY(0.1f),        mRotationFreqZ(0.2f),
    mIsSpotLightOn(TRUE),     mIsDirectionalLightOn(TRUE), mIsPointLightOn(TRUE),
    m3dLabsTextureUnit(NULL), mRustTextureUnit(NULL),      mStonewallTextureUnit(NULL),
    mPointLightAmbient(0.0f, 0.0f, 0.0f),          mPointLightDiffuse(1.0f, 0.5f, 1.0f),
    mPointLightSpecular(1.0f, 0.5f, 1.0f),         mPointLightEmission(1.0f, 1.0f, 1.0f),
    mSpotLightAmbient(0.0f, 0.0f, 0.0f),           mSpotLightDiffuse(1.0f, 1.0f, 1.0f),
    mSpotLightSpecular(1.0f, 1.0f, 1.0f),          mSpotLightEmission(1.0f, 1.0f, 1.0f),
    mDirectionalLightAmbient(0.0f, 0.0f, 0.0f),    mDirectionalLightDiffuse(0.86f, 0.69f, 0.04f),
    mDirectionalLightSpecular(0.91f, 0.93f, 0.0f), mDirectionalLightEmission(1.0f, 1.0f, 1.0f),
    mMaterialAmbient(0.0f, 0.0f, 0.0f),            mMaterialDiffuse(1.0f, 1.0f, 1.0f),
    mMaterialSpecular(1.0f, 1.0f, 1.0f),           mMaterialEmission(0.0f, 0.0f, 0.0f),
    mActiveColorComponent(RED_COMPONENT),          mIsShaderOn(FALSE),
    mFogColor(Color::BLACK),                       mCubeColor(Color::RED), 
    mLastMouseX(0),                                mLastMouseY(0),
    mAxisScaleFactor(15.0f),                       mAutomaticRotation(FALSE)
{
     mPointLightPosition[0] = 20.0f;
     mPointLightPosition[1] = 10.0f;
     mPointLightPosition[2] = 3.0f;
     mPointLightPosition[3] = 1.0f;

     mDirectionalLightPosition[0] = -60.0f;
     mDirectionalLightPosition[1] = 0.0f;
     mDirectionalLightPosition[2] = 3.0f;
     mDirectionalLightPosition[3] = 0.0f;

     mMaterialShininess[0] = 100.0f;
}

Tp3Application::~Tp3Application()
{
}

void Tp3Application::initialize()
{
    OpenGlApplication::initialize();

    // Separate calculation of the specular contribution after texturing is done
    glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ); 
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE ); 
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); // Two-side mode in OpenGL
    glEnable( GL_VERTEX_PROGRAM_TWO_SIDE );            // Two-side mode in GLSL            

    initializeTextures();

    // Compile Display List
    compileQuadGridList(20.0f, 30, 30, TRUE);

    // The Vertex and Fragment Shaders are initialized in the constructor
    mShaderProgram = new Tp3ShaderProgram(&mIsPointLightOn, &mIsSpotLightOn, &mIsDirectionalLightOn);
    mShaderProgram->link();
}

void Tp3Application::compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal)
{
    mQuadGridListId = glGenLists(1);
    glNewList(mQuadGridListId, GL_COMPILE);
    {
        applyTextures();
        drawQuadGrid(size, rowCount, columnCount, isOutsideNormal);
    }
    glEndList();
}

void Tp3Application::drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal) 
{
   INT normFact = isOutsideNormal ? 1 : -1;
   
   FLOAT startX = -size / 2.0f;
   FLOAT startY = 0.0f;
   FLOAT startZ = size / 2.0f;
   FLOAT s1, t1, s2, t2;

   FLOAT incrementX = size / (FLOAT) columnCount;
   FLOAT incrementZ = size / (FLOAT) rowCount;

   glBegin(GL_QUADS);
   glNormal3f(0.0f, (FLOAT) normFact, 0.0f);

   for ( INT i = 0; i < columnCount; ++i )
   {
      for ( INT k = 0; k < rowCount; ++k )
      {
         s1 = (i * incrementX) / size;
         s2 = ((i + 1) * incrementX) / size;
         t1 = (k * incrementZ) / size;
         t2 = ((k + 1) * incrementZ) / size;

         glMultiTexCoord2f(GL_TEXTURE0, s1, t1); 
         glMultiTexCoord2f(GL_TEXTURE1, s1, t1); 
         glMultiTexCoord2f(GL_TEXTURE2, s1, t1); 
         glVertex3f(startX + i * incrementX, 0.0f, startZ - k * incrementZ);

         glMultiTexCoord2f(GL_TEXTURE0, s2, t1); 
         glMultiTexCoord2f(GL_TEXTURE1, s2, t1); 
         glMultiTexCoord2f(GL_TEXTURE2, s2, t1); 
         glVertex3f((startX + i * incrementX) + incrementX, 0.0f, startZ - k * incrementZ);

         glMultiTexCoord2f(GL_TEXTURE0, s2, t2); 
         glMultiTexCoord2f(GL_TEXTURE1, s2, t2); 
         glMultiTexCoord2f(GL_TEXTURE2, s2, t2); 
         glVertex3f((startX + i * incrementX) + incrementX, 0.0f, (startZ - k * incrementZ) - incrementZ);

         glMultiTexCoord2f(GL_TEXTURE0, s1, t2); 
         glMultiTexCoord2f(GL_TEXTURE1, s1, t2); 
         glMultiTexCoord2f(GL_TEXTURE2, s1, t2); 
         glVertex3f(startX + i * incrementX, 0.0f, (startZ - k * incrementZ) - incrementZ);
      }
   }
   glEnd();
}

void Tp3Application::keyPressed(Window* window, INT keyCode, INT repeat)
{
   FLOAT* component = NULL; 
   switch(keyCode) 
   {
      case VK_X :
         mIsShaderOn = !mIsShaderOn;
         break;
      case VK_F1 :
         mActiveColorComponent = RED_COMPONENT;
         break;
      case VK_F2 :
         mActiveColorComponent = GREEN_COMPONENT;
         break;
      case VK_F3 :
         mActiveColorComponent = BLUE_COMPONENT;
         break;
      case VK_PRIOR : // Page Up
         component = &mCubeColor.components[mActiveColorComponent];
         *component = CLIP(*component + 0.05f, 0.0f, 1.0f);
         break;
      case VK_NEXT :  // Page Down
         component = &mCubeColor.components[mActiveColorComponent];
         *component = CLIP(*component - 0.05f, 0.0f, 1.0f);
         break;
      case VK_S : 
         mIsSpotLightOn = !mIsSpotLightOn;               // Toggle Spot Light
         break;
      case VK_D :
         mIsDirectionalLightOn = !mIsDirectionalLightOn; // Toggle Directional Light
         break;
      case VK_A :
         mIsPointLightOn = !mIsPointLightOn;             // Toggle Point Light
         break;
      case VK_SPACE :
         mAutomaticRotation = !mAutomaticRotation;       // Toggle Automatic Rotation
         break;
	}

    OpenGlApplication::keyPressed(window, keyCode, repeat);
}

void Tp3Application::mousePressed(Window* window, INT button, INT x, INT y)
{
    if ( button == MOUSE_BUTTON_LEFT )
    {
        mLastMouseX = x;
        mLastMouseY = y;
    }
}

void Tp3Application::mouseDragged(Window* window, INT x, INT y)
{
    mRotationAngleX += y - mLastMouseY;
    mRotationAngleZ -= x - mLastMouseX;

    mLastMouseX = x;
    mLastMouseY = y;
}

void Tp3Application::draw()
{
	glFogi (GL_FOG_MODE,    GL_LINEAR);
    glFogf (GL_FOG_START,   mCameraRho);
	glFogf (GL_FOG_END,     mCameraRho + FOG_DELTA);
    glFogfv(GL_FOG_COLOR,   mFogColor.components);
	glFogf (GL_FOG_DENSITY, 1.0);

    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);

    // Draw Cube
    glPushMatrix();
    {
        // Apply Material
        // TODO Define Material + Properties
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMaterialAmbient.components);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mMaterialDiffuse.components);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mMaterialSpecular.components);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mMaterialEmission.components);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mMaterialShininess);

        if (mAutomaticRotation) 
        {
            mRotationAngleX += 360.0f * (mRotationFreqX / mFramerate);
            mRotationAngleY += 360.0f * (mRotationFreqY / mFramerate);
            mRotationAngleZ += 360.0f * (mRotationFreqZ / mFramerate);

            if (mRotationAngleX >= 360.0f) mRotationAngleX -= 360.0f;
            if (mRotationAngleY >= 360.0f) mRotationAngleY -= 360.0f;
            if (mRotationAngleZ >= 360.0f) mRotationAngleZ -= 360.0f;
        }	

        glRotatef(180.0, 1.0, 0.0, 0.0);
        glRotatef(mRotationAngleX, 1.0, 0.0, 0.0);
        glRotatef(mRotationAngleY, 0.0, 1.0, 0.0);
        glRotatef(mRotationAngleZ, 0.0, 0.0, 1.0);

        glColor4f(0.0, 0.0, 1.0, 1.0);

        glCallList(mQuadGridListId);
        deactivateTextures();
    }
    glPopMatrix();

    glUseProgram(EMPTY_SHADER_PROGRAM); 

    // Draw Axis without shaders
    glPushMatrix();
    {		
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG); 
    		
        glLineWidth(3.0);

        glBegin(GL_LINES);
        {
            // X axis in red
            glColor4f(1.0, 0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(1.0f * mAxisScaleFactor, 0.0, 0.0);

            // Y axis in green
            glColor4f(0.0, 1.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 1.0f * mAxisScaleFactor, 0.0);

            // Z axis in blue
            glColor4f(0.0, 0.0, 1.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 1.0f * mAxisScaleFactor);
        }
        glEnd();

        glEnable(GL_FOG);
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);
    
    glFlush();
}

void Tp3Application::updateWorld()
{
    updateLights();
}

void Tp3Application::updateLights()
{
    if (mIsPointLightOn) 
    {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, mPointLightAmbient.components);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, mPointLightDiffuse.components);
        glLightfv(GL_LIGHT0, GL_SPECULAR, mPointLightSpecular.components);
        glLightfv(GL_LIGHT0, GL_EMISSION, mPointLightEmission.components);
        glLightfv(GL_LIGHT0, GL_POSITION, mPointLightPosition);
    }
    else 
        glDisable(GL_LIGHT0);

    if (mIsSpotLightOn) 
    {
        FLOAT spotPosition[4] =  { mCameraX, mCameraY, mCameraZ, 1.0 };
        FLOAT spotDirection[3] = { -mCameraX, -mCameraY, -mCameraZ };

        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, mSpotLightAmbient.components);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, mSpotLightDiffuse.components);
        glLightfv(GL_LIGHT1, GL_SPECULAR, mSpotLightSpecular.components);
        glLightfv(GL_LIGHT1, GL_EMISSION, mSpotLightEmission.components);
        glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
        glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
        glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 30.0); 
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection); 
    }
    else 
        glDisable(GL_LIGHT1);

    if (mIsDirectionalLightOn) 
    {
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_AMBIENT, mDirectionalLightAmbient.components);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, mDirectionalLightDiffuse.components);
        glLightfv(GL_LIGHT2, GL_SPECULAR, mDirectionalLightSpecular.components);
        glLightfv(GL_LIGHT2, GL_EMISSION, mDirectionalLightEmission.components);
        glLightfv(GL_LIGHT2, GL_POSITION, mDirectionalLightPosition);
    }
    else 
        glDisable(GL_LIGHT2);
}

void Tp3Application::applyTextures()
{
   mStonewallTextureUnit->activate();
   mRustTextureUnit->activate();
   m3dLabsTextureUnit->activate();
}

void Tp3Application::initializeTextures()
{	
    mStonewallTextureUnit = new TextureUnit(GL_TEXTURE0, "stonewall_diffuse.bmp");
    mStonewallTextureUnit->initialize();
    mStonewallTextureUnit->addCombiner(GL_TEXTURE_ENV_MODE, GL_MODULATE);

    mRustTextureUnit = new TextureUnit(GL_TEXTURE1, "rust.bmp");
    mRustTextureUnit->initialize();
    mRustTextureUnit->addCombiner(GL_TEXTURE_ENV_MODE, GL_COMBINE).
                      addCombiner(GL_COMBINE_RGB, GL_MODULATE).
                      addCombiner(GL_SOURCE0_RGB, GL_TEXTURE).
                      addCombiner(GL_SOURCE1_RGB, GL_PREVIOUS);

    m3dLabsTextureUnit = new TextureUnit(GL_TEXTURE2, "3d_labs.bmp");
    m3dLabsTextureUnit->initialize();
    m3dLabsTextureUnit->addCombiner(GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Tp3Application::deactivateTextures()
{
   glActiveTexture(GL_TEXTURE1);
   glDisable(GL_TEXTURE_2D);

   glActiveTexture(GL_TEXTURE2);
   glDisable(GL_TEXTURE_2D);

   glActiveTexture(GL_TEXTURE0);
   glDisable(GL_TEXTURE_2D);
}
