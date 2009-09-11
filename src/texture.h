#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

// TODO Add textures parameters (CLAMP, MAG_FILTER, MIN_FILTER, etc)
class Texture
{
public:
    Texture(const CHAR* filename);
    virtual ~Texture();

    virtual void initialize();

protected:
    STRING mImageFilename;
    UINT mHandle;

};

#endif