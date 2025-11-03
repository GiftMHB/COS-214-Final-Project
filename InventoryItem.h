#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>
#include "Plant.h"

/**
 * @class InventoryItem
 * @brief Represents a stocked plant with quantity, supplier, and restock info
 *
 * Aggregates a Plant pointer and adds stock-related data
 * Defines the InventoryItem class representing a stocked plant in inventory
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
        ~InventoryItem();

        std::string getId();
        Plant* getPlant();
        int getQuantity();
        void setQuantity(int quantity);

        void incrementQuantity(int amount);
        bool decrementQuantity(int amount);
        bool isLowStock();

        int getReorderLevel();
        void setReorderLevel(int level);

        std::string getSupplier();
        void setSupplier(std::string supplier);

        std::string getLastRestocked();
        void setLastRestocked(std::string date);

        double getTotalValue();
};

#endif 