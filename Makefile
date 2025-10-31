# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

# ==== Add only the .cpp files that are implemented ====
SOURCES = FactoryStrategyIteratorMain.cpp \
          Tree.cpp \
          TreeFactory.cpp \
          Vegetable.cpp \
          Plant.cpp \
          CareStrategy.cpp \
		  SeasonalCare.cpp \
		  CategoryIterator.cpp \
		  ConcreteInventoryIterator.cpp \
		  Inventory.cpp \
		  Flower.cpp \
		  FlowerFactory.cpp \
		  VegetableFactory.cpp \
		  HighMaintenanceCare.cpp \
		  LowMaintenanceCare.cpp \
		  InventoryItem.cpp \
		  InventoryAggregate.cpp \
		  InventoryIterator.cpp \
		  LowStockIterator.cpp \
		  PlantFactory.cpp

# ======================================================

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = garden_test

# ==== TEST SOURCES ====
TEST_SOURCES = tests/test_main.cpp \
               tests/test_plant.cpp \
               tests/test_inventory.cpp \
               tests/test_iterators.cpp \
               tests/test_factories.cpp \
               tests/test_care_stategies.cpp

# Test objects
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Test executable name
TEST_TARGET = run_tests

# Default target
all: $(TARGET)

# Main program linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test program linking
$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out FactoryStrategyIteratorMain.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile rule for main source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile rule for test files
tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run main program
run: $(TARGET)
	./$(TARGET)

# 🔍 Run all tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# 🔍 Run tests with verbose output
test-verbose: $(TEST_TARGET)
	./$(TEST_TARGET) -s

# 🔍 Run specific test suites
test-plant: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Plant"

test-inventory: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Inventory"

test-factories: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Factory"

test-care: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Care"

test-iterators: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Iterator"

# 🔍 Run specific test cases
test-flower: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Flower"

test-tree: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Tree"

test-vegetable: $(TEST_TARGET)
	./$(TEST_TARGET) -tc="Vegetable"

# 🔍 Memory leak check for tests
valgrind-test: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)

# 🔍 Memory leak check for main program
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean main program build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Clean test files
clean-tests:
	rm -f $(TEST_OBJECTS) $(TEST_TARGET)

# Clean everything
clean-all: clean clean-tests

# Build only tests (without main program)
build-tests: $(TEST_TARGET)

# Build everything including tests
build-all: $(TARGET) $(TEST_TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build main program (default)"
	@echo "  run          - Build and run main program"
	@echo "  test         - Build and run all tests"
	@echo "  test-verbose - Run tests with detailed output"
	@echo "  test-plant   - Run only plant-related tests"
	@echo "  test-inventory - Run only inventory tests"
	@echo "  test-factories - Run only factory tests"
	@echo "  test-care    - Run only care strategy tests"
	@echo "  test-iterators - Run only iterator tests"
	@echo "  build-tests  - Build tests without running"
	@echo "  build-all    - Build both main program and tests"
	@echo "  valgrind-test - Run tests with memory checking"
	@echo "  valgrind     - Run main program with memory checking"
	@echo "  clean        - Clean main program build files"
	@echo "  clean-tests  - Clean test build files"
	@echo "  clean-all    - Clean everything"
	@echo "  help         - Show this help message"

# Phony targets
.PHONY: all run test test-verbose test-plant test-inventory test-factories test-care \
        test-iterators test-flower test-tree test-vegetable valgrind-test valgrind \
        clean clean-tests clean-all build-tests build-all help