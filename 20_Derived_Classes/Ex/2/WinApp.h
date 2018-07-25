#ifndef __WIN_APP_H__
#define __WIN_APP_H__

namespace windows
{
	typedef struct _WindowHandle* WindowHandle;

	bool InitApp();
	WindowHandle WindowNew(const char* title, int nWidth = -1, int nHeight = -1);
	void WindowShow(WindowHandle wnd);
	void WindowMove(WindowHandle wnd, int dx, int dy);
	void RunMessageLoop();
}

#endif // __WIN_APP_H__
