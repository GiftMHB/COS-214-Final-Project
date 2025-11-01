#ifndef WATER_PLANT_COMMAND_H
#define WATER_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class WaterPlantCommand : public Command {
private:
    Plant* plant;
    double waterAmount;
    std::string staffMember;
    double previousWaterLevel;
    bool executed;

public:
    WaterPlantCommand(Plant* plant, double amount, const std::string& staff);
    std::string execute() override;
    std::string undo() override;
    std::string getDescription() const override;
    std::string getCommandType() const override;
};

#endif