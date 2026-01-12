#pragma once
#include <string>
#include <fstream>
#include <sstream>

namespace efengine {

// Log severity levels (PascalCase to avoid Windows macro conflicts)
enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

class Logger {
public:
    static Logger& Get();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    bool Initialize(const std::string& logFilePath = "engine.log");
    void Shutdown();

    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const { return m_logLevel; }

    void Log(LogLevel level, const std::string& message, const char* file, int line);

private:
    Logger();
    ~Logger();

    const char* LogLevelToString(LogLevel level) const;
    const char* LogLevelToColor(LogLevel level) const;
    std::string GetTimestamp() const;
    void WriteToConsole(LogLevel level, const std::string& fullMessage);
    void WriteToFile(const std::string& fullMessage);
    void WriteToDebugger(const std::string& fullMessage);

    LogLevel m_logLevel;
    std::ofstream m_logFile;
    bool m_initialized;
};

// Stream-based log helper class
class LogStream {
public:
    LogStream(LogLevel level, const char* file, int line)
        : m_level(level), m_file(file), m_line(line) {}

    ~LogStream() {
        Logger::Get().Log(m_level, m_stream.str(), m_file, m_line);
    }

    template<typename T>
    LogStream& operator<<(const T& value) {
        m_stream << value;
        return *this;
    }

private:
    LogLevel m_level;
    const char* m_file;
    int m_line;
    std::ostringstream m_stream;
};

} // namespace efengine

// Helper to extract filename from path
inline const char* GetFileName(const char* path) {
    const char* file = path;
    while (*path) {
        if (*path == '/' || *path == '\\') {
            file = path + 1;
        }
        path++;
    }
    return file;
}

// Simple macros using stream syntax: LOG_INFO() << "Message " << value;
#define LOG_TRACE() efengine::LogStream(efengine::LogLevel::Trace, GetFileName(__FILE__), __LINE__)
#define LOG_DEBUG() efengine::LogStream(efengine::LogLevel::Debug, GetFileName(__FILE__), __LINE__)
#define LOG_INFO()  efengine::LogStream(efengine::LogLevel::Info, GetFileName(__FILE__), __LINE__)
#define LOG_WARN()  efengine::LogStream(efengine::LogLevel::Warn, GetFileName(__FILE__), __LINE__)
#define LOG_ERROR() efengine::LogStream(efengine::LogLevel::Error, GetFileName(__FILE__), __LINE__)
#define LOG_FATAL() efengine::LogStream(efengine::LogLevel::Fatal, GetFileName(__FILE__), __LINE__)
