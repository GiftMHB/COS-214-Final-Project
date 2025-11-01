#include "SellPlantCommand.h"
#include <iostream>

SellPlantCommand::SellPlantCommand(Plant* plant, const std::string& customer, 
                                 double price, const std::string& staff)
    : plant(plant), customerName(customer), salePrice(price), 
      staffMember(staff), wasSold(false), wasReadyForSale(false) {
      
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
        wasReadyForSale = plant->isReadyForSale();
        
        // Mark plant as sold (not ready for sale)
        plant->setReadyForSale(false);
        
        wasSold = true;
        
        std::time_t now = std::time(nullptr);
        std::tm* timeInfo = std::localtime(&now);
        
        ss << "[" << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << "] "
           << staffMember << " successfully sold plant '" 
           << plant->getName() << "' to " << customerName << " for $" << salePrice;
           
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
        // Restore readyForSale state
        plant->setReadyForSale(wasReadyForSale);
        
        wasSold = false;
        
        ss << "UNDO: Reverted sale to " << customerName 
           << ". Plant ready-for-sale status restored";
           
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