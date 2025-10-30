#include "Vegetable.h"

Vegetable::Vegetable(PlantInfo& info,int harvestTime,double yield,string vegetableType,bool isEdible)
    : Plant(info), harvestTime(harvestTime), yield(yield), vegetableType(vegetableType), isEdible(isEdible)
{

}

Vegetable::~Vegetable()
{
    
}

int Vegetable::getHarvestTime()
{
    return harvestTime;
}

double Vegetable::harvest()
{
    if (isReadyToHarvest())
    {
        double harvestedYield = yield;
        yield = 0; 
        return harvestedYield;
    }
    return 0.0; 
}

bool Vegetable::isReadyToHarvest(){
    return yield > 0;
}

std::string Vegetable::getDescription(){
    return "Vegetable: " + info.name + ", Type: " + vegetableType;
}