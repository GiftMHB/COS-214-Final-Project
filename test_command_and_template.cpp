#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Staff.h"
#include "WaterPlantCommand.h"
#include "FertilizePlantCommand.h"
#include "SellPlantCommand.h"
#include "CommandInvoker.h"
#include "Reports.h"
#include "PlantHealthReport.h"
#include "ConcretePlant.h"
#include <vector>
#include <memory>

TEST_SUITE("Command Pattern") {
    TEST_CASE("Staff Class") {
        SUBCASE("Staff creation and basic properties") {
            Staff staff("John Doe", "Senior Gardener");
            
            CHECK(staff.getName() == "John Doe");
            CHECK(staff.getRole() == "Senior Gardener");
            CHECK(staff.getAssignedTasks().empty());
        }
        
        SUBCASE("Task assignment and completion") {
            Staff staff("Jane Smith", "Assistant");
            
            staff.assignTask("Water plants");
            staff.assignTask("Fertilize garden");
            
            auto tasks = staff.getAssignedTasks();
            REQUIRE(tasks.size() == 2);
            CHECK(tasks[0] == "Water plants");
            CHECK(tasks[1] == "Fertilize garden");
            
            staff.completeTask("Water plants");
            tasks = staff.getAssignedTasks();
            REQUIRE(tasks.size() == 1);
            CHECK(tasks[0] == "Fertilize garden");
        }
        
        SUBCASE("Staff information display") {
            Staff staff("Bob Wilson", "Manager");
            staff.assignTask("Manage inventory");
            staff.assignTask("Schedule staff");
            
            std::string info = staff.getStaffInfo();
            CHECK(info.find("Bob Wilson") != std::string::npos);
            CHECK(info.find("Manager") != std::string::npos);
            CHECK(info.find("Manage inventory") != std::string::npos);
            CHECK(info.find("Schedule staff") != std::string::npos);
        }
    }
    
    TEST_CASE("WaterPlantCommand") {
        ConcretePlant plant("Test Plant", "Species", 15.99);
        
        SUBCASE("Command execution increases water level") {
            int initialWater = plant.getWaterLevel();
            WaterPlantCommand command(&plant, 30, "Gardener");
            std::string result = command.execute();
            
            CHECK(plant.getWaterLevel() == initialWater + 30);
            CHECK(result.find("successfully watered") != std::string::npos);
            CHECK(result.find("Gardener") != std::string::npos);
        }
        
        SUBCASE("Command undo restores previous state") {
            int initialWater = plant.getWaterLevel();
            WaterPlantCommand command(&plant, 25, "Test Staff");
            
            command.execute();
            CHECK(plant.getWaterLevel() == initialWater + 25);
            
            std::string undoResult = command.undo();
            CHECK(plant.getWaterLevel() == initialWater);
            CHECK(undoResult.find("UNDO") != std::string::npos);
            CHECK(undoResult.find("Reverted watering") != std::string::npos);
        }
        
        SUBCASE("Command description contains relevant info") {
            WaterPlantCommand command(&plant, 40, "John");
            std::string desc = command.getDescription();
            
            CHECK(desc.find("WaterPlantCommand") != std::string::npos);
            CHECK(desc.find("John") != std::string::npos);
            CHECK(desc.find("40") != std::string::npos);
        }
        
        SUBCASE("Command type identification") {
            WaterPlantCommand command(&plant, 10, "Staff");
            CHECK(command.getCommandType() == "Water");
        }
    }
    
    TEST_CASE("FertilizePlantCommand") {
        ConcretePlant plant("Test Plant", "Species", 12.50);
        
        SUBCASE("Command execution increases nutrient level") {
            int initialNutrients = plant.getNutrientLevel();
            FertilizePlantCommand command(&plant, 20, "Gardener");
            std::string result = command.execute();
            
            CHECK(plant.getNutrientLevel() == initialNutrients + 20);
            CHECK(result.find("successfully fertilized") != std::string::npos);
        }
        
        SUBCASE("Command undo functionality") {
            int initialNutrients = plant.getNutrientLevel();
            FertilizePlantCommand command(&plant, 15, "Staff");
            
            command.execute();
            std::string undoResult = command.undo();
            
            CHECK(plant.getNutrientLevel() == initialNutrients);
            CHECK(undoResult.find("UNDO") != std::string::npos);
            CHECK(undoResult.find("Reverted fertilization") != std::string::npos);
        }
        
        SUBCASE("Command metadata") {
            FertilizePlantCommand command(&plant, 25, "Alice");
            CHECK(command.getCommandType() == "Fertilize");
            
            std::string desc = command.getDescription();
            CHECK(desc.find("FertilizePlantCommand") != std::string::npos);
            CHECK(desc.find("Alice") != std::string::npos);
        }
    }
    
    TEST_CASE("SellPlantCommand") {
        ConcretePlant plant("Rose", "Flower", 25.99);
        
        SUBCASE("Sell command marks plant as not ready for sale") {
            plant.setReadyForSale(true);
            
            
            SellPlantCommand command(&plant, "John Customer", 25.99, "Salesperson");
            std::string result = command.execute();
            
            CHECK(plant.isReadyForSale() == false);
            CHECK(result.find("successfully sold") != std::string::npos);
            CHECK(result.find("John Customer") != std::string::npos);
        }
        
        SUBCASE("Undo sell command restores ready status") {
            plant.setReadyForSale(true);
            bool initialStatus = plant.isReadyForSale();
            
            SellPlantCommand command(&plant, "Customer", 19.99, "Staff");
            command.execute();
            CHECK(plant.isReadyForSale() == false);
            
            command.undo();
            CHECK(plant.isReadyForSale() == initialStatus);
        }
        
        SUBCASE("Sell command description") {
            SellPlantCommand command(&plant, "Jane Doe", 29.99, "Bob");
            std::string desc = command.getDescription();
            
            CHECK(desc.find("SellPlantCommand") != std::string::npos);
            CHECK(desc.find("Bob") != std::string::npos);
            CHECK(desc.find("Jane Doe") != std::string::npos);
            CHECK(desc.find("29.99") != std::string::npos);
        }
    }
    
    TEST_CASE("CommandInvoker Management") {
        ConcretePlant plant("Test Plant", "Species", 10.0);
        CommandInvoker invoker;
        
        SUBCASE("Single command execution") {
            WaterPlantCommand* command = new WaterPlantCommand(&plant, 15, "Staff");
            std::string result = invoker.executeCommand(command);
            
            CHECK(plant.getWaterLevel() == 35); // 20 + 15
            CHECK(invoker.getHistorySize() == 1);
            CHECK_FALSE(result.empty());
        }
        
        SUBCASE("Multiple command execution and history") {
            WaterPlantCommand* cmd1 = new WaterPlantCommand(&plant, 5, "Staff1");
            FertilizePlantCommand* cmd2 = new FertilizePlantCommand(&plant, 10, "Staff2");
            WaterPlantCommand* cmd3 = new WaterPlantCommand(&plant, 8, "Staff3");
            
            invoker.executeCommand(cmd1);
            invoker.executeCommand(cmd2);
            invoker.executeCommand(cmd3);
            
            CHECK(invoker.getHistorySize() == 3);
            CHECK(plant.getWaterLevel() == 33); // 20 + 5 + 8
            CHECK(plant.getNutrientLevel() == 60); // 50 + 10
        }
        
        SUBCASE("Undo/Redo functionality") {
            WaterPlantCommand* cmd1 = new WaterPlantCommand(&plant, 10, "Staff");
            invoker.executeCommand(cmd1);
            int waterAfterFirst = plant.getWaterLevel();
            
            CHECK(invoker.canUndo() == true);
            
            std::string undoResult = invoker.undo();
            CHECK(undoResult.find("UNDO") != std::string::npos);
            CHECK(plant.getWaterLevel() == 20); // Back to initial
            CHECK(invoker.canRedo() == true);
            
            std::string redoResult = invoker.redo();
            CHECK(redoResult.find("successfully watered") != std::string::npos);
            CHECK(plant.getWaterLevel() == waterAfterFirst);
        }
        
        SUBCASE("Command history retrieval") {
            WaterPlantCommand* cmd1 = new WaterPlantCommand(&plant, 5, "Alice");
            FertilizePlantCommand* cmd2 = new FertilizePlantCommand(&plant, 12, "Bob");
            
            invoker.executeCommand(cmd1);
            invoker.executeCommand(cmd2);
            
            auto history = invoker.getCommandHistory();
            REQUIRE(history.size() == 2);
            CHECK(history[0].find("Alice") != std::string::npos);
            CHECK(history[1].find("Bob") != std::string::npos);
            CHECK(history[0].find("WaterPlantCommand") != std::string::npos);
            CHECK(history[1].find("FertilizePlantCommand") != std::string::npos);
        }
        
        SUBCASE("History clearing") {
            WaterPlantCommand* cmd1 = new WaterPlantCommand(&plant, 5, "Staff");
            invoker.executeCommand(cmd1);
            
            CHECK(invoker.getHistorySize() == 1);
            invoker.clearHistory();
            CHECK(invoker.getHistorySize() == 0);
            CHECK(invoker.canUndo() == false);
            CHECK(invoker.canRedo() == false);
        }
        
        SUBCASE("History size limiting") {
            // Add more commands than the default limit (100)
            for (int i = 0; i < 105; i++) {
                WaterPlantCommand* cmd = new WaterPlantCommand(&plant, 1, "Staff");
                invoker.executeCommand(cmd);
            }
            
            // Should not exceed maximum history size
            CHECK(invoker.getHistorySize() <= 100);
        }
    }
}

