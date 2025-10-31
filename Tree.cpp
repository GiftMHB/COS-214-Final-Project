#include "Tree.h"

Tree::Tree(PlantInfo& info,std::string treeType,double height,bool isEvergreen,double trunkDiameter)
    : Plant(info), treeType(treeType), height(height), isEvergreen(isEvergreen), trunkDiameter(trunkDiameter)
{

}  

Tree::~Tree()
{
    
}

double Tree::getHeight()
{
    return height;
}

std::string Tree::getDescription() const 
{
    return "Tree: " + info.name + ", Type: " + treeType + ", Height: " + std::to_string(height) +
           ", Evergreen: " + (isEvergreen ? "Yes" : "No") + ", Trunk Diameter: " + std::to_string(trunkDiameter);
}

double Tree::getTrunkDiameter()
{
    return trunkDiameter;
}

void Tree::prune()
{
    // Simple pruning logic: reduce height by 10% and trunk diameter by 5%
    height *= 0.9;
    trunkDiameter *= 0.95;
}

