#include "../lib/doctest/doctest.h"
#include "../Inventory.h"
#include "../InventoryItem.h"
#include "../Flower.h"

TEST_CASE("Inventory Management") {
    Inventory inventory;
    
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.salePrice = 10.0;
    info.classification = "Flower";
    
    // Use concrete Flower class
    Flower* plant = new Flower(info, "Red", "Spring", 24, true);
    InventoryItem* item = new InventoryItem(plant, 10);
    
    SUBCASE("Add and retrieve items") {
        inventory.addItem(item);
        InventoryItem* retrieved = inventory.getItem(item->getId());
        CHECK(retrieved != nullptr);
        CHECK(retrieved->getQuantity() == 10);
    }
    
    // Cleanup
    delete plant;
    delete item;
}

TEST_CASE("InventoryItem Basic Functions") {
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.salePrice = 15.0;
    info.classification = "Flower";
    
    Flower* plant = new Flower(info, "Blue", "Summer", 12, false);
    InventoryItem item(plant, 10);
    
    SUBCASE("Basic getters work") {
        CHECK(item.getQuantity() == 10);
        CHECK(item.getPlant()->getName() == "Test Plant");
        CHECK(item.isLowStock() == false);
    }
    
    delete plant;
}