#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct {
	Display *display;
} CPF_Global;
CPF_Global CPF_global;

typedef Window CPF_Window;

void CPF_initialize() {
	CPF_global.display = XOpenDisplay(0);
}

CPF_Window CPF_createwindow(const char* title, int width, int height) {
	Display *display = CPF_global.display;
	int screenId = DefaultScreen(display);

	CPF_Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height, 1,
	                                      WhitePixel(display, screenId), BlackPixel(display, screenId));

	XSetStandardProperties(display, window, title, "Icon", None, NULL, 0, NULL);
	XClearWindow(display, window);

	return window;
}

void CPF_showwindow(CPF_Window window) {
	XMapRaised(CPF_global.display, window);
}

void CPF_eventloop(CPF_Window window) {
	Display *display = CPF_global.display;
	Atom deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &deleteMessage, 1);

	XEvent event;
	while (true)
	{
		XNextEvent(display, &event);
		if (event.type == ClientMessage && event.xclient.data.l[0] == deleteMessage)
			break;
	}
}

void CPF_finalize() { }
