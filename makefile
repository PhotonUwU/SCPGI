# Define the compiler and flags
CXX := g++
CXXFLAGS := -Wall -g -I/usr/include/SDL2
LDFLAGS := -lSDL2
SRC_DIR := src
BUILD_DIR := build
TARGET := main

# Find all .cpp files in src directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Define object files path
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Link the final executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile .cpp files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET)

.PHONY: all clean
