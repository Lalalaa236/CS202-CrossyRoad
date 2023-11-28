# Target executable
TARGET = CrossRoad

# Set the build type (debug or release)
BUILD_TYPE ?= debug

# Use different obj and dep directories for debug and release builds
OBJ_DIR = obj/$(BUILD_TYPE)
DEP_DIR = dep/$(BUILD_TYPE)

# Compiler and flags
CXX = g++
ifeq ($(BUILD_TYPE),debug)
    CXXFLAGS := -g -O0 -Wall -Wextra -Iinclude
else
    CXXFLAGS := -O2 -Wall -Wextra -Iinclude
endif

LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Source and object files
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))


# Build rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build rule for the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Phony targets
.PHONY: all clean debug release

# Default target
all: $(TARGET)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Debug target
debug: BUILD_TYPE = debug
debug: clean all

# Release target
release: BUILD_TYPE = release
release: clean all
