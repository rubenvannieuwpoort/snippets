// minimal X11 example
// you might need to install some X11 dev package (sudo apt install libx11-dev on Ubuntu)
// compile with gcc minimal_x11.c -o minimal_x11 -lX11

#include "header.h"

void display() {  // Display function will draw the image.

    glClearColor(0, 0, 0, 1);  // (In fact, this is the default.)
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); // red
    glVertex2f(-0.8, -0.8);
    glColor3f(0, 1, 0); // green
    glVertex2f(0.8, -0.8);
    glColor3f(0, 0, 1); // blue
    glVertex2f(0, 0.9);
    glEnd();

    //glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

int main() {
	CPF_initialize();
	CPF_Window window = CPF_createwindow("Hello, CPF!", 1024, 1024);
	CPF_showwindow(window);
	CPF_eventloop(window);
	CPF_finalize();
	return 0;
}
