#include "Plant.h"
#include "ConcretePlant.h"
#include "PlantFactory.h"
#include "Command.h"
#include "CommandInvoker.h"
#include "WaterPlantCommand.h"
#include "FertilizePlantCommand.h"
#include "SellPlantCommand.h"
#include "Staff.h"
#include "Reports.h"
#include "PlantHealthReport.h"
#include <iostream>
#include <memory>
#include <vector>

void testAbstractFactory() {
    std::cout << "=== Testing Abstract Factory ===\n";
    try {
        auto factory = PlantFactoryProvider::createFactory("flower");
        Plant* rose = factory->createPlant("Rose", "Rosa", 25.99);
        std::cout << "Created: " << rose->getName() << std::endl;
        std::cout << "Health: " << rose->getHealthPercentage() << "%\n";
        delete rose;
        
        auto treeFactory = PlantFactoryProvider::createFactory("tree");
        Plant* oak = treeFactory->createPlant("Oak Tree", "Quercus", 99.99);
        std::cout << "Created: " << oak->getName() << std::endl;
        delete oak;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testCommandPattern() {
    std::cout << "\n=== Testing Command Pattern ===\n";
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    CommandInvoker invoker;
    
    // Test Staff
    Staff gardener("John Doe", "Senior Gardener");
    gardener.assignTask("Water plants in section A");
    std::cout << gardener.getStaffInfo() << std::endl;
    
    // Test Water Command
    WaterPlantCommand* waterCmd = new WaterPlantCommand(&plant, 50, gardener.getName());
    std::string result = invoker.executeCommand(waterCmd);
    std::cout << result << std::endl;
    
    // Test Fertilize Command
    FertilizePlantCommand* fertilizeCmd = new FertilizePlantCommand(&plant, 20, gardener.getName());
    result = invoker.executeCommand(fertilizeCmd);
    std::cout << result << std::endl;
    
    // Test Undo
    if (invoker.canUndo()) {
        std::cout << "\nTesting undo:\n";
        std::string undoResult = invoker.undo();
        std::cout << undoResult << std::endl;
    }
    
    // Clean up
    invoker.clearHistory();
}

void testTemplateMethod() {
    std::cout << "\n=== Testing Template Method ===\n";
    
    // Create some test plants
    std::vector<Plant*> plants;
    plants.push_back(new ConcretePlant("Rose", "Flower", 25.99));
    plants.push_back(new ConcretePlant("Oak", "Tree", 99.99));
    plants.push_back(new ConcretePlant("Tomato", "Vegetable", 15.99));
    
    // Test Plant Health Report
    PlantHealthReport healthReport(plants);
    std::string report = healthReport.generateReport();
    std::cout << report << std::endl;
    
    // Clean up plants
    for (Plant* plant : plants) {
        delete plant;
    }
    plants.clear();
}

int main() {
    testAbstractFactory();
    testCommandPattern();
    testTemplateMethod();
    std::cout << "\nAll tests completed successfully!\n";
    return 0;
}