# Makefile for Plant Nursery Simulation
# Design Patterns: Composite, Observer, Facade
# Testing Version

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = nursery_simulation

# Source files
SOURCES = main.cpp \
          Plant.cpp \
          Subject.cpp \
          GardenArea.cpp \
          GardenSection.cpp \
          PlantBed.cpp \
          HealthMonitor.cpp \
          GrowthTracker.cpp \
          InventoryObserver.cpp \
          SimulationFacade.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = GardenComponent.h \
          GardenArea.h \
          GardenSection.h \
          PlantBed.h \
          Observer.h \
          Subject.h \
          Plant.h \
          HealthMonitor.h \
          GrowthTracker.h \
          InventoryObserver.h \
          SimulationFacade.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo ""
	@echo "════════════════════════════════════════════════════════════"
	@echo "  ✅ Build Successful!"
	@echo "════════════════════════════════════════════════════════════"
	@echo "  Run with: ./$(TARGET)"
	@echo "════════════════════════════════════════════════════════════"
	@echo ""

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning build files..."
	@rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Clean complete!"

# Run the program
run: $(TARGET)
	@echo ""
	@echo "════════════════════════════════════════════════════════════"
	@echo "  🌱 Running Plant Nursery Simulation..."
	@echo "════════════════════════════════════════════════════════════"
	@echo ""
	@./$(TARGET)

# Rebuild everything
rebuild: clean all

# Generate documentation with Doxygen
docs:
	@echo "Generating Doxygen documentation..."
	@doxygen Doxyfile
	@echo "✓ Documentation generated in ./docs/"

# Check for memory leaks (requires valgrind)
memcheck: $(TARGET)
	@echo "Running memory leak check..."
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Quick memory check
valgrind: $(TARGET)
	@valgrind --leak-check=yes ./$(TARGET)

# Display file statistics
stats:
	@echo ""
	@echo "════════════════════════════════════════════════════════════"
	@echo "  📊 Project Statistics"
	@echo "════════════════════════════════════════════════════════════"
	@echo "  Source files:    " `echo $(SOURCES) | wc -w`
	@echo "  Header files:    " `echo $(HEADERS) | wc -w`
	@echo "  Total C++ files: " `expr \`echo $(SOURCES) | wc -w\` + \`echo $(HEADERS) | wc -w\``
	@echo "  Lines of code:   " `cat $(SOURCES) $(HEADERS) 2>/dev/null | wc -l`
	@echo "════════════════════════════════════════════════════════════"
	@echo ""

# List all source files
list:
	@echo ""
	@echo "Source Files:"
	@echo "$(SOURCES)" | tr ' ' '\n'
	@echo ""
	@echo "Header Files:"
	@echo "$(HEADERS)" | tr ' ' '\n'
	@echo ""

# Check compilation without linking
check:
	@echo "Checking compilation (no linking)..."
	@$(CXX) $(CXXFLAGS) -c $(SOURCES)
	@echo "✓ All files compile successfully!"
	@rm -f $(OBJECTS)

# Debug build with extra symbols
debug: CXXFLAGS += -DDEBUG -g3
debug: clean all
	@echo "✓ Debug build complete!"

# Release build with optimizations
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all
	@echo "✓ Release build complete!"

# Help target
help:
	@echo ""
	@echo "════════════════════════════════════════════════════════════"
	@echo "  🌱 Plant Nursery Simulation - Makefile Help"
	@echo "════════════════════════════════════════════════════════════"
	@echo ""
	@echo "Build Targets:"
	@echo "  make              - Build the project"
	@echo "  make all          - Build the project (same as make)"
	@echo "  make debug        - Build with debug symbols"
	@echo "  make release      - Build optimized release version"
	@echo ""
	@echo "Run Targets:"
	@echo "  make run          - Build and run the program"
	@echo ""
	@echo "Cleanup Targets:"
	@echo "  make clean        - Remove build files"
	@echo "  make rebuild      - Clean and rebuild"
	@echo ""
	@echo "Testing Targets:"
	@echo "  make check        - Check if files compile"
	@echo "  make valgrind     - Run with memory leak detection"
	@echo "  make memcheck     - Detailed memory leak check"
	@echo ""
	@echo "Documentation:"
	@echo "  make docs         - Generate Doxygen documentation"
	@echo ""
	@echo "Information:"
	@echo "  make stats        - Show project statistics"
	@echo "  make list         - List all source/header files"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "════════════════════════════════════════════════════════════"
	@echo ""

.PHONY: all clean run rebuild docs memcheck valgrind stats list check debug release help