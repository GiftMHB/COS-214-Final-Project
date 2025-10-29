#include "Plant.h"
#include <iostream>

Plant::Plant(PlantInfo &info)
{
    this->info = info;
}

Plant::~Plant()
{
}

void Plant::setCareStrategy(CareStrategy *strategy)
{
    info.careStrategy = strategy;
}

void Plant::applyCareStrategy()
{
    if (info.careStrategy)
        info.careStrategy->applyCare(this);
    else
        std::cout << "No care strategy set for this plant.\n";
}

std::string Plant::getCareStrategyName()
{
    return info.careStrategy ? info.careStrategy->getStrategyName() : "No Strategy";
}

void Plant::water(int amount)
{
    // Increase water level, but not beyond 100
    int newWaterLevel = info.waterLevel + amount;

    if (newWaterLevel < 0)
        newWaterLevel = 0;
    else if (newWaterLevel > 100)
        newWaterLevel = 100;

    info.waterLevel = newWaterLevel;
    std::cout << info.name << " watered by " << amount
              << " units. Current water level: " << info.waterLevel << "\n";

    if (info.waterLevel >= 40 && info.waterLevel <= 80)
        info.healthLevel = std::min(100, info.healthLevel + 2);
    else if (info.waterLevel > 90)
        info.healthLevel = std::max(0, info.healthLevel - 3); // overwatering 
}

void Plant::fertilize(int amount)
{
    int newnutrientLevel = info.nutrientLevel + amount;

    if (newnutrientLevel < 0)
        newnutrientLevel = 0;
    else if (newnutrientLevel > 100)
        newnutrientLevel = 100;

    info.nutrientLevel = newnutrientLevel;

    std::cout << info.name << " fertilized by " << amount
              << " units. Nutrient level: " << info.nutrientLevel << "\n";

    // Slight growth effect
    if (info.nutrientLevel > 40)
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.5);
}

void Plant::exposeToSunlight(int hours)
{
    std::cout << info.name << " exposed to sunlight for " << hours << " hours.\n";

    // Simulate effect of sunlight
    if (hours < info.sunlightNeed)
        info.healthLevel = std::max(0, info.healthLevel - 2); // not enough sunlight
    else if (hours > info.sunlightNeed + 3)
        info.healthLevel = std::max(0, info.healthLevel - 1); // too much sunlight
    else
        info.healthLevel = std::min(100, info.healthLevel + 1); // ideal sunlight

    if (info.healthLevel > 70)
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.2);
}
