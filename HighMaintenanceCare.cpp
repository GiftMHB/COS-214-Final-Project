#include "HighMaintenanceCare.h"
#include "Plant.h"
#include <iostream>
#include <algorithm> 

HighMaintenanceCare::HighMaintenanceCare(int waterFreq, int nutrientFreq, std::vector<std::string>& treatments)
    : waterFrequency(waterFreq), nutrientFrequency(nutrientFreq), specialTreatments(treatments) {}

void HighMaintenanceCare::applyCare(Plant* plant) {
    std::cout << "Applying high-maintenance care to " << plant->getName() << "\n";

    plant->water(calculateWaterNeeds(plant));
    plant->fertilize(calculateNutrientNeeds(plant));
    plant->exposeToSunlight(calculateSunlightNeeds(plant));

    if (!specialTreatments.empty()) {
        applySpecialTreatment(plant);
    }

    std::cout << "Finished high-maintenance care for " << plant->getName() << "\n";
}

int HighMaintenanceCare::calculateWaterNeeds(Plant* plant) {
    // More frequent watering = higher water need per session
    int water = std::max(2, 8 - waterFrequency);
    std::cout << "Calculated water need for " << plant->getName() << ": " << water << "\n";
    return water;
}

int HighMaintenanceCare::calculateSunlightNeeds(Plant* plant) {
    // These plants may need longer, brighter light periods
    int sunlightHours = 6; // Example: 6 hours per day
    std::cout << "Calculated sunlight need for " << plant->getName() << ": " << sunlightHours << " hours\n";
    return sunlightHours;
}

int HighMaintenanceCare::calculateNutrientNeeds(Plant* plant) {
    // More frequent feeding → higher nutrient needs
    int nutrients = std::max(2, 6 - nutrientFrequency);
    std::cout << "Calculated nutrient need for " << plant->getName() << ": " << nutrients << "\n";
    return nutrients;
}

std::string HighMaintenanceCare::getStrategyName() {
    return "High Maintenance Care";
}


void HighMaintenanceCare::applySpecialTreatment(Plant* plant) {
    std::cout << "Applying special treatments to " << plant->getName() << ":\n";

    for (const std::string& treatment : specialTreatments) {
        std::cout << " - Performing: " << treatment << "\n";

        // examples
        if (treatment == "pruning") {
            std::cout << "   Pruning encourages new growth.\n";
        } else if (treatment == "misting") {
            std::cout << "   Misting increases humidity and leaf health.\n";
        } else if (treatment == "repotting") {
            std::cout << "   Repotting refreshes soil nutrients.\n";
        }
    }
}
