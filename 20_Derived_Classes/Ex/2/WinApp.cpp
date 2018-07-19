#include <Windows.h>
#include <cassert>
#include "WinApp.h"

namespace
{
	static HMODULE g_hInstance = nullptr;
	static const char g_mainWindowClassName[] = "MainWindowClass";
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, "WM_LBUTTONDOWN", "WM_LBUTTONDOWN", 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

windows::WindowHandle windows::WindowNew(const char* title, int nWidth, int nHeight)
{
	assert(g_hInstance); // Assume InitApp was called
	return reinterpret_cast<windows::WindowHandle>(CreateWindowEx(
		0,						// Optional window styles
		g_mainWindowClassName,
		title,					// Window text
		WS_OVERLAPPEDWINDOW,	// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// Position
		nWidth == -1 ? CW_USEDEFAULT : nWidth,
		nHeight == -1 ? CW_USEDEFAULT : nHeight,
		NULL,					// Parent window
		NULL,					// Menu
		g_hInstance,
		NULL));					// Additional application data
}

void windows::RunMessageLoop()
{
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool windows::InitApp()
{
	// Handle to the file used to create the calling process
	g_hInstance = GetModuleHandle(NULL);
	if (!g_hInstance)
		return false;
	// Detach the calling process from its console
	FreeConsole();
	// Register main window class
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = g_hInstance;
	wc.lpszClassName = g_mainWindowClassName;
	if (!RegisterClassEx(&wc))
		return false;
	return true;
}

void windows::WindowShow(windows::WindowHandle wnd)
{
	ShowWindow(reinterpret_cast<HWND>(wnd), SW_SHOW);
}

//// Example:
//int main(int, const char **av)
//{
//	using namespace windows;
//	if (!InitApp())
//		return 1;
//	auto wnd = WindowNew("Title");
//	if (!wnd)
//		return 1;
//	WindowShow(wnd);
//	RunMessageLoop();
//	return 0;
//}
