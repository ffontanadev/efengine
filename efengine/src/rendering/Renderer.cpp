#define GLFW_INCLUDE_NONE
#include "rendering/Renderer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace efengine {

Renderer::Renderer()
    : m_initialized(false)
{
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(GLFWwindow* window) {
    if (m_initialized) {
        std::cout << "[RENDERER] Already initialized" << std::endl;
        return true;
    }

    // Load OpenGL using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[GLAD] Failed to initialize OpenGL context" << std::endl;
        return false;
    }

    std::cout << "[GLAD] OpenGL loaded successfully" << std::endl;
    std::cout << "[OpenGL] Version: " << glGetString(GL_VERSION) << std::endl;

    m_initialized = true;
    return true;
}

void Renderer::Shutdown() {
    m_initialized = false;
}

void Renderer::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::OnResize(int width, int height) {
    SetViewport(width, height);
    std::cout << "[WINDOW] Resized to " << width << "x" << height << std::endl;
}

} // namespace efengine
