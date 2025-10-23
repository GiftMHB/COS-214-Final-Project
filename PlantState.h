#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include <string>

class Plant;  

class PlantState {
public:

    virtual ~PlantState() = default;
    

    virtual void water(Plant* plant) = 0;

    virtual void fertilize(Plant* plant) = 0;

    virtual void grow(Plant* plant) = 0;

    virtual void checkTransition(Plant* plant) = 0;

    virtual std::string getStateName() const = 0;

    virtual int getHealthPercentage() const = 0;
    

};

#endif
