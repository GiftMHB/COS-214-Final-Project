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
        Plant* createFlower(PlantInfo& info,string color,string bloomSeason,int petalCount,bool fragrance);
        Plant* createTree(PlantInfo& info,string treeType,double height,bool isEvergreen,double trunkDiameter);
        Plant* createVegetable(PlantInfo& info,string vegetableType,int harvestTime,double expectedYield,bool isEdible);

    public:
        FlowerFactory();
        Plant* createPlant(PlantInfo& info, string type, string color, string bloomSeason, int petalCount, bool fragrance) override;

        Plant* createPlant(PlantInfo& info, string type, string treeType, double height, bool isEvergreen, double trunkDiameter) override;
        Plant* createPlant(PlantInfo& info, string type, string vegetableType, int harvestTime, double expectedYield, bool isEdible) override;
};

#endif 