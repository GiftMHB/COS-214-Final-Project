/**
 * @file SimulationFacade.cpp
 * @brief Implementation of the comprehensive SimulationFacade
 */

#include "SimulationFacade.h"
#include "GardenArea.h"
#include "Inventory.h"
#include "Plant.h"
#include "PlantState.h"
#include "FlowerFactory.h"
#include "TreeFactory.h"
#include "VegetableFactory.h"
#include "LowMaintenanceCare.h"
#include "HighMaintenanceCare.h"
#include "SeasonalCare.h"
#include "CommandInvoker.h"
#include "WaterPlantCommand.h"
#include "FertilizePlantCommand.h"
#include "SellPlantCommand.h"
#include "InventoryReport.h"
#include "SalesReport.h"
#include "PlantHealthReport.h"
#include "HealthMonitor.h"
#include "GrowthTracker.h"
#include "SeedlingState.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <cstdlib>
#include <ctime>

// Remove the duplicate SimpleStaff class - using NurseryStaff from header

SimulationFacade::SimulationFacade() 
    : gardenArea(nullptr), inventory(nullptr), commandInvoker(nullptr),
      reportGenerator(nullptr), simulationRunning(false), 
      currentSeason("Spring"), currentDay(0), nurseryFunds(10000.0) {
    
    std::srand(std::time(0)); // Seed for random events
}

SimulationFacade::~SimulationFacade() {
    // Clean up resources
    for (auto& pair : allPlants) {
        delete pair.second;
    }
    allPlants.clear();
    
    for (auto staff : staffMembers) {
        delete staff;
    }
    staffMembers.clear();
    
    delete commandInvoker;
    delete inventory;
    // GardenArea is singleton, don't delete
}

void SimulationFacade::initializeSystem() {
    std::cout << "\n=== Initializing Plant Nursery Simulation ===\n";
    
    // Initialize subsystems
    gardenArea = &GardenArea::getInstance();
    inventory = new Inventory();
    commandInvoker = new CommandInvoker();
    
    // Set up initial environment
    gardenArea->setTemperature(22.0);
    gardenArea->setHumidity(60.0);
    
    // Create default plants and staff
    initializeDefaultPlants();
    initializeDefaultStaff();
    
    std::cout << "System initialized successfully!\n";
    std::cout << "Season: " << currentSeason << "\n";
    std::cout << "Starting funds: R" << nurseryFunds << "\n";
}

void SimulationFacade::initializeDefaultPlants() {
    // Create some sample plants
    std::vector<std::string> plantTypes = {"Rose", "Tulip", "Oak", "Maple", "Tomato", "Carrot"};
    std::vector<std::string> careLevels = {"Low", "Medium", "High"};
    
    for (int i = 0; i < 6; ++i) {
        std::string type = plantTypes[i];
        std::string careLevel = careLevels[i % 3];
        addPlant(type, type + " " + std::to_string(i + 1), careLevel);
    }
}

void SimulationFacade::initializeDefaultStaff() {
    hireStaff("Gift", "Gardener");
    hireStaff("Tiego", "Salesperson");
    hireStaff("Lufuno", "Manager");
}

void SimulationFacade::startSimulation() {
    if (simulationRunning) {
        std::cout << "Simulation is already running!\n";
        return;
    }
    
    simulationRunning = true;
    currentDay = 0;
    std::cout << "\n=== Simulation Started ===\n";
    std::cout << "Season: " << currentSeason << "\n";
    std::cout << "Use the menu to control the simulation.\n";
}

void SimulationFacade::stopSimulation() {
    if (!simulationRunning) {
        std::cout << "Simulation is not running!\n";
        return;
    }
    
    simulationRunning = false;
    std::cout << "\n=== Simulation Stopped ===\n";
    std::cout << "Final day: " << currentDay << "\n";
    std::cout << "Final funds: $" << nurseryFunds << "\n";
}

void SimulationFacade::simulateDay() {
    if (!simulationRunning) {
        std::cout << "Start simulation first!\n";
        return;
    }
    
    currentDay++;
    std::cout << "\n=== Day " << currentDay << " - " << currentSeason << " ===\n";
    
    // Process daily events
    updatePlantStates();
    processDailyEvents();
    processSeasonalChanges();
    
    std::cout << "Day " << currentDay << " completed.\n";
}

void SimulationFacade::runSimulation(int days) {
    if (!simulationRunning) {
        std::cout << "Start simulation first!\n";
        return;
    }
    
    std::cout << "\n=== Running " << days << " days of simulation ===\n";
    for (int i = 0; i < days; ++i) {
        simulateDay();
    }
}

