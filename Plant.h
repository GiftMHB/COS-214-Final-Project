// Here's my specific header
/**
 * @file Plant.h
 * @brief Concrete Subject class representing a plant that can be observed
 * @details Plant implements the Subject interface and maintains state that
 *          observers can monitor.
 */

#ifndef PLANT_H
#define PLANT_H

#include "Subject.h"
#include <string>

// Forward declarations
class PlantState;
class CareStrategy;

/**
 * @class Plant
 * @brief Concrete subject representing a plant in the nursery
 * 
 * This class represents a plant that can be observed for changes in
 * health, water level, nutrient level, and growth state.
 */
class Plant : public Subject {
private:
    std::string id; ///< Unique plant identifier
    std::string name; ///< Plant name
    std::string species; ///< Plant species
    std::string classification; ///< Plant classification
    double price; ///< Sale price
    int waterLevel; ///< Current water level (0-100)
    int nutrientLevel; ///< Current nutrient level (0-100)
    double health; ///< Health status (0.0-100.0)
    bool isAlive; ///< Whether plant is alive
    PlantState* currentState; ///< Current growth state
    CareStrategy* careStrategy; ///< Care strategy

public:
    /**
     * @brief Constructor
     * @param plantName Name of the plant
     * @param plantSpecies Species of the plant
     */
    Plant(const std::string& plantName, const std::string& plantSpecies);

    /**
     * @brief Destructor
     */
    ~Plant();

    /**
     * @brief Water the plant
     * @param amount Amount of water to add (1-100)
     */
    void water(int amount);

    /**
     * @brief Fertilize the plant
     * @param amount Amount of fertilizer to add (1-100)
     */
    void fertilize(int amount);

    /**
     * @brief Apply care strategy to the plant
     */
    void applyCare();

    /**
     * @brief Change the plant's growth state
     * @param newState Pointer to the new state
     */
    void changeState(PlantState* newState);

    /**
     * @brief Get the plant's health
     * @return Health value (0.0-100.0)
     */
    double getHealth() const;

    /**
     * @brief Check if plant is ready for sale
     * @return true if ready for sale, false otherwise
     */
    bool isReadyForSale() const;

    /**
     * @brief Get plant ID
     * @return Plant identifier
     */
    std::string getId() const;

    /**
     * @brief Get plant name
     * @return Plant name
     */
    std::string getName() const;

    /**
     * @brief Get plant species
     * @return Plant species
     */
    std::string getSpecies() const;

    /**
     * @brief Get water level
     * @return Current water level
     */
    int getWaterLevel() const;

    /**
     * @brief Get nutrient level
     * @return Current nutrient level
     */
    int getNutrientLevel() const;

    /**
     * @brief Set plant price
     * @param newPrice New price
     */
    void setPrice(double newPrice);

    /**
     * @brief Get plant price
     * @return Current price
     */
    double getPrice() const;

    /**
     * @brief Check if plant is alive
     * @return true if alive, false otherwise
     */
    bool getIsAlive() const;
};

#endif // PLANT_H
