#include "WaterPlantCommand.h"
#include <iostream>

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

std::string WaterPlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "WaterPlantCommand: " << staffMember << " waters plant with " 
       << waterAmount << "ml";
    return ss.str();
}

std::string WaterPlantCommand::getCommandType() const {
    return "Water";
}