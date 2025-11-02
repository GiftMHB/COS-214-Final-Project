#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Plant.h"
#include "ConcretePlant.h"
#include "PlantFactory.h"
#include "Staff.h"
#include "CommandInvoker.h"
#include "WaterPlantCommand.h"
#include "FertilizePlantCommand.h"
#include "SellPlantCommand.h"
#include "Reports.h"
#include "PlantHealthReport.h"
#include <memory>
#include <vector>

// ============================================================================
// TEST CASES FOR PLANT CLASS
// ============================================================================

TEST_CASE("Plant Creation and Basic Properties") {
    SUBCASE("Create plant with basic constructor") {
        ConcretePlant plant("Rose", "Flower", 25.99);
        
        CHECK(plant.getName() == "Rose");
        CHECK(plant.getSpecies() == "Flower");
        CHECK(plant.getPrice() == 25.99);
        CHECK(plant.getHealthPercentage() == 100);
        CHECK(plant.getIsAlive() == true);
        CHECK(plant.getWaterLevel() == 20);
    }
    
    SUBCASE("Create plant with species constructor") {
        ConcretePlant plant("Oak", "Tree");
        
        CHECK(plant.getName() == "Oak");
        CHECK(plant.getSpecies() == "Tree");
        CHECK(plant.getIsAlive() == true);
    }
}

TEST_CASE("Plant Watering Functionality") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    int initialWater = plant.getWaterLevel();
    
    SUBCASE("Water plant increases water level") {
        plant.water(30);
        CHECK(plant.getWaterLevel() == initialWater + 30);
    }
    
    SUBCASE("Water level caps at 100") {
        plant.water(100);
        CHECK(plant.getWaterLevel() == 100);
    }
    
    SUBCASE("Watering dead plant has no effect") {
        plant.setHealthLevel(0); // Kill the plant
        plant.water(50);
        CHECK(plant.getIsAlive() == false);
    }
}

TEST_CASE("Plant Health Management") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    
    SUBCASE("Set health level within bounds") {
        plant.setHealthLevel(75);
        CHECK(plant.getHealthPercentage() == 75);
        CHECK(plant.getHealth() == 75.0);
    }
    
    SUBCASE("Health level caps at 100") {
        plant.setHealthLevel(150);
        CHECK(plant.getHealthPercentage() == 100);
    }
    
    SUBCASE("Health level minimum is 0") {
        plant.setHealthLevel(-50);
        CHECK(plant.getHealthPercentage() == 0);
        CHECK(plant.getIsAlive() == false);
    }
}

// ============================================================================
// TEST CASES FOR ABSTRACT FACTORY PATTERN
// ============================================================================

TEST_CASE("Plant Factory Creation") {
    SUBCASE("Create flower factory") {
        auto factory = PlantFactoryProvider::createFactory("flower");
        CHECK(factory->getFactoryType() == "Flower");
        CHECK_FALSE(factory->getDescription().empty());
    }
    
    SUBCASE("Create tree factory") {
        auto factory = PlantFactoryProvider::createFactory("tree");
        CHECK(factory->getFactoryType() == "Tree");
    }
    
    SUBCASE("Create vegetable factory") {
        auto factory = PlantFactoryProvider::createFactory("vegetable");
        CHECK(factory->getFactoryType() == "Vegetable");
    }
    
    SUBCASE("Invalid factory type throws exception") {
        CHECK_THROWS_AS(PlantFactoryProvider::createFactory("invalid"), std::invalid_argument);
    }
}

TEST_CASE("Plant Factory Product Creation") {
    SUBCASE("Flower factory creates plants") {
        auto factory = PlantFactoryProvider::createFactory("flower");
        Plant* rose = factory->createPlant("Rose", "Rosa", 25.99);
        
        CHECK(rose != nullptr);
        CHECK(rose->getName() == "Rose");
        CHECK(rose->getSpecies() == "Rosa");
        CHECK(rose->getPrice() == 25.99);
        
        delete rose;
    }
    
    SUBCASE("Tree factory creates plants") {
        auto factory = PlantFactoryProvider::createFactory("tree");
        Plant* oak = factory->createPlant("Oak", "Quercus", 99.99);
        
        CHECK(oak != nullptr);
        CHECK(oak->getName() == "Oak");
        
        delete oak;
    }
}

