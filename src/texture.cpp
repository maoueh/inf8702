#include "image_factory.h"
#include "texture.h"

Texture::Texture(const CHAR* imageFilename) :
    mImageFilename(imageFilename), mHandle(NULL)
{
    glGenTextures(1, &mHandle);	
}

Texture::~Texture()
{
    glDeleteTextures(1, &mHandle);
}

void Texture::initialize()
{
    Image* image = ImageFactory::create(mImageFilename.c_str());
    assert(image != NULL && "Could not load texture image");

    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1); 

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->getWidth(), image->getHeight(), 
                 0, GL_BGR, GL_UNSIGNED_BYTE, image->getData());

    delete image;
}