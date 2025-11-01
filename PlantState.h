#ifndef PLANT_STATE_H
#define PLANT_STATE_H

#include <string>

class Plant;

class PlantState {
public:
    virtual ~PlantState() = default;
    virtual void grow(Plant* plant) = 0;
    virtual std::string getStateName() const = 0;
};

#endif