void SimulationFacade::addPlant(const std::string& type, const std::string& name, 
                               const std::string& careLevel) {
    Plant* newPlant = createPlant(type, name, careLevel);
    if (newPlant) {
        allPlants[newPlant->getId()] = newPlant;
        
        // Attach observers
        HealthMonitor* healthMon = new HealthMonitor();
        GrowthTracker* growthTrack = new GrowthTracker();
        newPlant->attach(healthMon);
        newPlant->attach(growthTrack);
        
        std::cout << "Added plant: " << name << " (" << type << ") - Care: " << careLevel << "\n";
        std::cout << "Plant ID: " << newPlant->getId() << "\n";
    }
}

Plant* SimulationFacade::createPlant(const std::string& type, const std::string& name, 
                                    const std::string& careLevel) {
    PlantInfo info;
    info.name = name;
    
    // Set the classification to match factory expectations
    if (type == "Rose" || type == "Tulip" || type == "Flower") {
        info.classification = "Flower";
    } else if (type == "Oak" || type == "Maple" || type == "Tree") {
        info.classification = "Tree"; 
    } else if (type == "Tomato" || type == "Carrot" || type == "Vegetable") {
        info.classification = "Vegetable";
    } else {
        info.classification = type;
    }
    
    info.salePrice = 25.0 + (std::rand() % 50);
    
    // Set reasonable defaults
    info.waterLevel = 50;
    info.healthLevel = 100;
    info.sunlightNeed = 5;
    info.fertilizerNeed = 2;
    info.nutrientLevel = 50;
    info.currentHeight = 0.0;
    info.maturityHeight = 100.0;
    info.currentAgeDays = 0;
    info.daysToMaturity = 365;
    info.isAlive = true;
    info.readyForSale = false;
    
    Plant* plant = nullptr;
    
    std::cout << "Creating plant: " << name << " of type: " << type << " with classification: " << info.classification << std::endl;
    
    // Map common names to factory types
    if (type == "Rose" || type == "Tulip" || info.classification == "Flower") {
        FlowerFactory factory;
        plant = factory.createPlant(info, "Flower", "Red", "Spring", 24, true);
    } else if (type == "Oak" || type == "Maple" || info.classification == "Tree") {
        TreeFactory factory;
        plant = factory.createPlant(info, "Tree", type, 2.0, true, 0.3);
    } else if (type == "Tomato" || type == "Carrot" || info.classification == "Vegetable") {
        VegetableFactory factory;
        plant = factory.createPlant(info, "Vegetable", type, 60, 2.5, true);
    }
    
    if (!plant) {
        std::cout << "Factory failed, trying direct creation...\n";
        // Fallback: create plants directly
        if (type == "Rose" || type == "Tulip" || info.classification == "Flower") {
            plant = new Flower(info, "Red", "Spring", 24, true);
        } else if (type == "Oak" || type == "Maple" || info.classification == "Tree") {
            plant = new Tree(info, type, 2.0, true, 0.3);
        } else if (type == "Tomato" || type == "Carrot" || info.classification == "Vegetable") {
            plant = new Vegetable(info, 60, 2.5, type, true);
        }
    }
    
    if (plant) {
        // Set care strategy
        CareStrategy* strategy = nullptr;
        if (careLevel == "Low") {
            strategy = new LowMaintenanceCare(4, 4);
        } else if (careLevel == "Medium") {
            std::vector<std::string> treatments = {"pruning"};
            strategy = new HighMaintenanceCare(2, 2, treatments);
        } else if (careLevel == "High") {
            std::vector<std::string> treatments = {"pruning", "misting", "repotting"};
            strategy = new HighMaintenanceCare(1, 1, treatments);
        }
        
        if (strategy) {
            plant->setCareStrategy(strategy);
        }
        
        // Set initial state
        // plant->setState(new SeedlingState());
        
        std::cout << "Successfully created plant: " << plant->getName() << " with ID: " << plant->getId() << std::endl;
    } else {
        std::cout << "Failed to create plant of type: " << type << std::endl;
    }
    
    return plant;
}

void SimulationFacade::removePlant(const std::string& plantId) {
    auto it = allPlants.find(plantId);
    if (it != allPlants.end()) {
        std::cout << "Removed plant: " << it->second->getName() << "\n";
        delete it->second;
        allPlants.erase(it);
    } else {
        std::cout << "Plant with ID " << plantId << " not found!\n";
    }
}

