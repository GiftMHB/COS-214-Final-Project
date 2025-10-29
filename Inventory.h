#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <vector>
#include <string>
#include "InventoryItem.h"
#include "InventoryAggregate.h"
#include "ConcreteInventoryIterator.h"
#include "LowStockIterator.h"
#include "CategoryIterator.h"

/**
 * @class Inventory
 * @brief ConcreteAggregate that manages stock items and creates iterators.
 */
class Inventory : public InventoryAggregate {
    private:
        std::map<std::string, InventoryItem*> items; // Maps item IDs to InventoryItem pointers
        int lowStockThreshold;                       

    public:
        Inventory();
        ~Inventory();

        void addItem(InventoryItem* item);
        bool removeItem( std::string itemId);
        InventoryItem* getItem( std::string itemId);
        void updateQuantity( std::string itemId, int quantity);
        int checkStock( std::string itemId);

        std::vector<InventoryItem*> getAllItems();
        std::vector<InventoryItem*> getLowStockItems();

        double getTotalValue();

        InventoryIterator* createIterator();
        InventoryIterator* createLowStockIterator();
        InventoryIterator* createCategoryIterator(std::string category);
};

#endif 