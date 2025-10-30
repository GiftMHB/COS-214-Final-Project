#include "Plant.h"
#include <iostream>

int PlantInfo::plantCount = 0;

Plant::Plant(PlantInfo& info) : info(info)
{
    PlantInfo::plantCount++;
    this->careStrategy = nullptr;
    this->state = nullptr;
}

Plant::~Plant()
{
    if (careStrategy)
    {
        delete careStrategy;
        careStrategy = nullptr;
    }
}

void Plant::setCareStrategy(CareStrategy *strategy)
{
    if (careStrategy)
        delete careStrategy;
    this->careStrategy = strategy;
}

void Plant::applyCareStrategy()
{
    if (this->careStrategy)
        this->careStrategy->applyCare(this);
    else
        std::cout << "No care strategy set for this plant.\n";
}

std::string Plant::getCareStrategyName()
{
    return this->careStrategy ? this->careStrategy->getStrategyName() : "No Strategy";
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

int Plant::getID()
{
    return info.id;
}

double Plant::getPrice()
{
    return info.salePrice;
}

void Plant::setPrice(double price)
{
    info.salePrice = price;
}

std::string Plant::getName()
{
    return info.name;
}

std::string Plant::getClassification()
{
    return info.classification;
}

std::string Plant::getDate()
{
    return info.addedDate;
}

int Plant::getWaterLevel()
{
    return info.waterLevel;
}

int Plant::getHealthLevel()
{
    return info.healthLevel;
}

PlantState *Plant::getState() const
{
    // return info.state;
}

void Plant::setState(PlantState *newState)
{
    // info.state = newState;
}

std::string Plant::getCurrentStateName()
{
    // return info.state ? info.state->getStateName() : "No State";
}

int Plant::getNutrientLevel() const
{
    return info.nutrientLevel;
}

void Plant::setNutrientLevel(int level)
{
    info.nutrientLevel = level;
}

void Plant::setHealthLevel(int level)
{
    info.healthLevel = level;
}

void Plant::setWaterLevel(int level)
{
    info.waterLevel = level;
}

int Plant::getAge() const
{
    return info.currentAgeDays;
}

void Plant::setAge(int newAge)
{
    info.currentAgeDays = newAge;
}

void Plant::grow()
{
    // info.state->grow(this);
}

void Plant::printStatus() const
{
    

}


