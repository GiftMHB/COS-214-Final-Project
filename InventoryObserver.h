#ifndef INVENTORY_OBSERVER_H
#define INVENTORY_OBSERVER_H

#include "Observer.h"

class InventoryObserver : public Observer {
public:
    virtual void update(Plant* plant);
};

#endif // INVENTORY_OBSERVER_H
