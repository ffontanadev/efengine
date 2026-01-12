#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/callbacks.h"
#include "core/gameloop.h"


bool isRunning = true;

struct Window {
	const char *title;

	int width;
	int height;

};

int main() {

	if (!glfwInit()) { // If there is an error initializing GLFW
		std::cout << "[GLFW] NOT INITIALIZED" << std::endl;
		return GLFW_FALSE;
	}
	std::cout << "[GLFW] Initialized successfully" << std::endl;

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Begin Window
	Window window;
	window.title = "My game";
	window.width = 1280;
	window.height = 720;

	GLFWwindow* window_instance = glfwCreateWindow(window.width, window.height, window.title, 0, 0);

	if (!window_instance) {
		std::cout << "[GLFW] FAILED CREATING WINDOW INSTANCE" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "[GLFW] Window created: " << window.width << "x" << window.height << std::endl;

	glfwMakeContextCurrent(window_instance);
	glfwSetFramebufferSizeCallback(window_instance, framebuffer_size_callback);
	glfwSetWindowCloseCallback(window_instance, close_callback);

	// Load OpenGL using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[GLAD] Failed to initialize OpenGL context" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "[GLAD] OpenGL loaded successfully" << std::endl;
	std::cout << "[OpenGL] Version: " << glGetString(GL_VERSION) << std::endl;

	
	gameLoop(window_instance);
	
	glfwDestroyWindow(window_instance);
	glfwTerminate();

	return 0;

}