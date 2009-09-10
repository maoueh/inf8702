#include "bitmap_image.h"
#include "image_factory.h"

Image* ImageFactory::create(const CHAR* imageFilename)
{
    STRING filename(imageFilename);
    STRING extension = ".bmp";

    UINT dotPosition = filename.rfind('.');
    if ( dotPosition != string::npos )
    {
        extension = filename.substr(dotPosition);
        Utils::toLowerCase(extension);
    }

    Image* image = NULL;
    if ( extension == ".bmp" )
        image = new BitmapImage(filename.c_str());

    assert(image != NULL && "Image extension not supported");
    if ( image->load() == TRUE )
        return image;

    // Image did not load successfully
    delete image;
    return NULL;
}