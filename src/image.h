#ifndef IMAGE_H
#define IMAGE_H

#include "common.h"

class Image
{
public:
    virtual ~Image() { };

    virtual BOOL load() = 0;

    virtual void*  getData() = 0;
    virtual void   getData(BYTE* dataHolder, INT* count) = 0;

    virtual STRING getFilename() = 0;

    virtual INT    getWidth()  = 0;
    virtual INT    getHeight() = 0;
};

#endif