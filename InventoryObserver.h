/**
 * @file InventoryObserver.h
 * @brief Concrete Observer that updates inventory when plants change
 * @details InventoryObserver monitors plants and updates inventory system accordingly
 */

#ifndef INVENTORY_OBSERVER_H
#define INVENTORY_OBSERVER_H

#include "Observer.h"
#include <string>

// Forward declaration
class InventoryAggregate;

/**
 * @class InventoryObserver
 * @brief Concrete observer for inventory management
 * 
 * This observer tracks plant state changes and updates the
 * inventory system when plants become ready for sale or die.
 */
class InventoryObserver : public Observer {
private:
    InventoryAggregate* inventoryReference; ///< Reference to inventory system

public:
    /**
     * @brief Constructor
     * @param inventory Pointer to the inventory system
     */
    InventoryObserver(InventoryAggregate* inventory);

    /**
     * @brief Destructor
     */
    ~InventoryObserver();

    /**
     * @brief Update method called when observed plant changes
     * @param subject Pointer to the plant that changed
     * @param eventType Type of event
     */
    void update(Plant* subject, const std::string& eventType);

    /**
     * @brief Get the observer type
     * @return Observer type string "InventoryObserver"
     */
    std::string getObserverType();
};

#endif // INVENTORY_OBSERVER_H