/**
 * @file CareStrategy.h
 * @brief Defines the abstract CareStrategy class used to apply care strategies to plants.
 */

#ifndef CARE_STRATEGY_H
#define CARE_STRATEGY_H

#include <string>

class Plant;

/**
 * @class CareStrategy
 * @brief Abstract base class for different plant care strategies.
 *
 * The CareStrategy class defines the interface for applying specific care
 * methods to Plant objects. Subclasses should implement the care logic
 * and provide a name for the strategy.
 */
class CareStrategy {
public:
    /**
     * @brief Virtual destructor for safe polymorphic destruction.
     */
    virtual ~CareStrategy() = default;

    /**
     * @brief Applies the care strategy to a given plant.
     * @param plant Pointer to the Plant object that the care will be applied to.
     */
    virtual void applyCare(Plant* plant) = 0;

    /**
     * @brief Retrieves the name of the care strategy.
     * @return A string containing the name of the strategy.
     */
    virtual std::string getStrategyName() const = 0;
};

#endif
