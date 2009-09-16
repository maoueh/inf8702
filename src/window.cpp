#include "keyboard_listener.h"
#include "mouse_listener.h"
#include "window.h"
#include "window_listener.h"

LRESULT WINAPI Window::messageDispatcher(HWND windowHandle, UINT messageId, WPARAM wParameter, LPARAM lParameter)
{
    Window* instance = NULL;
    if(messageId == WM_NCCREATE)
    {
        instance = (Window*) ((LPCREATESTRUCT) lParameter)->lpCreateParams;
        instance->mHandle = windowHandle;
        SetWindowLongPtr(windowHandle, GWL_USERDATA,(LONG_PTR) instance);
    }
    else
        instance = (Window*) GetWindowLongPtr(windowHandle, GWL_USERDATA);

    if ( instance == NULL )
        return DefWindowProc( windowHandle, messageId, wParameter, lParameter );
    else
        return instance->messageHandler(messageId, wParameter, lParameter);
}

Window::Window(STRING className, STRING name, BOOL isWindowed) : 
    mClientSize(), mHandle(), mIsWindowed(isWindowed), mClassName(className), mName(name),
    mRenderingContext(NULL), mWidth(800), mHeight(800), mWindowListeners()
{
    mInstance = GetModuleHandle( mClassName.c_str() );
}

Window::~Window() 
{ 
    dispose();
}

void Window::addKeyboardListener(KeyboardListener* listener)
{
    mKeyboardListeners.push_back(listener);
}

void Window::removeKeyboardListener(KeyboardListener* listener)
{
    vector<KeyboardListener*>::iterator it = mKeyboardListeners.begin();
    while( it != mKeyboardListeners.end() ) {
        if ( *it == listener )
            mKeyboardListeners.erase(it);
        it++;
    }
}

void Window::addMouseListener(MouseListener* listener)
{
    mMouseListeners.push_back(listener);
}

void Window::removeMouseListener(MouseListener* listener)
{
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) {
        if ( *it == listener )
            mMouseListeners.erase(it);
        it++;
    }
}

void Window::addWindowListener(WindowListener* listener)
{
    mWindowListeners.push_back(listener);
}

void Window::removeWindowListener(WindowListener* listener)
{
    vector<WindowListener*>::iterator it = mWindowListeners.begin();
    while( it != mWindowListeners.end() ) {
        if ( *it == listener )
            mWindowListeners.erase(it);
        it++;
    }
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

void Window::initialize(BOOL isWindowed) 
{ 
	mIsWindowed = isWindowed;

	WNDCLASSEX windowAttributes;
	windowAttributes.cbSize         = sizeof(windowAttributes);
	windowAttributes.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowAttributes.lpfnWndProc    = messageDispatcher;
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
                                    x, y, mWidth, mHeight, NULL, NULL, mInstance, this)) )
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

