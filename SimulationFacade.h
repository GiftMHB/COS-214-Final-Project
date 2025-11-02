/**
 * @file SimulationFacade.h
 * @brief Facade pattern providing simplified interface to the nursery simulation
 * @details SimulationFacade coordinates between garden, inventory, staff, and reporting
 *          subsystems to provide a unified, simplified interface for the entire system.
 */

#ifndef SIMULATION_FACADE_H
#define SIMULATION_FACADE_H

#include <string>
#include <list>

// Forward declarations
class GardenArea;
class InventoryAggregate;
class Reports;
class SystemOriginator;
class Staff;
class Plant;
class Observer;

/**
 * @class SimulationFacade
 * @brief Facade providing simplified access to complex nursery subsystems
 * 
 * This class implements the Facade pattern to hide the complexity of
 * interacting with multiple subsystems (garden, inventory, staff, reports).
 * It provides high-level methods for common operations.
 */
class SimulationFacade {
private:
    GardenArea* gardenArea; ///< Pointer to garden management system
    InventoryAggregate* inventory; ///< Pointer to inventory system
    Reports* reports; ///< Pointer to reporting system
    SystemOriginator* systemOriginator; ///< Pointer to memento originator
    std::list<Staff*> staff; ///< List of staff members
    std::list<Plant*> managedPlants; ///< Plants created by facade
    std::list<Observer*> managedObservers; ///< Observers created by facade
    bool simulationRunning; ///< Simulation status flag
    std::string currentSeason; ///< Current season (Spring/Summer/Autumn/Winter)
    int dayCounter; ///< Day counter for simulation

public:
    /**
     * @brief Constructor - initializes all subsystems
     */
    SimulationFacade();

    /**
     * @brief Destructor - cleans up resources
     */
    ~SimulationFacade();

    /**
     * @brief Initialize the nursery with default setup
     */
    void initializeNursery();

    /**
     * @brief Start the simulation
     */
    void startSimulation();

    /**
     * @brief Stop the simulation
     */
    void stopSimulation();

    /**
     * @brief Simulate one day of nursery operations
     */
    void simulateDay();

    /**
     * @brief Update all plants (care, growth, health)
     */
    void updateAllPlants();

    /**
     * @brief Update all observers with current plant states
     */
    void updateObservers();

    /**
     * @brief Manage plant care routines (staff caring for plants)
     */
    void managePlantCare();

    /**
     * @brief Manage sales operations
     */
    void manageSales();

    /**
     * @brief Generate reports for the nursery
     */
    void generateReports();

    /**
     * @brief Hire a new staff member
     * @param name Staff member's name
     * @param role Staff role (e.g., "Gardener", "Salesperson")
     */
    void hireStaff(const std::string& name, const std::string& role);

    /**
     * @brief Fire a staff member
     * @param staffId ID of the staff member to fire
     */
    void fireStaff(const std::string& staffId);

    /**
     * @brief Add a new plant to the nursery
     * @param type Plant type (e.g., "Rose", "Cactus")
     * @param careLevel Care difficulty level (e.g., "Easy", "Medium", "Hard")
     */
    void addNewPlant(const std::string& type, const std::string& careLevel);

    /**
     * @brief Remove a plant from the nursery
     * @param plantId ID of the plant to remove
     * @return true if plant was found and removed
     */
    bool removePlant(const std::string& plantId);

    /**
     * @brief Get a summary of all plants
     * @return Summary string with plant counts and statistics
     */
    std::string getPlantSummary();

    /**
     * @brief Get inventory summary
     * @return Summary string with inventory statistics
     */
    std::string getInventorySummary();

    /**
     * @brief Save the current system state to a file
     * @param filePath Path to save file
     */
    void saveSystemState(const std::string& filePath);

    /**
     * @brief Load system state from a file
     * @param filePath Path to load file
     */
    void loadSystemState(const std::string& filePath);

    /**
     * @brief Find a plant by ID
     * @param plantId ID of the plant to find
     * @return Pointer to the plant, nullptr if not found
     */
    Plant* findPlant(const std::string& plantId);

    /**
     * @brief Get current simulation day
     * @return Day counter
     */
    int getCurrentDay() const;

    /**
     * @brief Get current season
     * @return Season string
     */
    std::string getCurrentSeason() const;

    /**
     * @brief Check if simulation is running
     * @return true if running, false otherwise
     */
    bool isRunning() const;
};

#endif // SIMULATION_FACADE_H