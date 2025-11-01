#include "FertilizePlantCommand.h"
#include <iostream>

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

std::string FertilizePlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "FertilizePlantCommand: " << staffMember << " fertilizes plant with " 
       << fertilizerAmount << " units";
    return ss.str();
}

std::string FertilizePlantCommand::getCommandType() const {
    return "Fertilize";
}