TEST_CASE("Factory Provider Utilities") {
    SUBCASE("Get supported factories") {
        auto supported = PlantFactoryProvider::getSupportedFactories();
        CHECK(supported.size() == 3);
        CHECK(std::find(supported.begin(), supported.end(), "flower") != supported.end());
        CHECK(std::find(supported.begin(), supported.end(), "tree") != supported.end());
        CHECK(std::find(supported.begin(), supported.end(), "vegetable") != supported.end());
    }
    
    SUBCASE("Check factory support") {
        CHECK(PlantFactoryProvider::isFactorySupported("flower") == true);
        CHECK(PlantFactoryProvider::isFactorySupported("tree") == true);
        CHECK(PlantFactoryProvider::isFactorySupported("vegetable") == true);
        CHECK(PlantFactoryProvider::isFactorySupported("invalid") == false);
    }
}

// ============================================================================
// TEST CASES FOR COMMAND PATTERN
// ============================================================================

TEST_CASE("Staff Management") {
    SUBCASE("Create staff member") {
        Staff gardener("John Doe", "Senior Gardener");
        
        CHECK(gardener.getName() == "John Doe");
        CHECK(gardener.getRole() == "Senior Gardener");
        CHECK(gardener.getAssignedTasks().empty());
    }
    
    SUBCASE("Assign and complete tasks") {
        Staff staff("Jane Smith", "Assistant");
        staff.assignTask("Water plants");
        staff.assignTask("Fertilize garden");
        
        auto tasks = staff.getAssignedTasks();
        CHECK(tasks.size() == 2);
        CHECK(std::find(tasks.begin(), tasks.end(), "Water plants") != tasks.end());
        
        staff.completeTask("Water plants");
        tasks = staff.getAssignedTasks();
        CHECK(tasks.size() == 1);
        CHECK(std::find(tasks.begin(), tasks.end(), "Water plants") == tasks.end());
    }
}

TEST_CASE("Water Plant Command") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    int initialWater = plant.getWaterLevel();
    
    SUBCASE("Execute water command") {
        WaterPlantCommand command(&plant, 30, "Test Staff");
        std::string result = command.execute();
        
        CHECK(plant.getWaterLevel() == initialWater + 30);
        CHECK(result.find("successfully watered") != std::string::npos);
    }
    
    SUBCASE("Undo water command") {
        WaterPlantCommand command(&plant, 30, "Test Staff");
        command.execute();
        std::string undoResult = command.undo();
        
        CHECK(plant.getWaterLevel() == initialWater);
        CHECK(undoResult.find("UNDO") != std::string::npos);
    }
    
    SUBCASE("Command description") {
        WaterPlantCommand command(&plant, 30, "Test Staff");
        std::string desc = command.getDescription();
        
        CHECK(desc.find("WaterPlantCommand") != std::string::npos);
        CHECK(desc.find("Test Staff") != std::string::npos);
    }
}

TEST_CASE("Fertilize Plant Command") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    int initialNutrients = plant.getNutrientLevel();
    
    SUBCASE("Execute fertilize command") {
        FertilizePlantCommand command(&plant, 20, "Test Staff");
        std::string result = command.execute();
        
        CHECK(plant.getNutrientLevel() == initialNutrients + 20);
        CHECK(result.find("successfully fertilized") != std::string::npos);
    }
    
    SUBCASE("Undo fertilize command") {
        FertilizePlantCommand command(&plant, 20, "Test Staff");
        command.execute();
        std::string undoResult = command.undo();
        
        CHECK(plant.getNutrientLevel() == initialNutrients);
        CHECK(undoResult.find("UNDO") != std::string::npos);
    }
}

