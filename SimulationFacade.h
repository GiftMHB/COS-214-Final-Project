/**
 * @file SimulationFacade.h
 * @brief Facade pattern providing simplified interface to the nursery simulation
 */

#ifndef SIMULATION_FACADE_H
#define SIMULATION_FACADE_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>


// Forward declarations
class GardenArea;
class Inventory;
class Plant;
class CommandInvoker;
class ReportGenerator;

/**
 * @class NurseryStaff
 * @brief Simple staff class for the facade
 */
class NurseryStaff {
public:
    std::string name;
    std::string role;
    std::vector<std::string> tasks;
    
    NurseryStaff(const std::string& n, const std::string& r) : name(n), role(r) {}
    
    void assignTask(const std::string& task) {
        tasks.push_back(task);
    }
    
    std::string getInfo() const {
        std::stringstream ss;
        ss << name << " (" << role << ") - Tasks: " << tasks.size();
        return ss.str();
    }
};

/**
 * @class SimulationFacade
 * @brief Main facade class that integrates all subsystems
 */
class SimulationFacade {
private:
    GardenArea* gardenArea;
    Inventory* inventory;
    CommandInvoker* commandInvoker;
    ReportGenerator* reportGenerator;
    
    std::vector<NurseryStaff*> staffMembers;  // Changed to NurseryStaff
    std::map<std::string, Plant*> allPlants;
    
    bool simulationRunning;
    std::string currentSeason;
    int currentDay;
    double nurseryFunds;

public:
    SimulationFacade();
    ~SimulationFacade();

    // Simulation control
    void initializeSystem();
    void startSimulation();
    void stopSimulation();
    void simulateDay();
    void runSimulation(int days);
    
    // Plant management
    void addPlant(const std::string& type, const std::string& name, 
                  const std::string& careLevel = "Medium");
    void removePlant(const std::string& plantId);
    void displayAllPlants();
    void displayPlantStatus(const std::string& plantId);
    
    // Staff operations
    void hireStaff(const std::string& name, const std::string& role);
    void assignTask(const std::string& staffName, const std::string& task);
    void displayStaff();
    
    // Garden management
    void displayGardenLayout();
    void setEnvironment(double temperature, double humidity);
    
    // Inventory operations
    void displayInventory();
    void displayLowStock();
    void restockItem(const std::string& itemId, int quantity);
    
    // Command operations
    void waterPlant(const std::string& plantId, const std::string& staffName);
    void fertilizePlant(const std::string& plantId, const std::string& staffName);
    void sellPlant(const std::string& plantId, const std::string& customerName);
    void undoLastCommand();
    void redoLastCommand();
    
    // Reporting
    void generateInventoryReport();
    void generateSalesReport();
    void generatePlantHealthReport();
    
    // System information
    void displaySystemStatus();
    std::string getCurrentSeason() const;
    int getCurrentDay() const;
    double getNurseryFunds() const;
    bool isRunning() const;
    
    // Interactive menu helpers
    std::vector<std::string> getAvailablePlantTypes() const;
    std::vector<std::string> getAvailableStaffRoles() const;
    std::vector<std::string> getAllPlantIds() const;
    
private:
    void updatePlantStates();
    void processDailyEvents();
    void processSeasonalChanges();
    Plant* createPlant(const std::string& type, const std::string& name, 
                       const std::string& careLevel);
    void initializeDefaultPlants();
    void initializeDefaultStaff();
};

#endif // SIMULATION_FACADE_H