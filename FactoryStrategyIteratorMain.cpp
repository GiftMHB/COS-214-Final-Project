// main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for EXIT_SUCCESS

// Project headers 
#include "FlowerFactory.h"
#include "TreeFactory.h"
#include "PlantFactory.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "ConcreteInventoryIterator.h"
#include "LowStockIterator.h"
#include "CategoryIterator.h"
#include "HighMaintenanceCare.h"
#include "LowMaintenanceCare.h"
#include "SeasonalCare.h"
#include "Plant.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

/* -----------------------
   Small helper: build PlantInfo for a Flower
   ----------------------- */
static PlantInfo makeFlowerInfo(int id, const string &name, double salePrice) {
    PlantInfo p;
    p.id = id;
    p.name = name;
    p.classification = "Flower";
    p.addedDate = "2025-10-30";
    p.purchasePrice = salePrice * 0.6;
    p.salePrice = salePrice;

    // sensible defaults (some of these may already be set in your PlantInfo default)
    p.waterLevel = 20;
    p.healthLevel = 100;
    p.sunlightNeed = 5;
    p.fertilizerNeed = 2;
    p.nutrientLevel = 50;
    p.currentHeight = 0.0;
    p.maturityHeight = 100.0;
    p.currentAgeDays = 0;
    p.daysToMaturity = 365;
    return p;
}

/* -----------------------
   Factory method test
   - returns Plant* (caller should delete)
   ----------------------- */
static Plant* testFactoryMethod() {
    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Testing Factory Method:\n";

    FlowerFactory  flowerFactory;
    PlantInfo info = makeFlowerInfo(1, "Autumn Rose", 19.99);

    // create a flower
    Plant *flower = flowerFactory.createPlant(info, "Flower", "Red", "Autumn", 24, true);
    Plant *Cabbege = flowerFactory.createPlant(info, "Vegetable", "Cabbage", "60", 4.5, true); 
    
    cout << "[Factory Main] Created: " << flower->getName() << " | class: " << flower->getClassification()
    << " | price: " << flower->getPrice() << "\n";

    // flower description
    cout << "Description: " << flower->getDescription() << "\n";

    // quick sanity: apply a few actions
    flower->water(10);
    flower->fertilize(11);
    flower->exposeToSunlight(3);

    cout << "----------------------------------------------------------------------------------------Factory\n\n";
    return flower;
}

/* -----------------------
   Strategy test
   - accepts a Plant* and assigns multiple CareStrategy objects
   - deletes strategies after use
   ----------------------- */
static void testStrategy(Plant *plant) {

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Testing Strategy:\n";

    if (!plant) {
        cout << "[testStrategy] no plant provided\n\n";
        return;
    }

    vector<CareStrategy*> strategies;

    // high maintenance with some treatments
    vector<string> treatments = {"pruning", "misting"};
    strategies.push_back(new HighMaintenanceCare(1, 1, treatments));

    // low maintenance
    strategies.push_back(new LowMaintenanceCare(4, 4));

    // seasonal (start with Summer)
    strategies.push_back(new SeasonalCare("Summer"));

    for (CareStrategy* strat : strategies) {
        if (!strat) continue;
        cout << "[testStrategy] Setting strategy: " << strat->getStrategyName() << "\n";
        plant->setCareStrategy(strat);
        plant->applyCareStrategy();
        cout << "[testStrategy] Done strategy: " << strat->getStrategyName() << "\n\n";
    }

    // runtime change in SeasonalCare to Winter
    SeasonalCare *seasonal = dynamic_cast<SeasonalCare*>(strategies.back());
    if (seasonal) {
        string newSeason = "Winter";
        seasonal->setSeason(newSeason);
        cout << "[testStrategy] Re-applying after season change\n";
        plant->setCareStrategy(seasonal);
        plant->applyCareStrategy();
        cout << "[testStrategy] Seasonal re-apply done\n\n";
    }

    // Delete strategies 
    for (CareStrategy* strat : strategies) {
        cout << "[testStrategy] Deleting strategy: " << (strat ? strat->getStrategyName() : string("nullptr")) << "\n";
        delete strat;
    }
    strategies.clear();

    cout << "----------------------------------------------------------------------------------------Strategy\n\n";
}

/* -----------------------
   Iterator test
   - builds an Inventory, populates with InventoryItems (wrapping Plants),
   - tests full iterator, low-stock iterator, and category iterator.
   - deletes all created objects.
   ----------------------- */