TEST_CASE("Sell Plant Command") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    bool initialReadyStatus = plant.isReadyForSale();
    
    SUBCASE("Execute sell command") {
        SellPlantCommand command(&plant, "Test Customer", 25.99, "Test Staff");
        std::string result = command.execute();
        
        CHECK(plant.isReadyForSale() == false);
        CHECK(result.find("successfully sold") != std::string::npos);
    }
    
    SUBCASE("Undo sell command") {
        plant.setReadyForSale(true);
        SellPlantCommand command(&plant, "Test Customer", 25.99, "Test Staff");
        command.execute();
        std::string undoResult = command.undo();
        
        CHECK(plant.isReadyForSale() == true);
        CHECK(undoResult.find("UNDO") != std::string::npos);
    }
}

TEST_CASE("Command Invoker") {
    ConcretePlant plant("Test Plant", "Test Species", 15.99);
    CommandInvoker invoker;
    
    SUBCASE("Execute command through invoker") {
        WaterPlantCommand* command = new WaterPlantCommand(&plant, 30, "Test Staff");
        std::string result = invoker.executeCommand(command);
        
        CHECK(plant.getWaterLevel() == 50); // 20 initial + 30
        CHECK(result.find("successfully watered") != std::string::npos);
        CHECK(invoker.getHistorySize() == 1);
    }
    
    SUBCASE("Undo/Redo functionality") {
        WaterPlantCommand* command1 = new WaterPlantCommand(&plant, 10, "Staff1");
        invoker.executeCommand(command1);
        
        CHECK(invoker.canUndo() == true);
        
        std::string undoResult = invoker.undo();
        CHECK(undoResult.find("UNDO") != std::string::npos);
        CHECK(invoker.canRedo() == true);
        
        std::string redoResult = invoker.redo();
        CHECK(redoResult.find("successfully watered") != std::string::npos);
    }
    
    SUBCASE("Command history management") {
        WaterPlantCommand* cmd1 = new WaterPlantCommand(&plant, 10, "Staff1");
        WaterPlantCommand* cmd2 = new WaterPlantCommand(&plant, 20, "Staff2");
        
        invoker.executeCommand(cmd1);
        invoker.executeCommand(cmd2);
        
        CHECK(invoker.getHistorySize() == 2);
        
        auto history = invoker.getCommandHistory();
        CHECK(history.size() == 2);
        CHECK(history[0].find("Staff1") != std::string::npos);
        CHECK(history[1].find("Staff2") != std::string::npos);
        
        invoker.clearHistory();
        CHECK(invoker.getHistorySize() == 0);
    }
}

// ============================================================================
// TEST CASES FOR TEMPLATE METHOD PATTERN
// ============================================================================

TEST_CASE("Report Base Class") {
    SUBCASE("Report interface") {
        // Test with a simple concrete report implementation
        class TestReport : public Report {
        public:
            void initializeReport() override {
                reportTitle = "Test Report";
                generatedDate = "2024-01-01";
            }
            
            void collectData() override {
                reportData["TestKey"] = "TestValue";
            }
            
            std::string formatBody() override {
                return "Test Body Content";
            }
            
            std::string getReportType() const override {
                return "Test";
            }
        };
        
        TestReport report;
        std::string result = report.generateReport();
        
        CHECK(result.find("Test Report") != std::string::npos);
        CHECK(result.find("Test Body Content") != std::string::npos);
        CHECK(report.getReportType() == "Test");
    }
}

TEST_CASE("Plant Health Report") {
    SUBCASE("Create plant health report with empty list") {
        std::vector<Plant*> emptyList;
        PlantHealthReport report(emptyList);
        
        std::string result = report.generateReport();
        CHECK(result.find("Plant Health") != std::string::npos);
        CHECK(result.find("Total Plants Monitored: 0") != std::string::npos);
    }
    
    SUBCASE("Create plant health report with plants") {
        std::vector<Plant*> plants;
        plants.push_back(new ConcretePlant("Rose", "Flower", 25.99));
        plants.push_back(new ConcretePlant("Oak", "Tree", 99.99));
        
        PlantHealthReport report(plants);
        std::string result = report.generateReport();
        
        CHECK(result.find("Total Plants Monitored: 2") != std::string::npos);
        CHECK(result.find("Rose") != std::string::npos);
        CHECK(result.find("Oak") != std::string::npos);
        CHECK(report.getReportType() == "Plant Health");
        
        // Clean up
        for (Plant* plant : plants) {
            delete plant;
        }
    }
}

