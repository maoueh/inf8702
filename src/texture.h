#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"

// TODO Add textures parameters (CLAMP, MAG_FILTER, MIN_FILTER, etc)
class Texture
{
public:
    Texture(const CHAR* filename);
    ~Texture();

    void initialize();

private:
    STRING mImageFilename;
    UINT mHandle;

};

#endif