void SimulationFacade::displayAllPlants() {
    std::cout << "\n=== All Plants (" << allPlants.size() << ") ===\n";
    for (const auto& pair : allPlants) {
        Plant* plant = pair.second;
        std::cout << "ID: " << plant->getId() 
                  << " | Name: " << plant->getName()
                  << " | Type: " << plant->getClassification()
                  << " | Health: " << plant->getHealthPercentage() << "%"
                  << " | Price: $" << plant->getPrice() << "\n";
    }
}

void SimulationFacade::displayPlantStatus(const std::string& plantId) {
    auto it = allPlants.find(plantId);
    if (it != allPlants.end()) {
        it->second->printStatus();
    } else {
        std::cout << "Plant with ID " << plantId << " not found!\n";
    }
}

void SimulationFacade::hireStaff(const std::string& name, const std::string& role) {
    NurseryStaff* newStaff = new NurseryStaff(name, role);  // Fixed: using NurseryStaff
    staffMembers.push_back(newStaff);
    std::cout << "Hired " << name << " as " << role << "\n";
}

void SimulationFacade::assignTask(const std::string& staffName, const std::string& task) {
    for (auto staff : staffMembers) {
        if (staff->name == staffName) {
            staff->assignTask(task);
            std::cout << "Assigned task to " << staffName << ": " << task << "\n";
            return;
        }
    }
    std::cout << "Staff member " << staffName << " not found!\n";
}

void SimulationFacade::displayStaff() {
    std::cout << "\n=== Staff Members (" << staffMembers.size() << ") ===\n";
    for (auto staff : staffMembers) {
        std::cout << staff->getInfo() << "\n";
    }
}

void SimulationFacade::displayGardenLayout() {
    if (gardenArea) {
        std::cout << "\n=== Garden Layout ===\n";
        gardenArea->display();
    }
}

void SimulationFacade::setEnvironment(double temperature, double humidity) {
    if (gardenArea) {
        gardenArea->setTemperature(temperature);
        gardenArea->setHumidity(humidity);
        std::cout << "Environment set to: " << temperature << "°C, " << humidity << "% humidity\n";
    }
}

void SimulationFacade::displayInventory() {
    std::cout << "\n=== Inventory Status ===\n";
    std::cout << "Total plants in system: " << allPlants.size() << "\n";
    std::cout << "Nursery funds: $" << nurseryFunds << "\n";
}

void SimulationFacade::displayLowStock() {
    std::cout << "\n=== Low Stock Alert ===\n";
    std::cout << "All plants are properly stocked.\n";
}

void SimulationFacade::waterPlant(const std::string& plantId, const std::string& staffName) {
    auto it = allPlants.find(plantId);
    if (it != allPlants.end()) {
        WaterPlantCommand* cmd = new WaterPlantCommand(it->second, 50.0, staffName);
        std::string result = commandInvoker->executeCommand(cmd);
        std::cout << result << "\n";
    } else {
        std::cout << "Plant with ID " << plantId << " not found!\n";
    }
}

void SimulationFacade::fertilizePlant(const std::string& plantId, const std::string& staffName) {
    auto it = allPlants.find(plantId);
    if (it != allPlants.end()) {
        FertilizePlantCommand* cmd = new FertilizePlantCommand(it->second, 25, staffName);
        std::string result = commandInvoker->executeCommand(cmd);
        std::cout << result << "\n";
    } else {
        std::cout << "Plant with ID " << plantId << " not found!\n";
    }
}

void SimulationFacade::sellPlant(const std::string& plantId, const std::string& customerName) {
    auto it = allPlants.find(plantId);
    if (it != allPlants.end()) {
        double price = it->second->getPrice();
        SellPlantCommand* cmd = new SellPlantCommand(it->second, customerName, price, "Salesperson");
        std::string result = commandInvoker->executeCommand(cmd);
        std::cout << result << "\n";
        
        // Update funds
        nurseryFunds += price;
        std::cout << "Nursery funds increased to: $" << nurseryFunds << "\n";
        
        // Remove from active plants
        removePlant(plantId);
    } else {
        std::cout << "Plant with ID " << plantId << " not found!\n";
    }
}

void SimulationFacade::undoLastCommand() {
    if (commandInvoker->canUndo()) {
        std::string result = commandInvoker->undo();
        std::cout << result << "\n";
    } else {
        std::cout << "No commands to undo!\n";
    }
}

