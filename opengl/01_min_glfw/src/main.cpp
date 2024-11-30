#include <GLFW/glfw3.h>

int main(void) {
	if (!glfwInit()) return -1;

	GLFWwindow* window;

	if (!(window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL))) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	while (!glfwWindowShouldClose(window) &&
	    glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
