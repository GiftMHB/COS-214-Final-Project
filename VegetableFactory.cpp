#include "VegetableFactory.h"
#include <iostream>

VegetableFactory::VegetableFactory()
    : PlantFactory()
{
}

Plant *VegetableFactory::createFlower(PlantInfo &info, string color, string bloomSeason, int petalCount, bool fragrance)
{
    std::cout << "[VegetableFactory] Cannot create Flower.\n";
    return nullptr;
}

Plant *VegetableFactory::createTree(PlantInfo &info, string treeType, double height, bool isEvergreen, double trunkDiameter)
{
    std::cout << "[VegetableFactory] Cannot create Tree.\n";
    return nullptr;
}

Plant *VegetableFactory::createVegetable(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible)
{
    if (info.classification == "Vegetable")
    {
        return new Vegetable(info, harvestTime, expectedYield, vegetableType, isEdible);
    }
    else
    {
        std::cout << "[VegetableFactory] Unsupported plant classification: " << info.classification << "\n";
        return nullptr;
    }
}

Plant *VegetableFactory::createPlant(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible)
{
    if (info.classification == "Vegetable")
    {
        return createVegetable(info, vegetableType, harvestTime, expectedYield, isEdible);
    }
    else
    {
        std::cout << "[VegetableFactory] Unsupported plant classification: " << info.classification << "\n";
        return nullptr;
    }
}
