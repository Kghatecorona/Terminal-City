# Makefile for Terminal City - Windows (MinGW) Compatible
# -------------------------------------------

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./include
LDFLAGS =

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = .
TARGET = terminalcity.exe

# Find all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file names
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link object files into executable
$(BIN_DIR)/$(TARGET): $(OBJS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)" >nul 2>&1
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)
	@echo Build complete: $(BIN_DIR)\$(TARGET)

# Compile each source file into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)" >nul 2>&1
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo Compiled: $<

# Clean build artifacts
clean:
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	if exist "$(BIN_DIR)\$(TARGET)" del /q "$(BIN_DIR)\$(TARGET)"
	if exist "game.log" del /q "game.log"

# Run the program
run: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)\$(TARGET)

# Build and run in one step
build-run: clean all run

# Phony targets
.PHONY: all clean run build-run help

# Help target
help:
	@echo Terminal City - Makefile targets:
	@echo   mingw32-make           - Build the executable
	@echo   mingw32-make run       - Build and run the program
	@echo   mingw32-make clean     - Remove build artifacts
	@echo   mingw32-make help      - Show this help message