#include "tp1_application.h"
#include "tp1_shader_program.h"

#include "logger.h"
#include "window.h"

Tp1Application::Tp1Application(CommandLine* commandLine) : OpenGlApplication(commandLine),
    mName("Tp1 - INF8702"), 
    mRotationAngleX(0.0), mRotationAngleY(0.0), mRotationAngleZ(0.0),
    mRotationFreqX(0.15f), mRotationFreqY(0.1f), mRotationFreqZ(0.2f),
    mAxisScaleFactor(15.0f), mAutomaticRotation(FALSE), mFramerate(50.0f)
{

}

Tp1Application::~Tp1Application()
{

}

void Tp1Application::initialize()
{
    OpenGlApplication::initialize();

   // Compile Display List
   compileQuadGridList(10.0f, 1, 1, TRUE);
   compileCubeList(10.0f);

   // The Vertex and Fragment Shaders are initialized in the constructor
   mShaderProgram = new Tp1ShaderProgram();
   mShaderProgram->link();
}


void Tp1Application::compileCubeList(FLOAT size) 
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

void Tp1Application::compileQuadGridList(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal)
{
   mQuadGridListId = glGenLists(1);
   glNewList(mQuadGridListId, GL_COMPILE);
      drawQuadGrid(size, rowCount, columnCount, isOutsideNormal);
   glEndList();
}

void Tp1Application::drawQuadGrid(FLOAT size, INT rowCount, INT columnCount, BOOL isOutsideNormal) 
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

void Tp1Application::draw()
{
    if (false)
    {
        //glUseProgram(fixedPipelineShaderProg);
    } 
    else
    {
        mShaderProgram->use();
    }

    // Dessiner le modèle 
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

        // appliquer le matériau du cube
        glColor4f(0.0, 0.0, 1.0, 1.0);

        glCallList(mCubeListId);
    }
    glPopMatrix();

    glUseProgram(EMPTY_SHADER_PROGRAM); 

    // Dessiner les axes pour se retrouver
    glPushMatrix();
    {		
        glLineWidth(3.0);

        glBegin(GL_LINES);
        {
            // l'axe des x en Rouge
            glColor4f(1.0, 0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(1.0f * mAxisScaleFactor, 0.0, 0.0);

            // l'axe des y en Vert
            glColor4f(0.0, 1.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 1.0f * mAxisScaleFactor, 0.0);

            // l'axe des z en Bleu
            glColor4f(0.0, 0.0, 1.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 1.0f * mAxisScaleFactor);
        }
        glEnd();
    }
    glPopMatrix();

    mShaderProgram->use();
    //glUseProgram( SHADER_ON ? fixedPipelineShaderProg : noShaderProg );
    
    glFlush();
}