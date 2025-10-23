#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

class SeedlingState : public PlantState {
private:

    int minAge;

    int requiredWater;


public:
    
    SeedlingState();

    virtual ~SeedlingState() = default;



    void water(Plant* plant) override;

    void fertilize(Plant* plant) override;

    void grow(Plant* plant) override;

    void checkTransition(Plant* plant) override;

    std::string getStateName() const override;

    int getHealthPercentage() const override;

};

#endif
