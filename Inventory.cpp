#include "Inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory() : lowStockThreshold(5) {

}

void Inventory::addItem(InventoryItem* item) {
    items[item->getId()] = item;
}

bool Inventory::removeItem( string itemId) {
    return items.erase(itemId) > 0;
}

InventoryItem* Inventory::getItem( string itemId) {
    auto it = items.find(itemId);
    return (it != items.end()) ? it->second : nullptr;
}

void Inventory::updateQuantity( string itemId, int quantity) {
    InventoryItem* item = getItem(itemId);
    if (item) item->setQuantity(quantity);
}


int Inventory::checkStock( string itemId)  {
    auto it = items.find(itemId);
    if (it != items.end()) return it->second->getQuantity();
    return -1;
}

vector<InventoryItem*> Inventory::getAllItems()  {
    vector<InventoryItem*> vec;
    for (auto& pair : items) vec.push_back(pair.second);
    return vec;
}

vector<InventoryItem*> Inventory::getLowStockItems()  {
    vector<InventoryItem*> low;
    for (auto& pair : items)
        if (pair.second->getQuantity() <= lowStockThreshold)
            low.push_back(pair.second);
    return low;
}


double Inventory::getTotalValue()  {
    double total = 0.0;
    for (auto& pair : items)
        total += pair.second->getTotalValue();
    return total;
}

Inventory::~Inventory() {
    /* for (auto& pair : items) {
        delete pair.second;
    }
    items.clear(); */
}

InventoryIterator* Inventory::createIterator()  {
    return new ConcreteInventoryIterator(getAllItems());
}

InventoryIterator* Inventory::createLowStockIterator()  {
    return new LowStockIterator(getAllItems(), lowStockThreshold);
}

InventoryIterator* Inventory::createCategoryIterator( string category)  {
    return new CategoryIterator(getAllItems(), category);
}
