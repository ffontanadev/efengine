#pragma once
#include <GLFW/glfw3.h>

namespace efengine {

class Window {
public:
    Window();
    ~Window();

    // Delete copy constructor and assignment (window shouldn't be copied)
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Two-phase initialization pattern
    bool Create(int width, int height, const char* title);
    void Destroy();

    // Window operations
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;
    void SetShouldClose(bool value);

    // Getters
    GLFWwindow* GetHandle() const { return m_window; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    const char* GetTitle() const { return m_title; }

    // Callback registration
    void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    const char* m_title;
};

} // namespace efengine
