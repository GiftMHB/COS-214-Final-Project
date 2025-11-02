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
class TreeFactory : public PlantFactory
{
    protected:
        Plant *createFlower(PlantInfo &info, string color, string bloomSeason, int petalCount, bool fragrance);
        Plant *createTree(PlantInfo &info, string treeType, double height, bool isEvergreen, double trunkDiameter);
        Plant *createVegetable(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible);

    public:
        TreeFactory();
        Plant* createPlant(PlantInfo& info, string type, string treeType, double height, bool isEvergreen, double trunkDiameter) override;

        Plant* createPlant(PlantInfo& info, string type, string color, string bloomSeason, int petalCount, bool fragrance) override;
        Plant* createPlant(PlantInfo& info, string type, string vegetableType, int harvestTime, double expectedYield, bool isEdible) override;
};

#endif