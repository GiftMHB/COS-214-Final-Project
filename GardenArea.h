/**
 * @file GardenArea.h
 * @brief Composite root class representing the entire garden area (Singleton)
 * @details Implements both Composite and Singleton patterns to manage the top-level
 *          garden hierarchy with a single instance.
 */

#ifndef GARDEN_AREA_H
#define GARDEN_AREA_H

#include "GardenComponent.h"
#include <list>
#include <string>

// Forward declaration
class Plant;

/**
 * @class GardenArea
 * @brief Singleton composite root managing all garden sections
 * 
 * This class represents the top-level container in the garden hierarchy.
 * It implements the Singleton pattern to ensure only one garden area exists.
 */
class GardenArea : public GardenComponent {
private:
    static GardenArea* instance; ///< Singleton instance
    std::list<GardenComponent*> sections; ///< Child sections
    int totalCapacity; ///< Maximum capacity of the garden
    double temperature; ///< Current temperature
    double humidity; ///< Current humidity level
    std::string id; ///< Unique identifier

    /**
     * @brief Private constructor for Singleton pattern
     */
    GardenArea();

    /**
     * @brief Private copy constructor (deleted)
     */
    GardenArea(const GardenArea&);

    /**
     * @brief Private assignment operator (deleted)
     */
    GardenArea& operator=(const GardenArea&);

public:
    /**
     * @brief Get the singleton instance of GardenArea
     * @return Reference to the GardenArea instance
     */
    static GardenArea& getInstance();

    /**
     * @brief Destructor - cleans up all child sections
     */
    ~GardenArea();

    /**
     * @brief Add a section to the garden
     * @param section Pointer to the section to add
     */
    void add(GardenComponent* section);

    /**
     * @brief Remove a section from the garden
     * @param section Pointer to the section to remove
     */
    void remove(GardenComponent* section);

    /**
     * @brief Display the entire garden hierarchy
     * @param depth Indentation depth for display formatting
     */
    void display(int depth = 0);

    /**
     * @brief Get total plant count across all sections
     * @return Total number of plants
     */
    int getPlantCount();

    /**
     * @brief Find a component by name in the hierarchy
     * @param name Name to search for
     * @return Pointer to found component, nullptr if not found
     */
    GardenComponent* findByName(const std::string& name);

    /**
     * @brief Get all plants from all sections
     * @return List of plant pointers
     */
    std::list<Plant*> getAllPlants();

    /**
     * @brief Set the garden temperature
     * @param temp Temperature value
     */
    void setTemperature(double temp);

    /**
     * @brief Get the current temperature
     * @return Current temperature
     */
    double getTemperature();

    /**
     * @brief Set the garden humidity
     * @param hum Humidity value
     */
    void setHumidity(double hum);

    /**
     * @brief Get the current humidity
     * @return Current humidity
     */
    double getHumidity();

    /**
     * @brief Get the component type
     * @return Type string "GardenArea"
     */
    std::string getType();

    /**
     * @brief Get the garden name
     * @return Garden name
     */
    std::string getName();
};

#endif // GARDEN_AREA_H