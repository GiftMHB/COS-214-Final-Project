#ifndef DEADSTATE_H
#define DEADSTATE_H


#include "PlantState.h"

class DeadState : public PlantState {
public:

    DeadState();

    virtual ~DeadState() = default;
    
    void water(Plant* plant) override;

    void fertilize(Plant* plant) override;
    
    void grow(Plant* plant) override;
    
    void checkTransition(Plant* plant) override;
    
    std::string getStateName() const override;
    
    int getHealthPercentage() const override;

    
};

#endif
