#include "LowMaintenanceCare.h"
#include "Plant.h"
#include <iostream>

LowMaintenanceCare::LowMaintenanceCare(int waterFreq, int nutrientFreq)
    : waterFrequency(waterFreq), nutrientFrequency(nutrientFreq) {}

void LowMaintenanceCare::applyCare(Plant* plant) {
    std::cout << "Applying low maintenance care to " << plant->getName() << "\n";
    plant->water(calculateWaterNeeds(plant));
    plant->fertilize(calculateNutrientNeeds(plant));
    plant->exposeToSunlight(calculateSunlightNeeds(plant));
}

int LowMaintenanceCare::calculateWaterNeeds(Plant* plant) {
    return std::max(1, 5 - waterFrequency); 
}

int LowMaintenanceCare::calculateSunlightNeeds(Plant* plant) {
    return 3;
}

int LowMaintenanceCare::calculateNutrientNeeds(Plant* plant) {
    return std::max(1, 4 - nutrientFrequency);
}

std::string LowMaintenanceCare::getStrategyName() {
    return "Low Maintenance Care";
}