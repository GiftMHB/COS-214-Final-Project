#include "SeedlingState.h"
#include "Plant.h"
#include "GrowingState.h"
#include <iostream>





SeedlingState::SeedlingState() : minAge(7), requiredWater(40) {}




void SeedlingState::water(Plant* plant) {


    if(plant){


        plant->setWaterLevel(plant->getWaterLevel()+10);

        std::cout << "Watered seedling " << plant->getName() << std::endl;

        checkTransition(plant);


    }

}



void SeedlingState::fertilize(Plant* plant) {

    if(plant){


        plant->setNutrientLevel(plant->getNutrientLevel()+5);

        std::cout << "Fertilized seedling " << plant->getName() << std::endl;


    }

}



void SeedlingState::grow(Plant* plant) {

    
    if(plant){


        plant->setAge(plant->getAge()+1);

        std::cout << "Seedling " << plant->getName() << " aged to " << plant->getAge() << " days" << std::endl;

        checkTransition(plant);


    }

}



void SeedlingState::checkTransition(Plant* plant) {

    
    if(plant&&plant->getAge()>=minAge&&plant->getWaterLevel()>=requiredWater){

        std::cout << "Seedling " << plant->getName() << " is transitioning to Growing state!" << std::endl;


        plant->setState(new GrowingState());


    }

}



std::string SeedlingState::getStateName() const {

    return "Seedling";

}



int SeedlingState::getHealthPercentage() const {

    return 85;

}
