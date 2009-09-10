#ifndef BITMAP_IMAGE_H
#define BITMAP_IMAGE_H

#include "image.h"

class BitmapImage : public Image
{
public:
    BitmapImage(const CHAR* filename);
    virtual ~BitmapImage();

    virtual BOOL   load();

    virtual void*  getData();
    virtual void   getData(BYTE* imageData, INT* count);

    virtual STRING getFilename();

    virtual INT    getWidth();
    virtual INT    getHeight();

private:
    BitmapImage(const BitmapImage& other);                // Cannot copy BitmapImage for now
    BitmapImage& operator=(const BitmapImage& rightSide); // Cannot copy BitmapImage for now
    
    STRING mFilename;

    BYTE* mImageData;
    INT mWidth;
    INT mHeight;
};

#endif