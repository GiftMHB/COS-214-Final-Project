/**
 * @file PlantBed.h
 * @brief Leaf class in the Composite pattern representing individual plant beds
 * @details PlantBed is a leaf node that contains actual Plant objects and
 *          cannot have child components.
 */

#ifndef PLANT_BED_H
#define PLANT_BED_H

#include "GardenComponent.h"
#include <list>
#include <string>

// Forward declaration
class Plant;

/**
 * @class PlantBed
 * @brief Leaf component that holds individual plants
 * 
 * This class represents the leaf nodes in the composite hierarchy.
 * It manages a collection of plants with a maximum capacity.
 */
class PlantBed : public GardenComponent {
private:
    std::string id; ///< Unique identifier
    int capacity; ///< Maximum number of plants
    std::list<Plant*> plants; ///< List of plants in the bed

public:
    /**
     * @brief Constructor
     * @param bedName Name of the plant bed
     * @param bedId Unique identifier
     * @param maxCapacity Maximum plant capacity (default 10)
     */
    PlantBed(const std::string& bedName, const std::string& bedId, int maxCapacity = 10);

    /**
     * @brief Destructor - does NOT delete plants (managed elsewhere)
     */
    ~PlantBed();

    /**
     * @brief Assign a plant to this bed
     * @param plant Pointer to the plant to assign
     * @return true if successful, false if bed is full
     */
    bool assignPlant(Plant* plant);

    /**
     * @brief Remove a plant from the bed by ID
     * @param plantId ID of the plant to remove
     * @return true if plant was found and removed
     */
    bool removePlant(const std::string& plantId);

    /**
     * @brief Get a plant by its ID
     * @param plantId ID of the plant
     * @return Pointer to the plant, nullptr if not found
     */
    Plant* getPlant(const std::string& plantId);

    /**
     * @brief Get all plants in this bed
     * @return List of plant pointers
     */
    std::list<Plant*> getPlants();

    /**
     * @brief Display this plant bed and its plants
     * @param depth Indentation depth for formatting
     */
    void display(int depth = 0);

    /**
     * @brief Get the number of plants in this bed
     * @return Plant count
     */
    int getPlantCount();

    /**
     * @brief Find a component by name (checks bed name and plant names)
     * @param searchName Name to search for
     * @return Pointer to this bed if name matches, nullptr otherwise
     */
    GardenComponent* findByName(const std::string& searchName);

    /**
     * @brief Get the component type
     * @return Type string "PlantBed"
     */
    std::string getType();

    /**
     * @brief Get the bed name
     * @return Bed name
     */
    std::string getName();
};

#endif // PLANT_BED_H