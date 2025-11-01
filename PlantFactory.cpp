#include "PlantFactory.h"
#include "ConcretePlant.h"
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iostream>

// Implement the concrete factories here in the cpp file
class FlowerFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, const std::string& species, double price) override {
        std::cout << "🌸 FlowerFactory: Creating '" << name << "' (" << species 
                  << ") priced at $" << price << std::endl;
        return new ConcretePlant(name, species, price);
    }
    
    CareKit* createCareKit() override {
        std::cout << "🛠️  FlowerFactory: Care kits not available\n";
        return nullptr;
    }
    
    Soil* createSoil() override {
        std::cout << "🌱 FlowerFactory: Soil not available\n";
        return nullptr;
    }
    
    std::string getFactoryType() const override {
        return "Flower";
    }
    
    std::string getDescription() const override {
        return "Specialized factory for creating flowering plants";
    }
};

class TreeFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, const std::string& species, double price) override {
        std::cout << "🌳 TreeFactory: Creating '" << name << "' (" << species 
                  << ") priced at $" << price << std::endl;
        return new ConcretePlant(name, species, price);
    }
    
    CareKit* createCareKit() override {
        std::cout << "🛠️  TreeFactory: Care kits not available\n";
        return nullptr;
    }
    
    Soil* createSoil() override {
        std::cout << "🌱 TreeFactory: Soil not available\n";
        return nullptr;
    }
    
    std::string getFactoryType() const override {
        return "Tree";
    }
    
    std::string getDescription() const override {
        return "Specialized factory for creating trees";
    }
};

class VegetableFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, const std::string& species, double price) override {
        std::cout << "🥕 VegetableFactory: Creating '" << name << "' (" << species 
                  << ") priced at $" << price << std::endl;
        return new ConcretePlant(name, species, price);
    }
    
    CareKit* createCareKit() override {
        std::cout << "🛠️  VegetableFactory: Care kits not available\n";
        return nullptr;
    }
    
    Soil* createSoil() override {
        std::cout << "🌱 VegetableFactory: Soil not available\n";
        return nullptr;
    }
    
    std::string getFactoryType() const override {
        return "Vegetable";
    }
    
    std::string getDescription() const override {
        return "Specialized factory for creating vegetables";
    }
};

// Now implement the provider
std::unique_ptr<PlantFactory> PlantFactoryProvider::createFactory(const std::string& type) {
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    if (lowerType == "flower") {
        return std::unique_ptr<PlantFactory>(new FlowerFactory());
    } else if (lowerType == "tree") {
        return std::unique_ptr<PlantFactory>(new TreeFactory());
    } else if (lowerType == "vegetable") {
        return std::unique_ptr<PlantFactory>(new VegetableFactory());
    }
    
    throw std::invalid_argument("Unsupported factory type: " + type);
}

std::vector<std::string> PlantFactoryProvider::getSupportedFactories() {
    return {"flower", "tree", "vegetable"};
}

bool PlantFactoryProvider::isFactorySupported(const std::string& type) {
    auto supported = getSupportedFactories();
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    return std::find(supported.begin(), supported.end(), lowerType) != supported.end();
}