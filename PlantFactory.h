/**
 * @file PlantFactory.h
 * @brief Defines the abstract PlantFactory class and the PlantFactoryProvider.
 */

#ifndef PLANT_FACTORY_H
#define PLANT_FACTORY_H

#include "Plant.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declarations
class CareKit;
class Soil;

/**
 * @class PlantFactory
 * @brief Abstract factory interface for creating plants and related products.
 *
 * This class defines the interface for concrete factories that can create
 * plants, care kits, and soil. Each concrete factory specializes in a type
 * of plant (e.g., Flower, Tree, Vegetable).
 */
class PlantFactory {
public:
    virtual ~PlantFactory() = default;

    /**
     * @brief Creates a plant of a specific type.
     * @param name Name of the plant.
     * @param species Species/classification of the plant.
     * @param price Price of the plant.
     * @return Pointer to the created Plant object.
     */
    virtual Plant* createPlant(const std::string& name, const std::string& species, double price) = 0;

    /**
     * @brief Creates a care kit for the plant type.
     * @return Pointer to the CareKit object (can be nullptr if not implemented).
     */
    virtual CareKit* createCareKit() = 0;

    /**
     * @brief Creates soil suitable for the plant type.
     * @return Pointer to the Soil object (can be nullptr if not implemented).
     */
    virtual Soil* createSoil() = 0;

    /**
     * @brief Gets the type of factory.
     * @return Factory type string (e.g., "Flower", "Tree", "Vegetable").
     */
    virtual std::string getFactoryType() const = 0;

    /**
     * @brief Provides a textual description of the factory.
     * @return Description string.
     */
    virtual std::string getDescription() const = 0;
};

/**
 * @class PlantFactoryProvider
 * @brief Provides access to concrete plant factories.
 *
 * This provider can create factories based on a string type and
 * also provides information about supported factory types.
 */
class PlantFactoryProvider {
public:
    /**
     * @brief Creates a concrete factory based on the provided type.
     * @param type Type of factory ("flower", "tree", "vegetable").
     * @return std::unique_ptr to the created PlantFactory.
     */
    static std::unique_ptr<PlantFactory> createFactory(const std::string& type);

    /**
     * @brief Returns a list of all supported factory types.
     * @return Vector of supported factory type strings.
     */
    static std::vector<std::string> getSupportedFactories();

    /**
     * @brief Checks if a factory type is supported.
     * @param type Factory type string.
     * @return True if the type is supported, false otherwise.
     */
    static bool isFactorySupported(const std::string& type);
};

#endif
