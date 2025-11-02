# Makefile for COS-214 Final Project

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Collect all .cpp files in the project automatically
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

# Executable
TARGET = nursery_simulator

# Default target: build the simulator
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the simulator
run: $(TARGET)
	./$(TARGET)

# Run with Valgrind to check memory leaks
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Clean object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run valgrind clean
