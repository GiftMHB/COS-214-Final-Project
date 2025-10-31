#include "SeasonalCare.h"
#include "Plant.h"
#include <iostream>
#include <algorithm> 


SeasonalCare::SeasonalCare(std::string season) : currentSeason(std::move(season))
{
    seasonalAdjustments = {
        {"Spring", 2},   // active growth — moderate needs
        {"Summer", 3},   // intense heat — higher needs
        {"Autumn", 1},   // cooling off — reduced needs
        {"Winter", 0}    // dormancy — minimal needs
    };
}

void SeasonalCare::applyCare(Plant *plant)
{
    std::cout << "Applying seasonal care for " << plant->getName()<< " during " << currentSeason << "\n";

    int water = calculateWaterNeeds(plant);
    int nutrients = calculateNutrientNeeds(plant);
    int sunlight = calculateSunlightNeeds(plant);

    plant->water(water);
    plant->fertilize(nutrients);
    plant->exposeToSunlight(sunlight);

    std::cout << "Finished seasonal care for " << plant->getName()<< " (" << currentSeason << ").\n";
}

int SeasonalCare::calculateWaterNeeds(Plant *plant)
{
    int base = 3; 
    int adjustment = seasonalAdjustments[currentSeason];
    int water = std::max(1, base + adjustment);

    std::cout << "Water needs (" << currentSeason << "): " << water << "\n";
    return water;
}

int SeasonalCare::calculateSunlightNeeds(Plant *plant)
{
    int base = 4;
    int adjustment = seasonalAdjustments[currentSeason];

    // Winter → less sunlight; Summer → more sunlight
    int value = base + adjustment;
    int sunlight = std::max(2, std::min(value, 8));

    std::cout << "Sunlight needs (" << currentSeason << "): " << sunlight << " hours\n";
    return sunlight;
}

int SeasonalCare::calculateNutrientNeeds(Plant *plant)
{
    int base = 2;
    int adjustment = seasonalAdjustments[currentSeason];

    // Fewer nutrients needed in colder seasons
    int nutrients = std::max(1, base + (adjustment / 2));

    std::cout << "Nutrient needs (" << currentSeason << "): " << nutrients << "\n";
    return nutrients;
}

std::string SeasonalCare::getStrategyName()
{
    return "Seasonal Care (" + currentSeason + ")";
}

void SeasonalCare::setSeason(std::string &season)
{
    
    if (seasonalAdjustments.find(season) != seasonalAdjustments.end())
    {
        currentSeason = season;
        std::cout << "Seasonal care updated to " << currentSeason << ".\n";
    }
    else
    {
        std::cout << "Unknown season '" << season<< "' Defaulting to Spring\n";
        currentSeason = "Spring";
    }
}
