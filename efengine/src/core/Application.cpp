#include "core/Application.h"
#include "core/Timer.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace efengine {

// Forward declare callback functions
static void error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Application::Application()
    : m_initialized(false)
{
}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    if (m_initialized) {
        return true;
    }

    // Step 1: Initialize GLFW
    if (!InitializeGLFW()) {
        return false;
    }

    // Step 2: Create Window
    if (!m_window.Create(1280, 720, "My game")) {
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
    std::cout << "[APPLICATION] Initialized successfully" << std::endl;
    return true;
}

void Application::Run() {
    if (!m_initialized) {
        std::cout << "[APPLICATION] Cannot run - not initialized" << std::endl;
        return;
    }

    std::cout << "[GAME] MAIN LOOP BEGIN" << std::endl;

    Timer timer;
    const double FIXED_TIMESTEP = 1.0 / 60.0;  // 60 updates per second (16.67ms)
    double accumulator = 0.0;

    // Main game loop
    while (!m_window.ShouldClose()) {
        double deltaTime = timer.getDeltaTime();

        // Clamp delta to prevent SPIRAL OF DEATH
        if (deltaTime > 0.25) {
            deltaTime = 0.25;  // Max 250ms
        }

        accumulator += deltaTime;

        while (accumulator >= FIXED_TIMESTEP) {
            // update(FIXED_TIMESTEP);  // Always 16.67ms
            accumulator -= FIXED_TIMESTEP;
        }
        
        double alpha = accumulator / FIXED_TIMESTEP;
        //render(alpha);

        // Process input
        m_input.ProcessInput(m_window.GetHandle());
        m_window.PollEvents();



        // Render
        m_renderer.Clear(0.1f, 0.1f, 0.15f, 1.0f);

        // Swap buffers
        m_window.SwapBuffers();
    }

    std::cout << "[GAME] MAIN LOOP END" << std::endl;
}

void Application::Shutdown() {
    if (!m_initialized) {
        return;
    }

    m_renderer.Shutdown();
    m_window.Destroy();
    glfwTerminate();

    m_initialized = false;
    std::cout << "[APPLICATION] Shutdown complete" << std::endl;
}

bool Application::InitializeGLFW() {
    if (!glfwInit()) {
        std::cout << "[GLFW] NOT INITIALIZED" << std::endl;
        return false;
    }

    std::cout << "[GLFW] Initialized successfully" << std::endl;
    glfwSetErrorCallback(error_callback);
    return true;
}

void Application::SetupCallbacks() {
    // Set window user pointer to renderer for callbacks
    glfwSetWindowUserPointer(m_window.GetHandle(), &m_renderer);

    // Setup framebuffer size callback
    m_window.SetFramebufferSizeCallback(framebuffer_size_callback);
}

// Static callback functions
static void error_callback(int error, const char* description) {
    std::cout << "[GLFW] Error " << error << ": " << description << std::endl;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Get renderer from window user pointer
    efengine::Renderer* renderer = static_cast<efengine::Renderer*>(glfwGetWindowUserPointer(window));
    if (renderer) {
        renderer->OnResize(width, height);
    }
}

} // namespace efengine
