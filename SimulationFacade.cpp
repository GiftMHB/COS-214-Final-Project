/**
 * @file SimulationFacade.cpp
 * @brief Implementation of the SimulationFacade
 */

#include "SimulationFacade.h"
#include "GardenArea.h"
#include "GardenSection.h"
#include "PlantBed.h"
#include "Plant.h"
#include "HealthMonitor.h"
#include "GrowthTracker.h"
#include "InventoryObserver.h"
#include <iostream>
#include <sstream>

SimulationFacade::SimulationFacade()
    : gardenArea(nullptr), inventory(nullptr), reports(nullptr),
      systemOriginator(nullptr), simulationRunning(false),
      currentSeason("Spring"), dayCounter(0) {
    
    std::cout << " Initializing Plant Nursery Simulation..." << std::endl;
}

SimulationFacade::~SimulationFacade() {
    
    for (std::list<Staff*>::iterator it = staff.begin(); 
         it != staff.end(); ++it) {
        // Note: Staff class is managed by team member
        // Uncomment when Staff implementation is available:
        // delete *it;
    }
    staff.clear();
    
    // Note: GardenArea is a singleton, so we don't delete it
    // Other subsystems would be cleaned up here
    
    std::cout << " Nursery simulation shut down." << std::endl;
}

void SimulationFacade::initializeNursery() {
    std::cout << "\n=== Initializing Nursery ===" << std::endl;
    
    
    gardenArea = &GardenArea::getInstance();
    
    
    GardenSection* flowerSection = new GardenSection("Flower Section", "FS01");
    GardenSection* treeSection = new GardenSection("Tree Section", "TS01");
    GardenSection* succulentSection = new GardenSection("Succulent Section", "SS01");
    
    
    PlantBed* roseBed = new PlantBed("Rose Bed", "RB01", 5);
    PlantBed* lavenderBed = new PlantBed("Lavender Bed", "LB01", 8);
    PlantBed* cactusBed = new PlantBed("Cactus Bed", "CB01", 10);
    
    
    flowerSection->add(roseBed);
    flowerSection->add(lavenderBed);
    succulentSection->add(cactusBed);
    
    gardenArea->add(flowerSection);
    gardenArea->add(treeSection);
    gardenArea->add(succulentSection);
    
    
    gardenArea->setTemperature(22.0);
    gardenArea->setHumidity(60.0);
    
    std::cout << " Garden structure created" << std::endl;
    std::cout << " Environmental controls set" << std::endl;
    std::cout << " Nursery initialization complete!\n" << std::endl;
}

void SimulationFacade::startSimulation() {
    if (simulationRunning) {
        std::cout << "Simulation is already running!" << std::endl;
        return;
    }
    
    simulationRunning = true;
    dayCounter = 0;
    std::cout << "\n Simulation started! Season: " << currentSeason << std::endl;
}

void SimulationFacade::stopSimulation() {
    if (!simulationRunning) {
        std::cout << "Simulation is not running!" << std::endl;
        return;
    }
    
    simulationRunning = false;
    std::cout << "\n Simulation stopped at day " << dayCounter << std::endl;
}

void SimulationFacade::simulateDay() {
    if (!simulationRunning) {
        std::cout << "Start simulation first!" << std::endl;
        return;
    }
    
    dayCounter++;
    std::cout << "\n=== Day " << dayCounter << " - " << currentSeason << " ===" << std::endl;
    
    
    if (dayCounter % 30 == 0) {
        if (currentSeason == "Spring") currentSeason = "Summer";
        else if (currentSeason == "Summer") currentSeason = "Autumn";
        else if (currentSeason == "Autumn") currentSeason = "Winter";
        else currentSeason = "Spring";
        
        std::cout << " Season changed to " << currentSeason << "!" << std::endl;
    }
    
    managePlantCare();
    updateAllPlants();
    manageSales();
    updateObservers();
}

void SimulationFacade::updateAllPlants() {
    if (gardenArea == nullptr) return;
    
    std::list<Plant*> allPlants = gardenArea->getAllPlants();
    
    for (std::list<Plant*>::iterator it = allPlants.begin(); 
         it != allPlants.end(); ++it) {
        Plant* plant = *it;
        
        
        plant->water(-5); 
        plant->fertilize(-3); 
    }
    
    std::cout << " Updated " << allPlants.size() << " plants" << std::endl;
}

void SimulationFacade::updateObservers() {
    // Observers are automatically notified when plants change
    
    std::cout << " Observers notified of changes" << std::endl;
}

