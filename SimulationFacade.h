#ifndef SIMULATION_FACADE_H
#define SIMULATION_FACADE_H

#include <string>
//#include "GardenArea.h"
//#include "Plant.h"

class SimulationFacade {
private:
    

public:
    SimulationFacade();

    void initializeSystem();
    void addPlant(const std::string& name);
    void runSimulation();
    void generateReport();
};

#endif // SIMULATION_FACADE_H
