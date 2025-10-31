# Makefile for Garden Center Management System
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Main program
MAIN_SOURCES = main.cpp PlantAbstractFactory.cpp Plant.cpp Command.cpp Report.cpp
MAIN_TARGET = garden_center

# Test program  
TEST_SOURCES = test_garden_center.cpp PlantAbstractFactory.cpp Plant.cpp Command.cpp Report.cpp
TEST_TARGET = garden_center_tests

# Default target
all: $(MAIN_TARGET) $(TEST_TARGET)

# Main program
$(MAIN_TARGET): $(MAIN_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) $(MAIN_SOURCES)

# Test program
$(TEST_TARGET): $(TEST_SOURCES) doctest.h
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run specific test suites
test-factory: $(TEST_TARGET)
	./$(TEST_TARGET) "Plant Abstract Factory Pattern"

test-command: $(TEST_TARGET)
	./$(TEST_TARGET) "Command Pattern"

test-template: $(TEST_TARGET)
	./$(TEST_TARGET) "Template Method Pattern"

test-integration: $(TEST_TARGET)
	./$(TEST_TARGET) "Integration Tests"

# Run with verbose output
test-verbose: $(TEST_TARGET)
	./$(TEST_TARGET) --success

# Clean up
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all test test-factory test-command test-template test-integration test-verbose clean