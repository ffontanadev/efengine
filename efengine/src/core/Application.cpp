#include "core/Application.h"
#include "core/Logger.h"
#include "core/Timer.h"
#include <GLFW/glfw3.h>

namespace efengine {

// Forward declare callback functions
static void error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Constructor
Application::Application()
    : m_initialized(false)
{
}

// Deconstructor
Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    if (m_initialized) {
        return true;
    }

    // Step 0: Initialize Logger (FIRST - so we can log everything else)
    if (!Logger::Get().Initialize("engine.log")) {
        return false;
    }

    // Step 1: Initialize GLFW
    if (!InitializeGLFW()) {
        return false;
    }

    // Step 2: Create Window
    if (!m_window.Create(1280, 720, "EFE ENGINE")) {
        glfwTerminate();
        return false;
    }

    // Step 3: Initialize Renderer (loads OpenGL/GLAD)
    if (!m_renderer.Initialize(m_window.GetHandle())) {
        m_window.Destroy();
        glfwTerminate();
        return false;
    }

    // Step 4: Setup callbacks
    SetupCallbacks();

    m_initialized = true;
    LOG_INFO() << "Application initialized successfully";
    return true;
}

void Application::Run() {
    if (!m_initialized) {
        LOG_ERROR() << "Cannot run - Application not initialized";
        return;
    }

    LOG_INFO() << "Main loop started";

    Timer timer;
    const double FIXED_TIMESTEP = 1.0 / 60.0;
    double accumulator = 0.0;

    while (!m_window.ShouldClose()) {
        double deltaTime = timer.getDeltaTime();

        if (deltaTime > 0.25) {
            deltaTime = 0.25;
        }

        accumulator += deltaTime;

        while (accumulator >= FIXED_TIMESTEP) {
            accumulator -= FIXED_TIMESTEP;
        }

        double alpha = accumulator / FIXED_TIMESTEP;
        (void)alpha; // Suppress unused warning for now

        m_input.ProcessInput(m_window.GetHandle());
        m_window.PollEvents();

        m_renderer.Clear(0.1f, 0.1f, 0.15f, 1.0f);
        m_window.SwapBuffers();
    }

    LOG_INFO() << "Main loop ended";
}

void Application::Shutdown() {
    if (!m_initialized) {
        return;
    }

    m_renderer.Shutdown();
    m_window.Destroy();
    glfwTerminate();

    m_initialized = false;
    LOG_INFO() << "Application shutdown complete";

    Logger::Get().Shutdown();
}

bool Application::InitializeGLFW() {
    if (!glfwInit()) {
        LOG_FATAL() << "GLFW initialization failed";
        return false;
    }

    LOG_INFO() << "GLFW initialized successfully";
    glfwSetErrorCallback(error_callback);
    return true;
}

void Application::SetupCallbacks() {
    glfwSetWindowUserPointer(m_window.GetHandle(), &m_renderer);
    m_window.SetFramebufferSizeCallback(framebuffer_size_callback);
}

static void error_callback(int error, const char* description) {
    LOG_ERROR() << "GLFW Error " << error << ": " << description;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    efengine::Renderer* renderer = static_cast<efengine::Renderer*>(glfwGetWindowUserPointer(window));
    if (renderer) {
        renderer->OnResize(width, height);
    }
}

} // namespace efengine
