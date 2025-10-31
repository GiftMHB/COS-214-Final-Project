/**
 * @file PlantAbstractFactory.cpp
 * @brief Implementation of Abstract Factory pattern for plant families
 */

#include "PlantAbstractFactory.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>

// Flower Factory implementations
Plant* FlowerPlantFactory::createPlant(const std::string& name, const std::string& species, double price) {
    if (name.empty() || species.empty()) {
        throw std::invalid_argument("Plant name and species cannot be empty");
    }
    if (price <= 0) {
        throw std::invalid_argument("Plant price must be positive");
    }
    
    // For demonstration, create flowers with some default properties
    std::string color = "Various";
    std::string bloomSeason = "Spring-Summer";
    bool isFragrant = true;
    
    std::cout << "🌸 FlowerFactory: Creating '" << name << "' (" << species 
              << ") priced at $" << std::fixed << std::setprecision(2) << price << std::endl;
    
    return new Flower(name, species, price, color, bloomSeason, isFragrant);
}

CareKit* FlowerPlantFactory::createCareKit() {
    std::cout << "🛠️  FlowerFactory: Creating comprehensive flower care kit\n";
    return new FlowerCareKit();
}

Soil* FlowerPlantFactory::createSoil() {
    std::cout << "🌱 FlowerFactory: Creating optimal well-draining potting soil\n";
    return new FlowerSoil();
}

std::string FlowerPlantFactory::getFactoryType() const {
    return "Flower";
}

std::string FlowerPlantFactory::getDescription() const {
    return "Specialized factory for creating flowering plants and their care products. "
           "Produces annuals, perennials, and flowering shrubs with appropriate soil "
           "and maintenance kits optimized for bloom production.";
}

// Tree Factory implementations
Plant* TreePlantFactory::createPlant(const std::string& name, const std::string& species, double price) {
    if (name.empty() || species.empty()) {
        throw std::invalid_argument("Plant name and species cannot be empty");
    }
    if (price <= 0) {
        throw std::invalid_argument("Plant price must be positive");
    }
    
    // Default tree properties
    double height = 1.5;
    double trunkDiameter = 0.15;
    std::string treeType = "Ornamental";
    bool isEvergreen = false;
    
    std::cout << "🌳 TreeFactory: Creating '" << name << "' (" << species 
              << ") priced at $" << std::fixed << std::setprecision(2) << price << std::endl;
    
    return new Tree(name, species, price, height, trunkDiameter, treeType, isEvergreen);
}

CareKit* TreePlantFactory::createCareKit() {
    std::cout << "🛠️  TreeFactory: Creating comprehensive tree care kit\n";
    return new TreeCareKit();
}

Soil* TreePlantFactory::createSoil() {
    std::cout << "🌱 TreeFactory: Creating nutrient-rich garden soil\n";
    return new TreeSoil();
}

std::string TreePlantFactory::getFactoryType() const {
    return "Tree";
}

std::string TreePlantFactory::getDescription() const {
    return "Specialized factory for creating trees and their care products. "
           "Produces deciduous, evergreen, and ornamental trees with deep-root "
           "soil formulations and long-term maintenance kits.";
}

// Factory Provider implementation
std::unique_ptr<PlantAbstractFactory> PlantFactoryProvider::createFactory(const std::string& type) {
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    if (lowerType == "flower") {
        return std::unique_ptr<PlantAbstractFactory>(new FlowerPlantFactory());
    } else if (lowerType == "tree") {
        return std::unique_ptr<PlantAbstractFactory>(new TreePlantFactory());
    }
    
    throw std::invalid_argument("Unsupported factory type: " + type);
}

std::unique_ptr<PlantAbstractFactory> PlantFactoryProvider::getFactory(const std::string& type) {
    return createFactory(type);
}

std::vector<std::string> PlantFactoryProvider::getSupportedFactories() {
    return {"flower", "tree"};
}

bool PlantFactoryProvider::isFactorySupported(const std::string& type) {
    auto supported = getSupportedFactories();
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    return std::find(supported.begin(), supported.end(), lowerType) != supported.end();
}