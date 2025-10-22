#ifndef CONCRETEPLANTFACTORY_H
#define CONCRETEPLANTFACTORY_H

#include "PlantFactory.h"

/**
 * @file ConcretePlantFactory.h
 * @brief Defines the ConcretePlantFactory class that implements PlantFactory.
 * @class ConcretePlantFactory
 * @brief Concrete implementation of PlantFactory for creating specific Plant instances.
 */
class ConcretePlantFactory : public PlantFactory {
    public:
        /**
         * @brief Creates a specific Plant object based on the provided attributes.
         * @param type The plant type (e.g., "Tree", "Flower").
         * @param name The name of the plant.
         * @param species The plant's species.
         * @param price The price of the plant.
         * @return Pointer to the created Plant.
         */
        Plant* createPlant(std::string type, std::string name, std::string species, double price);
};

#endif 