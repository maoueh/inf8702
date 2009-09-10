#ifndef IMAGE_FACTORY_H
#define IMAGE_FACTORY_H

#include "image.h"

class ImageFactory
{
public:
    // The factory is not responsible to desallocate the Image pointer
    static Image* create(const CHAR* imageFilename);

private:
    // Class cannot be instantiated
    ImageFactory();
    ImageFactory(const ImageFactory& other);
    ImageFactory& operator=(const ImageFactory& rightSide);

};

#endif