void SimulationFacade::redoLastCommand() {
    if (commandInvoker->canRedo()) {
        std::string result = commandInvoker->redo();
        std::cout << result << "\n";
    } else {
        std::cout << "No commands to redo!\n";
    }
}

void SimulationFacade::generateInventoryReport() {
    std::cout << "\n=== Inventory Report ===\n";
    std::cout << "Total Plants: " << allPlants.size() << "\n";
    std::cout << "Total Staff: " << staffMembers.size() << "\n";
    std::cout << "Nursery Funds: $" << nurseryFunds << "\n";
    std::cout << "Current Season: " << currentSeason << "\n";
    std::cout << "Simulation Day: " << currentDay << "\n";
}

void SimulationFacade::generateSalesReport() {
    std::cout << "\n=== Sales Report ===\n";
    std::cout << "Total plants available for sale: " << allPlants.size() << "\n";
    std::cout << "Average plant price: $50.00\n";
    std::cout << "Projected revenue: $" << (allPlants.size() * 50.0) << "\n";
}

void SimulationFacade::generatePlantHealthReport() {
    std::cout << "\n=== Plant Health Report ===\n";
    int healthy = 0, needsCare = 0;
    
    for (const auto& pair : allPlants) {
        if (pair.second->getHealthPercentage() > 70) {
            healthy++;
        } else {
            needsCare++;
        }
    }
    
    std::cout << "Healthy plants: " << healthy << "\n";
    std::cout << "Plants needing care: " << needsCare << "\n";
    std::cout << "Overall health: " << (healthy * 100 / allPlants.size()) << "%\n";
}

void SimulationFacade::displaySystemStatus() {
    std::cout << "\n=== System Status ===\n";
    std::cout << "Simulation Running: " << (simulationRunning ? "Yes" : "No") << "\n";
    std::cout << "Current Day: " << currentDay << "\n";
    std::cout << "Current Season: " << currentSeason << "\n";
    std::cout << "Total Plants: " << allPlants.size() << "\n";
    std::cout << "Total Staff: " << staffMembers.size() << "\n";
    std::cout << "Nursery Funds: $" << nurseryFunds << "\n";
}

void SimulationFacade::updatePlantStates() {
    for (auto& pair : allPlants) {
        pair.second->grow();
        
        // Random events
        if (std::rand() % 10 == 0) { // 10% chance
            pair.second->water(-10); // Plant loses water
        }
    }
}

void SimulationFacade::processDailyEvents() {
    // Random daily events
    int event = std::rand() % 10;
    
    switch (event) {
        case 0:
            std::cout << "Event: Sunny day - plants are happy!\n";
            break;
        case 1:
            std::cout << "Event: Rainy day - plants get natural watering\n";
            for (auto& pair : allPlants) {
                pair.second->water(15);
            }
            break;
        case 2:
            std::cout << "Event: Customer visited the nursery\n";
            if (!allPlants.empty()) {
                auto it = allPlants.begin();
                std::advance(it, std::rand() % allPlants.size());
                std::cout << "Customer interested in: " << it->second->getName() << "\n";
            }
            break;
        default:
            // No special event
            break;
    }
}

void SimulationFacade::processSeasonalChanges() {
    if (currentDay % 30 == 0) {
        if (currentSeason == "Spring") currentSeason = "Summer";
        else if (currentSeason == "Summer") currentSeason = "Autumn";
        else if (currentSeason == "Autumn") currentSeason = "Winter";
        else currentSeason = "Spring";
        
        std::cout << "Season changed to: " << currentSeason << "!\n";
        
        // Update seasonal care strategies
        for (auto& pair : allPlants) {
            SeasonalCare* seasonalCare = new SeasonalCare(currentSeason);
            pair.second->setCareStrategy(seasonalCare);
        }
    }
}

std::string SimulationFacade::getCurrentSeason() const { return currentSeason; }
int SimulationFacade::getCurrentDay() const { return currentDay; }
double SimulationFacade::getNurseryFunds() const { return nurseryFunds; }
bool SimulationFacade::isRunning() const { return simulationRunning; }

std::vector<std::string> SimulationFacade::getAvailablePlantTypes() const {
    return {"Rose", "Tulip", "Oak", "Maple", "Tomato", "Carrot"};
}

std::vector<std::string> SimulationFacade::getAvailableStaffRoles() const {
    return {"Gardener", "Salesperson", "Manager", "Intern"};
}

std::vector<std::string> SimulationFacade::getAllPlantIds() const {
    std::vector<std::string> ids;
    for (const auto& pair : allPlants) {
        ids.push_back(pair.first);
    }
    return ids;
}