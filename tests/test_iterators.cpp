#include "../lib/doctest/doctest.h"
#include "../ConcreteInventoryIterator.h"
#include "../CategoryIterator.h"
#include "../LowStockIterator.h"
#include "../InventoryItem.h"
#include "../Flower.h"

TEST_CASE("ConcreteInventoryIterator Basic Iteration") {
    std::vector<InventoryItem*> items;
    
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.classification = "Flower";
    
    Flower* plant = new Flower(info, "Red", "Spring", 24, true);
    InventoryItem* item = new InventoryItem(plant, 5);
    items.push_back(item);
    
    ConcreteInventoryIterator iterator(items);
    
    CHECK(iterator.hasNext() == true);
    CHECK(iterator.next() == item);
    CHECK(iterator.hasNext() == false);
    
    delete plant;
    delete item;
}

TEST_CASE("LowStockIterator Filters Correctly") {
    std::vector<InventoryItem*> items;
    
    PlantInfo info1, info2;
    info1.id = 1; info1.name = "LowStock"; info1.classification = "Flower";
    info2.id = 2; info2.name = "AdequateStock"; info2.classification = "Flower";
    
    Flower* p1 = new Flower(info1, "Red", "Spring", 24, true);
    Flower* p2 = new Flower(info2, "Blue", "Summer", 12, false);
    
    InventoryItem* item1 = new InventoryItem(p1, 3);  // Low stock
    InventoryItem* item2 = new InventoryItem(p2, 10); // Adequate stock
    
    items.push_back(item1);
    items.push_back(item2);
    
    LowStockIterator iterator(items, 5); // Threshold = 5
    
    int lowStockCount = 0;
    while (iterator.hasNext()) {
        InventoryItem* item = iterator.next();
        CHECK(item->getQuantity() <= 5);
        lowStockCount++;
    }
    CHECK(lowStockCount == 1);
    
    delete p1; delete p2;
    delete item1; delete item2;
}