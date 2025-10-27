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
        Plant *createFlower(PlantInfo &info, string color, string bloomSeason, int petalCount, bool fragrance);
        Plant *createTree(PlantInfo &info, string treeType, double height, bool isEvergreen, double trunkDiameter);
        Plant *createVegetable(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible);

    public:
        Plant *createPlant(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible);
};

#endif 