#include "Plant.h"
#include "SeedlingState.h"
#include <iostream>



int Plant::plantCount = 0;




Plant::Plant(const std::string& name, const std::string& species, double price) : name(name), species(species), price(price),

waterLevel(50), nutrientLevel(50), age(0), currentState(new SeedlingState()){


    id = "PLANT-" + std::to_string(++plantCount);


    std::cout << "Created new plant: " << name << " (ID: " << id << ")" << std::endl;


}



Plant::~Plant() {

    delete currentState;


}



std::string Plant::getId() const{
    
    return id; 

}

std::string Plant::getName() const{ 
    
    
    return name; 


}

std::string Plant::getSpecies() const{ 
    
    return species; 

}

double Plant::getPrice() const{ 
    
    return price; 

}

int Plant::getWaterLevel() const{
    
    return waterLevel; 

}

int Plant::getNutrientLevel() const{ 
    
    return nutrientLevel; 

}

int Plant::getAge() const{ 
    
    return age; 
}


PlantState* Plant::getState() const{ 
    
    return currentState; 
}

std::string Plant::getStateName() const{ 
    
    return currentState->getStateName(); 
}


void Plant::setPrice(double newPrice){ 
    
    price = newPrice; 

}

void Plant::setWaterLevel(int level){


    waterLevel = level; 

    if(waterLevel>100) 
    
    waterLevel = 100;

    if(waterLevel<0) 
    
    waterLevel = 0;

}

void Plant::setNutrientLevel(int level) { 

    nutrientLevel = level; 

    if(nutrientLevel>100) 
    
    nutrientLevel = 100;

    if(nutrientLevel<0) 
    
    nutrientLevel = 0;

}


void Plant::setAge(int newAge){ 
    
    age = newAge; 

}



void Plant::setState(PlantState* newState) {

   
    if(currentState!=newState){


        delete currentState;

        currentState = newState;

        std::cout  << name << " changed state to: " << currentState->getStateName() << std::endl;

    }

}



void Plant::water(int amount) {

    currentState->water(this);

}




void Plant::fertilize(int amount) {

    currentState->fertilize(this);

}



void Plant::grow() {

    currentState->grow(this);

}



void Plant::printStatus() const {

    std::cout << "\n=== " << name << " Status ===" << std::endl;

    std::cout << "ID: " << id << std::endl;

    std::cout << "Species: " << species << std::endl;

    std::cout << "Price: R" << price << std::endl;

    std::cout << "State: " << getStateName() << std::endl;

    std::cout << "Age: " << age << " days" << std::endl;

    std::cout << "Water: " << waterLevel << "/100" << std::endl;

    std::cout << "Nutrients: " << nutrientLevel << "/100" << std::endl;

    std::cout << "Health: " << currentState->getHealthPercentage() << "%" << std::endl;

    std::cout << "==========================" << std::endl;

    

}
