/**
 * @file PlantState.h
 * @brief Defines the abstract PlantState class for implementing plant growth states.
 */

#ifndef PLANT_STATE_H
#define PLANT_STATE_H

#include <string>

class Plant;

/**
 * @class PlantState
 * @brief Abstract base class representing the state of a plant in the State pattern.
 *
 * PlantState defines the interface for different growth or health states of a plant.
 * Concrete states will implement behavior for growing and handling plant-specific logic.
 */
class PlantState {
public:
    /**
     * @brief Virtual destructor for proper cleanup in derived classes.
     */
    virtual ~PlantState() = default;

    /**
     * @brief Performs growth actions specific to this state.
     * @param plant Pointer to the Plant object being grown.
     */
    virtual void grow(Plant* plant) = 0;

    /**
     * @brief Handles state-specific logic for the plant.
     * @param plant Pointer to the Plant object to handle.
     */
    virtual void handle(Plant* plant) = 0;

    /**
     * @brief Returns the name of the current state.
     * @return String representing the state name.
     */
    virtual std::string getStateName() const = 0;
};

#endif
