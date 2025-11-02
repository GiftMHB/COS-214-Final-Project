#include "WiltingState.h"
#include "Plant.h"
#include "GrowingState.h"
#include "DeadState.h"
#include <iostream>




WiltingState::WiltingState() : recoveryChance(0.7), timeInState(0) {}


void WiltingState::water(Plant* plant) {

    
    if(plant){


        plant->setWaterLevel(plant->getWaterLevel()+20);

        std::cout << "Extra water for wilting " << plant->getName() << std::endl;

        checkTransition(plant);


    }

}



void WiltingState::fertilize(Plant* plant) {

    
    if(plant){


        plant->setNutrientLevel(plant->getNutrientLevel()+15);

        std::cout << "Extra nutrients for wilting " << plant->getName() << std::endl;

        
        checkTransition(plant);

    }

}



void WiltingState::grow(Plant* plant) {

  
    if(plant){


        timeInState++;

        std::cout << "Wilting " << plant->getName() << " has been wilting for " << timeInState << " days" << std::endl;

        checkTransition(plant);

    }

}



void WiltingState::checkTransition(Plant* plant) {

   
   
    if(!plant) 
    
    return;

    
    
    
    if(attemptRecovery(plant)){

    
        std::cout  << plant->getName() << " recovered from wilting!" << std::endl;
    
        plant->setState(new GrowingState());
    
    
    } 
    
    else if(timeInState>7){

    
        std::cout << plant->getName() << " has died after prolonged wilting!" << std::endl;
    
        plant->setState(new DeadState());
    
    }
}





std::string WiltingState::getStateName() const {

    return "Wilting";

}




int WiltingState::getHealthPercentage() const {

    return 40;

}



bool WiltingState::attemptRecovery(Plant* plant) {

   
    if(!plant) 
    
    return false;

    
    
    bool canRecover = (plant->getWaterLevel()>=60&&plant->getNutrientLevel()>=50);
    
    
    if(canRecover){

    
        std::cout << "Recovery attempt for " << plant->getName() << " - conditions improving!" << std::endl;
    
    }
    


    return canRecover;


}
