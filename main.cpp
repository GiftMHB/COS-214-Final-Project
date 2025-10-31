/**
 * @file main.cpp
 * @brief Garden Center Management System - Demonstration of Design Patterns
 * @details Demonstrates Abstract Factory, Command, and Template Method patterns
 */

#include "PlantAbstractFactory.h"
#include "Command.h"
#include "Report.h"
#include <iostream>
#include "Plant.h"
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * @brief Demonstrate Abstract Factory Pattern
 */
void demonstrateAbstractFactory() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "ABSTRACT FACTORY PATTERN DEMONSTRATION\n";
    std::cout << std::string(60, '=') << "\n";
    
    try {
        // Get available factory types
        auto factoryTypes = PlantFactoryProvider::getSupportedFactories();
        std::cout << "Available factory types: ";
        for (const auto& type : factoryTypes) {
            std::cout << type << " ";
        }
        std::cout << "\n\n";
        
        // Demonstrate Flower Factory
        std::cout << "🎯 DEMONSTRATING FLOWER FACTORY:\n";
        std::cout << std::string(40, '-') << "\n";
        auto flowerFactory = PlantFactoryProvider::getFactory("flower");
        std::cout << "Factory Type: " << flowerFactory->getFactoryType() << "\n";
        std::cout << "Description: " << flowerFactory->getDescription() << "\n\n";
        
        // Create flower products
        auto rose = std::unique_ptr<Plant>(flowerFactory->createPlant("Rose", "Rosa rubiginosa", 24.99));
        auto flowerKit = std::unique_ptr<CareKit>(flowerFactory->createCareKit());
        auto flowerSoil = std::unique_ptr<Soil>(flowerFactory->createSoil());
        
        std::cout << "\n";
        rose->displayInfo();
        std::cout << "\n";
        flowerKit->displayInfo();
        std::cout << "\n";
        flowerSoil->displayInfo();
        
        // Apply care kit to demonstrate functionality
        std::cout << "\n🧪 Applying care kit to rose:\n";
        flowerKit->applyCare(rose.get());
        
        // Demonstrate Tree Factory
        std::cout << "\n\n🎯 DEMONSTRATING TREE FACTORY:\n";
        std::cout << std::string(40, '-') << "\n";
        auto treeFactory = PlantFactoryProvider::getFactory("tree");
        std::cout << "Factory Type: " << treeFactory->getFactoryType() << "\n";
        std::cout << "Description: " << treeFactory->getDescription() << "\n\n";
        
        // Create tree products
        auto oak = std::unique_ptr<Plant>(treeFactory->createPlant("Oak", "Quercus robur", 89.99));
        auto treeKit = std::unique_ptr<CareKit>(treeFactory->createCareKit());
        auto treeSoil = std::unique_ptr<Soil>(treeFactory->createSoil());
        
        std::cout << "\n";
        oak->displayInfo();
        std::cout << "\n";
        treeKit->displayInfo();
        std::cout << "\n";
        treeSoil->displayInfo();
        
        // Apply care kit to tree
        std::cout << "\n🧪 Applying care kit to oak tree:\n";
        treeKit->applyCare(oak.get());
        
        // Demonstrate factory error handling
        std::cout << "\n\n🎯 DEMONSTRATING ERROR HANDLING:\n";
        std::cout << std::string(40, '-') << "\n";
        try {
            auto invalidFactory = PlantFactoryProvider::getFactory("invalid");
        } catch (const std::exception& e) {
            std::cout << "❌ Expected error: " << e.what() << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error in Abstract Factory demonstration: " << e.what() << "\n";
    }
}

/**
 * @brief Demonstrate Command Pattern
 */
