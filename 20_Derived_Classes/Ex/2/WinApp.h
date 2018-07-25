#ifndef __WIN_APP_H__
#define __WIN_APP_H__

#include <functional>

namespace windows
{
	typedef struct _WindowHandle* WindowHandle;
	using Callback = std::function<void()>;

	bool InitApp();
	WindowHandle WindowNew(const char* title, int nWidth = -1, int nHeight = -1);
	void WindowShow(WindowHandle wnd, Callback cb);
	void WindowMove(WindowHandle wnd, int dx, int dy);
	void RunMessageLoop();
	void DrawLine(WindowHandle wnd, int xStart, int yStart, int xEnd, int yEnd);
}

#endif // __WIN_APP_H__
