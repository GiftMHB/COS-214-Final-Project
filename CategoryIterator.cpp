#include "CategoryIterator.h"


CategoryIterator::CategoryIterator( std::vector<InventoryItem*> items,  std::string category)
    : items(items), position(0), category(category) {

    }


bool CategoryIterator::hasNext()  {
    int pos = position;
    while (pos < static_cast<int>(items.size())) {
        if (items[pos]->getPlant()->getClassification() == category)
            return true;
        ++pos;
    }
    return false;
}

InventoryItem* CategoryIterator::next() {
    while (position < static_cast<int>(items.size())) {
        InventoryItem* item = items[position++];
        if (item->getPlant()->getClassification() == category)
            return item;
    }
    return nullptr;
}

void CategoryIterator::reset() { 
    position = 0;   
}

CategoryIterator::~CategoryIterator() {
    
}