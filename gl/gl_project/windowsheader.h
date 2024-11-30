#include <windows.h>
#include <assert.h>

typedef HWND CPF_Window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void CPF_initialize() { }

void CPF_finalize() { }

void CPF_showwindow(CPF_Window window)
{
    ShowWindow(window, 1);
}

CPF_Window CPF_createwindow(const char *title, int width, int height) {
    HINSTANCE instance = GetModuleHandle(0);
    int showCode = 1;

    WNDCLASS windowClass = { 0 };
    windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIconA(0, IDI_APPLICATION);
    windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = "MyWindowClass";

    assert(RegisterClassA(&windowClass));

    // TODO: correct width and height for border
    HWND windowHandle = CreateWindowExA(0, windowClass.lpszClassName, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);
    assert(windowHandle);

    return windowHandle;
}

void CPF_eventloop(CPF_Window window)
{
    MSG message;
    while (GetMessage(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
}
