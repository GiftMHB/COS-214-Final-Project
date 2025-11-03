#ifndef LOWSTOCKITERATOR_H
#define LOWSTOCKITERATOR_H

#include <vector>
#include "InventoryIterator.h"

/**
 * @file LowStockIterator.h
 * @brief Defines the LowStockIterator for traversing low-stock inventory items
 * @class LowStockIterator
 * @brief Iterator that filters and iterates through items below a stock threshold
 */
class LowStockIterator : public InventoryIterator {
    private:
        std::vector<InventoryItem*> items; 
        int position;                  
        int threshold;                     

    public:
        LowStockIterator(std::vector<InventoryItem*> items, int threshold);
        ~LowStockIterator();

        bool hasNext();
        InventoryItem* next();
        void reset();
};

#endif 