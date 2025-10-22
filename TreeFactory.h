#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "PlantFactory.h"
#include "Tree.h"

/**
 * @file TreeFactory.h
 * @brief Concrete factory for creating Tree objects
 * @class TreeFactory
 * @brief Concrete factory class that creates Tree plants
 */
class TreeFactory : public PlantFactory {
    protected:
        Plant* createFlower(std::string name, double price);
        Plant* createTree(std::string name, double price);
        // Plant* createShrub(std::string name, double price);
        Plant* createVegetable(std::string name, double price);

    public:
        Plant* createPlant(std::string type, std::string name, double price) override;
};

#endif