#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
#include "PlantState.h"
#include "CareStrategy.h"
// #include "PlantObserver.h"

using namespace std;

/**
 * @file Plant.h
 * @brief Defines the abstract Plant class representing a plant entity.
 * @class Plant
 * @brief Represents a plant in the system with dynamic state and care behavior and also
 * Acts as the Context in the Strategy Pattern by maintaining a reference
 * to a CareStrategy, which defines how the plant is maintained
 */

struct PlantInfo {
struct PlantInfo
{
    int id;
    std::string name;
    std::string classification;
    std::string addedDate;
    double purchasePrice;
    double salePrice;

    // reasonable defaults
    int waterLevel = 50;
    int healthLevel = 100;
    int sunlightNeed = 5;
    int fertilizerNeed = 2;
    
    // State and Strategy pointers
    PlantState *state;
    CareStrategy *careStrategy;
    
    // Static plant counter
    static int plantCount;

    // reasonable defaults
    int waterLevel = 20;
    int healthLevel = 100;
    int sunlightNeed = 5;
    int fertilizerNeed = 2;
    int nutrientLevel = 50;
    double currentHeight = 0.0;
    double maturityHeight = 100.0;
    int currentAgeDays = 0;
    int daysToMaturity = 365;
};

class Plant {
    protected:
        PlantInfo info;
        std::string AddedDate;

        CareStrategy* careStrategy;
        //PlantState* state;
        // std::list<PlantObserver*> observers;
class Plant
{
    protected:
        PlantInfo info;
        //  std::list<PlantObserver*> observers;

    public:
        /**
         * @brief Constructs a Plant with the given PlantInfo struct.
         * @param info PlantInfo struct containing all plant data.
         */
        Plant(PlantInfo& info);

        virtual ~Plant();

        // Price management
        void setPrice(double price);
        double getPrice();
        
        // Pure virtual method
        virtual std::string getDescription() = 0;
        
        // State management
        void handleState();
        void applyCare();
        int getID();
        int getWaterLevel();
        PlantState *getState() const;
        void setState(PlantState *newState);
        std::string getCurrentStateName();

        // Care management
        // void applyCare();
        void setCareStrategy(CareStrategy *strategy);
        //To delegate the care behavior to the currently assigned strategy
        void applyCareStrategy();
        std::string getCareStrategyName();
        
        // Care needs calculation
       /*  int calculateWaterNeeds();
        int calculateSunlightNeeds();
        int calculateNutrientNeeds(); */

        // Basic getters
        std::string getID();
        std::string getName();
        std::string getClassification();
        std::string getDate();
        std::string getSpecies() const;
        
        // Level getters and setters
        int getWaterLevel();
        void setWaterLevel(int level);
        int getHealthLevel();
        void setHealthLevel(int level);
        int getNutrientLevel() const;
        void setNutrientLevel(int level);
        
        // Age management
        int getAge() const;
        void setAge(int newAge);

        // Plant actions
        void water(int amount);
        void fertilize(int amount);
        void exposeToSunlight(int hours);
        void grow();
        void printStatus() const;
};

#endif
