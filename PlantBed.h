#ifndef PLANT_BED_H
#define PLANT_BED_H

#include "GardenComponent.h"
#include <list>
#include <string>

class Plant; //Forward declaration

class PlantBed : public GardenComponent {
private:
    std::list<Plant*> plants;

public:
    void assignPlant(Plant* plants);
    Plant* getPlant();
    void display(int depth);
    int getPlantCount();
};

#endif // PLANT_BED_H