TEST_CASE("Report Generator") {
    SUBCASE("Register and generate reports") {
        ReportGenerator generator;
        std::vector<Plant*> plants;
        plants.push_back(new ConcretePlant("Test Plant", "Test Species", 15.99));
        
        auto healthReport = std::unique_ptr<Report>(new PlantHealthReport(plants));
        generator.registerReport("health", std::move(healthReport));
        
        CHECK(generator.hasReport("health") == true);
        CHECK(generator.hasReport("nonexistent") == false);
        
        auto available = generator.getAvailableReports();
        CHECK(available.size() == 1);
        CHECK(available[0] == "health");
        
        std::string result = generator.generateReport("health");
        CHECK(result.find("Plant Health") != std::string::npos);
        
        // Clean up
        for (Plant* plant : plants) {
            delete plant;
        }
    }
    
    SUBCASE("Generate non-existent report throws exception") {
        ReportGenerator generator;
        CHECK_THROWS_AS(generator.generateReport("nonexistent"), std::invalid_argument);
    }
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST_CASE("Integration: Factory + Command Pattern") {
    SUBCASE("Create plant with factory and manipulate with commands") {
        auto factory = PlantFactoryProvider::createFactory("flower");
        Plant* plant = factory->createPlant("Rose", "Rosa", 25.99);
        
        CommandInvoker invoker;
        WaterPlantCommand* waterCmd = new WaterPlantCommand(plant, 30, "Test Staff");
        FertilizePlantCommand* fertilizeCmd = new FertilizePlantCommand(plant, 20, "Test Staff");
        
        invoker.executeCommand(waterCmd);
        invoker.executeCommand(fertilizeCmd);
        
        CHECK(plant->getWaterLevel() > 20); // Should be increased
        CHECK(plant->getNutrientLevel() > 50); // Should be increased
        
        // Clean up
        invoker.clearHistory();
        delete plant;
    }
}

TEST_CASE("Integration: All Three Patterns") {
    SUBCASE("Complete workflow") {
        // 1. Abstract Factory: Create plants
        auto flowerFactory = PlantFactoryProvider::createFactory("flower");
        auto treeFactory = PlantFactoryProvider::createFactory("tree");
        
        Plant* rose = flowerFactory->createPlant("Rose", "Rosa", 25.99);
        Plant* oak = treeFactory->createPlant("Oak", "Quercus", 99.99);
        
        // 2. Command Pattern: Staff operations
        Staff gardener("John", "Gardener");
        CommandInvoker invoker;
        
        gardener.assignTask("Water rose plant");
        WaterPlantCommand* waterRose = new WaterPlantCommand(rose, 25, gardener.getName());
        invoker.executeCommand(waterRose);
        
        gardener.assignTask("Fertilize oak tree");
        FertilizePlantCommand* fertilizeOak = new FertilizePlantCommand(oak, 15, gardener.getName());
        invoker.executeCommand(fertilizeOak);
        
        gardener.completeTask("Water rose plant");
        
        // 3. Template Method: Generate reports
        std::vector<Plant*> plants = {rose, oak};
        PlantHealthReport healthReport(plants);
        std::string report = healthReport.generateReport();
        
        // Verify results
        CHECK(rose->getWaterLevel() == 45); // 20 initial + 25
        CHECK(oak->getNutrientLevel() == 65); // 50 initial + 15
        CHECK(report.find("Rose") != std::string::npos);
        CHECK(report.find("Oak") != std::string::npos);
        CHECK(gardener.getAssignedTasks().size() == 1); // One task completed, one remaining
        
        // Clean up
        invoker.clearHistory();
        delete rose;
        delete oak;
    }
}