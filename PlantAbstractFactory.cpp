/**
 * @file PlantAbstractFactory.cpp
 * @brief Abstract Factory pattern implementation for plant families
 */

#include "PlantAbstractFactory.h"
#include "ConcretePlant.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

// ============================================================================
// FACTORY IMPLEMENTATIONS
// ============================================================================

// Flower Factory implementations
Plant* FlowerPlantFactory::createPlant(const std::string& name, const std::string& species, double price) {
    if (name.empty() || species.empty()) {
        throw std::invalid_argument("Plant name and species cannot be empty");
    }
    if (price <= 0) {
        throw std::invalid_argument("Plant price must be positive");
    }
    
    std::cout << "🌸 FlowerFactory: Creating '" << name << "' (" << species 
              << ") priced at $" << std::fixed << std::setprecision(2) << price << std::endl;
    
    // Use our concrete Plant implementation
    return new ConcretePlant(name, species, price);
}

CareKit* FlowerPlantFactory::createCareKit() {
    std::cout << "🛠️  FlowerFactory: Care kits not available with unified Plant system\n";
    return nullptr;
}

Soil* FlowerPlantFactory::createSoil() {
    std::cout << "🌱 FlowerFactory: Soil not available with unified Plant system\n";
    return nullptr;
}

std::string FlowerPlantFactory::getFactoryType() const {
    return "Flower";
}

std::string FlowerPlantFactory::getDescription() const {
    return "Specialized factory for creating flowering plants using unified Plant system.";
}

// Tree Factory implementations
Plant* TreePlantFactory::createPlant(const std::string& name, const std::string& species, double price) {
    if (name.empty() || species.empty()) {
        throw std::invalid_argument("Plant name and species cannot be empty");
    }
    if (price <= 0) {
        throw std::invalid_argument("Plant price must be positive");
    }
    
    std::cout << "🌳 TreeFactory: Creating '" << name << "' (" << species 
              << ") priced at $" << std::fixed << std::setprecision(2) << price << std::endl;
    
    // Use our concrete Plant implementation
    return new ConcretePlant(name, species, price);
}

CareKit* TreePlantFactory::createCareKit() {
    std::cout << "🛠️  TreeFactory: Care kits not available with unified Plant system\n";
    return nullptr;
}

Soil* TreePlantFactory::createSoil() {
    std::cout << "🌱 TreeFactory: Soil not available with unified Plant system\n";
    return nullptr;
}

std::string TreePlantFactory::getFactoryType() const {
    return "Tree";
}

std::string TreePlantFactory::getDescription() const {
    return "Specialized factory for creating trees using unified Plant system.";
}

// ============================================================================
// FACTORY PROVIDER IMPLEMENTATION
// ============================================================================

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