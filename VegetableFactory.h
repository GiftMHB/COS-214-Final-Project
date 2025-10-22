#ifndef VEGETABLEFACTORY_H
#define VEGETABLEFACTORY_H

#include "PlantFactory.h"
#include "Vegetable.h"

/**
 * @file VegetableFactory.h
 * @brief Concrete factory for creating Vegetable objects
 * @class VegetableFactory
 * @brief Concrete factory class that creates Vegetable plants
 */
class VegetableFactory : public PlantFactory {
    protected:
        Plant* createFlower(std::string name, double price);
        Plant* createTree(std::string name, double price);
        // Plant* createShrub(std::string name, double price);
        Plant* createVegetable(std::string name, double price);

    public:
        Plant* createPlant(std::string type, std::string name, double price) override;
};

#endif 