/**
 * @file HealthMonitor.cpp
 * @brief Implementation of the HealthMonitor concrete observer
 */

#include "HealthMonitor.h"
#include "Plant.h"
#include <iostream>

HealthMonitor::HealthMonitor() : lastHealthReading(100.0) {}

HealthMonitor::~HealthMonitor() {}

void HealthMonitor::update(Plant* subject, const std::string& eventType) {
    if (subject == nullptr) {
        return;
    }

    if (eventType == "health_low") {
        std::cout << "[HEALTH ALERT] Plant '" << subject->getName() 
                  << "' (ID: " << subject->getId() << ") has low health: " 
                  << subject->getHealth() << "%" << std::endl;
        logHealthData(subject);
    } else if (eventType == "watered" || eventType == "fertilized") {
        double currentHealth = subject->getHealth();
        if (currentHealth != lastHealthReading) {
            std::cout << "[HEALTH UPDATE] Plant '" << subject->getName() 
                      << "' health changed: " << lastHealthReading 
                      << "% -> " << currentHealth << "%" << std::endl;
            lastHealthReading = currentHealth;
        }
    }
}

std::string HealthMonitor::getObserverType() {
    return "HealthMonitor";
}

void HealthMonitor::logHealthData(Plant* subject) {
    if (subject == nullptr) {
        return;
    }

    std::cout << "--- Health Report for " << subject->getName() << " ---" << std::endl;
    std::cout << "  ID: " << subject->getId() << std::endl;
    std::cout << "  Species: " << subject->getSpecies() << std::endl;
    std::cout << "  Health: " << subject->getHealth() << "%" << std::endl;
    std::cout << "  Water Level: " << subject->getWaterLevel() << "%" << std::endl;
    std::cout << "  Nutrient Level: " << subject->getNutrientLevel() << "%" << std::endl;
    std::cout << "  Status: " << (subject->getIsAlive() ? "Alive" : "Dead") << std::endl;
    std::cout << "  Ready for Sale: " << (subject->isReadyForSale() ? "Yes" : "No") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    lastHealthReading = subject->getHealth();
}