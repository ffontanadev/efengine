#pragma once

struct GLFWwindow;

namespace efengine {

class InputManager {
public:
    InputManager();
    ~InputManager();

    // Delete copy constructor and assignment
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    // Process input each frame
    void ProcessInput(GLFWwindow* window);

    // Query input state
    bool IsKeyPressed(GLFWwindow* window, int key) const;
};

} // namespace efengine
