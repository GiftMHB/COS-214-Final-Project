#ifndef LOWMAINTENANCECARE_H
#define LOWMAINTENANCECARE_H

#include "CareStrategy.h"

/**
 * @file LowMaintenanceCare.h
 * @brief Defines the LowMaintenanceCare strategy for minimal care plants
 * @class LowMaintenanceCare
 * @brief Strategy for plants that require minimal watering and nutrients.
 */
class LowMaintenanceCare : public CareStrategy {
    private:
        int waterFrequency;// Frequency of watering (in days)
        int nutrientFrequency;// Frequency of nutrient application (in days)

    public:
        /**
         * @brief Constructs a LowMaintenanceCare strategy with specified frequencies.
         * @param waterFreq Days between watering sessions.
         * @param nutrientFreq Days between nutrient applications.
         */
        LowMaintenanceCare(int waterFreq, int nutrientFreq);

        void applyCare(Plant* plant);
        int calculateWaterNeeds(Plant* plant);
        int calculateSunlightNeeds(Plant* plant);
        int calculateNutrientNeeds(Plant* plant);
        std::string getStrategyName();
};

#endif 