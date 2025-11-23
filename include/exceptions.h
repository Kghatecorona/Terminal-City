#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Custom exception for invalid grid coordinates
class InvalidCoordinateException : public std::exception {
private:
    std::string message;
public:
    InvalidCoordinateException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Custom exception for insufficient funds
class InsufficientFundsException : public std::exception {
private:
    std::string message;
public:
    InsufficientFundsException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Custom exception for file operations
class FileOperationException : public std::exception {
private:
    std::string message;
public:
    FileOperationException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Custom exception for invalid input
class InvalidInputException : public std::exception {
private:
    std::string message;
public:
    InvalidInputException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_H