#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

enum LogLevel { DEBUG, INFO, WARNING, ERROR_LEVEL, CRITICAL };

// Simple logging system
class Logger {
private:
    std::ofstream logFile;
    LogLevel currentLevel;
    
public:
    Logger(const std::string& filename = "game.log");
    ~Logger();
    
    // Log a message with specified level
    void log(LogLevel level, const std::string& message);
    
    // Convenience methods
    void debug(const std::string& msg) { log(DEBUG, msg); }
    void info(const std::string& msg) { log(INFO, msg); }
    void warning(const std::string& msg) { log(WARNING, msg); }
    void error(const std::string& msg) { log(ERROR_LEVEL, msg); }
    void critical(const std::string& msg) { log(CRITICAL, msg); }
    
    // Set minimum log level to display
    void setLogLevel(LogLevel level) { currentLevel = level; }
};

#endif // LOGGER_H