static void testIterator() {

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Testing Iterator:\n";

    Inventory inventory;

    FlowerFactory flowerFactory;
    TreeFactory treeFactory;

    // Flower plants
    PlantInfo f1 = makeFlowerInfo(101, "Red Rose", 9.99);
    PlantInfo f2 = makeFlowerInfo(102, "Yellow Tulip", 7.50);
    PlantInfo f3 = makeFlowerInfo(103, "White Lily", 12.00);

    Plant* p1 = flowerFactory.createPlant(f1, "Flower", "Red", "Spring", 20, true);
    Plant* p2 = flowerFactory.createPlant(f2, "Flower", "Yellow", "Summer", 10, false);
    Plant* p3 = flowerFactory.createPlant(f3, "Flower", "White", "Autumn", 18, true);

    PlantInfo tinfo;
    tinfo.id = 200;
    tinfo.name = "Oak";
    tinfo.classification = "Tree";
    tinfo.addedDate = "2025-09-20";
    tinfo.purchasePrice = 30.0;
    tinfo.salePrice = 60.0;

    // Turn plants into InventoryItems 
    vector<InventoryItem*> createdItems;
    if (p1) createdItems.push_back(new InventoryItem(p1, 10)); // healthy stock
    if (p2) createdItems.push_back(new InventoryItem(p2, 2));  // low stock
    if (p3) createdItems.push_back(new InventoryItem(p3, 1));  // low stock

    // Add items to inventory
    for (InventoryItem* it : createdItems) {
        inventory.addItem(it);
    }

    cout << "[testIterator] Total inventory value: " << inventory.getTotalValue() << "\n";

    // 1) Full iterator
    InventoryIterator* itAll = inventory.createIterator();
    cout << "[testIterator] All items:\n";
    while (itAll && itAll->hasNext()) {
        InventoryItem* item = itAll->next();
        if (!item) continue;
        cout << " - " << item->getId() << " : " << item->getPlant()->getName()
             << " (qty=" << item->getQuantity() << ")\n";
    }
    delete itAll; itAll = nullptr;

    // 2) Low-stock iterator
    InventoryIterator* itLow = inventory.createLowStockIterator();
    cout << "[testIterator] Low stock items:\n";
    while (itLow && itLow->hasNext()) {
        InventoryItem* item = itLow->next();
        if (!item) continue;
        cout << " - " << item->getId() << " : " << item->getPlant()->getName()
             << " (qty=" << item->getQuantity() << ")\n";
    }
    delete itLow; itLow = nullptr;

    // 3) Category iterator (Flowers)
    InventoryIterator* itCat = inventory.createCategoryIterator("Flower");
    cout << "[testIterator] Category (Flower) items:\n";
    while (itCat && itCat->hasNext()) {
        InventoryItem* item = itCat->next();
        if (!item) continue;
        cout << " - " << item->getId() << " : " << item->getPlant()->getName()
             << " (qty=" << item->getQuantity() << ")\n";
    }
    delete itCat; itCat = nullptr;

    // Cleanup: Inventory destructor currently does NOT delete items (I noticed this in your Inventory.cpp),
    // so we must delete the InventoryItems ourselves to avoid leaks.
    cout << "[testIterator] Deleting inventory items and associated plants\n";
    for (InventoryItem* item : createdItems) {
        if (!item) continue;
        Plant* ownerPlant = item->getPlant();
        cout << " - deleting InventoryItem: " << item->getId() << "\n";
        delete item; // InventoryItem destructor does not delete Plant
        if (ownerPlant) {
            cout << "   deleting its Plant: " << ownerPlant->getName() << "\n";
            delete ownerPlant;
        }
    }
    createdItems.clear();

    // Inventory still exists but is now empty of pointers we owned
    cout << "----------------------------------------------------------------------------------------Iterator\n\n";
}

int main() {
    cout << "Integration tests: Factory, Strategy, Iterator \n\n";

    // Factory test (returns allocated Plant*)
    Plant* plant = testFactoryMethod();

    // Strategy test (uses and deletes strategies, does NOT delete plant)
    testStrategy(plant);

    // Iterator test 
    testIterator();

    // cleanup plant from factory test
    if (plant) {
        cout << "[main] Deleting plant created by factory test: " << plant->getName() << "\n";
        delete plant;
        plant = nullptr;
    }

    cout << "\nAll tests complete. Use valgrind or similar to confirm no leaks.\n";
    return EXIT_SUCCESS;
}
