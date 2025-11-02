#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include <string>
#include "Plant.h"

using namespace std;

/**
 * @file PlantFactory.h
 * @brief Defines the abstract PlantFactory class responsible for creating Plant objects
 * @class PlantFactory
 * @brief Abstract base class that defines the interface for creating Plant objects
 * 
 * The Factory Method pattern allows subclasses to decide which Plant subclass to instantiate
 */
class PlantFactory {
    private:
        Plant* plant;

    protected:
        //Protected factory helper methods to be implemented by concrete factories
        virtual Plant* createFlower(PlantInfo& info,string color,string bloomSeason,int petalCount,bool fragrance) = 0;
        virtual Plant* createTree(PlantInfo& info,string treeType,double height,bool isEvergreen,double trunkDiameter) = 0;
        virtual Plant* createVegetable(PlantInfo& info,string vegetableType,int harvestTime,double expectedYield,bool isEdible) = 0;

    public:
        /**
         * @brief Creates a plant of the specified type.
         * @param type Type of plant (e.g., "Flower", "Tree", "Vegetable").
         * @param name The name of the plant.
         * @param price The price of the plant.
         * @return Pointer to the newly created Plant.
         */
        PlantFactory();
        virtual ~PlantFactory();
        /**
         * @note This is the public factory method that clients call
         */
        virtual Plant* createPlant(PlantInfo& info, string type, string color, string bloomSeason, int petalCount, bool fragrance) = 0;
        virtual Plant* createPlant(PlantInfo& info, string type, string treeType, double height, bool isEvergreen, double trunkDiameter) = 0;
        virtual Plant* createPlant(PlantInfo& info, string type, string vegetableType, int harvestTime, double expectedYield, bool isEdible) = 0;
};

#endif