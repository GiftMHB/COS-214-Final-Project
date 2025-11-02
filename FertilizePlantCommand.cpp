/**
 * @file FertilizePlantCommand.cpp
 * @brief Implements the FertilizePlantCommand class for fertilizing plants and undoing the action.
 */

#include "FertilizePlantCommand.h"
#include <iostream>

/**
 * @brief Constructs a FertilizePlantCommand object.
 * 
 * Initializes the command with a target plant, the amount of fertilizer to be applied,
 * and the staff member performing the action.
 * 
 * @param plant Pointer to the Plant to be fertilized.
 * @param amount Amount of fertilizer to apply (must be positive).
 * @param staff Name of the staff member performing the fertilization.
 * @throws std::invalid_argument if the plant pointer is null, amount is non-positive, or staff is empty.
 */
FertilizePlantCommand::FertilizePlantCommand(Plant* plant, int amount, const std::string& staff) 
    : plant(plant), fertilizerAmount(amount), staffMember(staff), previousNutrientLevel(0), executed(false) {
        
    if (plant == nullptr) {
        throw std::invalid_argument("Plant cannot be null");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Fertilizer amount must be positive");
    }
    if (staff.empty()) {
        throw std::invalid_argument("Staff member name cannot be empty");
    }
}

/**
 * @brief Executes the fertilization command on the plant.
 * 
 * Increases the plant's nutrient level by the specified amount and logs the action
 * with the staff member's name and timestamp. The previous nutrient level is stored
 * to support undo functionality.
 * 
 * @return A string describing the result of the fertilization action.
 */
std::string FertilizePlantCommand::execute() {
    if (executed) {
        return "Command already executed";
    }
    
    std::stringstream ss;
    
    try {
        // Store previous state for undo
        previousNutrientLevel = plant->getNutrientLevel();
        
        // Execute fertilization
        plant->fertilize(fertilizerAmount);
        
        executed = true;
        
        // Get current time for logging
        std::time_t now = std::time(nullptr);
        std::tm* timeInfo = std::localtime(&now);
        
        ss << "[" << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << "] "
           << staffMember << " successfully fertilized plant '" 
           << plant->getName() << "' with " 
           << fertilizerAmount << " units of fertilizer";
           
    } catch (const std::exception& e) {
        ss << "Error fertilizing plant: " << e.what();
    }
    
    return ss.str();
}

/**
 * @brief Undoes the fertilization action.
 * 
 * Restores the plant's nutrient level to its previous value before the command
 * was executed.
 * 
 * @return A string describing the result of the undo operation.
 */
std::string FertilizePlantCommand::undo() {
    if (!executed) {
        return "Command not executed yet";
    }
    
    std::stringstream ss;
    
    try {
        // Restore previous nutrient level
        plant->setNutrientLevel(previousNutrientLevel);
        
        executed = false;
        
        ss << "UNDO: Reverted fertilization by " << staffMember 
           << ". Restored nutrient level to " << previousNutrientLevel;
           
    } catch (const std::exception& e) {
        ss << "Error undoing fertilization command: " << e.what();
    }
    
    return ss.str();
}

/**
 * @brief Provides a human-readable description of the command.
 * 
 * @return A string describing the fertilization action with staff and amount details.
 */
std::string FertilizePlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "FertilizePlantCommand: " << staffMember << " fertilizes plant with " 
       << fertilizerAmount << " units";
    return ss.str();
}

/**
 * @brief Returns the command type identifier.
 * 
 * @return A string representing the type of the command ("Fertilize").
 */
std::string FertilizePlantCommand::getCommandType() const {
    return "Fertilize";
}
