#pragma once

struct GLFWwindow;

namespace efengine {

class Renderer {
public:
    Renderer();
    ~Renderer();

    // Delete copy constructor and assignment
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Two-phase initialization
    bool Initialize(GLFWwindow* window);
    void Shutdown();

    // Rendering operations
    void Clear(float r, float g, float b, float a);
    void SetViewport(int width, int height);

    // Callback for window resize
    void OnResize(int width, int height);

private:
    bool m_initialized;
};

} // namespace efengine
