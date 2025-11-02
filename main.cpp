#include "SimulationFacade.h"
#include "GardenArea.h"
#include "GardenSection.h"
#include "PlantBed.h"
#include "Plant.h"
#include "HealthMonitor.h"
#include "GrowthTracker.h"
#include "InventoryObserver.h"
#include <iostream>
#include <memory>

/**
 * @brief Demonstrate the Composite Pattern
 */
void demonstrateCompositePattern() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DEMONSTRATING COMPOSITE PATTERN" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Get Garden Area (Singleton Composite Root)
    GardenArea& garden = GardenArea::getInstance();
    garden.setTemperature(25.0);
    garden.setHumidity(60.0);
    
    // Create sections (Composite nodes)
    auto succulentSection = std::make_shared<GardenSection>("Succulent Zone", "S001");
    auto flowerSection = std::make_shared<GardenSection>("Flower Garden", "S002");
    
    // Create plant beds (Leaf nodes)
    auto cactusBed = std::make_shared<PlantBed>("Cactus Collection", "B001", 5);
    auto roseBed = std::make_shared<PlantBed>("Rose Garden", "B002", 10);
    auto lavenderBed = std::make_shared<PlantBed>("Lavender Field", "B003", 8);
    
    // Create plants
    auto cactus1 = std::make_shared<Plant>("Golden Barrel", "Echinocactus grusonii");
    auto rose1 = std::make_shared<Plant>("Peace Rose", "Rosa 'Peace'");
    auto lavender1 = std::make_shared<Plant>("English Lavender", "Lavandula angustifolia");
    
    // Build the hierarchy
    cactusBed->assignPlant(cactus1);
    roseBed->assignPlant(rose1);
    lavenderBed->assignPlant(lavender1);
    
    succulentSection->add(cactusBed);
    flowerSection->add(roseBed);
    flowerSection->add(lavenderBed);
    
    garden.add(succulentSection);
    garden.add(flowerSection);
    
    // Display the entire composite structure
    std::cout << "\nDisplaying Garden Hierarchy:" << std::endl;
    garden.display();
    
    // Demonstrate uniform interface
    std::cout << "\n\nDemonstrating Uniform Interface:" << std::endl;
    std::cout << "Total plants in garden: " << garden.getPlantCount() << std::endl;
    std::cout << "Plants in Flower section: " << flowerSection->getPlantCount() << std::endl;
    std::cout << "Plants in Rose bed: " << roseBed->getPlantCount() << std::endl;
}

/**
 * @brief Demonstrate the Observer Pattern
 */
void demonstrateObserverPattern() {
    std::cout << "\n\n" << std::string(60, '=') << std::endl;
    std::cout << "DEMONSTRATING OBSERVER PATTERN" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Create a plant (Subject)
    auto orchid = std::make_shared<Plant>("Phalaenopsis Orchid", "Phalaenopsis amabilis");
    
    // Create observers
    auto healthMonitor = std::make_shared<HealthMonitor>();
    auto growthTracker = std::make_shared<GrowthTracker>();
    auto inventoryObs = std::make_shared<InventoryObserver>(nullptr);
    
    // Attach observers to the plant
    std::cout << "\nAttaching Observers:" << std::endl;
    orchid->attach(healthMonitor);
    orchid->attach(growthTracker);
    orchid->attach(inventoryObs);
    
    // Perform actions that notify observers
    std::cout << "\n\nPerforming Actions on Plant:" << std::endl;
    std::cout << "\n1. Watering the orchid..." << std::endl;
    orchid->water(20);
    
    std::cout << "\n2. Fertilizing the orchid..." << std::endl;
    orchid->fertilize(15);
    
    std::cout << "\n3. Applying care strategy..." << std::endl;
    orchid->applyCare();
    
    // Water more to increase health
    std::cout << "\n4. Additional watering..." << std::endl;
    orchid->water(15);
    orchid->water(10);
    
    // Detach one observer
    std::cout << "\n\nDetaching Growth Tracker:" << std::endl;
    orchid->detach(growthTracker);
    
    std::cout << "\n5. Fertilizing after detaching observer..." << std::endl;
    orchid->fertilize(10);
}

/**
 * @brief Demonstrate the Facade Pattern
 */
void demonstrateFacadePattern() {
    std::cout << "\n\n" << std::string(60, '=') << std::endl;
    std::cout << "DEMONSTRATING FACADE PATTERN" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Create the facade - single point of access to complex subsystems
    SimulationFacade facade;
    
    // Initialize the entire nursery with one call
    std::cout << "\n1. Initializing Nursery through Facade:" << std::endl;
    facade.initializeNursery();
    
    // Start simulation
    std::cout << "\n\n2. Starting Simulation:" << std::endl;
    facade.startSimulation();
    
    // Simulate several days
    std::cout << "\n\n3. Simulating Multiple Days:" << std::endl;
    for (int i = 0; i < 3; i++) {
        facade.simulateDay();
    }
    
    // Add new plant through facade
    std::cout << "\n\n4. Adding New Plant through Facade:" << std::endl;
    facade.addNewPlant("Bamboo", "Low");
    
    // Get summaries
    std::cout << "\n\n5. Getting System Summaries:" << std::endl;
    std::cout << facade.getPlantSummary();
    std::cout << facade.getInventorySummary();
    
    // Hire staff
    std::cout << "\n6. Managing Staff through Facade:" << std::endl;
    facade.hireStaff("Alice Green", "Plant Care Specialist");
    facade.hireStaff("Bob Brown", "Sales Associate");
    
    // Stop simulation
    std::cout << "\n\n7. Stopping Simulation:" << std::endl;
    facade.stopSimulation();
}

int main() {
    std::cout << " PLANT NURSERY SIMULATION 🌿🌿🌿" << std::endl;
    std::cout << "Design Patterns Demonstration: Composite, Observer, Facade" << std::endl;
    
    try {
        // Demonstrate each pattern
        demonstrateCompositePattern();
        demonstrateObserverPattern();
        demonstrateFacadePattern();
        
        std::cout << "\n\n" << std::string(60, '=') << std::endl;
        std::cout << "ALL DEMONSTRATIONS COMPLETED SUCCESSFULLY!" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        
        // Clean up singleton
        GardenArea::destroyInstance();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}