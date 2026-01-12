#pragma once
#include "core/Window.h"
#include "rendering/Renderer.h"
#include "input/InputManager.h"

namespace efengine {

class Application {
public:
    Application();
    ~Application();

    // Delete copy constructor and assignment
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Application lifecycle
    bool Initialize();
    void Run();
    void Shutdown();

private:
    bool InitializeGLFW();
    void SetupCallbacks();

    Window m_window;
    Renderer m_renderer;
    InputManager m_input;
    bool m_initialized;
};

} // namespace efengine
