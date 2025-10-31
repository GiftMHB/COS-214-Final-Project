#include "../lib/doctest/doctest.h"
#include "../FlowerFactory.h"
#include "../TreeFactory.h"
#include "../VegetableFactory.h"

TEST_CASE("FlowerFactory Public Interface") {
    FlowerFactory factory;
    
    PlantInfo info;
    info.id = 1;
    info.name = "Rose";
    info.classification = "Flower";
    
    SUBCASE("Create flower using public createPlant method") {
        // Use the public interface that's available
        Plant* flower = factory.createPlant(info, "Flower", "Red", "Spring", 24, true);
        CHECK(flower != nullptr);
        CHECK(flower->getName() == "Rose");
        CHECK(flower->getClassification() == "Flower");
        
        delete flower;
    }
}

TEST_CASE("TreeFactory Public Interface") {
    TreeFactory factory;
    
    PlantInfo info;
    info.id = 1;
    info.name = "Oak";
    info.classification = "Tree";
    
    SUBCASE("Create tree using public createPlant method") {
        Plant* tree = factory.createPlant(info, "Tree", "Deciduous", 15.5, false, 2.1);
        CHECK(tree != nullptr);
        CHECK(tree->getName() == "Oak");
        CHECK(tree->getClassification() == "Tree");
        
        delete tree;
    }
}

TEST_CASE("VegetableFactory Public Interface") {
    VegetableFactory factory;
    
    PlantInfo info;
    info.id = 1;
    info.name = "Tomato";
    info.classification = "Vegetable";
    
    SUBCASE("Create vegetable using public createPlant method") {
        Plant* vegetable = factory.createPlant(info, "Vegetable", "Fruit", 90, 5.5, true);
        CHECK(vegetable != nullptr);
        CHECK(vegetable->getName() == "Tomato");
        CHECK(vegetable->getClassification() == "Vegetable");
        
        delete vegetable;
    }
}