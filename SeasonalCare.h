#ifndef SEASONALCARE_H
#define SEASONALCARE_H

#include <map>
#include <string>
#include "CareStrategy.h"

/**
 * @file SeasonalCare.h
 * @brief Defines the SeasonalCare strategy for adapting care routines based on season
 * @class SeasonalCare
 * @brief Strategy that adjusts plant care depending on the current season.
 */
class SeasonalCare : public CareStrategy
{
    private:
        std::string currentSeason;                      
        std::map<std::string, int> seasonalAdjustments; // Seasonal adjustment factors for care.

    public:
        /**
         * @brief Constructs a SeasonalCare strategy with optional initial season.
         * @param season Initial season (default = "Spring").
         */
        explicit SeasonalCare(std::string season = "Spring");

        void applyCare(Plant *plant);
        int calculateWaterNeeds(Plant *plant);
        int calculateSunlightNeeds(Plant *plant);
        int calculateNutrientNeeds(Plant *plant);
        std::string getStrategyName();

        /**
         * @brief Sets the current season for this strategy.
         * @param season The new active season.
         */
        void setSeason(std::string &season);
};

#endif