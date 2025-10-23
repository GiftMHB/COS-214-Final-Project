#ifndef CONCRETEINVENTORYITERATOR_H
#define CONCRETEINVENTORYITERATOR_H

#include <vector>
#include "InventoryIterator.h"

/**
 * @file ConcreteInventoryIterator.h
 * @brief Defines the ConcreteInventoryIterator class for sequential iteration
 * @class ConcreteInventoryIterator
 * @brief Concrete iterator that iterates through all inventory items sequentially
 */
class ConcreteInventoryIterator : public InventoryIterator {
    private:
        std::vector<InventoryItem*> items; 
        int position;       

    public:
        /**
         * @brief Constructs an iterator with a list of items
         * @param items Vector of InventoryItem pointers
         */
        explicit ConcreteInventoryIterator(std::vector<InventoryItem*> items);

        bool hasNext();
        InventoryItem* next();
        void reset();
};

#endif 