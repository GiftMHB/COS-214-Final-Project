/**
 * @file SellPlantCommand.h
 * @brief Declares the SellPlantCommand class, which handles selling plants and undoing the sale.
 */

#ifndef SELL_PLANT_COMMAND_H
#define SELL_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

/**
 * @class SellPlantCommand
 * @brief Represents a command to sell a specific plant to a customer.
 *
 * The SellPlantCommand class implements the Command interface to perform and
 * undo the sale of a Plant object. It tracks the customer, sale price, staff member,
 * and the state of the plant before the sale.
 */
class SellPlantCommand : public Command {
private:
    /**
     * @brief Pointer to the plant being sold.
     */
    Plant* plant;

    /**
     * @brief Name of the customer buying the plant.
     */
    std::string customerName;

    /**
     * @brief Sale price of the plant.
     */
    double salePrice;

    /**
     * @brief Name of the staff member performing the sale.
     */
    std::string staffMember;

    /**
     * @brief Tracks whether the plant has already been sold.
     */
    bool wasSold;

    /**
     * @brief Tracks whether the plant was ready for sale before executing the command.
     */
    bool wasReadyForSale;

public:
    /**
     * @brief Constructs a SellPlantCommand object.
     * @param plant Pointer to the Plant to be sold.
     * @param customer Name of the customer purchasing the plant.
     * @param price Sale price of the plant.
     * @param staff Name of the staff member handling the sale.
     */
    SellPlantCommand(Plant* plant, const std::string& customer, double price, const std::string& staff);

    /**
     * @brief Executes the sale of the plant.
     * @return A string describing the result of the sale action.
     * @throws std::runtime_error if the command cannot be executed.
     */
    std::string execute() override;

    /**
     * @brief Undoes the sale of the plant.
     * @return A string describing the result of the undo operation.
     * @throws std::runtime_error if undo cannot be performed.
     */
    std::string undo() override;

    /**
     * @brief Provides a human-readable description of the command.
     * @return A string describing the sale action.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the type of the command.
     * @return A string indicating the command type (e.g., "SellPlantCommand").
     */
    std::string getCommandType() const override;
};

#endif
