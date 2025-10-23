#ifndef GARDEN_COMPONENT_H
#define GARDEN_COMPONENT_H

#include <string>
#include <vector>

class GardenComponent {
public:
    virtual ~GardenComponent() {}

    virtual void addComponent(GardenComponent* component) {}
    virtual void removeComponent(GardenComponent* component) {}
    virtual GardenComponent* getChild(int index) = 0;
    virtual void display(int depth = 0) const = 0;
    virtual int getPlantCount() = 0;
};

#endif // GARDEN_COMPONENT_H
