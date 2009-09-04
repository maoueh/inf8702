#ifndef RENDERING_CONTEXT
#define RENDERING_CONTEXT

#include "common.h"

class RenderingContext
{
public:
    RenderingContext();
    virtual ~RenderingContext();

    virtual void registerContext();
    virtual void dispose();

    virtual void swapBuffers();

    // System Dependent Methods
    inline void setWindowHandle(HWND windowHandle);

private:
    // System Dependent Members
    HWND  mWindowHandle;
    HDC   mDeviceContextHandle;
    HGLRC mHandle;

};

#include "rendering_context.inl"

#endif