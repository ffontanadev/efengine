#include "core/Window.h"
#include "core/Logger.h"

namespace efengine {

Window::Window()
    : m_window(nullptr)
    , m_width(0)
    , m_height(0)
    , m_title(nullptr)
{
}

Window::~Window() {
    Destroy();
}

bool Window::Create(int width, int height, const char* title) {
    m_width = width;
    m_height = height;
    m_title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

    if (!m_window) {
        LOG_ERROR() << "Failed to create GLFW window";
        return false;
    }

    LOG_INFO() << "Window created: " << m_width << "x" << m_height;

    glfwMakeContextCurrent(m_window);

    return true;
}

void Window::Destroy() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SwapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

bool Window::ShouldClose() const {
    return m_window ? glfwWindowShouldClose(m_window) : true;
}

void Window::SetShouldClose(bool value) {
    if (m_window) {
        glfwSetWindowShouldClose(m_window, value);
    }
}

void Window::SetFramebufferSizeCallback(GLFWframebuffersizefun callback) {
    if (m_window) {
        glfwSetFramebufferSizeCallback(m_window, callback);
    }
}

} // namespace efengine
