#include "TreeFactory.h"
#include <iostream>

TreeFactory::TreeFactory()
{
    
}

Plant *TreeFactory::createFlower(PlantInfo &info, string color, string bloomSeason, int petalCount, bool fragrance)
{
    std::cout << "[TreeFactory] Cannot create Flower.\n";
    return nullptr;
}

Plant *TreeFactory::createVegetable(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible)
{
    std::cout << "[TreeFactory] Cannot create Vegetable.\n";
    return nullptr;
}

Plant *TreeFactory::createTree(PlantInfo &info, string treeType, double height, bool isEvergreen, double trunkDiameter)
{
    if (info.classification == "Tree")
    {
        return new Tree(info, treeType, height, isEvergreen, trunkDiameter);
    }
    else
    {
        std::cout << "[TreeFactory] Unsupported plant classification: " << info.classification << "\n";
        return nullptr;
    }
}

Plant *TreeFactory::createPlant(PlantInfo& info, string type, string treeType, double height, bool isEvergreen, double trunkDiameter)
{
    if (info.classification == "Tree")
    {
        return createTree(info, treeType, height, isEvergreen, trunkDiameter);
    }
    else
    {
        std::cout << "[TreeFactory] Unsupported plant classification: " << info.classification << "\n";
        return nullptr;
    }
}

Plant* TreeFactory::createPlant(PlantInfo& info, string type, string color, string bloomSeason, int petalCount, bool fragrance) {
    std::cout << "[TreeFactory] Cannot create Flower.\n";
    return nullptr;
}

Plant* TreeFactory::createPlant(PlantInfo& info, string type, string vegetableType, int harvestTime, double expectedYield, bool isEdible) {
    std::cout << "[TreeFactory] Cannot create Vegetable.\n";
    return nullptr;
}