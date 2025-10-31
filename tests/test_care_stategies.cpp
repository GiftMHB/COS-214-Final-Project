#include "../lib/doctest/doctest.h"
#include "../LowMaintenanceCare.h"
#include "../HighMaintenanceCare.h"
#include "../SeasonalCare.h"
#include "../Flower.h"  

TEST_CASE("LowMaintenanceCare") {
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.waterLevel = 50;
    info.nutrientLevel = 50;
    info.classification = "Flower";
    
    Flower plant(info, "Red", "Spring", 24, true);
    LowMaintenanceCare strategy(2, 1);
    
    SUBCASE("Strategy name") {
        CHECK(strategy.getStrategyName() == "Low Maintenance Care");
    }
    
    SUBCASE("Calculate needs") {
        CHECK(strategy.calculateWaterNeeds(&plant) > 0);
        CHECK(strategy.calculateNutrientNeeds(&plant) > 0);
        CHECK(strategy.calculateSunlightNeeds(&plant) == 3);
    }
}

TEST_CASE("HighMaintenanceCare") {
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.classification = "Flower";
    
    Flower plant(info, "Red", "Spring", 24, true);
    std::vector<std::string> treatments = {"pruning", "misting"};
    HighMaintenanceCare strategy(1, 1, treatments);
    
    SUBCASE("Strategy name") {
        CHECK(strategy.getStrategyName() == "High Maintenance Care");
    }
    
    SUBCASE("Calculate needs") {
        CHECK(strategy.calculateWaterNeeds(&plant) > 0);
        CHECK(strategy.calculateNutrientNeeds(&plant) > 0);
        CHECK(strategy.calculateSunlightNeeds(&plant) == 6);
    }
}

TEST_CASE("SeasonalCare") {
    SeasonalCare springCare("Spring");
    SeasonalCare winterCare("Winter");
    
    PlantInfo info;
    info.id = 1;
    info.name = "Test Plant";
    info.classification = "Flower";
    Flower plant(info, "Red", "Spring", 24, true);
    
    SUBCASE("Strategy names include season") {
        CHECK(springCare.getStrategyName().find("Spring") != std::string::npos);
        CHECK(winterCare.getStrategyName().find("Winter") != std::string::npos);
    }
    
    SUBCASE("Season adjustment affects needs") {
        int springWater = springCare.calculateWaterNeeds(&plant);
        int winterWater = winterCare.calculateWaterNeeds(&plant);
        CHECK(springWater > winterWater);
    }
}