#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "../include/Plant.h"
#include "../include/SeedlingState.h"
#include "../include/GrowingState.h"
#include "../include/MatureState.h"
#include "../include/WiltingState.h"
#include "../include/DeadState.h"


void clearInput(){

    std::cin.clear();
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}



void printMenu() {

    
    std::cout << "\nPlant State Pattern Simulator" << std::endl;
    
    std::cout << "=================================" << std::endl;
    
    std::cout << "1. Create New Plant" << std::endl;
    
    std::cout << "2. Water Plant" << std::endl;
    
    
    std::cout << "3. Fertilize Plant" << std::endl;
    
    std::cout << "4. Grow Plant (Advance Time)" << std::endl;
    
    std::cout << "5. Show Plant Status" << std::endl;
    
    std::cout << "6. Force State Change (Debug)" << std::endl;
    
    std::cout << "7. List All Plants" << std::endl;
    
    std::cout << "8. Run Auto Demo" << std::endl;
    
    std::cout << "0. Exit" << std::endl;
    
    std::cout << "=================================" << std::endl;
    
    std::cout << "Choose an option: ";




}





void printPlantStatus(Plant& plant) {



    std::cout << "\n=== " << plant.getName() << " Status ===" << std::endl;

    std::cout << "ID: " << plant.getId() << std::endl;

    std::cout << "Species: " << plant.getSpecies() << std::endl;

    std::cout << "Price: R" << plant.getPrice() << std::endl;

    std::cout << "State: " << plant.getStateName() << std::endl;

    std::cout << "Age: " << plant.getAge() << " days" << std::endl;

    std::cout << "Water: " << plant.getWaterLevel() << "/100" << std::endl;

    std::cout << "Nutrients: " << plant.getNutrientLevel() << "/100" << std::endl;

    std::cout << "Health: " << plant.getState()->getHealthPercentage() << "%" << std::endl;



    std::cout << "==========================" << std::endl;



}





void runAutoDemo(){


    std::cout << "\nRunning Auto Demo of State Pattern..." << std::endl;
    

    Plant demoPlant("Demo Rose", "Rosa demo", 100.0);


    std::cout << "Created: " << demoPlant.getName() << std::endl;

    
    demoPlant.printStatus();
    
    std::cout << "\nAdvancing to Growing state..." << std::endl;
    
    demoPlant.setWaterLevel(60);
    
    demoPlant.setAge(10);
    
    demoPlant.grow();
    
    demoPlant.printStatus();
    

    std::cout << "\nAdvancing to Mature state..." << std::endl;
    
    demoPlant.setAge(35);
    
    demoPlant.grow();
    
    demoPlant.printStatus();
    

    
    std::cout << "\nSimulating neglect (Mature -> Wilting)..." << std::endl;
    
    demoPlant.setWaterLevel(10);
    
    demoPlant.setNutrientLevel(10);
    
    demoPlant.grow();
    
    demoPlant.printStatus();
    


    
    std::cout << "\nAttempting recovery (Wilting -> Growing)..." << std::endl;
    
    demoPlant.setWaterLevel(80);
    
    demoPlant.setNutrientLevel(70);
    
    demoPlant.grow();
    
    demoPlant.printStatus();
    

    
    std::cout << "\nDemonstrating Dead state..." << std::endl;
    
    Plant deadDemo("Dead Plant", "Dead species", 50.0);
    
    deadDemo.setState(new DeadState());
    
    deadDemo.printStatus();
    
    deadDemo.water(50);
    
    deadDemo.fertilize(30);
    

    
    std::cout << "\nAuto Demo Completed!" << std::endl;


}






