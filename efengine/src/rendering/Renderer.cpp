#define GLFW_INCLUDE_NONE
#include "rendering/Renderer.h"
#include "core/Logger.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

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
        LOG_WARN() << "Renderer already initialized";
        return true;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_FATAL() << "Failed to initialize OpenGL context (GLAD)";
        return false;
    }

    LOG_INFO() << "OpenGL loaded successfully (GLAD)";
    LOG_INFO() << "OpenGL Version: " << (const char*)glGetString(GL_VERSION);

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
    LOG_INFO() << "Window resized to " << width << "x" << height;
}

} // namespace efengine
