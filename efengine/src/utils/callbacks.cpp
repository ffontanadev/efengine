#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "callbacks.h"

extern bool isRunning; // Declare that isRunning exists in main.cpp

// GLFW Error Callback
void error_callback(int error, const char* description) {
	std::cout << "[GLFW] Error " << error << ": " << description << std::endl;
}

// GLFW Close Callback
void close_callback(GLFWwindow* window) {
	isRunning = false;
}

// GLFW Resize Callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "[WINDOW] Resized to " << width << "x" << height << std::endl;
}

// User Input Callback
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}