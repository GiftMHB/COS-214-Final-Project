#ifndef HIGHMAINTENANCECARE_H
#define HIGHMAINTENANCECARE_H

#include <vector>
#include <string>
#include "CareStrategy.h"

/**
 * @file HighMaintenanceCare.h
 * @brief Defines the HighMaintenanceCare strategy for plants needing frequent care
 * @class HighMaintenanceCare
 * @brief Strategy for plants requiring frequent watering and extra treatments
 */
class HighMaintenanceCare : public CareStrategy {
    private:
        int waterFrequency;                      
        int nutrientFrequency;                    
        std::vector<std::string> specialTreatments; // List of special care treatments

    public:
        /**
         * @brief Constructs a HighMaintenanceCare strategy with given parameters.
         * @param waterFreq Days between watering.
         * @param nutrientFreq Days between nutrient feeding.
         * @param treatments List of extra treatments (e.g., pruning, misting).
         */
        HighMaintenanceCare(int waterFreq, int nutrientFreq, std::vector<std::string>& treatments);

        void applyCare(Plant* plant);
        int calculateWaterNeeds(Plant* plant);
        int calculateSunlightNeeds(Plant* plant);
        int calculateNutrientNeeds(Plant* plant);
        std::string getStrategyName();

        /**
         * @brief Applies a special treatment to the given plant.
         * @param plant Pointer to the plant.
         */
        void applySpecialTreatment(Plant* plant);
};

#endif