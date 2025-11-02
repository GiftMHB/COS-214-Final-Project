#ifndef INVENTORYAGGREGATE_H
#define INVENTORYAGGREGATE_H

#include <string>
#include "InventoryIterator.h"

/**
 * @class InventoryAggregate
 * @brief Abstract interface representing a collection that can create iterators.
 *
 * Acts as the Aggregate in the Iterator Pattern.
 */
class InventoryAggregate {
    public:
        virtual InventoryIterator* createIterator()  = 0;
        virtual InventoryIterator* createLowStockIterator() = 0;
        virtual InventoryIterator* createCategoryIterator( std::string category) = 0;

        virtual ~InventoryAggregate();
};

#endif 