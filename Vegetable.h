#ifndef VEGETABLE_H
#define VEGETABLE_H

#include <string>
#include "Plant.h"

/**
 * @file Vegetable.h
 * @brief Defines the Vegetable class derived from Plant.
 * @class Vegetable
 * @brief Represents a vegetable plant with attributes related to harvesting and yield.
 */
class Vegetable : public Plant {
    private:
        int harvestTime;           
        bool isEdible;             
        double yield;              
        std::string vegetableType; // Type of vegetable (e.g., "Carrot", "Lettuce")

    public:
        /**
         * @brief Constructs a Vegetable with core plant information and its specific attributes.
         * @param name The name of the vegetable
         * @param harvestTime Days until harvest
         * @param yield Expected yield amount
         * @param vegetableType The type or variety of the vegetable
         * @param isEdible Whether the vegetable is edible (default = true)
         */
        Vegetable(std::string name, int harvestTime, double yield,
                std::string vegetableType, bool isEdible = true);

        ~Vegetable();

        int getHarvestTime();
        double harvest();
        bool isReadyToHarvest();
        std::string getDescription();
};

#endif 