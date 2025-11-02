/**
 * @file FertilizePlantCommand.h
 * @brief Declares the FertilizePlantCommand class, which handles fertilizing plants and undoing the action.
 */

#ifndef FERTILIZE_PLANT_COMMAND_H
#define FERTILIZE_PLANT_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

/**
 * @class FertilizePlantCommand
 * @brief Represents a command to fertilize a specific plant.
 *
 * The FertilizePlantCommand class implements the Command interface to perform
 * and undo fertilization on a Plant object. It tracks the fertilizer amount,
 * staff member, and the plant's previous nutrient level.
 */
class FertilizePlantCommand : public Command {
private:
    /**
     * @brief Pointer to the plant being fertilized.
     */
    Plant* plant;

    /**
     * @brief Amount of fertilizer to apply to the plant.
     */
    int fertilizerAmount;

    /**
     * @brief Name of the staff member performing the fertilization.
     */
    std::string staffMember;

    /**
     * @brief Stores the plant’s previous nutrient level for undo operations.
     */
    int previousNutrientLevel;

    /**
     * @brief Indicates whether the command has already been executed.
     */
    bool executed;

public:
    /**
     * @brief Constructs a FertilizePlantCommand object.
     * @param plant Pointer to the Plant to be fertilized.
     * @param amount Amount of fertilizer to apply.
     * @param staff Name of the staff member performing the action.
     */
    FertilizePlantCommand(Plant* plant, int amount, const std::string& staff);

    /**
     * @brief Executes the fertilization action on the plant.
     * @return A string describing the result of the fertilization.
     * @throws std::runtime_error if the command cannot be executed.
     */
    std::string execute() override;

    /**
     * @brief Undoes the fertilization action, restoring the previous nutrient level.
     * @return A string describing the result of the undo operation.
     * @throws std::runtime_error if undo cannot be performed.
     */
    std::string undo() override;

    /**
     * @brief Provides a human-readable description of the command.
     * @return A string describing the fertilization action.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the type of the command.
     * @return A string indicating the command type (e.g., "Fertilize").
     */
    std::string getCommandType() const override;
};

#endif
