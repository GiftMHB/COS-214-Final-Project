#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Plant.h"
#include "../include/SeedlingState.h"
#include "../include/GrowingState.h"
#include "../include/MatureState.h"
#include "../include/WiltingState.h"
#include "../include/DeadState.h"

TEST_SUITE("State Pattern Unit Tests") {
    
    TEST_CASE("Plant Initialization") {
        Plant plant("Rose", "Rosa", 100.0);
        
        CHECK(plant.getName() == "Rose");
        CHECK(plant.getSpecies() == "Rosa");
        CHECK(plant.getPrice() == 100.0);
        CHECK(plant.getStateName() == "Seedling");
        CHECK(plant.getWaterLevel() == 50);
        CHECK(plant.getNutrientLevel() == 50);
        CHECK(plant.getAge() == 0);
    }
    
    TEST_CASE("Seedling State Transitions") {
        Plant plant("Test Plant", "Test Species", 50.0);
        
        SUBCASE("Seedling remains seedling with insufficient conditions") {
            plant.setAge(5);  // Below min age
            plant.setWaterLevel(30);  // Below required water
            plant.grow();
            
            CHECK(plant.getStateName() == "Seedling");
        }
        
        SUBCASE("Seedling transitions to growing with proper conditions") {
            plant.setAge(10);  // Above min age
            plant.setWaterLevel(60);  // Above required water
            plant.grow();
            
            CHECK(plant.getStateName() == "Growing");
        }
    }
    
    TEST_CASE("Growing State Transitions") {
        Plant plant("Growing Plant", "Test Species", 50.0);
        plant.setState(new GrowingState());
        
        SUBCASE("Growing transitions to mature with age") {
            plant.setAge(35);  // Above maturation age
            plant.grow();
            
            CHECK(plant.getStateName() == "Mature");
        }
        
        SUBCASE("Growing transitions to wilting with low resources") {
            plant.setWaterLevel(10);  // Very low water
            plant.setNutrientLevel(10);  // Very low nutrients
            plant.grow();
            
            CHECK(plant.getStateName() == "Wilting");
        }
    }
    
    TEST_CASE("Mature State Behavior") {
        Plant plant("Mature Plant", "Test Species", 50.0);
        plant.setState(new MatureState());
        
        SUBCASE("Mature plant responds to watering") {
            int initialWater = plant.getWaterLevel();
            plant.water(0);
            
            CHECK(plant.getWaterLevel() > initialWater);
        }
        
        SUBCASE("Mature transitions to wilting when neglected") {
            plant.setWaterLevel(10);
            plant.setNutrientLevel(10);
            plant.grow();
            
            CHECK(plant.getStateName() == "Wilting");
        }
    }
    
    TEST_CASE("Wilting State Recovery") {
        Plant plant("Wilting Plant", "Test Species", 50.0);
        plant.setState(new WiltingState());
        
        SUBCASE("Wilting can recover with proper care") {
            plant.setWaterLevel(80);
            plant.setNutrientLevel(70);
            plant.grow();
            
            CHECK(plant.getStateName() == "Growing");
        }
        
        SUBCASE("Wilting dies after prolonged neglect") {
            plant.setWaterLevel(10);
            plant.setNutrientLevel(10);
            
            // Simulate multiple days of wilting
            for (int i = 0; i < 10; i++) {
                plant.grow();
            }
            
            CHECK(plant.getStateName() == "Dead");
        }
    }
    
    TEST_CASE("Dead State Terminal Behavior") {
        Plant plant("Dead Plant", "Test Species", 50.0);
        plant.setState(new DeadState());
        
        SUBCASE("Dead plant ignores watering") {
            int initialWater = plant.getWaterLevel();
            plant.water(50);
            
            CHECK(plant.getWaterLevel() == initialWater);
        }
        
        SUBCASE("Dead plant ignores fertilizing") {
            int initialNutrients = plant.getNutrientLevel();
            plant.fertilize(30);
            
            CHECK(plant.getNutrientLevel() == initialNutrients);
        }
        
        SUBCASE("Dead plant cannot change state") {
            plant.grow();
            CHECK(plant.getStateName() == "Dead");
        }
    }
    
    TEST_CASE("State Health Percentages") {
        SUBCASE("Seedling health") {
            SeedlingState state;
            CHECK(state.getHealthPercentage() == 85);
        }
        
        SUBCASE("Growing health") {
            GrowingState state;
            CHECK(state.getHealthPercentage() == 90);
        }
        
        SUBCASE("Mature health") {
            MatureState state;
            CHECK(state.getHealthPercentage() == 95);
        }
        
        SUBCASE("Wilting health") {
            WiltingState state;
            CHECK(state.getHealthPercentage() == 40);
        }
        
        SUBCASE("Dead health") {
            DeadState state;
            CHECK(state.getHealthPercentage() == 0);
        }
    }
    
    TEST_CASE("Resource Level Management") {
        Plant plant("Resource Test", "Test Species", 50.0);
        
        SUBCASE("Water level clamping") {
            plant.setWaterLevel(150);  // Above max
            CHECK(plant.getWaterLevel() == 100);
            
            plant.setWaterLevel(-10);  // Below min
            CHECK(plant.getWaterLevel() == 0);
        }
        
        SUBCASE("Nutrient level clamping") {
            plant.setNutrientLevel(200);  // Above max
            CHECK(plant.getNutrientLevel() == 100);
            
            plant.setNutrientLevel(-5);  // Below min
            CHECK(plant.getNutrientLevel() == 0);
        }
    }
    
    TEST_CASE("Multiple Plant Management") {
        Plant* plant1 = new Plant("Plant 1", "Species A", 25.0);
        Plant* plant2 = new Plant("Plant 2", "Species B", 35.0);
        
        CHECK(plant1->getStateName() == "Seedling");
        CHECK(plant2->getStateName() == "Seedling");
        CHECK(plant1->getName() != plant2->getName());
        
        // Test independent state progression
        plant1->setAge(10);
        plant1->setWaterLevel(60);
        plant1->grow();
        
        CHECK(plant1->getStateName() == "Growing");
        CHECK(plant2->getStateName() == "Seedling");  // Should remain unchanged
        
        delete plant1;
        delete plant2;
    }
    
    TEST_CASE("State Name Consistency") {
        CHECK(SeedlingState().getStateName() == "Seedling");
        CHECK(GrowingState().getStateName() == "Growing");
        CHECK(MatureState().getStateName() == "Mature");
        CHECK(WiltingState().getStateName() == "Wilting");
        CHECK(DeadState().getStateName() == "Dead");
    }
}