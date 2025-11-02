/**
 * @file SellPlantCommand.cpp
 * @brief Implements the SellPlantCommand class for selling plants and undoing the sale.
 */

#include "SellPlantCommand.h"
#include <iostream>

/**
 * @brief Constructs a SellPlantCommand object.
 * 
 * Initializes the command with a target plant, customer name, sale price,
 * and the staff member performing the sale.
 * 
 * @param plant Pointer to the Plant to be sold.
 * @param customer Name of the customer purchasing the plant.
 * @param price Sale price of the plant.
 * @param staff Name of the staff member handling the sale.
 * @throws std::invalid_argument if plant is null, customer is empty, price is non-positive, or staff is empty.
 */
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

/**
 * @brief Executes the sale of the plant.
 * 
 * Marks the plant as sold (not ready for sale), logs the sale with timestamp,
 * and records the staff member and customer details.
 * 
 * @return A string describing the result of the sale action.
 */
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

/**
 * @brief Undoes the sale of the plant.
 * 
 * Restores the plant's ready-for-sale status to its previous state and
 * marks the sale as undone.
 * 
 * @return A string describing the result of the undo operation.
 */
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

/**
 * @brief Provides a human-readable description of the command.
 * 
 * @return A string describing the sale action with staff, customer, and price details.
 */
std::string SellPlantCommand::getDescription() const {
    std::stringstream ss;
    ss << "SellPlantCommand: " << staffMember << " sells plant to " 
       << customerName << " for $" << std::fixed << std::setprecision(2) 
       << salePrice;
    return ss.str();
}

/**
 * @brief Returns the command type identifier.
 * 
 * @return A string representing the type of the command ("Sell").
 */
std::string SellPlantCommand::getCommandType() const {
    return "Sell";
}
