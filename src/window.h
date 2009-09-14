#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include "common.h"
#include "rendering_context.h"

class KeyboardListener;
class MouseListener;
class WindowListener;

class Window
{
public:
	Window(STRING className, STRING name, BOOL isWindowed = FALSE);
	~Window();

    void           addKeyboardListener(KeyboardListener* listener);
    void           addMouseListener(MouseListener* listener);
    void           addWindowListener(WindowListener* listener);

    void           removeKeyboardListener(KeyboardListener* listener);
    void           removeMouseListener(MouseListener* listener);
    void           removeWindowListener(WindowListener* listener);

    void           initialize(BOOL isWindowed = FALSE);
    void           dispose();

	void	       toggleFullscreen();
	void	       toggleWindowed(INT width, INT height);

	inline void    show();
	inline void    hide();

    inline void    invalidate();
    inline void    swapBuffers();

    inline HWND	   getHandle();
	inline RECT	   getClientSize();
    inline INT     getWidth();
    inline INT     getHeight();

    inline void    setRenderingContext(RenderingContext* context);

	inline BOOL	   isWindowed();
	inline BOOL	   isFullscreen();

private:
    static LRESULT WINAPI messageDispatcher(HWND windowHandle, UINT messageId, 
                                            WPARAM wParameter, LPARAM lParameter);

    LRESULT messageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL    isAnyMouseButtonPressed();

    void    notifyMousePressed(INT button, INT x, INT y);
    void    notifyMouseReleased(INT button, INT x, INT y);
    void    notifyMouseDoubleClicked(INT button, INT x, INT y);

	HWND		              mHandle;
	RECT		              mClientSize;
    STRING                    mClassName;
	STRING		              mName;
	HINSTANCE	              mInstance;
	BOOL		              mIsWindowed;
    RenderingContext*         mRenderingContext;

    INT                       mWidth;
    INT                       mHeight;

    vector<KeyboardListener*> mKeyboardListeners;
    vector<MouseListener*>    mMouseListeners;
    vector<WindowListener*>   mWindowListeners;

};

#include "window.inl"

#endif