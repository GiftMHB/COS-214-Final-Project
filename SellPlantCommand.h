#ifndef SELL_PLANT_COMMAND_H
#define SELL_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class SellPlantCommand : public Command {
private:
    Plant* plant;
    std::string customerName;
    double salePrice;
    std::string staffMember;
    bool wasSold;
    bool wasReadyForSale;

public:
    SellPlantCommand(Plant* plant, const std::string& customer, double price, const std::string& staff);
    std::string execute() override;
    std::string undo() override;
    std::string getDescription() const override;
    std::string getCommandType() const override;
};

#endif