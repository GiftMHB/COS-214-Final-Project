#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

class MatureState : public PlantState {
private:

    bool maintenanceRequired;

public:

    MatureState();

    virtual ~MatureState() = default;



    void water(Plant* plant) override;

    void fertilize(Plant* plant) override;

    void grow(Plant* plant) override;

    void checkTransition(Plant* plant) override;

    std::string getStateName() const override;

    int getHealthPercentage() const override;

};

#endif
