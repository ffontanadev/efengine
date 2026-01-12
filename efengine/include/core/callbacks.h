#pragma once
#include <GLFW/glfw3.h>

// Declare all callback functions
void error_callback(int error, const char* description);
void close_callback(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
