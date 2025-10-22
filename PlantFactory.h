#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include <string>
#include "Plant.h"

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
        virtual Plant* createFlower(std::string name, double price) = 0;
        virtual Plant* createTree(std::string name, double price) = 0;
        // virtual Plant* createShrub(std::string name, double price) = 0;
        virtual Plant* createVegetable(std::string name, double price) = 0;

    public:
        /**
         * @brief Creates a plant of the specified type.
         * @param type Type of plant (e.g., "Flower", "Tree", "Vegetable").
         * @param name The name of the plant.
         * @param price The price of the plant.
         * @return Pointer to the newly created Plant.
         */
        virtual Plant* createPlant(std::string type, std::string name, double price) = 0;
        virtual ~PlantFactory();
};

#endif 