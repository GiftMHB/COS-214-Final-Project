#ifndef WATER_PLANT_COMMAND_H
#define WATER_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

/**
 * @file WaterPlantCommand.h
 * @brief Declares the WaterPlantCommand class, which handles watering actions for plants
 * @class WaterPlantCommand
 * @brief Represents a command that waters a specific plant.
 *
 * The WaterPlantCommand class implements the Command interface to perform and
 * undo watering actions on a Plant object. It records details such as the amount
 * of water added, the staff member responsible, and the previous water level.
 */
class WaterPlantCommand : public Command {
private:
    /**
     * @brief Pointer to the plant being watered.
     */
    Plant* plant;

    /**
     * @brief Amount of water to apply to the plant.
     */
    double waterAmount;

    /**
     * @brief Name of the staff member performing the watering.
     */
    std::string staffMember;

    /**
     * @brief Stores the plant’s previous water level for undo operations.
     */
    double previousWaterLevel;

    /**
     * @brief Indicates whether the command has already been executed.
     */
    bool executed;

public:
    /**
     * @brief Constructs a WaterPlantCommand object.
     * @param plant Pointer to the plant to be watered.
     * @param amount The amount of water to add to the plant.
     * @param staff The name of the staff member performing the action.
     */
    WaterPlantCommand(Plant* plant, double amount, const std::string& staff);

    /**
     * @brief Executes the watering action on the plant.
     * @return A string describing the result of the watering action.
     * @throws std::runtime_error if the command cannot be executed.
     */
    std::string execute() override;

    /**
     * @brief Undoes the last watering action, restoring the previous water level.
     * @return A string describing the result of the undo operation.
     * @throws std::runtime_error if undo cannot be performed.
     */
    std::string undo() override;

    /**
     * @brief Provides a human-readable description of the command.
     * @return A string describing the watering action.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the type of the command.
     * @return A string indicating the command type (e.g., "WaterPlantCommand").
     */
    std::string getCommandType() const override;
};

#endif
