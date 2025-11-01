#include "Plant.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <sstream>

// Static counters for both ID systems
int PlantInfo::plantCount = 0;
static int plantIdCounter = 1000;  // YOUR ID counter

// === THEIR CONSTRUCTORS ===

Plant::Plant(PlantInfo& pInfo) : info(pInfo), careStrategy(nullptr), state(nullptr) {
    if (info.id.empty()) {
        info.id = "P" + std::to_string(++PlantInfo::plantCount);
    }
    if (info.addedDate.empty()) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                         std::to_string(1 + ltm->tm_mon) + "-" +
                         std::to_string(ltm->tm_mday);
    }
    if (info.species.empty()) {
        info.species = info.classification;
    }
}

Plant::Plant(const std::string& name, const std::string& classification, double price) 
    : careStrategy(nullptr), state(nullptr) {
    // THEIR ID system
    info.id = "P" + std::to_string(++PlantInfo::plantCount);
    info.name = name;
    info.classification = classification;
    info.species = classification;
    info.salePrice = price;
    info.purchasePrice = price * 0.7;
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                     std::to_string(1 + ltm->tm_mon) + "-" +
                     std::to_string(ltm->tm_mday);
}

// === YOUR CONSTRUCTOR (added to their class) ===

Plant::Plant(const std::string& plantName, const std::string& plantSpecies)
    : careStrategy(nullptr), state(nullptr) {
    // YOUR ID system
    std::stringstream ss;
    ss << "P" << plantIdCounter++;
    info.id = ss.str();
    
    info.name = plantName;
    info.species = plantSpecies;
    info.classification = plantSpecies;
    info.salePrice = 0.0;  // YOUR default
    info.purchasePrice = 0.0;
    info.waterLevel = 50;  // YOUR default
    info.nutrientLevel = 50;  // YOUR default
    info.healthLevel = 100;  // YOUR equivalent
    info.isAlive = true;  // YOUR field
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                     std::to_string(1 + ltm->tm_mon) + "-" +
                     std::to_string(ltm->tm_mday);
}

Plant::Plant(const Plant& other)
    : Subject(other), info(other.info), careStrategy(nullptr), state(nullptr) {
    // Copy logic
}

Plant::~Plant() {
    //delete careStrategy;
    delete state;
}

// === YOUR METHODS (added to their class) ===

void Plant::changeState(PlantState* newState) {
    if (newState != nullptr) {
        // YOUR logic
        delete state;  // Clean up old state
        state = newState;
        notify("state_changed");
    }
}

double Plant::getHealth() const {
    // YOUR method: returns double instead of int
    return static_cast<double>(info.healthLevel);
}

bool Plant::getIsAlive() const {
    // YOUR method
    return info.isAlive;
}

// === THEIR METHODS (keep all their logic) ===

std::string Plant::getId() const { 
    return info.id; 
}

std::string Plant::getName() const { 
    return info.name; 
}

std::string Plant::getSpecies() const { 
    return info.species; 
}

std::string Plant::getClassification() const { 
    return info.classification; 
}

std::string Plant::getDate() const { 
    return info.addedDate; 
}

double Plant::getPrice() const { 
    return info.salePrice; 
}

void Plant::setPrice(double price) { 
    info.salePrice = price; 
}

double Plant::getSalePrice() const { 
    return info.salePrice; 
}

PlantState* Plant::getState() const { 
    return state; 
}

void Plant::setState(PlantState* newState) { 
    if (state != newState) {
        delete state;
        state = newState;
        notify("state_changed");
    }
}

std::string Plant::getCurrentStateName() const {
    return state ? state->getStateName() : "Unknown";
}

int Plant::getHealthPercentage() const {
    // THEIR method: returns int
    return info.healthLevel;
}

void Plant::setCareStrategy(CareStrategy* strategy) {
    if (careStrategy != strategy) {
        //delete careStrategy;
        careStrategy = strategy;
    }
}

void Plant::applyCare() {
    if (careStrategy) {
        careStrategy->applyCare(this);
        notifyCareApplied("care_applied");
    }
}

std::string Plant::getCareStrategyName() const {
    return careStrategy ? careStrategy->getStrategyName() : "No Strategy";
}

int Plant::getWaterLevel() const { 
    return info.waterLevel; 
}

void Plant::setWaterLevel(int level) { 
    info.waterLevel = std::max(0, std::min(100, level)); 
}

int Plant::getSunlightLevel() const { 
    return info.sunlightLevel; 
}

void Plant::setSunlightLevel(int level) { 
    info.sunlightLevel = std::max(0, level); 
}

void Plant::setHealthLevel(int level) { 
    // THEIR method: takes int
    info.healthLevel = std::max(0, std::min(100, level));
    if (info.healthLevel <= 0) {
        info.isAlive = false;  // Update YOUR field
    }
    notifyHealthChange();
}

int Plant::getNutrientLevel() const { 
    return info.nutrientLevel; 
}

void Plant::setNutrientLevel(int level) { 
    info.nutrientLevel = std::max(0, std::min(100, level)); 
}

int Plant::getAge() const { 
    return info.currentAgeDays; 
}

void Plant::setAge(int newAge) { 
    info.currentAgeDays = newAge; 
}

double Plant::getCurrentHeight() const { 
    return info.currentHeight; 
}

double Plant::getMaturityHeight() const { 
    return info.maturityHeight; 
}

