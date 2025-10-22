#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
// #include "PlantState.h"
#include "CareStrategy.h"
// #include "PlantObserver.h"

/**
 * @file Plant.h
 * @brief Defines the abstract Plant class representing a plant entity.
 * @class Plant
 * @brief Represents a plant in the system with dynamic state and care behavior.
 */
class Plant {
    protected:
        // PlantState* state;                  
        CareStrategy* careStrategy;         
        std::string id;                    
        std::string name;                   
        std::string classification;// classification (e.g., Flower, Tree)
        double price;                    
        int waterLevel;                     
        // std::list<PlantObserver*> observers;
        std::string date;                   

    public:
        /**
         * @brief Constructs a Plant with the given parameters.
         * @param name Plant name.
         * @param classification Plant category or type.
         * @param price Price of the plant.
         * @param date Creation or planting date.
         */
        Plant(const std::string& name, const std::string& classification, double price, const std::string& date);

        virtual ~Plant();

        void setPrice(double price);
        double getPrice() const;
        std::string getDescription() const;
        void handleState();
        void applyCare();
        std::string getID() const;
        int getWaterLevel() const;
};

#endif 