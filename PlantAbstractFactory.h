/**
 * @file PlantAbstractFactory.h
 * @brief Abstract Factory pattern for creating plant families and related products
 */

#ifndef PLANT_ABSTRACT_FACTORY_H
#define PLANT_ABSTRACT_FACTORY_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "Plant.h"  // Include the complete plant hierarchy

/**
 * @brief Abstract factory interface for creating plant family products
 */
class PlantAbstractFactory {
public:
    virtual ~PlantAbstractFactory() = default;
    
    virtual Plant* createPlant(const std::string& name, const std::string& species, double price) = 0;
    virtual CareKit* createCareKit() = 0;
    virtual Soil* createSoil() = 0;
    virtual std::string getFactoryType() const = 0;
    virtual std::string getDescription() const = 0;
};

/**
 * @brief Concrete factory for creating flower family products
 */
class FlowerPlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const std::string& name, const std::string& species, double price) override;
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    std::string getFactoryType() const override;
    std::string getDescription() const override;
};

/**
 * @brief Concrete factory for creating tree family products
 */
class TreePlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const std::string& name, const std::string& species, double price) override;
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    std::string getFactoryType() const override;
    std::string getDescription() const override;
};

/**
 * @brief Factory provider and registry
 */
class PlantFactoryProvider {
private:
    static std::unique_ptr<PlantAbstractFactory> createFactory(const std::string& type);
    
public:
    static std::unique_ptr<PlantAbstractFactory> getFactory(const std::string& type);
    static std::vector<std::string> getSupportedFactories();
    static bool isFactorySupported(const std::string& type);
};

#endif // PLANT_ABSTRACT_FACTORY_H