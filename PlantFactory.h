#ifndef PLANT_FACTORY_H
#define PLANT_FACTORY_H

#include "Plant.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declarations
class CareKit;
class Soil;

class PlantFactory {
public:
    virtual ~PlantFactory() = default;
    virtual Plant* createPlant(const std::string& name, const std::string& species, double price) = 0;
    virtual CareKit* createCareKit() = 0;
    virtual Soil* createSoil() = 0;
    virtual std::string getFactoryType() const = 0;
    virtual std::string getDescription() const = 0;
};

class PlantFactoryProvider {
public:
    static std::unique_ptr<PlantFactory> createFactory(const std::string& type);
    static std::vector<std::string> getSupportedFactories();
    static bool isFactorySupported(const std::string& type);
};

#endif