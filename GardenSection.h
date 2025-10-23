#ifndef GARDEN_SECTION_H
#define GARDEN_SECTION_H

#include "GardenComponent.h"
#include "Plant.h"
#include <vector>
#include <list>

//class Plant; //Forward declaration

class GardenSection : public GardenComponent {
private:
    std::vector<GardenComponent*> components;

public:
    void addComponent(GardenComponent* component) {}
    void removeComponent(GardenComponent* component) {}
    bool addPlant(Plant* plant);
    std::list<Plant*> getPlants();
    int getPlantCount();
};

#endif // GARDEN_SECTION_H
