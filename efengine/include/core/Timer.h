#pragma once

class Timer {
private:
    double m_lastTime;

public:
    Timer();
    double getDeltaTime();
    void reset();
};