#include "tp2_application.h"
#include "tp2_shader_program.h"

#include "color.h"
#include "logger.h"
#include "window.h"

Tp2Application::Tp2Application(CommandLine* commandLine) : OpenGlApplication(commandLine),
    mName("Tp2 - INF8702"), 
    mRotationAngleX(0.0), mRotationAngleY(0.0), mRotationAngleZ(0.0),
    mRotationFreqX(0.15f), mRotationFreqY(0.1f), mRotationFreqZ(0.2f),
    mAxisScaleFactor(15.0f), mAutomaticRotation(FALSE), mFramerate(50.0f),
    mActiveColorComponent(RED_COMPONENT), mIsShaderOn(TRUE), mCubeColor(Color::RED),
    mLastMouseX(0), mLastMouseY(0)
{

}

Tp2Application::~Tp2Application()
{
}

void Tp2Application::initialize()
{
    OpenGlApplication::initialize();

   // Compile Display List
   compileQuadGridList(10.0f, 1, 1, TRUE);
   compileCubeList(10.0f);

   // The Vertex and Fragment Shaders are initialized in the constructor
   mShaderProgram = new Tp2ShaderProgram();
   mShaderProgram->link();
}

void Tp2Application::compileCubeList(FLOAT size) 
{
    mCubeListId = glGenLists(1);
	glNewList(mCubeListId, GL_COMPILE);
	{
	  // Front Face
	  glPushMatrix();
		 glTranslatef(0.0f, size / 2.0f, 0.0f);
		 glCallList(mQuadGridListId);
	  glPopMatrix();

	  // Back Face
	  glPushMatrix();
		 glTranslatef(0.0f, -size / 2.0f, 0.0f);
		 glRotatef(180.0, 0.0, 0.0, 1.0);
		 glCallList(mQuadGridListId);
	  glPopMatrix();

	  // Left Face
	  glPushMatrix();
		 glTranslatef(-size / 2.0f, 0.0f, 0.0f);
		 glRotatef(90.0, 0.0, 0.0, 1.0);
		 glCallList(mQuadGridListId);
	  glPopMatrix();

	  // Right Face
	  glPushMatrix();
		 glTranslatef(size / 2.0f, 0.0f, 0.0f);
		 glRotatef(-90.0, 0.0, 0.0, 1.0);
		 glCallList(mQuadGridListId);
	  glPopMatrix();

	  // Down Face
	  glPushMatrix();
		 glTranslatef(0.0f, 0.0f, size / 2.0f);
		 glRotatef(90.0, 1.0, 0.0, 0.0);
		 glCallList(mQuadGridListId);
	  glPopMatrix();

	  // Up Face
	  glPushMatrix();
		 glTranslatef(0.0f, 0.0f, -size / 2.0f);
		 glRotatef(-90.0, 1.0, 0.0, 0.0);
		 glCallList(mQuadGridListId);
	  glPopMatrix();
	}
	glEndList();
}

void Tp2Application::compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal)
{
    mQuadGridListId = glGenLists(1);
    glNewList(mQuadGridListId, GL_COMPILE);
        drawQuadGrid(size, rowCount, columnCount, isOutsideNormal);
    glEndList();
}

void Tp2Application::drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal) 
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

void Tp2Application::keyPressed(Window* window, INT keyCode, INT repeat)
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
      case VK_PRIOR :
         component = &mCubeColor.components[mActiveColorComponent];
         *component = CLIP(*component + 0.05f, 0.0f, 1.0f);
         break;
      case VK_NEXT :
         component = &mCubeColor.components[mActiveColorComponent];
         *component = CLIP(*component - 0.05f, 0.0f, 1.0f);
         break;
	}

    OpenGlApplication::keyPressed(window, keyCode, repeat);
}

void Tp2Application::mousePressed(Window* window, INT button, INT x, INT y)
{
    if ( button == MOUSE_BUTTON_LEFT )
    {
        mLastMouseX = x;
        mLastMouseY = y;
    }
}

void Tp2Application::mouseDragged(Window* window, INT x, INT y)
{
    mRotationAngleX += y - mLastMouseY;
    mRotationAngleZ -= x - mLastMouseX;

    mLastMouseX = x;
    mLastMouseY = y;
}

void Tp2Application::draw()
{
    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);

    // Draw Cube
    glPushMatrix();
    {
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

        glCallList(mCubeListId);
    }
    glPopMatrix();

    glUseProgram(EMPTY_SHADER_PROGRAM); 

    // Draw Axis without shaders
    glPushMatrix();
    {		
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
    }
    glPopMatrix();

    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);
    
    glFlush();
}