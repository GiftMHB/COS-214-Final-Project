#ifndef CATEGORYITERATOR_H
#define CATEGORYITERATOR_H

#include <vector>
#include <string>
#include "InventoryIterator.h"

/**
 * @file CategoryIterator.h
 * @brief Defines the CategoryIterator for iterating items by category
 * @class CategoryIterator
 * @brief Iterator that filters items belonging to a specific plant category
 */
class CategoryIterator : public InventoryIterator {
    private:
        std::vector<InventoryItem*> items; 
        int position;
        std::string category;

    public:
        CategoryIterator(std::vector<InventoryItem*> items,std::string category);

        bool hasNext();
        InventoryItem* next();
        void reset();
};

#endif 