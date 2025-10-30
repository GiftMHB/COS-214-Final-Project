# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

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
		  PlantFactory.cpp \
		  VegetableFactory.cpp 
# ======================================================

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = garden_test

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program
run: $(TARGET)
	./$(TARGET)

# 🔍 Memory leak check (requires valgrind)
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
