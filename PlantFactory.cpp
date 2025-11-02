/**
 * @file PlantFactory.cpp
 * @brief Implements concrete plant factories and the PlantFactoryProvider.
 */

#include "PlantFactory.h"
#include "ConcretePlant.h"
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iostream>

/**
 * @class FlowerFactory
 * @brief Concrete factory for creating flowering plants.
 */
class FlowerFactory : public PlantFactory {
public:
    /**
     * @brief Creates a new flowering plant.
     * @param name Name of the plant.
     * @param species Species/classification of the plant.
     * @param price Price of the plant.
     * @return Pointer to the created Plant object.
     */
    Plant* createPlant(const std::string& name, const std::string& species, double price) override {
        std::cout << "🌸 FlowerFactory: Creating '" << name << "' (" << species 
                  << ") priced at $" << price << std::endl;
        return new ConcretePlant(name, species, price);
    }

    /**
     * @brief Creates a care kit for flowering plants.
     * @return Always returns nullptr (not implemented).
     */
    CareKit* createCareKit() override {
        std::cout << "🛠️  FlowerFactory: Care kits not available\n";
        return nullptr;
    }

    /**
     * @brief Creates soil for flowering plants.
     * @return Always returns nullptr (not implemented).
     */
    Soil* createSoil() override {
        std::cout << "🌱 FlowerFactory: Soil not available\n";
        return nullptr;
    }

    /**
     * @brief Returns the factory type.
     * @return "Flower".
     */
    std::string getFactoryType() const override {
        return "Flower";
    }

    /**
     * @brief Returns a description of the factory.
     * @return Description string.
     */
    std::string getDescription() const override {
        return "Specialized factory for creating flowering plants";
    }
};

/**
 * @class TreeFactory
 * @brief Concrete factory for creating trees.
 */
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

/**
 * @class VegetableFactory
 * @brief Concrete factory for creating vegetables.
 */
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

/**
 * @brief Creates a factory based on the type string.
 * @param type The type of factory ("flower", "tree", "vegetable").
 * @return std::unique_ptr to the created factory.
 * @throws std::invalid_argument if the type is unsupported.
 */
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

/**
 * @brief Returns a list of supported factory types.
 * @return Vector of supported factory strings.
 */
std::vector<std::string> PlantFactoryProvider::getSupportedFactories() {
    return {"flower", "tree", "vegetable"};
}

/**
 * @brief Checks if a factory type is supported.
 * @param type The factory type string.
 * @return True if supported, false otherwise.
 */
bool PlantFactoryProvider::isFactorySupported(const std::string& type) {
    auto supported = getSupportedFactories();
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    return std::find(supported.begin(), supported.end(), lowerType) != supported.end();
}
