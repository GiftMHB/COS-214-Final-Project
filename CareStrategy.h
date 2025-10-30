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
        virtual int calculateWaterNeeds(Plant* plant) = 0;
        virtual int calculateSunlightNeeds(Plant* plant) = 0;
        virtual int calculateNutrientNeeds(Plant* plant) = 0;
        virtual std::string getStrategyName() = 0;
        virtual ~CareStrategy();
};

#endif 
