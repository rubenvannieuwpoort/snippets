// sudo apt install libx11-dev mesa-common-dev
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <assert.h>
#include <stdbool.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
typedef GLXContext (glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

Display *display;
GLXFBConfig *framebufferConfig;
Window window;

Atom deleteMessage;

GLXContext glContext;

glXCreateContextAttribsARBProc *glx_createContextAttribs;

void initializeGlProcs(void) {
    glx_createContextAttribs = (glXCreateContextAttribsARBProc*)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    assert(glx_createContextAttribs);
}

GLXFBConfig *getFrameBufferConfiguration(void) {
    static int attributeList[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, true,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        None
    };

    int framebufferCount;
    GLXFBConfig *framebufferConfig = glXChooseFBConfig(display, DefaultScreen(display), attributeList, &framebufferCount);
    assert(framebufferConfig && framebufferCount);
    return framebufferConfig;
}

Window getXWindow(XVisualInfo *visualInfo) {
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, RootWindow(display, visualInfo->screen), visualInfo->visual, AllocNone);
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask;

    Window window = XCreateWindow(display, RootWindow(display, visualInfo->screen), 0, 0, 100, 100, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWBorderPixel|CWColormap|CWEventMask, &swa);
    assert(window);
    return window;
}

GLXContext getGLContext() {
    static int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 6,
        None
    };

    GLXContext glContext = glx_createContextAttribs(display, framebufferConfig[0], 0, 1, context_attribs);
    assert(glContext);
    return glContext;
}

void initializeDeleteMessage() {
    deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
}

void init(void) {
    display = XOpenDisplay(0);
    initializeDeleteMessage();
    initializeGlProcs();

    framebufferConfig = getFrameBufferConfiguration();

    XVisualInfo *visualInfo = glXGetVisualFromFBConfig(display, framebufferConfig[0]);
    window = getXWindow(visualInfo);
    XSetWMProtocols(display, window, &deleteMessage, 1);
    XSetStandardProperties(display, window, "Minimal OpenGL example", "Icon", None, NULL, 0, NULL);

    glContext = getGLContext();

    glXMakeCurrent(display, window, glContext);  // make the context we created the current context    
    XMapRaised(display, window);  // show window and move to front
}

void finalize_opengl(void) {
    glXMakeCurrent(display, 0, 0);
    glXDestroyContext(display, glContext);
}

void finalize_x(void) {
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

void finalize(void) {
    finalize_opengl();
    finalize_x();
}

int main(int argc, char **argv)
{
    init();

    XEvent event;
    while (true)
    {
        XNextEvent(display, &event);

        if (event.type == ClientMessage)
        {
            if (event.xclient.data.l[0] == deleteMessage)
                break;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers(display, window);
    }

    finalize();
}