void Plant::setCurrentHeight(double height) { 
    info.currentHeight = height; 
}

void Plant::water(int amount) {
    // THEIR logic with YOUR isAlive check
    if (!info.isAlive) {
        std::cout << info.name << " is dead and cannot be watered." << std::endl;
        return;
    }

    int newWaterLevel = info.waterLevel + amount;
    info.waterLevel = std::max(0, std::min(100, newWaterLevel));
    
    std::cout << info.name << " watered by " << amount
              << " units. Current water level: " << info.waterLevel << "\n";

    // THEIR health impact logic
    if (info.waterLevel >= 40 && info.waterLevel <= 80) {
        info.healthLevel = std::min(100, info.healthLevel + 2);
    } else if (info.waterLevel > 90) {
        info.healthLevel = std::max(0, info.healthLevel - 3);
    }
    
    // Update YOUR isAlive field
    if (info.healthLevel <= 0) {
        info.isAlive = false;
    }
    
    notifyCareApplied("watered");
    checkHealth();
}

void Plant::fertilize(int amount) {
    // THEIR logic with YOUR isAlive check
    if (!info.isAlive) {
        std::cout << info.name << " is dead and cannot be fertilized." << std::endl;
        return;
    }

    int newNutrientLevel = info.nutrientLevel + amount;
    info.nutrientLevel = std::max(0, std::min(100, newNutrientLevel));
    
    std::cout << info.name << " fertilized by " << amount
              << " units. Nutrient level: " << info.nutrientLevel << "\n";

    // THEIR growth impact
    if (info.nutrientLevel > 40) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.5);
    }
    
    // Update YOUR isAlive field
    if (info.healthLevel <= 0) {
        info.isAlive = false;
    }
    
    notifyCareApplied("fertilized");
    checkHealth();
}

void Plant::addSunlight(int amount) {
    exposeToSunlight(amount);
}

void Plant::exposeToSunlight(int hours) {
    info.sunlightLevel += hours;
    std::cout << info.name << " exposed to sunlight for " << hours << " hours.\n";

    // THEIR health impact
    if (hours < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 2);
    } else if (hours > info.sunlightNeed + 3) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
    } else {
        info.healthLevel = std::min(100, info.healthLevel + 1);
    }

    // THEIR growth impact
    if (info.healthLevel > 70) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.2);
    }
    
    // Update YOUR isAlive field
    if (info.healthLevel <= 0) {
        info.isAlive = false;
    }
    
    notifyCareApplied("sunlight_added");
    checkHealth();
}

void Plant::grow() {
    if (state) {
        state->grow(this);
    }
    info.currentAgeDays++;
    updateResourceLevels();
    notifyGrowth();
    checkHealth();
}

void Plant::checkHealth() {
    // THEIR health checking logic
    if (info.healthLevel < 30) {
        if (state) {
            state->handle(this);
        }
        notify("health_critical");
    } else if (info.waterLevel < 20 || info.nutrientLevel < 20 || info.sunlightLevel < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
        notifyHealthChange();
    }
    
    // Update YOUR isAlive field
    if (info.healthLevel <= 0) {
        info.isAlive = false;
        notify("plant_died");
    }
    
    // Update ready for sale status
    bool wasReady = info.readyForSale;
    info.readyForSale = (info.healthLevel > 70 && info.currentAgeDays > 30);
    
    if (info.readyForSale && !wasReady) {
        notify("ready_for_sale");
    }
}

std::string Plant::getDescription() const {
    return info.name + " (" + info.species + ") - " + std::to_string(info.healthLevel) + "% healthy";
}

bool Plant::isReadyForSale() const {
    // Combined logic: THEIR criteria + YOUR isAlive check
    return info.isAlive && info.healthLevel > 70 && info.currentAgeDays > 30;
}

void Plant::setReadyForSale(bool ready) {
    info.readyForSale = ready;
}

void Plant::printStatus() const {
    std::cout << "Plant: " << info.name << " (" << info.species << ")\n"
              << "ID: " << info.id << ", Health: " << info.healthLevel 
              << "%, Water: " << info.waterLevel
              << ", Sunlight: " << info.sunlightLevel << ", Nutrients: " << info.nutrientLevel
              << ", Age: " << info.currentAgeDays << " days\n"
              << "Height: " << info.currentHeight << "/" << info.maturityHeight
              << ", Alive: " << (info.isAlive ? "Yes" : "No")
              << ", Ready for sale: " << (info.readyForSale ? "Yes" : "No") << "\n";
}

// === PROTECTED METHODS ===

void Plant::updateResourceLevels() {
    info.waterLevel = std::max(0, info.waterLevel - 5);
    info.sunlightLevel = 0;
    info.nutrientLevel = std::max(0, info.nutrientLevel - 2);
}

double Plant::calculateGrowthRate() {
    return (info.healthLevel / 100.0) * (info.nutrientLevel / 50.0);
}

void Plant::notifyHealthChange() {
    if (info.healthLevel < 30) {
        notify("health_low");
    } else if (info.healthLevel > 80) {
        notify("health_good");
    }
}

void Plant::notifyGrowth() {
    notify("grew");
    if (info.currentHeight >= info.maturityHeight * 0.8) {
        notify("nearing_maturity");
    }
}

void Plant::notifyCareApplied(const std::string& careType) {
    notify(careType);
}