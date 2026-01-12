#include "core/Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <Windows.h>
#endif

namespace efengine {

Logger::Logger()
    : m_logLevel(LogLevel::Trace)
    , m_initialized(false)
{
}

Logger::~Logger() {
    Shutdown();
}

Logger& Logger::Get() {
    static Logger instance;
    return instance;
}

bool Logger::Initialize(const std::string& logFilePath) {
    if (m_initialized) {
        return true;
    }

    m_logFile.open(logFilePath, std::ios::out | std::ios::trunc);
    if (!m_logFile.is_open()) {
        std::cerr << "[LOGGER] Failed to open log file: " << logFilePath << std::endl;
        return false;
    }

    m_initialized = true;

    // Log initialization using the Log function directly (no macros yet)
    std::ostringstream ss;
    ss << "=== Logger Initialized === Log file: " << logFilePath;
    Log(LogLevel::Info, ss.str(), "Logger.cpp", 44);

    return true;
}

void Logger::Shutdown() {
    if (!m_initialized) {
        return;
    }

    Log(LogLevel::Info, "=== Logger Shutdown ===", "Logger.cpp", 53);

    if (m_logFile.is_open()) {
        m_logFile.close();
    }

    m_initialized = false;
}

void Logger::SetLogLevel(LogLevel level) {
    m_logLevel = level;
}

void Logger::Log(LogLevel level, const std::string& message, const char* file, int line) {
    if (level < m_logLevel) {
        return;
    }

    std::ostringstream ss;
    ss << "[" << GetTimestamp() << "] ";
    ss << "[" << LogLevelToString(level) << "] ";
    ss << message;
    ss << " (" << file << ":" << line << ")";

    std::string fullMessage = ss.str();

    WriteToConsole(level, fullMessage);
    WriteToFile(fullMessage);
    WriteToDebugger(fullMessage);
}

const char* Logger::LogLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info:  return "INFO ";
        case LogLevel::Warn:  return "WARN ";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Fatal: return "FATAL";
        default: return "?????";
    }
}

const char* Logger::LogLevelToColor(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace: return "\033[37m";
        case LogLevel::Debug: return "\033[36m";
        case LogLevel::Info:  return "\033[32m";
        case LogLevel::Warn:  return "\033[33m";
        case LogLevel::Error: return "\033[31m";
        case LogLevel::Fatal: return "\033[35m";
        default: return "\033[0m";
    }
}

std::string Logger::GetTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::ostringstream ss;

#ifdef _WIN32
    struct tm timeInfo;
    localtime_s(&timeInfo, &time);
    ss << std::put_time(&timeInfo, "%H:%M:%S");
#else
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");
#endif

    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

void Logger::WriteToConsole(LogLevel level, const std::string& fullMessage) {
#ifdef _WIN32
    static bool consoleInitialized = false;
    if (!consoleInitialized) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            DWORD mode = 0;
            if (GetConsoleMode(hConsole, &mode)) {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hConsole, mode);
            }
        }
        consoleInitialized = true;
    }
    std::cout << LogLevelToColor(level) << fullMessage << "\033[0m" << std::endl;
#else
    std::cout << fullMessage << std::endl;
#endif
}

void Logger::WriteToFile(const std::string& fullMessage) {
    if (m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
        m_logFile.flush();
    }
}

void Logger::WriteToDebugger(const std::string& fullMessage) {
#ifdef _WIN32
    OutputDebugStringA((fullMessage + "\n").c_str());
#endif
}

} // namespace efengine
