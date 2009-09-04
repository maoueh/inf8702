#include "window.h"

Window::Window(STRING className, STRING name, BOOL isWindowed) : 
    mClientSize(), mHandle(), mIsWindowed(isWindowed), mClassName(className), mName(name),
    mRenderingContext(NULL), mWidth(800), mHeight(800)
{
    mInstance = GetModuleHandle( mClassName.c_str() );
}

Window::~Window() 
{ 
    dispose();
}

void Window::dispose()
{
    if ( !mIsWindowed )
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

    if ( mRenderingContext != NULL )
    {
        delete mRenderingContext;
        mRenderingContext = NULL;
    }

    if ( mHandle != NULL )
	{
		DestroyWindow(mHandle);
		mHandle = NULL;
	}

	if ( mInstance != NULL )
	{
		UnregisterClass( mClassName.c_str(), mInstance );
		mInstance = NULL;
	}
}

void Window::initialize(WNDPROC windowProcedure, BOOL isWindowed) 
{ 
	mIsWindowed = isWindowed;

	WNDCLASSEX windowAttributes;
	windowAttributes.cbSize         = sizeof(windowAttributes);
	windowAttributes.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//windowAttributes.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	windowAttributes.lpfnWndProc    = windowProcedure;
	windowAttributes.cbClsExtra     = 0;
	windowAttributes.cbWndExtra     = 0;
	windowAttributes.hInstance      = mInstance;
	windowAttributes.hIcon          = LoadIcon(NULL, IDI_APPLICATION); // LoadIcon(NULL, :TODO: RESSOURCE);
	windowAttributes.hCursor        = LoadCursor(NULL, IDC_ARROW); // LoadIcon(NULL, :TODO: RESSOURCE);
	windowAttributes.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);
	windowAttributes.lpszMenuName   = NULL;
    windowAttributes.lpszClassName  = mClassName.c_str();
	windowAttributes.hIconSm        = LoadIcon(NULL, IDI_WINLOGO); // LoadIcon(NULL, :TODO: RESSOURCE);

	if( RegisterClassEx(&windowAttributes) == NULL )
	{
        dispose();
        MessageBox(mHandle, Utils::format("Couldn't register class %s", mClassName).c_str(), "Error", 0);
        return;
	}

	mWidth        = isWindowed ? mWidth  : GetSystemMetrics(SM_CXSCREEN);
	mHeight       = isWindowed ? mHeight : GetSystemMetrics(SM_CYSCREEN);
	INT x         = isWindowed ? (INT) ((GetSystemMetrics(SM_CXSCREEN) / 2) - (mWidth / 2.0f)) : 0;
	INT y         = isWindowed ? (INT) ((GetSystemMetrics(SM_CYSCREEN) / 2) - (mHeight / 2.0f)) : 0;
	DWORD style   = isWindowed ? WS_OVERLAPPEDWINDOW : WS_POPUP;
    DWORD exStyle = isWindowed ? WS_EX_APPWINDOW | WS_EX_WINDOWEDGE : WS_EX_APPWINDOW;

    if ( !isWindowed )
	{
		DEVMODE deviceSettings;								
		memset(&deviceSettings, 0, sizeof(deviceSettings));

		deviceSettings.dmSize = sizeof(deviceSettings);
		deviceSettings.dmPelsWidth	= mWidth;
		deviceSettings.dmPelsHeight	= mHeight;
		deviceSettings.dmBitsPerPel	= 32;
		deviceSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        ShowCursor(FALSE);
		if ( ChangeDisplaySettings(&deviceSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
		{
			dispose();
			MessageBox(mHandle, "Couldn't set device mode settings", "Error", 0);
            return;
		}
	}

    RECT windowRect = {0, mWidth, 0, mHeight};
    AdjustWindowRectEx(&windowRect, style, FALSE, exStyle);

	if ( !(mHandle = CreateWindowEx(exStyle, mClassName.c_str(), mName.c_str(), style,  
                                    x, y, mWidth, mHeight, NULL, NULL, mInstance, NULL)) )
	{
        dispose();
        MessageBox(mHandle, Utils::format("Couldn't create window %s", mName).c_str(), "Error", 0);
        return;
	}

    if ( mRenderingContext != NULL )
    {
        mRenderingContext->setWindowHandle(mHandle);
        mRenderingContext->registerContext();
    }

	SetWindowPos(mHandle, HWND_TOP, x, y, mWidth, mHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
    SetForegroundWindow(mHandle);					
	SetFocus(mHandle);

	// Don't show everything off yet
	hide();
}

void Window::toggleFullscreen()
{
	if( !mIsWindowed )
		return;

	INT width  = GetSystemMetrics(SM_CXSCREEN);
	INT height = GetSystemMetrics(SM_CYSCREEN);

	SetWindowLongPtr(mHandle, GWL_STYLE, WS_POPUP);
	SetWindowPos(mHandle, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);	

	mIsWindowed = FALSE;
}

void Window::toggleWindowed(INT width, INT height)
{
	if( mIsWindowed ) 
	    return;

	RECT windowRect = {0, 0, width, height};
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	
	SetWindowLongPtr(mHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	SetWindowPos(mHandle, HWND_TOP, 100, 100, 
				 windowRect.right, windowRect.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);

	mIsWindowed = TRUE;
}