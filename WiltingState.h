#ifndef WILTINGSTATE_H
#define WILTINGSTATE_H

#include "PlantState.h"

class WiltingState : public PlantState {
private:


    double recoveryChance;

    int timeInState;





public:

    WiltingState();

    virtual ~WiltingState() = default;



    void water(Plant* plant) override;

    void fertilize(Plant* plant) override;

    void grow(Plant* plant) override;

    void checkTransition(Plant* plant) override;

    std::string getStateName() const override;

    int getHealthPercentage() const override;

    bool attemptRecovery(Plant* plant);

};

#endif
