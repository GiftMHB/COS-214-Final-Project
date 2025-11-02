#ifndef GROWINGSTATE_H
#define GROWINGSTATE_H

#include "PlantState.h"

class GrowingState : public PlantState {
private:

    double growthRate;

public:

    GrowingState();

    virtual ~GrowingState() = default;
    

    void water(Plant* plant) override;

    void fertilize(Plant* plant) override;

    void grow(Plant* plant) override;

    void checkTransition(Plant* plant) override;


    std::string getStateName() const override;

    int getHealthPercentage() const override;
    
};

#endif
