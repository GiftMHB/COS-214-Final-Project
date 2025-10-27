#include "Flower.h"

Flower::Flower(PlantInfo& info,string color,string bloomSeason,int petalCount,bool fragrance)
    : Plant(info), color(color), bloomSeason(bloomSeason), petalCount(petalCount), fragrance(fragrance)
{

}

Flower::~Flower()
{
    
}

std::string Flower::getColor()
{
    return color;
}

std::string Flower::getBloomSeason()
{
    return bloomSeason;
}

int Flower::getPetalCount()
{
    return petalCount;
}

bool Flower::hasFragrance()
{
    return fragrance;
}

std::string Flower::getDescription()
{
    return "Flower: " + info.name + ", Color: " + color + ", Bloom Season: " + bloomSeason +
           ", Petal Count: " + std::to_string(petalCount) + ", Fragrance: " + (fragrance ? "Yes" : "No");
}