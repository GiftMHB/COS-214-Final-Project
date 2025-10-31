/**
 * @file Command.cpp
 * @brief Implementation of Command pattern classes for garden center operations
 */

#include "Command.h"
#include "Plant.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

// WaterPlantCommand implementation
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
        plant->water(waterAmount);
        
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
        plant->setWaterLevel(previousWaterLevel);
        
        executed = false;
        
        ss << "UNDO: Reverted watering by " << staffMember 
           << ". Restored water level to " << previousWaterLevel << "ml";
           
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

// SellPlantCommand implementation
SellPlantCommand::SellPlantCommand(Plant* plant, const std::string& customer, 
                                 double price, const std::string& staff)
    : plant(plant), customerName(customer), salePrice(price), 
      staffMember(staff), wasSold(false), previousStatus("Available") {
      
    if (plant == nullptr) {
        throw std::invalid_argument("Plant cannot be null");
    }
    if (customer.empty()) {
        throw std::invalid_argument("Customer name cannot be empty");
    }
    if (price <= 0) {
        throw std::invalid_argument("Sale price must be positive");
    }
    if (staff.empty()) {
        throw std::invalid_argument("Staff member name cannot be empty");
    }
}

std::string SellPlantCommand::execute() {
    if (wasSold) {
        return "Plant already sold";
    }
    
    std::stringstream ss;
    
    try {
        // Store previous state
        previousStatus = plant->getStatus();
        
        // Execute sale - mark plant as sold
        plant->markAsSold();
        
        wasSold = true;
        
        std::time_t now = std::time(nullptr);
        std::tm* timeInfo = std::localtime(&now);
        
        ss << "[" << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << "] "
           << staffMember << " successfully sold plant '" 
           << plant->getName() << "' to " 
           << customerName << " for $" << std::fixed << std::setprecision(2) 
           << salePrice;
           
    } catch (const std::exception& e) {
        ss << "Error selling plant: " << e.what();
    }
    
    return ss.str();
}

std::string SellPlantCommand::undo() {
    if (!wasSold) {
        return "Plant not sold yet";
    }
    
    std::stringstream ss;
    
    try {
        // Reverse the sale - mark plant as available again
        plant->markAsAvailable();
        
        wasSold = false;
        
        ss << "UNDO: Reverted sale to " << customerName 
           << ". Plant status restored to 'Available'";
           
    } catch (const std::exception& e) {
        ss << "Error undoing sale command: " << e.what();
    }
    
    return ss.str();
}

std::string SellPlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "SellPlantCommand: " << staffMember << " sells plant to " 
       << customerName << " for $" << std::fixed << std::setprecision(2) 
       << salePrice;
    return ss.str();
}

std::string SellPlantCommand::getCommandType() const {
    return "Sell";
}

// CommandInvoker implementation
CommandInvoker::~CommandInvoker() {
    clearHistory();
    for (Command* cmd : undoneCommands) {
        delete cmd;
    }
}

std::string CommandInvoker::executeCommand(Command* command) {
    if (command == nullptr) {
        return "Error: Cannot execute null command";
    }
    
    std::string result;
    
    try {
        result = command->execute();
        commandHistory.push_back(command);
        
        // Clear redo stack when new command is executed
        for (Command* cmd : undoneCommands) {
            delete cmd;
        }
        undoneCommands.clear();
        
        // Maintain history size limit
        if (commandHistory.size() > MAX_HISTORY_SIZE) {
            delete commandHistory.front();
            commandHistory.erase(commandHistory.begin());
        }
        
    } catch (const std::exception& e) {
        result = "Command execution failed: " + std::string(e.what());
        delete command; // Clean up on failure
    }
    
    return result;
}

std::string CommandInvoker::undo() {
    if (commandHistory.empty()) {
        return "No commands to undo";
    }
    
    Command* cmd = commandHistory.back();
    
    if (!cmd->isUndoable()) {
        return "Cannot undo this command";
    }
    
    std::string result = cmd->undo();
    commandHistory.pop_back();
    undoneCommands.push_back(cmd);
    
    return result;
}

std::string CommandInvoker::redo() {
    if (undoneCommands.empty()) {
        return "No commands to redo";
    }
    
    Command* cmd = undoneCommands.back();
    std::string result = cmd->execute();
    undoneCommands.pop_back();
    commandHistory.push_back(cmd);
    
    return result;
}

std::vector<std::string> CommandInvoker::getCommandHistory() const {
    std::vector<std::string> history;
    for (const Command* cmd : commandHistory) {
        history.push_back(cmd->getDescription());
    }
    return history;
}

void CommandInvoker::clearHistory() {
    for (Command* cmd : commandHistory) {
        delete cmd;
    }
    commandHistory.clear();
}

bool CommandInvoker::canUndo() const {
    return !commandHistory.empty();
}

bool CommandInvoker::canRedo() const {
    return !undoneCommands.empty();
}