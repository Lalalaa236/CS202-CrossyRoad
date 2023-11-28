# Compiler and flags
CXX = g++
CXXFLAGS = -w -Iinclude
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target executable
TARGET = CrossRoad

# Build rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build rule for the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
