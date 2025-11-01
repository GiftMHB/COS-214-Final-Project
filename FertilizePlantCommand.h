#ifndef FERTILIZE_PLANT_COMMAND_H
#define FERTILIZE_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class FertilizePlantCommand : public Command {
private:
    Plant* plant;
    int fertilizerAmount;
    std::string staffMember;
    int previousNutrientLevel;
    bool executed;

public:
    FertilizePlantCommand(Plant* plant, int amount, const std::string& staff);
    std::string execute() override;
    std::string undo() override;
    std::string getDescription() const override;
    std::string getCommandType() const override;
};

#endif