void demonstrateCommandPattern() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "COMMAND PATTERN DEMONSTRATION\n";
    std::cout << std::string(60, '=') << "\n";
    
    try {
        // Create some plants for demonstration using the factory
        auto flowerFactory = PlantFactoryProvider::getFactory("flower");
        auto treeFactory = PlantFactoryProvider::getFactory("tree");
        
        auto rose = std::unique_ptr<Plant>(flowerFactory->createPlant("Rose", "Rosa", 19.99));
        auto oak = std::unique_ptr<Plant>(treeFactory->createPlant("Oak", "Quercus", 79.99));
        
        // Create command invoker
        CommandInvoker invoker;
        
        // Demonstrate watering commands
        std::cout << "🚰 DEMONSTRATING WATERING COMMANDS:\n";
        std::cout << std::string(40, '-') << "\n";
        
        auto waterRoseCmd = new WaterPlantCommand(rose.get(), 200, "Gardener John");
        auto waterOakCmd = new WaterPlantCommand(oak.get(), 500, "Gardener Jane");
        
        std::cout << "Executing commands:\n";
        std::cout << "➡️  " << invoker.executeCommand(waterRoseCmd) << "\n";
        std::cout << "➡️  " << invoker.executeCommand(waterOakCmd) << "\n";
        
        // Demonstrate selling commands
        std::cout << "\n💰 DEMONSTRATING SELLING COMMANDS:\n";
        std::cout << std::string(40, '-') << "\n";
        
        auto sellRoseCmd = new SellPlantCommand(rose.get(), "Alice Smith", 24.99, "Salesperson Bob");
        auto sellOakCmd = new SellPlantCommand(oak.get(), "Bob Johnson", 85.00, "Salesperson Carol");
        
        std::cout << "Executing sales:\n";
        std::cout << "➡️  " << invoker.executeCommand(sellRoseCmd) << "\n";
        std::cout << "➡️  " << invoker.executeCommand(sellOakCmd) << "\n";
        
        // Demonstrate undo/redo functionality
        std::cout << "\n↩️  DEMONSTRATING UNDO/REDO FUNCTIONALITY:\n";
        std::cout << std::string(40, '-') << "\n";
        
        std::cout << "Undoing last command:\n";
        std::cout << "↩️  " << invoker.undo() << "\n";
        
        std::cout << "Redoing undone command:\n";
        std::cout << "↪️  " << invoker.redo() << "\n";
        
        std::cout << "Undoing two commands:\n";
        std::cout << "↩️  " << invoker.undo() << "\n";
        std::cout << "↩️  " << invoker.undo() << "\n";
        
        // Show command history
        std::cout << "\n📜 COMMAND HISTORY:\n";
        std::cout << std::string(40, '-') << "\n";
        auto history = invoker.getCommandHistory();
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << i + 1 << ". " << history[i] << "\n";
        }
        
        std::cout << "\nCan undo: " << (invoker.canUndo() ? "Yes" : "No") << "\n";
        std::cout << "Can redo: " << (invoker.canRedo() ? "Yes" : "No") << "\n";
        std::cout << "History size: " << invoker.getHistorySize() << "\n";
        std::cout << "Redo stack size: " << invoker.getRedoStackSize() << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error in Command Pattern demonstration: " << e.what() << "\n";
    }
}

/**
 * @brief Demonstrate Template Method Pattern
 */
void demonstrateTemplateMethod() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEMPLATE METHOD PATTERN DEMONSTRATION\n";
    std::cout << std::string(60, '=') << "\n";
    
    try {
        // Create report generator
        ReportGenerator reportGen;
        
        // Create and register reports (using nullptr for dependencies in demo)
        reportGen.registerReport("inventory", std::make_unique<InventoryReport>(nullptr));
        
        // Use current time for sales report
        std::time_t now = std::time(nullptr);
        reportGen.registerReport("sales", std::make_unique<SalesReport>(nullptr, now, now));
        
        // Demonstrate available reports
        std::cout << "📊 AVAILABLE REPORTS:\n";
        std::cout << std::string(40, '-') << "\n";
        auto availableReports = reportGen.getAvailableReports();
        for (const auto& reportType : availableReports) {
            std::cout << "• " << reportType << "\n";
        }
        
        // Generate inventory report
        std::cout << "\n📦 GENERATING INVENTORY REPORT:\n";
        std::cout << std::string(40, '-') << "\n";
        auto inventoryReport = reportGen.generateReport("inventory");
        std::cout << inventoryReport << "\n";
        
        // Generate sales report
        std::cout << "\n💰 GENERATING SALES REPORT:\n";
        std::cout << std::string(40, '-') << "\n";
        auto salesReport = reportGen.generateReport("sales");
        std::cout << salesReport << "\n";
        
        // Demonstrate report export functionality
        std::cout << "\n📤 DEMONSTRATING REPORT EXPORT:\n";
        std::cout << std::string(40, '-') << "\n";
        auto inventoryReportObj = std::make_unique<InventoryReport>(nullptr);
        std::cout << inventoryReportObj->exportReport("pdf") << "\n";
        std::cout << inventoryReportObj->exportReport("html") << "\n";
        std::cout << inventoryReportObj->exportReport("txt") << "\n";
        
        // Demonstrate error handling for unknown report types
        std::cout << "\n🎯 DEMONSTRATING ERROR HANDLING:\n";
        std::cout << std::string(40, '-') << "\n";
        try {
            auto unknownReport = reportGen.generateReport("unknown");
        } catch (const std::exception& e) {
            std::cout << "❌ Expected error: " << e.what() << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error in Template Method demonstration: " << e.what() << "\n";
    }
}

/**
 * @brief Demonstrate integrated system functionality
 */
