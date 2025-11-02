#ifndef GARDENCOMPONENT_H
#define GARDENCOMPONENT_H

#include <string>
#include <list>
#include <vector>
#include <cstddef>  // for size_t

#include "Plant.h"  // Include full Plant.h for complete type (fixes potential override issues)

class GardenComponent {
public:
    virtual ~GardenComponent() {}
    virtual void add(GardenComponent* component) = 0;
    virtual void remove(GardenComponent* component) = 0;
    virtual void display(int depth = 0) = 0;
    virtual int getPlantCount() = 0;
    virtual GardenComponent* findByName(const std::string& name) = 0;
    virtual std::list<Plant*> getAllPlants() = 0;
    virtual std::string getType() = 0;
    virtual std::string getName() = 0;
    virtual GardenComponent* getChild(size_t index) { return nullptr; }
};

#endif // GARDENCOMPONENT_H