#ifndef WINDOW
#define WINDOW

#include "common.h"
#include "rendering_context.h"

class Window
{

public:
	Window(STRING className, STRING name, BOOL isWindowed = FALSE);
	~Window();

    void           initialize(WNDPROC windowProcedure, BOOL isWindowed = FALSE);
    void           dispose();

	void	       toggleFullscreen();
	void	       toggleWindowed(INT width, INT height);

	inline void    show();
	inline void    hide();

    inline void    swapBuffers();

    inline HWND	   getHandle();
	inline RECT	   getClientSize();
    inline INT     getWidth();
    inline INT     getHeight();

    inline void    setRenderingContext(RenderingContext* context);

	inline BOOL	   isWindowed();
	inline BOOL	   isFullscreen();

private:
	HWND		      mHandle;
	RECT		      mClientSize;
    STRING            mClassName;
	STRING		      mName;
	HINSTANCE	      mInstance;
	BOOL		      mIsWindowed;
    RenderingContext* mRenderingContext;

    INT               mWidth;
    INT               mHeight;
};

#include "window.inl"

#endif