int main() {


    std::cout << "Welcome to the Plant State Pattern Simulator!" << std::endl;


    std::cout << "Demonstrating State Pattern with plant lifecycle management.\n" << std::endl;


    
    
    std::vector<Plant*> plants;
    
    int choice;
    

    
    do{

    
        printMenu();
    
        std::cin >> choice;
    
        clearInput();
    
        
        
        switch(choice){

        
            
            case 1:{

        
                std::string name, species;
        
                double price;
        
                
                
                std::cout << "Enter plant name: ";
                
                std::getline(std::cin, name);
                
                std::cout << "Enter species: ";
                
                std::getline(std::cin, species);
                
                std::cout << "Enter price: ";
                
                std::cin >> price;
                
                clearInput();
                

                
                plants.push_back(new Plant(name, species, price));
                
                
                std::cout << "Created: " << name << " (ID: " << plants.back()->getId() << ")" << std::endl;
                
                break;



            }


            

            
            case 2:{


            
                if(plants.empty()){

            
                    std::cout << "No plants available. Create a plant first." << std::endl;
            
                    break;


            
                }
            
                
                
                std::cout << "Select plant to water (0-" << plants.size()-1 << "): ";
                
                int index;
                
                std::cin >> index;
                
                clearInput();
                

                
                if(index>=0&&index<plants.size()){

                
                    plants[index]->water(0);
                

                } 
                
                
                else{

                
                    std::cout << "Invalid plant index." << std::endl;


                
                }
                


                break;
            
            
            
            }

            

            
            case 3:{

            
            
                if(plants.empty()){

            
                    std::cout << "No plants available. Create a plant first." << std::endl;
            
            
                    break;


            
                }
            
                
                
                std::cout << "Select plant to fertilize (0-" << plants.size()-1 << "): ";
                
                int index;
                
                std::cin >> index;
                
                clearInput();
                


                
                if(index>=0&&index<plants.size()){

                
                    plants[index]->fertilize(0);
                

                } 
                
                
                else{

                
                    
                    std::cout << "Invalid plant index." << std::endl;
                

                }
                


                break;
            
            
            
            }

            

            
            case 4:{


            

                
                if(plants.empty()){

            
                    std::cout << "No plants available. Create a plant first." << std::endl;
            
                    break;
            

                }
            
                
                

                std::cout << "Select plant to grow (0-" << plants.size()-1 << "): ";
                

                int index;
                

                std::cin >> index;
                

                clearInput();
                


                
                if(index>=0&&index<plants.size()){

                
                    
                    plants[index]->grow();



                } 
                
                
                else{

                
                
                    std::cout << "Invalid plant index." << std::endl;
                

                }


                break;
            
            
            
            }
            


            
            case 5:{



                if(plants.empty()){


                    std::cout << "No plants available. Create a plant first." << std::endl;
                    
                    
                    break;



                }


                

                
                std::cout << "Select plant to show status (0-" << plants.size()-1 << "): ";
                
                int index;
                
                std::cin >> index;
                
                clearInput();
                

                
                if(index>=0&&index<plants.size()){

                
                    printPlantStatus(*plants[index]);
                

                } 
                
                
                else{


                
                    std::cout << "Invalid plant index." << std::endl;
                

                }
                


                break;
            
            
            }

            


            case 6:{


                if(plants.empty()){


                    
                    std::cout << "No plants available. Create a plant first." << std::endl;
                    


                    break;


                }

                
               
                std::cout << "Select plant to force state change (0-" << plants.size()-1 << "): ";
               
                int index;
               
                std::cin >> index;
               
                clearInput();
               
                
                
                if(index>=0&&index<plants.size()){


                    std::cout << "Select new state:" << std::endl;
                
                
                
                    std::cout << "1. Seedling  2. Growing  3. Mature  4. Wilting  5. Dead" << std::endl;
                    
                    int stateChoice;
                
                    std::cin >> stateChoice;
                
                    
                    clearInput();
                
                    

                    
                    switch(stateChoice){

                    
                        case 1: plants[index]->setState(new SeedlingState()); break;
                    
                        case 2: plants[index]->setState(new GrowingState()); break;
                    
                        case 3: plants[index]->setState(new MatureState()); break;
                    
                        case 4: plants[index]->setState(new WiltingState()); break;
                    
                        case 5: plants[index]->setState(new DeadState()); break;
                    
                        default: std::cout << "Invalid state choice." << std::endl;
                    
                    }


                } 
                
                
                else{


                    std::cout << "Invalid plant index." << std::endl;


                }


                break;



            }
            



            case 7:{


                
                if(plants.empty()){

                
                    std::cout << "No plants available." << std::endl;
                
                    break;
                
                }
                

                
                std::cout << "\n=== All Plants ===" << std::endl;
                
                
                for(size_t i=0;i<plants.size();i++){

                
                    std::cout << i << ". " << plants[i]->getName() 
                
                    << " (" << plants[i]->getStateName() << ", Age: " << plants[i]->getAge() 
                
                    << " days, Water: " << plants[i]->getWaterLevel() << ")" << std::endl;

                
                }
                

                break;



            }

            


            case 8:{


                
                runAutoDemo();
                
                break;
            }

            

            
            case 0:
            
            std::cout << "Goodbye!" << std::endl;
            
            break;
            
            
            
            default:
            
            std::cout << "Invalid option. Please try again." << std::endl;



        }

        
        
    } 
    
    
    
    while(choice!=0);


    for(auto plant:plants){


        
        
        delete plant;
    }

    

    
    return 0;
}

