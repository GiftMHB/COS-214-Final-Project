#include "../lib/doctest/doctest.h"
#include "../Flower.h"
#include "../Tree.h"
#include "../Vegetable.h"

TEST_CASE("Flower Functionality") {
    PlantInfo info;
    info.id = 1;
    info.name = "Rose";
    info.classification = "Flower";
    info.waterLevel = 50;
    info.healthLevel = 80;
    info.nutrientLevel = 60;
    info.salePrice = 25.0;
    
    Flower flower(info, "Red", "Spring", 24, true);
    
    SUBCASE("Flower getters return correct values") {
        CHECK(flower.getID() == 1);
        CHECK(flower.getName() == "Rose");
        CHECK(flower.getWaterLevel() == 50);
        CHECK(flower.getColor() == "Red");
        CHECK(flower.getBloomSeason() == "Spring");
        CHECK(flower.getPetalCount() == 24);
        CHECK(flower.hasFragrance() == true);
    }
    
    SUBCASE("Flower description contains expected information") {
        std::string desc = flower.getDescription();
        CHECK(desc.find("Rose") != std::string::npos);
        CHECK(desc.find("Red") != std::string::npos);
        CHECK(desc.find("Spring") != std::string::npos);
    }
}

TEST_CASE("Tree Functionality") {
    PlantInfo info;
    info.id = 2;
    info.name = "Oak";
    info.classification = "Tree";
    
    Tree tree(info, "Deciduous", 15.5, false, 2.1);
    
    SUBCASE("Tree getters work correctly") {
        CHECK(tree.getHeight() == 15.5);
        CHECK(tree.getTrunkDiameter() == 2.1);
        CHECK(tree.getName() == "Oak");
    }
    
    SUBCASE("Pruning reduces dimensions") {
        double originalHeight = tree.getHeight();
        double originalDiameter = tree.getTrunkDiameter();
        
        tree.prune();
        
        CHECK(tree.getHeight() == doctest::Approx(originalHeight * 0.9));
        CHECK(tree.getTrunkDiameter() == doctest::Approx(originalDiameter * 0.95));
    }
}

TEST_CASE("Vegetable Functionality") {
    PlantInfo info;
    info.id = 3;
    info.name = "Tomato";
    info.classification = "Vegetable";
    
    Vegetable vegetable(info, 90, 5.5, "Fruit", true);
    
    SUBCASE("Vegetable getters work correctly") {
        CHECK(vegetable.getHarvestTime() == 90);
        CHECK(vegetable.getName() == "Tomato");
    }
    
    SUBCASE("Harvest functionality") {
        CHECK(vegetable.isReadyToHarvest() == true);
        
        double yield = vegetable.harvest();
        CHECK(yield == 5.5);
        CHECK(vegetable.isReadyToHarvest() == false);
    }
}