#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "core/Timer.h"

Timer::Timer()
    : m_lastTime(glfwGetTime())
{
}

double Timer::getDeltaTime() {
    double currentTime = glfwGetTime();
    double delta = currentTime - m_lastTime;
    m_lastTime = currentTime;
    return delta;
}

void Timer::reset() {
    m_lastTime = glfwGetTime();
}


