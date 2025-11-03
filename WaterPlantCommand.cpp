#include "WaterPlantCommand.h"
#include <iostream>

/**
 * @file WaterPlantCommand.cpp
 * @brief Implements the WaterPlantCommand class responsible for watering plants and undoing the action
 * @brief Constructs a WaterPlantCommand object.
 * 
 * Initializes the command with a target plant, the amount of water to be added,
 * and the name of the staff member performing the watering.
 * 
 * @param plant Pointer to the Plant object to be watered.
 * @param amount The amount of water (in milliliters) to apply.
 * @param staff The name of the staff member executing the watering.
 * @throws std::invalid_argument if the plant pointer is null, the amount is non-positive, or the staff name is empty.
 */
WaterPlantCommand::WaterPlantCommand(Plant* plant, double amount, const std::string& staff) 
    : plant(plant), waterAmount(amount), staffMember(staff), previousWaterLevel(0.0), executed(false) {
        
    if (plant == nullptr) {
        throw std::invalid_argument("Plant cannot be null");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Water amount must be positive");
    }
    if (staff.empty()) {
        throw std::invalid_argument("Staff member name cannot be empty");
    }
}

/**
 * @brief Executes the watering command on the associated plant.
 * 
 * Increases the plant's water level by the specified amount, logs the action,
 * and records the time and staff member responsible. The previous water level
 * is stored to support undo functionality.
 * 
 * @return A formatted string describing the result of the watering action.
 */
std::string WaterPlantCommand::execute() {
    if (executed) {
        return "Command already executed";
    }
    
    std::stringstream ss;
    
    try {
        // Store previous state for undo
        previousWaterLevel = plant->getWaterLevel();
        
        // Execute watering
        plant->water(static_cast<int>(waterAmount));
        
        executed = true;
        
        // Get current time for logging
        std::time_t now = std::time(nullptr);
        std::tm* timeInfo = std::localtime(&now);
        
        ss << "[" << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << "] "
           << staffMember << " successfully watered plant '" 
           << plant->getName() << "' with " 
           << waterAmount << "ml of water";
           
    } catch (const std::exception& e) {
        ss << "Error watering plant: " << e.what();
    }
    
    return ss.str();
}

/**
 * @brief Undoes the previously executed watering action.
 * 
 * Restores the plant's water level to the value it had before the
 * last execution of this command.
 * 
 * @return A string describing the undo operation result.
 */
std::string WaterPlantCommand::undo() {
    if (!executed) {
        return "Command not executed yet";
    }
    
    std::stringstream ss;
    
    try {
        // Restore previous water level
        plant->setWaterLevel(static_cast<int>(previousWaterLevel));
        
        executed = false;
        
        ss << "UNDO: Reverted watering by " << staffMember 
           << ". Restored water level to " << static_cast<int>(previousWaterLevel);
           
    } catch (const std::exception& e) {
        ss << "Error undoing water command: " << e.what();
    }
    
    return ss.str();
}

/**
 * @brief Provides a human-readable description of the command.
 * 
 * @return A string describing the watering action performed by the staff member.
 */
std::string WaterPlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "WaterPlantCommand: " << staffMember << " waters plant with " 
       << waterAmount << "ml";
    return ss.str();
}

/**
 * @brief Returns the command type identifier.
 * 
 * @return A string representing the type of the command ("Water").
 */
std::string WaterPlantCommand::getCommandType() const {
    return "Water";
}