TEST_SUITE("Template Method Pattern") {
    TEST_CASE("Report Base Class Template") {
        // Concrete implementation for testing
        class TestReport : public Report {
        public:
            void initializeReport() override {
                reportTitle = "Test Report Template";
                generatedDate = "2024-01-01 10:00:00";
            }
            
            void collectData() override {
                reportData["total_items"] = "150";
                reportData["active_items"] = "142";
                reportData["inactive_items"] = "8";
            }
            
            void processData() override {
                Report::processData();
                // Additional processing
                int total = std::stoi(reportData["total_items"]);
                int active = std::stoi(reportData["active_items"]);
                double percentage = (static_cast<double>(active) / total) * 100;
                
                std::stringstream ss;
                ss << std::fixed << std::setprecision(1) << percentage;
                reportData["active_percentage"] = ss.str() + "%";
            }
            
            std::string formatBody() override {
                std::stringstream body;
                body << "Report Body:\n";
                body << "Total Items: " << reportData["total_items"] << "\n";
                body << "Active Items: " << reportData["active_items"] << "\n";
                body << "Active Percentage: " << reportData["active_percentage"] << "\n";
                return body.str();
            }
            
            std::string getReportType() const override {
                return "Test Report";
            }
        };
        
        SUBCASE("Report generation follows template structure") {
            TestReport report;
            std::string result = report.generateReport();
            
            // Check template structure
            CHECK(result.find("=== Test Report Template ===") != std::string::npos);
            CHECK(result.find("Generated: 2024-01-01 10:00:00") != std::string::npos);
            CHECK(result.find("Report Type: Test Report") != std::string::npos);
            CHECK(result.find("Report Body:") != std::string::npos);
            CHECK(result.find("Total Items: 150") != std::string::npos);
            CHECK(result.find("Active Percentage: 94.7%") != std::string::npos);
            CHECK(result.find("End of Test Report Template") != std::string::npos);
        }
        
        SUBCASE("Report type identification") {
            TestReport report;
            CHECK(report.getReportType() == "Test Report");
        }
        
        SUBCASE("Report export functionality") {
            TestReport report;
            
            SUBCASE("PDF export") {
                std::string result = report.exportReport("pdf");
                CHECK(result.find("PDF export completed") != std::string::npos);
            }
            
            SUBCASE("HTML export") {
                std::string result = report.exportReport("html");
                CHECK(result.find("HTML export completed") != std::string::npos);
            }
            
            SUBCASE("Unsupported format") {
                std::string result = report.exportReport("xml");
                CHECK(result.find("Unsupported export format") != std::string::npos);
            }
        }
    }
    
    TEST_CASE("PlantHealthReport Specific Implementation") {
        SUBCASE("Empty plant list report") {
            std::vector<Plant*> emptyList;
            PlantHealthReport report(emptyList);
            
            std::string result = report.generateReport();
            
            CHECK(result.find("Comprehensive Plant Health Status Report") != std::string::npos);
            CHECK(result.find("Total Plants Monitored: 0") != std::string::npos);
            CHECK(result.find("No plants available for health analysis") != std::string::npos);
            CHECK(report.getReportType() == "Plant Health");
        }
        
        SUBCASE("Single plant health report") {
            std::vector<Plant*> plants;
            ConcretePlant* plant = new ConcretePlant("Single Plant", "Test Species", 25.99);
            plant->setHealthLevel(85);
            plants.push_back(plant);
            
            PlantHealthReport report(plants);
            std::string result = report.generateReport();
            
            CHECK(result.find("Total Plants Monitored: 1") != std::string::npos);
            CHECK(result.find("Single Plant") != std::string::npos);
            CHECK(result.find("Healthy Plants (≥70% health): 1") != std::string::npos);
            
            delete plant;
        }
        
        SUBCASE("Mixed health plants report") {
            std::vector<Plant*> plants;
            
            // Healthy plant
            ConcretePlant* healthy = new ConcretePlant("Healthy Rose", "Flower", 30.0);
            healthy->setHealthLevel(95);
            plants.push_back(healthy);
            
            // Unhealthy plant
            ConcretePlant* unhealthy = new ConcretePlant("Struggling Oak", "Tree", 75.0);
            unhealthy->setHealthLevel(45);
            plants.push_back(unhealthy);
            
            // Dead plant
            ConcretePlant* dead = new ConcretePlant("Dead Bush", "Shrub", 15.0);
            dead->setHealthLevel(15);
            plants.push_back(dead);
            
            PlantHealthReport report(plants);
            std::string result = report.generateReport();
            
            // Check health distribution
            CHECK(result.find("Healthy Plants (≥70% health): 1") != std::string::npos);
            CHECK(result.find("Unhealthy Plants (30-69% health): 1") != std::string::npos);
            CHECK(result.find("Dead Plants (<30% health): 1") != std::string::npos);
            CHECK(result.find("Healthy Rose") != std::string::npos);
            CHECK(result.find("Struggling Oak") != std::string::npos);
            CHECK(result.find("Dead Bush") != std::string::npos);
            
            // Check recommendations section
            CHECK(result.find("RECOMMENDED ACTIONS:") != std::string::npos);
            CHECK(result.find("Review care procedures for unhealthy plants") != std::string::npos);
            CHECK(result.find("Isolate dead plants to prevent disease spread") != std::string::npos);
            
            // Cleanup
            for (Plant* plant : plants) delete plant;
        }
        
        SUBCASE("Plant health data processing") {
            std::vector<Plant*> plants;
            plants.push_back(new ConcretePlant("Plant1", "Type1", 10.0));
            plants.push_back(new ConcretePlant("Plant2", "Type2", 20.0));
            plants.push_back(new ConcretePlant("Plant3", "Type3", 30.0));
            
            // Set different health levels
            plants[0]->setHealthLevel(80); // Healthy
            plants[1]->setHealthLevel(50); // Unhealthy  
            plants[2]->setHealthLevel(20); // Dead
            
            PlantHealthReport report(plants);
            report.collectData();
            report.processData();
            
            // The report should calculate percentages and risk assessment
            std::string result = report.generateReport();
            CHECK(result.find("33.3%") != std::string::npos); // Should find percentage for one category
            
            // Cleanup
            for (Plant* plant : plants) delete plant;
        }
    }
    
    TEST_CASE("ReportGenerator Management") {
        SUBCASE("Report registration and management") {
            ReportGenerator generator;
            std::vector<Plant*> plants;
            plants.push_back(new ConcretePlant("Test Plant", "Species", 15.99));
            
            SUBCASE("Register single report") {
                generator.registerReport("health", std::unique_ptr<Report>(new PlantHealthReport(plants)));
                
                CHECK(generator.hasReport("health") == true);
                CHECK(generator.hasReport("nonexistent") == false);
                
                auto available = generator.getAvailableReports();
                CHECK(available.size() == 1);
                CHECK(available[0] == "health");
            }
            
            SUBCASE("Register multiple reports") {
                generator.registerReport("health", std::unique_ptr<Report>(new PlantHealthReport(plants)));
                generator.registerReport("summary", std::unique_ptr<Report>(new PlantHealthReport(plants)));
                
                auto available = generator.getAvailableReports();
                CHECK(available.size() == 2);
                CHECK(std::find(available.begin(), available.end(), "health") != available.end());
                CHECK(std::find(available.begin(), available.end(), "summary") != available.end());
            }
            
            SUBCASE("Generate registered reports") {
                generator.registerReport("plant_health", std::unique_ptr<Report>(new PlantHealthReport(plants)));
                
                std::string result = generator.generateReport("plant_health");
                CHECK(result.find("Plant Health") != std::string::npos);
                CHECK_FALSE(result.empty());
            }
            
            SUBCASE("Generate non-existent report throws exception") {
                CHECK_THROWS_AS(generator.generateReport("invalid_report"), std::invalid_argument);
            }
            
            // Cleanup
            for (Plant* plant : plants) delete plant;
        }
    }
}

