/**
 * @file GrowthTracker.cpp
 * @brief Implementation of the GrowthTracker concrete observer
 */

#include "GrowthTracker.h"
#include "Plant.h"
#include <iostream>

GrowthTracker::GrowthTracker() : lastGrowthStage("Unknown") {}

GrowthTracker::~GrowthTracker() {}

void GrowthTracker::update(Plant* subject, const std::string& eventType) {
    if (subject == nullptr) {
        return;
    }

    if (eventType == "state_changed") {
        std::cout << "[GROWTH TRACKER] Plant '" << subject->getName() 
                  << "' (ID: " << subject->getId() 
                  << ") has changed growth stage!" << std::endl;
        recordGrowthStage(subject);
    } else if (eventType == "watered" || eventType == "fertilized") {
        // Check if plant is ready for sale (matured)
        if (subject->isReadyForSale() && lastGrowthStage != "Mature") {
            std::cout << "[GROWTH TRACKER] Plant '" << subject->getName() 
                      << "' has matured and is ready for sale!" << std::endl;
            lastGrowthStage = "Mature";
        }
    }
}

std::string GrowthTracker::getObserverType() {
    return "GrowthTracker";
}

void GrowthTracker::recordGrowthStage(Plant* subject) {
    if (subject == nullptr) {
        return;
    }

    std::cout << "--- Growth Record for " << subject->getName() << " ---" << std::endl;
    std::cout << "  ID: " << subject->getId() << std::endl;
    std::cout << "  Previous Stage: " << lastGrowthStage << std::endl;
    
    // Determine current stage based on health and readiness
    std::string currentStage;
    if (!subject->getIsAlive()) {
        currentStage = "Dead";
    } else if (subject->isReadyForSale()) {
        currentStage = "Mature";
    } else if (subject->getHealth() >= 50.0) {
        currentStage = "Growing";
    } else {
        currentStage = "Seedling";
    }
    
    std::cout << "  Current Stage: " << currentStage << std::endl;
    std::cout << "  Health: " << subject->getHealth() << "%" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    lastGrowthStage = currentStage;
}