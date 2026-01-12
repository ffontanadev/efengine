#include "input/InputManager.h"
#include <GLFW/glfw3.h>

namespace efengine {

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

void InputManager::ProcessInput(GLFWwindow* window) {
    // Handle ESC key to close window
    if (IsKeyPressed(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

bool InputManager::IsKeyPressed(GLFWwindow* window, int key) const {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace efengine
