

#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>
#include <ctime>
#include "Plant.h"

/**
 * @file InventoryItem.h
 * @brief Defines the InventoryItem class representing an item in stock
 * @class InventoryItem
 * @brief Represents a plant item and its stock information in the inventory
 */
class InventoryItem {
    private:
        std::string id;            
        Plant* plant;
        int quantity;
        int reorderLevel;
        std::string supplier;
        std::string lastRestocked;

    public:
        InventoryItem(Plant* plant, int quantity);

        std::string getId();
        Plant* getPlant();
        int getQuantity();
        void setQuantity(int quantity);
        void incrementQuantity(int amount);
        bool decrementQuantity(int amount);
        bool isLowStock();
        int getReorderLevel();
        void setReorderLevel(int level);
        double getTotalValue();
        std::string getSupplier();
        void setSupplier(std::string supplier);
};

#endif 