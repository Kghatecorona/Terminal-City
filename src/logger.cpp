#include "logger.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Logger::Logger(const std::string& filename)
    : currentLevel(INFO) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Warning: Could not open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) return;
    
    // Get current timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    std::ostringstream timestamp;
    timestamp << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    
    // Convert level to string
    std::string levelStr;
    switch (level) {
        case DEBUG: levelStr = "DEBUG"; break;
        case INFO: levelStr = "INFO"; break;
        case WARNING: levelStr = "WARNING"; break;
        case ERROR_LEVEL: levelStr = "ERROR"; break;
        case CRITICAL: levelStr = "CRITICAL"; break;
    }
    
    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp.str() << "] [" << levelStr << "] "
             << message << std::endl;
    
    // Output to console
    std::cout << logEntry.str();
    
    // Output to file
    if (logFile.is_open()) {
        logFile << logEntry.str();
        logFile.flush();
    }
}