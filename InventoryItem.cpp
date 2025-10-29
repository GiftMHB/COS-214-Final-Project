#include "InventoryItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

/**
 * @brief ructs an inventory item associated with a plant.
 */
InventoryItem::InventoryItem(Plant *plant, int quantity)
    : plant(plant), quantity(quantity), reorderLevel(5), supplier("Unknown")
{
    static int nextId = 1;
    id = "ITEM_" + to_string(nextId++);
    lastRestocked = "2025-01-01"; // default
}


string InventoryItem::getId() { 
    return id; 
}

Plant *InventoryItem::getPlant() { 
    return plant;   
}

int InventoryItem::getQuantity() { 
    return quantity; 
}

void InventoryItem::setQuantity(int quantity) { 
    this->quantity = quantity; 
}

void InventoryItem::incrementQuantity(int amount) { 
    quantity += amount; 
}

bool InventoryItem::decrementQuantity(int amount)
{
    if (amount > quantity)
        return false;
    quantity -= amount;
    return true;
}

bool InventoryItem::isLowStock()
{
    return quantity <= reorderLevel;
}

int InventoryItem::getReorderLevel() {  
    return reorderLevel; 
}

void InventoryItem::setReorderLevel(int level) { 
    reorderLevel = level; 
}

string InventoryItem::getSupplier() { 
    return supplier; 
}

void InventoryItem::setSupplier( string supplier) { 
    this->supplier = supplier; 
}

string InventoryItem::getLastRestocked() {  
    return lastRestocked; 
}

void InventoryItem::setLastRestocked(string date) { 
    lastRestocked = date; 
}


double InventoryItem::getTotalValue()
{
    return plant->getPrice() * quantity;
}

InventoryItem::~InventoryItem() {
    
}