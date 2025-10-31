//Here is my Plant.cpp - TIEGO MOKWENA
/**
 * @file Plant.cpp
 * @brief Implementation of the Plant concrete subject class
 */

#include "Plant.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>


static int plantIdCounter = 1000;

Plant::Plant(const std::string& plantName, const std::string& plantSpecies)
    : name(plantName), species(plantSpecies), classification("Unknown"),
      price(0.0), waterLevel(50), nutrientLevel(50), health(100.0),
      isAlive(true), currentState(nullptr), careStrategy(nullptr) {
    
    
    std::stringstream ss;
    ss << "P" << plantIdCounter++;
    id = ss.str();
}

Plant::~Plant() {
    // Note: State and Strategy are managed by other systems done by my teammates
    
}

void Plant::water(int amount) {
    if (!isAlive) {
        std::cout << name << " is dead and cannot be watered." << std::endl;
        return;
    }

    waterLevel += amount;
    if (waterLevel > 100) {
        waterLevel = 100;
    }

    
    if (waterLevel > 80) {
        health += 5.0;
    } else if (waterLevel < 20) {
        health -= 10.0;
    }

    if (health > 100.0) health = 100.0;
    if (health < 0.0) {
        health = 0.0;
        isAlive = false;
    }

    
    notify("watered");

    if (health < 30.0) {
        notify("health_low");
    }
}

void Plant::fertilize(int amount) {
    if (!isAlive) {
        std::cout << name << " is dead and cannot be fertilized." << std::endl;
        return;
    }

    nutrientLevel += amount;
    if (nutrientLevel > 100) {
        nutrientLevel = 100;
    }

    
    if (nutrientLevel > 70) {
        health += 8.0;
    } else if (nutrientLevel < 30) {
        health -= 5.0;
    }

    if (health > 100.0) health = 100.0;
    if (health < 0.0) {
        health = 0.0;
        isAlive = false;
    }

    
    notify("fertilized");

    if (health < 30.0) {
        notify("health_low");
    }
}

void Plant::applyCare() {
    if (careStrategy != nullptr) {
        // Care strategy would call water/fertilize with appropriate amounts
        // This is a placeholder for strategy pattern integration
        notify("care_applied");
    }
}

void Plant::changeState(PlantState* newState) {
    if (newState != nullptr) {
        currentState = newState;
        notify("state_changed");
    }
}

double Plant::getHealth() const {
    return health;
}

bool Plant::isReadyForSale() const {
    return isAlive && health >= 70.0 && waterLevel >= 40 && nutrientLevel >= 40;
}

std::string Plant::getId() const {
    return id;
}

std::string Plant::getName() const {
    return name;
}

std::string Plant::getSpecies() const {
    return species;
}

int Plant::getWaterLevel() const {
    return waterLevel;
}

int Plant::getNutrientLevel() const {
    return nutrientLevel;
}

void Plant::setPrice(double newPrice) {
    price = newPrice;
}

double Plant::getPrice() const {
    return price;
}

bool Plant::getIsAlive() const {
    return isAlive;
}
