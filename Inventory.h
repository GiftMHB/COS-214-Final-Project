#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <vector>
#include <string>
#include "InventoryItem.h"
#include "InventoryIterator.h"
#include "ConcreteInventoryIterator.h"
#include "LowStockIterator.h"
#include "CategoryIterator.h"

/**
 * @file Inventory.h
 * @brief Defines the Inventory class that manages all stock items and iterators
 * @class Inventory
 * @brief Represents the collection of all inventory items and provides iterator creation
 */
class Inventory {
    private:
        std::map<std::string, InventoryItem*> items; 
        int lowStockThreshold;                       

    public:
        Inventory();

        void addItem(InventoryItem* item);
        bool removeItem(std::string itemId);
        InventoryItem* getItem(std::string itemId);
        void updateQuantity(std::string itemId, int quantity);
        int checkStock(std::string itemId);
        std::vector<InventoryItem*> getLowStockItems();
        std::vector<InventoryItem*> getAllItems();

        /**
         * @brief Creates a general-purpose iterator over all inventory items.
         * @return A pointer to a new ConcreteInventoryIterator.
         */
        InventoryIterator* createIterator();

        double getTotalValue();
};

#endif 