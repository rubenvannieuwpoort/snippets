#include <windows.h>

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	
	switch (message) {
		case WM_CLOSE: {
			// If we don't do this our window will hide but thread will remain.
			PostQuitMessage(5);
			OutputDebugString("close button clicked\n");
		} break;
		default: {
			// Do the default action for this message.
			result = DefWindowProc(window, message, wParam, lParam);
		}
	}
	
	return result;
}

void error(LPCSTR message, UINT exitCode)
{
	OutputDebugString(message);
	ExitProcess(exitCode);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdline, int cmdShow)
{
	// Register a windowclass
	WNDCLASS windowClass = { };
	windowClass.style = 0;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance= instance;
	windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "WindowClass";
	// for a WNDCLASSEX, you should also fill hIconSm property
	
	if (!RegisterClass(&windowClass)) error("Error while registering window class\n", 2);
	
	// You can also use CreateWindowEx
	HWND window = CreateWindow("WindowClass", "window name", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, 0);
	if (window == 0) error("Error while registering window\n", 2);
	
	BOOL messageResult;
	MSG message;
	
	// messageResult = 0 when WM_QUIT is posted, and -1 on error.
	while ((messageResult = GetMessage(&message, 0, 0, 0))) {
		if (messageResult == -1) error("Error in message loop\n", 3);
		
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	
	// This is not really necessary since the resources will be cleaned on exit
	// anyway. This is also why we don't really care if there's an error here.
	DestroyWindow(window);
	
	return message.wParam;
}
