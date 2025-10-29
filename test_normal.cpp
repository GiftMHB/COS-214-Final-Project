#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "../include/Plant.h"
#include "../include/SeedlingState.h"
#include "../include/GrowingState.h"
#include "../include/MatureState.h"
#include "../include/WiltingState.h"
#include "../include/DeadState.h"




void testStateTransitions(){



    
    std::cout << "=== Testing State Transitions ===" << std::endl;
    


    
    Plant rose("Royal Rose", "Rosa damascena", 150.0);
    
    assert(rose.getStateName()=="Seedling");
    
    std::cout << "Initial state: " << rose.getStateName() << std::endl;
    


    
    std::cout << "\n--- Testing Seedling -> Growing transition ---" << std::endl;
    
    rose.setWaterLevel(60);  
    
    rose.setAge(10);         
    


    
    rose.grow();
    
    std::cout << "After growth - State: " << rose.getStateName() << std::endl;
    
    assert(rose.getStateName()=="Growing");
    

    
    
    
    std::cout << "\n--- Testing Growing -> Mature transition ---" << std::endl;
    
    rose.setAge(35);  
    
    rose.grow();
    
    std::cout << "After maturation - State: " << rose.getStateName() << std::endl;
    
    assert(rose.getStateName()=="Mature");
    

    
    
    
    std::cout << "\n--- Testing Mature -> Wilting transition ---" << std::endl;
    
    rose.setWaterLevel(10);  
    
    rose.grow();
    
    std::cout << "After neglect - State: " << rose.getStateName() << std::endl;
    
    assert(rose.getStateName()=="Wilting");
    

    
  
    
    std::cout << "\n--- Testing Wilting recovery ---" << std::endl;
    
    rose.setWaterLevel(80); 
    
    rose.setNutrientLevel(70); 
    
    rose.grow();
    
    std::cout << "After recovery attempt - State: " << rose.getStateName() << std::endl;
    
    assert(rose.getStateName()=="Growing");
    

    
   
    
    std::cout << "\n--- Testing Wilting -> Dead transition ---" << std::endl;
    
    Plant cactus("Dying Cactus", "Cactaceae", 50.0);
    
    cactus.setState(new WiltingState());
    
    cactus.setWaterLevel(10);  
    
    cactus.setNutrientLevel(10);
    

    
    
    for(int i=0;i<10;i++){

    
        cactus.grow();
    

    }
    

    std::cout << "After prolonged wilting - State: " << cactus.getStateName() << std::endl;
    
    
    assert(cactus.getStateName()=="Dead");
    


    
    std::cout << "\n--- Testing Dead state behavior ---" << std::endl;
    
    int initialWater = cactus.getWaterLevel();
    
    cactus.water(50);  
    
    cactus.fertilize(30); 
    
    
    std::cout << "Water level after watering dead plant: " << cactus.getWaterLevel() << std::endl;
    
    assert(cactus.getWaterLevel()==initialWater); 
    

    
    std::cout << "\nAll state transition tests passed!" << std::endl;


}





void testMultiplePlants(){


    std::cout << "\n=== Testing Multiple Plants ===" << std::endl;

    
    
    std::vector<Plant*> plants; 
    
    plants.push_back(new Plant("Sunflower", "Helianthus", 25.0));
    
    plants.push_back(new Plant("Oak Tree", "Quercus", 300.0));
    
    plants.push_back(new Plant("Lavender", "Lavandula", 35.0));
    

    
    for(auto& plant:plants){

    
        std::cout << plant->getName() << " initial state: " << plant->getStateName() << std::endl;
    
        assert(plant->getStateName()=="Seedling");
    
    }
    

    
    
    plants[0]->setWaterLevel(60);
    
    plants[0]->setAge(10);
    
    plants[0]->grow();
    

    
    std::cout << "\nAfter advancing first plant:" << std::endl;
    
   
    for(auto& plant:plants){

    
        std::cout << plant->getName() << " state: " << plant->getStateName() << std::endl;
    
    }
    

    
    assert(plants[0]->getStateName()=="Growing");
    
    assert(plants[1]->getStateName()=="Seedling");
    
    assert(plants[2]->getStateName()=="Seedling");
    


    
    for(auto plant:plants){

    
        delete plant;
    

    }
    

    
    std::cout << "\nMultiple plants test passed!" << std::endl;



}




void testStateSpecificBehavior() {



    std::cout << "\n=== Testing State-Specific Behavior ===" << std::endl;

    
    
    Plant testPlant("Test Plant", "Test Species", 100.0);
    

    
    std::cout << "--- Testing Seedling State Behavior ---" << std::endl;
    
    int initialWater = testPlant.getWaterLevel();
    
    testPlant.water(10);
    
    assert(testPlant.getWaterLevel()>initialWater);
    
    std::cout << "Seedling responds to watering" << std::endl;
    

    
    
    std::cout << "--- Testing Dead State Behavior ---" << std::endl;
    
    Plant deadPlant("Dead Plant", "Dead Species", 50.0);
    
    deadPlant.setState(new DeadState());
    

    
    int deadWater = deadPlant.getWaterLevel();
    
    deadPlant.water(50);
    
    assert(deadPlant.getWaterLevel()==deadWater);
    
    std::cout << "Dead plant ignores watering" << std::endl;
    

    
    std::cout << "All state-specific behavior tests passed!" << std::endl;


}







int main() {




    std::cout << "Starting State Pattern Automated Tests\n" << std::endl;

    
    
    try{

    
        testStateTransitions();
    

        
        testMultiplePlants();
    

        testStateSpecificBehavior();
    
        
        
        std::cout << "\nAll State Pattern tests completed successfully!" << std::endl;
        

        
        return 0;


    } 
    


    catch(const std::exception& e){

    
        std::cerr << "Test failed: " << e.what() << std::endl;
    
    
        return 1;


    } 
    
    
    catch (...){


    
        std::cerr << "Unknown test failure occurred!" << std::endl;
    
        return 1;


    
    }
}


