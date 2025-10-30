#ifndef INVENTORYITERATOR_H
#define INVENTORYITERATOR_H

#include "InventoryItem.h"

/**
 * @file InventoryIterator.h
 * @brief Defines the InventoryIterator interface for traversing inventory items
 * @class InventoryIterator
 * @brief Interface for iterating through a collection of InventoryItem objects
 */
class InventoryIterator {
    public: 
        virtual bool hasNext() = 0;
        virtual InventoryItem* next() = 0;
        virtual void reset() = 0;
        virtual ~InventoryIterator();
};

#endif 