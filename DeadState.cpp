#include "DeadState.h"
#include "Plant.h"
#include <iostream>



DeadState::DeadState() {}



void DeadState::water(Plant* plant) {


    std::cout << "Cannot water dead plant " << plant->getName() << std::endl;

}





void DeadState::fertilize(Plant* plant) {


    
    std::cout << "Cannot fertilize dead plant " << plant->getName() << std::endl;


}




void DeadState::grow(Plant* plant){


    std::cout << "Dead plant " << plant->getName() << " cannot grow" << std::endl;


}





void DeadState::checkTransition(Plant* plant) {

    // No transitions



}




std::string DeadState::getStateName() const {


    return "Dead";


}





int DeadState::getHealthPercentage() const {
  
  
    return 0;



}