TEST_SUITE("Integration: Command + Template Method Patterns") {
    TEST_CASE("Staff operations with reporting") {
        // Create plants
        std::vector<Plant*> plants;
        plants.push_back(new ConcretePlant("Rose", "Flower", 25.99));
        plants.push_back(new ConcretePlant("Oak", "Tree", 99.99));
        plants.push_back(new ConcretePlant("Tomato", "Vegetable", 15.99));
        
        // Staff performs operations using commands
        Staff gardener("John Gardener", "Senior Gardener");
        CommandInvoker invoker;
        
        SUBCASE("Water all plants and generate health report") {
            // Water each plant
            for (Plant* plant : plants) {
                WaterPlantCommand* cmd = new WaterPlantCommand(plant, 20, gardener.getName());
                invoker.executeCommand(cmd);
                gardener.assignTask("Water " + plant->getName());
            }
            
            // Generate health report
            PlantHealthReport healthReport(plants);
            std::string report = healthReport.generateReport();
            
            // Verify results
            for (Plant* plant : plants) {
                CHECK(plant->getWaterLevel() == 40); // 20 initial + 20
            }
            CHECK(report.find("Total Plants Monitored: 3") != std::string::npos);
            CHECK(gardener.getAssignedTasks().size() == 3);
            
            // Test undo of last watering
            if (invoker.canUndo()) {
                invoker.undo();
                CHECK(plants[2]->getWaterLevel() == 20); // Last plant back to initial
            }
        }
        
        SUBCASE("Mixed operations with comprehensive reporting") {
            // Various operations on plants
            WaterPlantCommand* waterRose = new WaterPlantCommand(plants[0], 25, gardener.getName());
            FertilizePlantCommand* fertilizeOak = new FertilizePlantCommand(plants[1], 30, gardener.getName());
            WaterPlantCommand* waterTomato = new WaterPlantCommand(plants[2], 15, gardener.getName());
            
            invoker.executeCommand(waterRose);
            invoker.executeCommand(fertilizeOak);
            invoker.executeCommand(waterTomato);
            
            // Assign tasks
            gardener.assignTask("Water rose");
            gardener.assignTask("Fertilize oak");
            gardener.assignTask("Water tomato");
            
            // Complete some tasks
            gardener.completeTask("Water rose");
            
            // Generate report
            PlantHealthReport report(plants);
            std::string reportOutput = report.generateReport();
            
            // Verify state
            CHECK(plants[0]->getWaterLevel() == 45); // 20 + 25
            CHECK(plants[1]->getNutrientLevel() == 80); // 50 + 30
            CHECK(plants[2]->getWaterLevel() == 35); // 20 + 15
            CHECK(gardener.getAssignedTasks().size() == 2); // One task completed
            CHECK(reportOutput.find("Rose") != std::string::npos);
            CHECK(reportOutput.find("Oak") != std::string::npos);
            CHECK(reportOutput.find("Tomato") != std::string::npos);
            
            // Cleanup commands
            invoker.clearHistory();
        }
        
        // Cleanup plants
        for (Plant* plant : plants) delete plant;
    }
}