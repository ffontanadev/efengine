#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/callbacks.h"
#include <core/Timer.h>
#include "core/gameloop.h"

static Timer timer;

void gameLoop(GLFWwindow *window_instance) {
	std::cout << "[GAME] MAIN LOOP BEGIN" << std::endl;
	
	timer.getDeltaTime();

	while (!glfwWindowShouldClose(window_instance)) {
		processInput(window_instance);
		Timer timer;
		timer.getDeltaTime();

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window_instance);
		glfwPollEvents();
	}

	std::cout << "[GAME] MAIN LOOP END" << std::endl;
}