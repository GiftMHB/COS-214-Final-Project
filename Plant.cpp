#include "Plant.h"
#include <iostream>
#include <ctime>  // For date if needed

int PlantInfo::plantCount = 0;

Plant::Plant(PlantInfo& pInfo) : info(pInfo), careStrategy(nullptr), state(nullptr) {
    if (info.id.empty()) {  // Auto-generate ID if not provided
        info.id = "P" + std::to_string(++PlantInfo::plantCount);
    }
    if (info.addedDate.empty()) {  // Set current date if not provided
        time_t now = time(0);
        tm* ltm = localtime(&now);
        info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                         std::to_string(1 + ltm->tm_mon) + "-" +
                         std::to_string(ltm->tm_mday);
    }
}

Plant::Plant(const std::string& name, const std::string& classification, double price) 
    : careStrategy(nullptr), state(nullptr) {
    info.id = "P" + std::to_string(++PlantInfo::plantCount);
    info.name = name;
    info.classification = classification;
    info.salePrice = price;
    info.purchasePrice = price * 0.7;  // Example default
    time_t now = time(0);
    tm* ltm = localtime(&now);
    info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                     std::to_string(1 + ltm->tm_mon) + "-" +
                     std::to_string(ltm->tm_mday);
}

Plant::~Plant() {
    delete careStrategy;
    delete state;
    for (auto obs : observers) {
        // Detach or cleanup if needed; assume observers outlive
    }
}

void Plant::setCareStrategy(CareStrategy* strategy) {
    delete careStrategy;  // Assume ownership; adjust if shared
    careStrategy = strategy;
}

void Plant::applyCare() {
    if (careStrategy) {
        careStrategy->applyCare(this);
    } else {
        std::cout << "No care strategy set for " << info.name << ".\n";
    }
}

std::string Plant::getCareStrategyName() const {
    return careStrategy ? careStrategy->getStrategyName() : "No Strategy";
}

void Plant::attach(Observer* observer) {
    observers.push_back(observer);
}

void Plant::detach(Observer* observer) {
    observers.remove(observer);
}

void Plant::notifyObservers(const std::string& eventType) {
    for (auto obs : observers) {
        obs->update(this, eventType);
    }
}

Plant::Plant(const Plant& other)
    : info(other.info),  // Safe: same-class access to protected member
      careStrategy(nullptr),  // Don't copy pointer; set to null (or clone if needed)
      state(nullptr) {  // Same for state
    // If observers need copying (from plan's Observer pattern):
    // observers = other.observers;  // Shallow copy of list
    
    // If you need deep copies of careStrategy/state (e.g., if they hold unique state):
    // Assume CareStrategy and PlantState have clone() methods (add if necessary):
    // if (other.careStrategy) careStrategy = other.careStrategy->clone();
    // if (other.state) state = other.state->clone();
}

void Plant::water(int amount) {
    int newWaterLevel = info.waterLevel + amount;
    info.waterLevel = std::max(0, std::min(100, newWaterLevel));
    std::cout << info.name << " watered by " << amount
              << " units. Current water level: " << info.waterLevel << "\n";

    if (info.waterLevel >= 40 && info.waterLevel <= 80) {
        info.healthLevel = std::min(100, info.healthLevel + 2);
    } else if (info.waterLevel > 90) {
        info.healthLevel = std::max(0, info.healthLevel - 3);  // Overwatering
    }
    notifyObservers("watered"); 
    checkHealth();
}

void Plant::fertilize(int amount) {
    int newNutrientLevel = info.nutrientLevel + amount;
    info.nutrientLevel = std::max(0, std::min(100, newNutrientLevel));
    std::cout << info.name << " fertilized by " << amount
              << " units. Nutrient level: " << info.nutrientLevel << "\n";

    if (info.nutrientLevel > 40) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.5);
    }
    notifyObservers("fertilized");
    checkHealth();
}

void Plant::addSunlight(int amount) {
    exposeToSunlight(amount);  // Alias for plan compatibility
}

void Plant::exposeToSunlight(int hours) {
    info.sunlightLevel += hours;  // Accumulate current exposure
    std::cout << info.name << " exposed to sunlight for " << hours << " hours.\n";

    if (hours < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 2);
    } else if (hours > info.sunlightNeed + 3) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
    } else {
        info.healthLevel = std::min(100, info.healthLevel + 1);
    }

    if (info.healthLevel > 70) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.2);
    }
    checkHealth();
}

void Plant::grow() {
    if (state) {
        state->grow(this);
    }
    info.currentAgeDays++;
    updateResourceLevels();  // From plan
    notifyObservers("grew");
    checkHealth();
}

void Plant::checkHealth() {
    // Example impl: check levels and transition state/notify
    if (info.healthLevel < 30) {
        if (state) state->handle(this);  // Assume state has handle() for transitions
    } else if (info.waterLevel < 20 || info.nutrientLevel < 20 || info.sunlightLevel < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
    }
    //notifyObservers("health check");  // Removed the call to avoid duplicates
}

void Plant::updateResourceLevels() {
    // Simulate daily decay (plan protected method)
    info.waterLevel = std::max(0, info.waterLevel - 5);
    info.sunlightLevel = 0;  // Reset daily?
    info.nutrientLevel = std::max(0, info.nutrientLevel - 2);
}

double Plant::calculateGrowthRate() {
    // Plan protected: example calculation
    return (info.healthLevel / 100.0) * (info.nutrientLevel / 50.0);
}

int Plant::getID() const { return std::stoi(info.id.substr(1)); }  // If needed as int

double Plant::getPrice() const { return info.salePrice; }

void Plant::setPrice(double price) { info.salePrice = price; }

std::string Plant::getName() const { return info.name; }

std::string Plant::getClassification() const { return info.classification; }

std::string Plant::getDate() const { return info.addedDate; }

int Plant::getWaterLevel() const { return info.waterLevel; }

void Plant::setWaterLevel(int level) { info.waterLevel = level; }

int Plant::getSunlightLevel() const { return info.sunlightLevel; }

void Plant::setSunlightLevel(int level) { info.sunlightLevel = level; }

int Plant::getHealthLevel() const { return info.healthLevel; }

void Plant::setHealthLevel(int level) { info.healthLevel = level; }

int Plant::getNutrientLevel() const { return info.nutrientLevel; }

void Plant::setNutrientLevel(int level) { info.nutrientLevel = level; }

int Plant::getAge() const { return info.currentAgeDays; }

void Plant::setAge(int newAge) { info.currentAgeDays = newAge; }

void Plant::printStatus() const {
    std::cout << "Plant: " << info.name << " (" << info.classification << ")\n"
              << "Health: " << info.healthLevel << ", Water: " << info.waterLevel
              << ", Sunlight: " << info.sunlightLevel << ", Nutrients: " << info.nutrientLevel
              << ", Age: " << info.currentAgeDays << " days\n";
    // Add more as needed
}