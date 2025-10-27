#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
//#include "PlantState.h"
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

    public:
        /**
         * @brief Constructs a Plant with the given parameters.
         * @param name Plant name.
         * @param classification Plant category or type.
         * @param price Price of the plant.
         * @param date Creation or planting date.
         */
        Plant(PlantInfo& info);
        virtual ~Plant();

        void setPrice(double price);
        double getPrice();
        std::string getDescription();
        void handleState();
        void applyCare();
        int getID();
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
};

#endif 
