#pragma comment(lib, "opengl32.lib")

#include <windows.h>
#include <gl/GL.h>

HDC deviceContext;
HGLRC renderContext;

static void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2i(-1, -1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(1, -1);
	glEnd();
	glFlush();
}

static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_PAINT:
		draw();
		break;
	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		if (wParam == 27)
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	case WM_CLOSE:
		wglMakeCurrent(deviceContext, NULL);
		wglDeleteContext(renderContext);
		ReleaseDC(hWnd, deviceContext);
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	return result;
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	windowClass.lpfnWndProc = (WNDPROC)wndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = NULL;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 640, 480 };
	DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	AdjustWindowRect(&rect, style, false);
	HWND windowHandle = CreateWindow("MyClass", "OpenGL example", style, 0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, instance, nullptr);
	
	deviceContext = GetDC(windowHandle);
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pixelFormatDesc;

	memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;

	pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
	SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc);
	renderContext = wglCreateContext(deviceContext);

	wglMakeCurrent(deviceContext, renderContext);

	ShowWindow(windowHandle, nCmdShow);
	UpdateWindow(windowHandle);

	MSG message;
	while (GetMessage(&message, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}