void SimulationFacade::managePlantCare() {
    if (gardenArea == nullptr) return;
    
    std::list<Plant*> allPlants = gardenArea->getAllPlants();
    int plantsCared = 0;
    
    for (std::list<Plant*>::iterator it = allPlants.begin(); 
         it != allPlants.end(); ++it) {
        Plant* plant = *it;
        
        
        if (plant->getWaterLevel() < 50) {
            plant->water(30);
            plantsCared++;
        }
        
        if (plant->getNutrientLevel() < 50) {
            plant->fertilize(25);
            plantsCared++;
        }
    }
    
    std::cout << " Staff cared for " << plantsCared << " plant needs" << std::endl;
}

void SimulationFacade::manageSales() {
    if (gardenArea == nullptr) return;
    
    std::list<Plant*> allPlants = gardenArea->getAllPlants();
    int readyForSale = 0;
    
    for (std::list<Plant*>::iterator it = allPlants.begin(); 
         it != allPlants.end(); ++it) {
        if ((*it)->isReadyForSale()) {
            readyForSale++;
        }
    }
    
    std::cout << " " << readyForSale << " plants ready for sale" << std::endl;
}

void SimulationFacade::generateReports() {
    std::cout << "\n=== Nursery Report ===" << std::endl;
    std::cout << getPlantSummary() << std::endl;
    std::cout << getInventorySummary() << std::endl;
    
    if (gardenArea != nullptr) {
        gardenArea->display();
    }
}

void SimulationFacade::hireStaff(const std::string& name, const std::string& role) {
    // Staff* newStaff = new Staff(name, role);
    // staff.push_back(newStaff);
    std::cout << " Hired " << name << " as " << role << std::endl;
}

void SimulationFacade::fireStaff(const std::string& staffId) {
    std::cout << " Fired staff member " << staffId << std::endl;
}

void SimulationFacade::addNewPlant(const std::string& type, const std::string& careLevel) {
    Plant* newPlant = new Plant(type, type + " Species");
    
    
    HealthMonitor* healthMon = new HealthMonitor();
    GrowthTracker* growthTrack = new GrowthTracker();
    
    newPlant->attach(healthMon);
    newPlant->attach(growthTrack);
    
    
    if (gardenArea != nullptr) {
        GardenComponent* found = gardenArea->findByName("Rose Bed");
        if (found != nullptr && found->getType() == "PlantBed") {
            PlantBed* bed = dynamic_cast<PlantBed*>(found);
            if (bed != nullptr) {
                if (!bed->assignPlant(newPlant)) {
                    // Bed is full, clean up
                    delete healthMon;
                    delete growthTrack;
                    delete newPlant;
                    return;
                }
            }
        }
    }
    
    std::cout << " Added new plant: " << type << " (Care: " << careLevel << ")" << std::endl;
}

bool SimulationFacade::removePlant(const std::string& plantId) {
    Plant* plant = findPlant(plantId);
    if (plant != nullptr) {
        std::cout << " Removed plant " << plantId << std::endl;
        return true;
    }
    std::cout << " Plant " << plantId << " not found" << std::endl;
    return false;
}

std::string SimulationFacade::getPlantSummary() {
    if (gardenArea == nullptr) {
        return "No garden data available";
    }
    
    std::stringstream ss;
    ss << "Total Plants: " << gardenArea->getPlantCount() << "\n";
    ss << "Temperature: " << gardenArea->getTemperature() << "°C\n";
    ss << "Humidity: " << gardenArea->getHumidity() << "%\n";
    
    return ss.str();
}

std::string SimulationFacade::getInventorySummary() {
    return "Inventory Status: Active";
}

void SimulationFacade::saveSystemState(const std::string& filePath) {
    std::cout << " Saving system state to " << filePath << "..." << std::endl;
    
}

void SimulationFacade::loadSystemState(const std::string& filePath) {
    std::cout << " Loading system state from " << filePath << "..." << std::endl;
    
}

Plant* SimulationFacade::findPlant(const std::string& plantId) {
    if (gardenArea == nullptr) return nullptr;
    
    std::list<Plant*> allPlants = gardenArea->getAllPlants();
    
    for (std::list<Plant*>::iterator it = allPlants.begin(); 
         it != allPlants.end(); ++it) {
        if ((*it)->getId() == plantId) {
            return *it;
        }
    }
    
    return nullptr;
}

int SimulationFacade::getCurrentDay() const {
    return dayCounter;
}

std::string SimulationFacade::getCurrentSeason() const {
    return currentSeason;
}

bool SimulationFacade::isRunning() const {
    return simulationRunning;
}