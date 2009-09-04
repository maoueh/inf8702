#include "rendering_context.h"

RenderingContext::RenderingContext() : 
    mHandle(NULL), mDeviceContextHandle(NULL), mWindowHandle(NULL)
{
}

RenderingContext::~RenderingContext()
{
    dispose();
}

void RenderingContext::dispose()
{
    if ( mHandle != NULL )
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(mHandle);
		mHandle = NULL;
	}

	if ( mDeviceContextHandle != NULL )
	{
		ReleaseDC(mWindowHandle, mDeviceContextHandle);
		mDeviceContextHandle = NULL;
	}
}

void RenderingContext::registerContext()
{
    assert(mWindowHandle != NULL && "forgot setWindowHandle(..) ?");

    static PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW | 						// Must Support Window, OpenGL and Double Buffering
		PFD_SUPPORT_OPENGL |						
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

    if ( !(mDeviceContextHandle = GetDC(mWindowHandle)) )
	{
		dispose();
		MessageBox(mWindowHandle, "Couldn't create device context", "Error", 0);
	}

    UINT pixelFormat;
	if ( !(pixelFormat = ChoosePixelFormat(mDeviceContextHandle, &pixelFormatDescriptor)) )
	{
		dispose();
		MessageBox(mWindowHandle, "Couldn't choose desired pixel format", "Error", 0);
	}

	if( !SetPixelFormat(mDeviceContextHandle, pixelFormat, &pixelFormatDescriptor) )
	{
		dispose();
		MessageBox(mWindowHandle, "Couldn't set desired pixel format", "Error", 0);
	}

	if ( !(mHandle = wglCreateContext(mDeviceContextHandle)) )
	{
		dispose();
		MessageBox(mWindowHandle, "Couldn't create rendering context", "Error", 0);
	}

	if( !wglMakeCurrent(mDeviceContextHandle, mHandle) )
	{
		dispose();
		MessageBox(mWindowHandle, "Couldn't activate rendering context", "Error", 0);
	}
}

void RenderingContext::swapBuffers()
{
    SwapBuffers(mDeviceContextHandle);
}
 