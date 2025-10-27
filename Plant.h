#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
#include "PlantState.h"  
#include "CareStrategy.h"
// #include "PlantObserver.h"

/**
 * @file Plant.h
 * @brief Defines the abstract Plant class representing a plant entity.
 * @class Plant
 * @brief Represents a plant in the system with dynamic state and care behavior and also
 * Acts as the Context in the Strategy Pattern by maintaining a reference 
 * to a CareStrategy, which defines how the plant is maintained
 */
class Plant {
    protected:
        PlantState* state;                  
        CareStrategy* careStrategy;         
        std::string id;                    
        std::string name;                   
        std::string classification;         
        std::string species;               
        double price;                    
        int waterLevel;                     
        int nutrientLevel;                
        int age;                         
        // std::list<PlantObserver*> observers;
        std::string date;
        int healthLevel;
        static int plantCount;             

    public:
        /**
         * @brief Constructs a Plant with the given parameters.
         * @param name Plant name.
         * @param classification Plant category or type.
         * @param price Price of the plant.
         * @param date Creation or planting date.
         */
        Plant(std::string name, std::string classification, double price, std::string date);

        virtual ~Plant();

      
        void setPrice(double price);
        double getPrice();
        std::string getDescription();
        void handleState();
        void applyCare();
        std::string getID();
        int getWaterLevel();

        void setCareStrategy(CareStrategy* strategy);//delegates care logic
        void applyCareStrategy();
        std::string getCareStrategyName();
        int calculateWaterNeeds();
        int calculateSunlightNeeds();
        int calculateNutrientNeeds();
        std::string getCurrentStateName();
        std::string getName();
        std::string getClassification();
        std::string getDate();
        int getHealthLevel();
        void setHealthLevel(int level);

        std::string getSpecies() const;              
        int getNutrientLevel() const;                
        int getAge() const;                         
        PlantState* getState() const;                
        void setWaterLevel(int level);               
        void setNutrientLevel(int level);            
        void setAge(int newAge);                     
        void setState(PlantState* newState);         
        void water(int amount);                      
        void fertilize(int amount);                  
        void grow();                                 
        void printStatus() const;                    

};
#endif
