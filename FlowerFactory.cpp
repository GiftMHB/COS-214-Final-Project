#include "FlowerFactory.h"
#include <iostream>
/**
 * @note The variable is only visible in this .cpp file
 */
static int nextId = 1;

FlowerFactory::FlowerFactory()
    : PlantFactory()
{
}

Plant *FlowerFactory::createTree(PlantInfo &info, string treeType, double height, bool isEvergreen, double trunkDiameter)
{
    std::cout << "[FlowerFactory] Cannot create Tree.\n";
    return nullptr;
}

Plant *FlowerFactory::createVegetable(PlantInfo &info, string vegetableType, int harvestTime, double expectedYield, bool isEdible)
{
    std::cout << "[FlowerFactory] Cannot create Vegetable.\n";
    return nullptr;
}

Plant *FlowerFactory::createFlower(PlantInfo &info, string color, string bloomSeason, int petalCount, bool fragrance)
{

    if (info.classification == "Flower")
    {
        nextId++;
        return new Flower(info, color, bloomSeason, petalCount, fragrance);
    }
    else
    {
        std::cout << "[FlowerFactory] Unsupported plant type: " << info.classification << "\n";
        return nullptr;
    }
}

Plant *FlowerFactory::createPlant(PlantInfo &info, std::string type, string color, string bloomSeason, int petalCount, bool fragrance)
{
    if (type == "Flower")
    {
        return createFlower(info, color, bloomSeason, petalCount, fragrance);
    }
    else
    {
        std::cout << "[FlowerFactory] Unsupported plant type: " << type << "\n";
        return nullptr;
    }
}

Plant* FlowerFactory::createPlant(PlantInfo& info, string type, string treeType, double height, bool isEvergreen, double trunkDiameter) {
    std::cout << "[FlowerFactory] Cannot create Tree.\n";
    return nullptr;
}

Plant* FlowerFactory::createPlant(PlantInfo& info, string type, string vegetableType, int harvestTime, double expectedYield, bool isEdible) {
    std::cout << "[FlowerFactory] Cannot create Vegetable.\n";
    return nullptr;
}
