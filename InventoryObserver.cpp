/**
 * @file InventoryObserver.cpp
 * @brief Implementation of the InventoryObserver concrete observer
 */

#include "InventoryObserver.h"
#include "Plant.h"
#include <iostream>

// Note: InventoryAggregate methods would be called here if needed
// For now, we'll just log the inventory-related events

InventoryObserver::InventoryObserver(InventoryAggregate* inventory)
    : inventoryReference(inventory) {}

InventoryObserver::~InventoryObserver() {}

void InventoryObserver::update(Plant* subject, const std::string& eventType) {
    if (subject == nullptr) {
        return;
    }

    if (eventType == "state_changed") {
        if (subject->isReadyForSale()) {
            std::cout << "[INVENTORY] Plant '" << subject->getName() 
                      << "' (ID: " << subject->getId() 
                      << ") is now ready for sale. Updating inventory..." << std::endl;
            
            // Here you would call inventory methods like:
            // if (inventoryReference != nullptr) {
            //     inventoryReference->markAsAvailable(subject);
            // }
        }
    } else if (eventType == "health_low") {
        std::cout << "[INVENTORY WARNING] Plant '" << subject->getName() 
                  << "' (ID: " << subject->getId() 
                  << ") has low health. May need to be removed from inventory." << std::endl;
    } else if (!subject->getIsAlive()) {
        std::cout << "[INVENTORY] Plant '" << subject->getName() 
                  << "' (ID: " << subject->getId() 
                  << ") has died. Removing from sellable inventory..." << std::endl;
        
        // Here you would call inventory methods like:
        // if (inventoryReference != nullptr) {
        //     inventoryReference->removeFromSale(subject);
        // }
    }
}

std::string InventoryObserver::getObserverType() {
    return "InventoryObserver";
}