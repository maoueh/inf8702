
void Window::show() 
{ 
	ShowWindow( mHandle, SW_SHOW );
}

void Window::hide() 
{ 
	ShowWindow( mHandle, SW_HIDE );
}

void Window::invalidate()
{
    InvalidateRect(mHandle, NULL, TRUE);
}

void Window::swapBuffers()
{
    mRenderingContext->swapBuffers();
}

HWND Window::getHandle()
{
	return mHandle;
}

RECT Window::getClientSize()
{
	GetClientRect(mHandle, &mClientSize);
	return mClientSize;
}

INT Window::getWidth()
{
    return mWidth;
}

INT Window::getHeight()
{
    return mHeight;
}

void Window::setRenderingContext(RenderingContext* context)
{
	mRenderingContext = context;
}

inline BOOL Window::isWindowed()
{
	return mIsWindowed;
}

inline BOOL Window::isFullscreen()
{
	return !mIsWindowed;
}
