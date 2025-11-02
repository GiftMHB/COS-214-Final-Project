#include "MatureState.h"
#include "Plant.h"
#include "WiltingState.h"
#include <iostream>




MatureState::MatureState() : maintenanceRequired(true) {}



void MatureState::water(Plant* plant) {

    if(plant){

        plant->setWaterLevel(plant->getWaterLevel()+12);

        std::cout << "Watered mature " << plant->getName() << std::endl;

        checkTransition(plant);


    }

}




void MatureState::fertilize(Plant* plant) {

    
    if(plant){


        plant->setNutrientLevel(plant->getNutrientLevel()+8);

        std::cout << "Fertilized mature " << plant->getName() << std::endl;


    }

}




void MatureState::grow(Plant* plant) {

   
    if(plant){


        plant->setAge(plant->getAge()+1);

        std::cout << "Mature " << plant->getName() << " aged to " << plant->getAge() << " days" << std::endl;

        checkTransition(plant);


    }

}




void MatureState::checkTransition(Plant* plant) {


    if(!plant) 
   
    return;

    
    
    if(plant->getWaterLevel()<15||plant->getNutrientLevel()<25){

    
        std::cout << plant->getName() << " is wilting due to neglect!" << std::endl;
    
        plant->setState(new WiltingState());
    

    }
}




std::string MatureState::getStateName() const {

    return "Mature";


}



int MatureState::getHealthPercentage() const {


    return 95;


}
