// minimal X11 example
// you might need to install some X11 dev package (sudo apt install libx11-dev on Ubuntu)
// compile with gcc minimal_x11.c -o minimal_x11 -lX11
#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main() {
	// initialize
	Display *display = XOpenDisplay(0);
	int screenId = DefaultScreen(display);
	Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 640, 480, 1,
	                             WhitePixel(display, screenId), BlackPixel(display, screenId));

	XSetStandardProperties(display, window, "Minimal X11 example", "Icon", None, NULL, 0, NULL);
	XClearWindow(display, window);
	XMapRaised(display, window);

	// loop, don't handle any events
	XSelectInput(display, window, NoEventMask);

    // funkyness necessary to catch the WM_DELETE_WINDOW message
    Atom deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &deleteMessage, 1);

	XEvent event;
    while (true)
    {
        XNextEvent(display, &event);
        if (event.type == ClientMessage && event.xclient.data.l[0] == deleteMessage)
            break;
    }
	
	// clean up
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	
	return 0;
}