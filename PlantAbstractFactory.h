#ifndef PLANTABSTRACTFACTORY_H
#define PLANTABSTRACTFACTORY_H

#include <string>
#include "Plant.h"
#include "CareKit.h"
#include "Soil.h"

using namespace std;

/**
 * @brief Abstract Factory interface for creating families of related garden objects
 * 
 * This factory creates complete plant packages including the plant itself,
 * its care kit, and appropriate soil type. Ensures all components work together
 * harmoniously for specific plant types (Flowers, Trees, etc.).
 */
class PlantAbstractFactory {
public:
    virtual ~PlantAbstractFactory() {}
    
    /**
     * @brief Creates a plant instance with specific type and attributes
     * @param name The common name of the plant (e.g., "Red Rose")
     * @param species The scientific species name
     * @param price The selling price of the plant
     * @return Pointer to the created Plant object
     */
    virtual Plant* createPlant(const string& name, 
                              const string& species, 
                              double price) = 0;
    
    /**
     * @brief Creates a care kit suitable for the plant type
     * @return Pointer to the created CareKit object
     */
    virtual CareKit* createCareKit() = 0;
    
    /**
     * @brief Creates soil optimized for the plant type
     * @return Pointer to the created Soil object
     */
    virtual Soil* createSoil() = 0;
    
    /**
     * @brief Gets the plant type this factory creates
     * @return String representing the plant type
     */
    virtual string getFactoryType() const = 0;
};

/**
 * @brief Concrete Factory for creating Flower plants and accessories
 */
class FlowerPlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const string& name, 
                      const string& species, 
                      double price) override;
    
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    string getFactoryType() const override;
};

/**
 * @brief Concrete Factory for creating Tree plants and accessories
 */
class TreePlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const string& name, 
                      const string& species, 
                      double price) override;
    
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    string getFactoryType() const override;
};

/**
 * @brief Concrete Factory for creating Shrub plants and accessories
 */
class ShrubPlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const string& name, 
                      const string& species, 
                      double price) override;
    
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    string getFactoryType() const override;
};

/**
 * @brief Concrete Factory for creating Vegetable plants and accessories
 */
class VegetablePlantFactory : public PlantAbstractFactory {
public:
    Plant* createPlant(const string& name, 
                      const string& species, 
                      double price) override;
    
    CareKit* createCareKit() override;
    Soil* createSoil() override;
    string getFactoryType() const override;
};

#endif // PLANTABSTRACTFACTORY_H