void demonstrateIntegratedSystem() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "INTEGRATED SYSTEM DEMONSTRATION\n";
    std::cout << std::string(60, '=') << "\n";
    
    try {
        // Create a complete plant ecosystem
        auto flowerFactory = PlantFactoryProvider::getFactory("flower");
        auto treeFactory = PlantFactoryProvider::getFactory("tree");
        
        // Create various plants
        auto rose = std::unique_ptr<Plant>(flowerFactory->createPlant("Rose", "Rosa", 24.99));
        auto tulip = std::unique_ptr<Plant>(flowerFactory->createPlant("Tulip", "Tulipa", 12.99));
        auto oak = std::unique_ptr<Plant>(treeFactory->createPlant("Oak", "Quercus", 89.99));
        auto maple = std::unique_ptr<Plant>(treeFactory->createPlant("Maple", "Acer", 65.99));
        
        // Create care kits
        auto flowerKit = std::unique_ptr<CareKit>(flowerFactory->createCareKit());
        auto treeKit = std::unique_ptr<CareKit>(treeFactory->createCareKit());
        
        // Create command invoker for staff operations
        CommandInvoker staffInvoker;
        
        std::cout << "🏪 GARDEN CENTER DAILY OPERATIONS SIMULATION:\n";
        std::cout << std::string(50, '-') << "\n";
        
        // Morning routine - watering plants
        std::cout << "\n🌅 MORNING ROUTINE - WATERING:\n";
        staffInvoker.executeCommand(new WaterPlantCommand(rose.get(), 200, "Gardener John"));
        staffInvoker.executeCommand(new WaterPlantCommand(tulip.get(), 150, "Gardener John"));
        staffInvoker.executeCommand(new WaterPlantCommand(oak.get(), 500, "Gardener Jane"));
        staffInvoker.executeCommand(new WaterPlantCommand(maple.get(), 450, "Gardener Jane"));
        
        // Mid-day - apply care kits
        std::cout << "\n🌞 MID-DAY - PLANT CARE:\n";
        flowerKit->applyCare(rose.get());
        treeKit->applyCare(oak.get());
        
        // Afternoon - sales
        std::cout << "\n🏪 AFTERNOON - SALES ACTIVITY:\n";
        staffInvoker.executeCommand(new SellPlantCommand(rose.get(), "Customer Alice", 26.49, "Salesperson Bob"));
        staffInvoker.executeCommand(new SellPlantCommand(tulip.get(), "Customer Charlie", 13.64, "Salesperson Bob"));
        
        // Evening - generate reports
        std::cout << "\n🌙 EVENING - REPORT GENERATION:\n";
        ReportGenerator dailyReportGen;
        dailyReportGen.registerReport("inventory", std::make_unique<InventoryReport>(nullptr));
        
        std::time_t now = std::time(nullptr);
        dailyReportGen.registerReport("sales", std::make_unique<SalesReport>(nullptr, now, now));
        
        std::cout << "Daily Sales Report:\n";
        std::cout << dailyReportGen.generateReport("sales") << "\n";
        
        // Show final command history
        std::cout << "📋 FINAL STAFF ACTIVITY LOG:\n";
        std::cout << std::string(40, '-') << "\n";
        auto finalHistory = staffInvoker.getCommandHistory();
        for (size_t i = 0; i < finalHistory.size(); ++i) {
            std::cout << i + 1 << ". " << finalHistory[i] << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error in integrated system demonstration: " << e.what() << "\n";
    }
}

/**
 * @brief Display program header and information
 */
void displayHeader() {
    std::cout << std::string(70, '=') << "\n";
    std::cout << "🌿 GARDEN CENTER MANAGEMENT SYSTEM 🌿\n";
    std::cout << "Design Patterns Demonstration\n";
    std::cout << "Implemented Patterns: Abstract Factory, Command, Template Method\n";
    std::cout << std::string(70, '=') << "\n";
    std::cout << "This program demonstrates three key design patterns:\n";
    std::cout << "• Abstract Factory - Creates families of related plant objects\n";
    std::cout << "• Command Pattern - Encapsulates staff operations with undo/redo\n";
    std::cout << "• Template Method - Defines report generation algorithm skeleton\n";
    std::cout << std::string(70, '=') << "\n";
}

/**
 * @brief Display program footer
 */
void displayFooter() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "🎉 DEMONSTRATION COMPLETED SUCCESSFULLY! 🎉\n";
    std::cout << "Key features demonstrated:\n";
    std::cout << "✓ Abstract Factory with multiple product families\n";
    std::cout << "✓ Command pattern with undo/redo functionality\n";
    std::cout << "✓ Template Method for customizable report generation\n";
    std::cout << "✓ Error handling and input validation\n";
    std::cout << "✓ Professional code structure and documentation\n";
    std::cout << std::string(70, '=') << "\n";
}

/**
 * @brief Main program entry point
 */
int main() {
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    try {
        // Display program header
        displayHeader();
        
        // Demonstrate each pattern
        demonstrateAbstractFactory();
        demonstrateCommandPattern();
        demonstrateTemplateMethod();
        
        // Show integrated system
        demonstrateIntegratedSystem();
        
        // Display completion message
        displayFooter();
        
    } catch (const std::exception& e) {
        std::cerr << "\n💥 CRITICAL ERROR: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}