LRESULT Window::messageHandler(UINT messageId, WPARAM wParameter, LPARAM lParameter)
{
    // TODO Break Down in smaller pieces like keyboardMessageHandler, mouseMessageHandler
    //      and then map key to functions
	switch(messageId)
	{
	  case WM_DESTROY:
      {
          notifyWindowClosed();
          return FALSE;
      }
      case WM_SYSKEYDOWN: // Fall through
      case WM_KEYDOWN:
      {
          notifyKeyPressed(wParameter, LOWORD(lParameter));
          return FALSE;
      }
      case WM_SYSKEYUP: // Fall through
      case WM_KEYUP:
      {
          notifyKeyReleased(wParameter);
          return FALSE;
      }
      case WM_LBUTTONDOWN:
      {
          notifyMousePressed(MOUSE_BUTTON_LEFT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_LBUTTONUP:
      {
          notifyMouseReleased(MOUSE_BUTTON_LEFT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_LBUTTONDBLCLK:
      {
          notifyMouseDoubleClicked(MOUSE_BUTTON_LEFT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_MBUTTONDOWN:
      {
          notifyMousePressed(MOUSE_BUTTON_MIDDLE, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_MBUTTONUP:
      {
          notifyMouseReleased(MOUSE_BUTTON_MIDDLE, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_MBUTTONDBLCLK:
      {
          notifyMouseDoubleClicked(MOUSE_BUTTON_MIDDLE, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_RBUTTONDOWN:
      {
          notifyMousePressed(MOUSE_BUTTON_RIGHT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_RBUTTONUP:
      {
          notifyMouseReleased(MOUSE_BUTTON_RIGHT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_RBUTTONDBLCLK:
      {
          notifyMouseDoubleClicked(MOUSE_BUTTON_RIGHT, LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_MOUSEHWHEEL:
      {
          notifyMouseWheel(LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_MOUSEMOVE:
      {
          notifyMouseMoved(LOWORD(lParameter), HIWORD(lParameter));
          return FALSE;
      }
      case WM_SIZE:
      {
          mWidth = LOWORD(lParameter);
          mHeight = HIWORD(lParameter);
          notifyWindowResized();
          return FALSE;
      }
	}

    return DefWindowProc( mHandle, messageId, wParameter, lParameter );
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

BOOL Window::isAnyMouseButtonPressed()
{
    return GetAsyncKeyState(VK_LBUTTON) & 0x8000 |
           GetAsyncKeyState(VK_MBUTTON) & 0x8000 |
           GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

void Window::notifyKeyPressed(INT keyCode, INT repeat)
{
    KeyEvent event(this, keyCode, repeat);
    vector<KeyboardListener*>::iterator it = mKeyboardListeners.begin();
    while( it != mKeyboardListeners.end() ) 
    {
      (*it)->keyPressed(event);
      it++;
    }
}

void Window::notifyKeyReleased(INT keyCode)
{
    KeyEvent event(this, keyCode);
    vector<KeyboardListener*>::iterator it = mKeyboardListeners.begin();
    while( it != mKeyboardListeners.end() ) 
    {
      (*it)->keyReleased(event);
      it++;
    }
}

void Window::notifyMousePressed(INT button, INT x, INT y)
{
    MouseEvent event(this, button, x, y);
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) 
    {
        (*it)->mousePressed(event);
        it++;
    }
}

void Window::notifyMouseReleased(INT button, INT x, INT y)
{
    MouseEvent event(this, button, x, y);
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) 
    {
        (*it)->mouseReleased(event);
        it++;
    }
}

void Window::notifyMouseDoubleClicked(INT button, INT x, INT y)
{
    MouseEvent event(this, button, x, y);
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) 
    {
        (*it)->mouseDoubleClicked(event);
        it++;
    }
}

void Window::notifyMouseMoved(INT x, INT y)
{
    BOOL anyMouseButtonPressed = isAnyMouseButtonPressed();
    
    MouseEvent event(this, NO_BUTTON, x, y);
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) 
    {
      if ( anyMouseButtonPressed ) 
          (*it)->mouseDragged(event);
      else
          (*it)->mouseMoved(event);
      it++;
    }
}

void Window::notifyMouseWheel(INT x, INT y)
{
    MouseEvent event(this, NO_BUTTON, x, y);
    vector<MouseListener*>::iterator it = mMouseListeners.begin();
    while( it != mMouseListeners.end() ) 
    {
       (*it)->mouseWheel(event);
       it++;
    }
}

void Window::notifyWindowClosed()
{
    WindowEvent event(this);
    vector<WindowListener*>::iterator it = mWindowListeners.begin();
    while( it != mWindowListeners.end() ) 
    {
      (*it)->windowClosed(event);
      it++;
    }
}

void Window::notifyWindowResized()
{
    WindowEvent event(this, mWidth, mHeight);
    vector<WindowListener*>::iterator it = mWindowListeners.begin();
    while( it != mWindowListeners.end() ) 
    {
      (*it)->windowResized(event);
      it++;
    }
}

