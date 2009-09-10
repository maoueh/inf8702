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
    mActiveColorComponent(RED_COMPONENT), mIsShaderOn(TRUE),
    mIsSpotLightOn(TRUE), mIsDirectionalLightOn(TRUE), mIsPointLightOn(FALSE),
    mFogColor(Color::BLACK), mCubeColor(Color::RED), 
    mLastMouseX(0), mLastMouseY(0)
{

}

Tp2Application::~Tp2Application()
{
}

void Tp2Application::initialize()
{
    OpenGlApplication::initialize();

    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );     // Two-side mode in OpenGL
    glEnable( GL_VERTEX_PROGRAM_TWO_SIDE );                // Two-side mode in GLSL

    // ajouter ici le mode de calcul séparé de la couleur spéculaire
    // ... 

    //chargerTextures();

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
    {
        //appliquerTextures();
        drawQuadGrid(size, rowCount, columnCount, isOutsideNormal);
    }
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
    // ajuster le fog dynamiquement selon la distance de l'observateur
    // vous devez ici l'améliorer... pour que les paramètres
    // GL_FOG_START et GL_FOG_END soient ajustés automatiquement
    // en fonction du zoom.
	glFogi (GL_FOG_MODE,    GL_LINEAR);
	glFogf (GL_FOG_START,   30.0);
	glFogf (GL_FOG_END,     40.0);
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
	    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiant_model);
	    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_model);
	    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_model);
	    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_model);
	    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess_model);

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
        //desactiverTextures();
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

/* A Faire */
////////////////////////////////////////////////////////////
////////////  FONCTIONS POUR LES TEXTURES //////////////////
////////////////////////////////////////////////////////////
//void appliquerTextures()
//{
//   // ETAGE 0 (texture de mur)
//   // ...
//   // ...
//  
//    
//   // ETAGE 1 (texture de rust)
//   // ...
//   // ...
//
//
//   // ETAGE 2 (texture "paint job")
//   // ...
//   // ...
//}
//
//
//
//SImage* LoadBMP( char *Filename )
//{
//    if( !Filename )
//        return NULL;
//
//    FILE *file;
//    unsigned int  width;
//    unsigned int  height;
//	unsigned long i;
//	unsigned short int planes; // planes in image (must be 1) 
//	unsigned short int bpp;    // bits per pixel (must be 24)
//	
//	// make sure the file is there.
//	if( ( file = fopen( Filename, "rb" ) ) == NULL )
//    {
//		printf( "File Not Found : %s\n", Filename );
//		return NULL;
//	}
//
//	// seek through the bmp header, up to the width/height:
//	fseek( file, 18, SEEK_CUR );
//
//	// read the width
//	if( ( i = ( unsigned long )fread( &width, 4, 1, file ) ) != 1 )
//    {
//		printf( "Error reading width from %s.\n", Filename );
//		return NULL;
//	}
//
//	// read the height 
//	if( ( i = ( unsigned long )fread( &height, 4, 1, file ) ) != 1 )
//    {
//		printf( "Error reading height from %s.\n", Filename );
//		return NULL;
//	}
//
//	// read the planes
//	if( ( ( unsigned long )fread( &planes, 2, 1, file ) ) != 1 )
//    {
//		printf( "Error reading planes from %s.\n", Filename );
//		return NULL;
//	}
//
//	if( planes != 1 )
//    {
//		printf( "Planes from %s is not 1: %u\n", Filename, planes );
//		return NULL;
//	}
//
//	// read the bpp
//	if( ( i = ( unsigned long )fread( &bpp, 2, 1, file ) ) != 1 )
//    {
//		printf("Error reading bpp from %s.\n", Filename );
//		return NULL;
//	}
//
//	if( bpp != 24 )
//    {
//		printf( "Bpp from %s is not 24: %u\n", Filename, bpp );
//		return NULL;
//	}
//
//	// seek past the rest of the bitmap header.
//	fseek( file, 24, SEEK_CUR );
//
//	// read the data.
//    SImage* Image = new SImage( width, height );
//
//	if( ( i = ( unsigned long )fread( Image->data, width * height * 3, 1, file ) ) != 1 )
//    {
//		printf("Error reading image data from %s.\n", Filename );
//		delete Image;
//		return NULL;
//	}
//
//	return Image;
//}
//
//
//
//void init2DTexture(GLint texName, GLint texWidth, GLint texHeight, GLubyte *texPtr)
//{
//   glBindTexture(GL_TEXTURE_2D, texName);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1.0); 
//   glTexImage2D(GL_TEXTURE_2D, 0, 3, texWidth, texHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, texPtr);
//}
//
//
//
//void chargerTextures()
//{	
//   SImage* Image = NULL;
//
//   if( Image = LoadBMP("textures/stonewalldiffuse.bmp" ) )
//   {
//      glGenTextures( 1, &texture0 );	
//      init2DTexture( texture0, Image->width, Image->height, Image->data );
//      delete Image;
//   }
//
//   if( Image = LoadBMP( "textures/rust.bmp" ) )
//   {
//      glGenTextures( 1, &texture1 );	
//      init2DTexture( texture1, Image->width, Image->height, Image->data );
//      delete Image;
//   }
//
//   if( Image = LoadBMP( "textures/3dlabs.bmp" ) )
//   {
//      glGenTextures( 1, &texture2 );
//      init2DTexture( texture2, Image->width, Image->height, Image->data );
//      delete Image;
//   }
//}
//
//
//void desactiverTextures()
//{
//   glActiveTexture(GL_TEXTURE0);
//   glDisable(GL_TEXTURE_2D);
//   glActiveTexture(GL_TEXTURE1);
//   glDisable(GL_TEXTURE_2D);
//   glActiveTexture(GL_TEXTURE2);
//   glDisable(GL_TEXTURE_2D);
//}
