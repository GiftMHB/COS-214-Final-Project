#include "ConcreteInventoryIterator.h"

ConcreteInventoryIterator::ConcreteInventoryIterator( std::vector<InventoryItem*> items)
    : items(items), position(0) {

    }

bool ConcreteInventoryIterator::hasNext()  {
    return position < static_cast<int>(items.size());
}

InventoryItem* ConcreteInventoryIterator::next() {
    if (!hasNext()) return nullptr;
    return items[position++];
}

void ConcreteInventoryIterator::reset() { 
    position = 0; 
}
