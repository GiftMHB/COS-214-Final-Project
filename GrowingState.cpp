#include "GrowingState.h"
#include "Plant.h"
#include "MatureState.h"
#include "WiltingState.h"
#include <iostream>



GrowingState::GrowingState() : growthRate(1.5) {}





void GrowingState::water(Plant* plant) {

    
    if(plant){


        plant->setWaterLevel(plant->getWaterLevel()+15);


        std::cout << "Watered growing " << plant->getName() << std::endl;


        checkTransition(plant);


    }

}






void GrowingState::fertilize(Plant* plant) {

   
   
    if(plant){


        plant->setNutrientLevel(plant->getNutrientLevel()+10);


        std::cout << "Fertilized growing " << plant->getName() << std::endl;



    }

}






void GrowingState::grow(Plant* plant) {


    if(plant){


        plant->setAge(plant->getAge()+1);


        std::cout << "Growing " << plant->getName() << " aged to " << plant->getAge() << " days" << std::endl;


        checkTransition(plant);


    }

}



void GrowingState::checkTransition(Plant* plant) {
  
  
  
    if(!plant) 
    
    return;
    
    
    if(plant->getAge()>=30){

        std::cout << plant->getName() << " is transitioning to Mature state!" << std::endl;
        
        plant->setState(new MatureState());



    } 
    
    

    else if(plant->getWaterLevel()<20||plant->getNutrientLevel()<30){

        
        std::cout << plant->getName() << " is wilting due to poor conditions!" << std::endl;
        
        
        plant->setState(new WiltingState());



    }

}





std::string GrowingState::getStateName() const {

    return "Growing";


}




int GrowingState::getHealthPercentage() const {




    return 90;

}
