# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# SFML include and library directories
SFML_INCLUDE_DIR = /usr/local/include
SFML_LIB_DIR = /usr/local/lib

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = main.cpp ../include/components/main.hpp

# Output binary
TARGET = sfml-app

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE_DIR) -L$(SFML_LIB_DIR) $(SRCS) -o $(TARGET) $(SFML_LIBS)

# Clean up
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
