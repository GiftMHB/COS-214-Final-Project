/**
 * @file test_facade.cpp
 * @brief Unit tests for Facade Pattern implementation
 */

#include "doctest.h"
#include "../SimulationFacade.h"
#include "../GardenArea.h"
#include <sstream>
#include <iostream>

// Helper class to capture cout output
class OutputCapture {
    std::stringstream buffer;
    std::streambuf* oldCout;
public:
    OutputCapture() : oldCout(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(oldCout); }
    std::string getOutput() { return buffer.str(); }
    void clear() { buffer.str(""); }
};

TEST_SUITE("Facade Pattern Tests") {
    
    TEST_CASE("Facade Initialization") {
        SimulationFacade facade;
        
        SUBCASE("Initial State") {
            CHECK(facade.isRunning() == false);
            CHECK(facade.getCurrentDay() == 0);
            CHECK(facade.getCurrentSeason() == "Spring");
        }
        
        SUBCASE("Nursery Initialization") {
            // Should not crash during initialization
            CHECK_NOTHROW(facade.initializeNursery());
        }
    }
    
    TEST_CASE("Simulation Lifecycle") {
        SimulationFacade facade;
        facade.initializeNursery();
        
        SUBCASE("Start Simulation") {
            facade.startSimulation();
            CHECK(facade.isRunning() == true);
            
            // Can't start twice
            OutputCapture capture;
            facade.startSimulation();
            std::string output = capture.getOutput();
            CHECK(output.find("already running") != std::string::npos);
        }
        
        SUBCASE("Stop Simulation") {
            facade.startSimulation();
            facade.stopSimulation();
            CHECK(facade.isRunning() == false);
            
            // Can't stop when not running
            OutputCapture capture;
            facade.stopSimulation();
            std::string output = capture.getOutput();
            CHECK(output.find("not running") != std::string::npos);
        }
    }
    
    TEST_CASE("Day Simulation") {
        SimulationFacade facade;
        facade.initializeNursery();
        facade.startSimulation();
        
        SUBCASE("Day Progression") {
            CHECK(facade.getCurrentDay() == 0);
            
            facade.simulateDay();
            CHECK(facade.getCurrentDay() == 1);
            
            facade.simulateDay();
            CHECK(facade.getCurrentDay() == 2);
        }
        
        SUBCASE("Season Changes") {
            // Simulate multiple days to trigger season change
            for (int i = 0; i < 30; i++) {
                facade.simulateDay();
            }
            
            CHECK(facade.getCurrentSeason() == "Summer");
            CHECK(facade.getCurrentDay() == 30);
        }
        
        SUBCASE("Cannot Simulate When Stopped") {
            facade.stopSimulation();
            
            OutputCapture capture;
            facade.simulateDay();
            std::string output = capture.getOutput();
            CHECK(output.find("Start simulation first") != std::string::npos);
        }
    }
    
    TEST_CASE("Plant Management") {
        SimulationFacade facade;
        facade.initializeNursery();
        
        SUBCASE("Add New Plant") {
            // Should not crash when adding plants
            CHECK_NOTHROW(facade.addNewPlant("Rose", "Medium"));
            CHECK_NOTHROW(facade.addNewPlant("Cactus", "Low"));
        }
        
        SUBCASE("Remove Plant") {
            // Test removing nonexistent plant
            CHECK(facade.removePlant("nonexistent") == false);
        }
        
        SUBCASE("Find Plant") {
            Plant* found = facade.findPlant("nonexistent");
            CHECK(found == nullptr);
        }
    }
    
    TEST_CASE("Staff Management") {
        SimulationFacade facade;
        
        SUBCASE("Hire Staff") {
            OutputCapture capture;
            facade.hireStaff("John Doe", "Gardener");
            
            std::string output = capture.getOutput();
            CHECK(output.find("Hired John Doe as Gardener") != std::string::npos);
        }
        
        SUBCASE("Fire Staff") {
            OutputCapture capture;
            facade.fireStaff("S123");
            
            std::string output = capture.getOutput();
            CHECK(output.find("Fired staff member S123") != std::string::npos);
        }
    }
    
    TEST_CASE("Reporting System") {
        SimulationFacade facade;
        facade.initializeNursery();
        
        SUBCASE("Plant Summary") {
            std::string summary = facade.getPlantSummary();
            CHECK(summary.find("Total Plants:") != std::string::npos);
            CHECK(summary.find("Temperature:") != std::string::npos);
            CHECK(summary.find("Humidity:") != std::string::npos);
        }
        
        SUBCASE("Inventory Summary") {
            std::string summary = facade.getInventorySummary();
            CHECK(summary == "Inventory Status: Active");
        }
        
        SUBCASE("Generate Reports") {
            OutputCapture capture;
            facade.generateReports();
            
            std::string output = capture.getOutput();
            CHECK(output.find("Nursery Report") != std::string::npos);
        }
    }
    
    TEST_CASE("System State Management") {
        SimulationFacade facade;
        
        SUBCASE("Save System State") {
            OutputCapture capture;
            facade.saveSystemState("test_save.dat");
            
            std::string output = capture.getOutput();
            CHECK(output.find("Saving system state") != std::string::npos);
        }
        
        SUBCASE("Load System State") {
            OutputCapture capture;
            facade.loadSystemState("test_load.dat");
            
            std::string output = capture.getOutput();
            CHECK(output.find("Loading system state") != std::string::npos);
        }
    }
    
    TEST_CASE("Integration with Composite System") {
        SimulationFacade facade;
        facade.initializeNursery();
        facade.startSimulation();
        
        SUBCASE("Plant Care Integration") {
            // Simulate a day which should trigger plant care
            OutputCapture capture;
            facade.simulateDay();
            
            std::string output = capture.getOutput();
            bool hasStaffCared = output.find("Staff cared for") != std::string::npos;
            bool hasReadyForSale = output.find("plants ready for sale") != std::string::npos;
            bool hasObserversNotified = output.find("Observers notified") != std::string::npos;
            
            CHECK(hasStaffCared);
            CHECK(hasReadyForSale);
            CHECK(hasObserversNotified);
        }
        
        SUBCASE("Multiple Day Integration") {
            for (int i = 0; i < 5; i++) {
                facade.simulateDay();
            }
            
            CHECK(facade.getCurrentDay() == 5);
            CHECK(facade.isRunning() == true);
        }
    }
}