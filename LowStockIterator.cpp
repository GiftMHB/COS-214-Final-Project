#include "LowStockIterator.h"


LowStockIterator::LowStockIterator( std::vector<InventoryItem*>items, int threshold)
    : items(items), position(0), threshold(threshold) {

    }

bool LowStockIterator::hasNext()  {
    int pos = position;
    while (pos < static_cast<int>(items.size())) {
        if (items[pos]->getQuantity() <= threshold) return true;
        ++pos;
    }
    return false;
}

InventoryItem* LowStockIterator::next() {
    while (position < static_cast<int>(items.size())) {
        InventoryItem* item = items[position++];
        if (item->getQuantity() <= threshold) return item;
    }
    return nullptr;
}

void LowStockIterator::reset() { 
    position = 0; 
}

LowStockIterator::~LowStockIterator() {
    
}