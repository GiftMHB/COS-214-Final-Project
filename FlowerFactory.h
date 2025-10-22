#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H

#include "PlantFactory.h"
#include "Flower.h"

/**
 * @file FlowerFactory.h
 * @brief Concrete factory for creating Flower objects
 * @class FlowerFactory
 * @brief Concrete factory class that creates Flower plants
 */
class FlowerFactory : public PlantFactory {
    protected:
        Plant* createFlower(std::string name, double price);
        Plant* createTree(std::string name, double price);
        // Plant* createShrub(std::string name, double price);
        Plant* createVegetable(std::string name, double price);

    public:
        Plant* createPlant(std::string type, std::string name, double price) override;
};

#endif 