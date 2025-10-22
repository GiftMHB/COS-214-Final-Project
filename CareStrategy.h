#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H

#include <string>
#include "Plant.h"

/**
 * @file CareStrategy.h
 * @brief Defines the CareStrategy interface for applying plant care behavior
 * @class CareStrategy
 * @brief Abstract interface for defining plant care strategies
 * 
 * The Strategy Pattern allows a Plant (Context) to use different care behaviors 
 * dynamically at runtime.
 */
class CareStrategy {
    public:
        /**
         * @brief Applies the overall care routine to the given plant.
         * @param plant Pointer to the plant receiving care.
         */
        virtual void applyCare(Plant* plant) = 0;

        /**
         * @brief Calculates the plant's required water amount
         * @return Water requirement 
         */
        virtual int calculateWaterNeeds(Plant* plant) = 0;

        /**
         * @brief Calculates how much sunlight the plant needs.
         * @return Sunlight requirement 
         */
        virtual int calculateSunlightNeeds(Plant* plant) = 0;

        /**
         * @brief Calculates the nutrient needs of the plant.
         * @return Nutrient requirement value.
         */
        virtual int calculateNutrientNeeds(Plant* plant) = 0;

        /**
         * @brief Returns the name of the current care strategy.
         * @return Strategy name as a string.
         */
        virtual std::string getStrategyName() = 0;

        virtual ~CareStrategy();
};

#endif 