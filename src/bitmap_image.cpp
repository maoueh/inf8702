#include "application_manager.h"
#include "bitmap_image.h"

BitmapImage::BitmapImage(const CHAR* filename) : Image(),
    mFilename(filename), mImageData(NULL), mWidth(0), mHeight(0)
{

}

BitmapImage::~BitmapImage()
{
    delete [] mImageData;
    mImageData = NULL;
}

BOOL BitmapImage::load()
{
    FILE* file = NULL;
    const CHAR* filename = mFilename.c_str();
	
	// Make sure the file is there.
    if( fopen_s(&file, filename, "rb") != FALSE )
    {
        ApplicationManager::get()->log("File Not Found : %s", filename);
		return FALSE;
	}

	// Seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// Read the width
	if( fread(&mWidth, 4, 1, file) != 1 )
    {
		ApplicationManager::get()->log("Error reading width from %s.", filename);
		return FALSE;
	}

	// Read the height 
	if( fread(&mHeight, 4, 1, file) != 1 )
    {
		ApplicationManager::get()->log("Error reading height from %s.", filename);
		return FALSE;
	}

	// Read the plane count (must be 1)
    USHORT planeCount;
	if( fread( &planeCount, 2, 1, file ) != 1 )
    {
		ApplicationManager::get()->log("Error reading planes from %s.", filename);
		return FALSE;
	}
	if( planeCount != 1 )
    {
        ApplicationManager::get()->log("Planes from %s should be 1, current: %u.", filename, planeCount);
		return FALSE;
	}

	// Read the bits per pixel (must be 24)
	USHORT bitsPerPixel; 
	if( fread(&bitsPerPixel, 2, 1, file) != 1 )
    {
		ApplicationManager::get()->log("Error reading bits per pixel from %s.", filename);
		return FALSE;
	}
	if( bitsPerPixel != 24 )
    {
        ApplicationManager::get()->log("Bits per pixel should be 24, current: %u.", filename, bitsPerPixel);
		return FALSE;
	}

	// Seek past the rest of the bitmap header
	fseek(file, 24, SEEK_CUR);

    // Allocate the memory needed
    ULONG byteCount = mWidth * mHeight * 3;
    mImageData = new BYTE[byteCount];

    // Read the data
	if( fread(mImageData, byteCount, 1, file) != 1 )
    {
		ApplicationManager::get()->log("Error reading image data from %s.", filename);
		delete [] mImageData;
        mImageData = NULL;

		return FALSE;
	}

	return TRUE;
}

void* BitmapImage::getData()
{
    return mImageData;
}

void BitmapImage::getData(BYTE* imageData, INT* count)
{
    imageData = mImageData;
    *count = mWidth * mHeight * 3;
}

STRING BitmapImage::getFilename()
{
    return mFilename;
}

INT BitmapImage::getWidth()
{
    return mWidth;
}

INT BitmapImage::getHeight()
{
    return mHeight;
}
