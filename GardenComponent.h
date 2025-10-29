/**
 * @file GardenComponent.h
 * @brief Abstract base class for the Composite pattern representing garden hierarchy
 * @details This class serves as the component interface in the Composite design pattern,
 *          allowing uniform treatment of individual plants and compositions of garden elements.
 */

#ifndef GARDEN_COMPONENT_H
#define GARDEN_COMPONENT_H

#include <string>
#include <list>

// Forward declaration
class Plant;

/**
 * @class GardenComponent
 * @brief Abstract component class for the Composite pattern
 * 
 * This class defines the interface for objects in the composition hierarchy.
 * It declares operations that are common to both leaf and composite objects.
 */
class GardenComponent {
protected:
    std::string name; ///< Name of the garden component

public:
    /**
     * @brief Virtual destructor
     */
    virtual ~GardenComponent() {}

    /**
     * @brief Add a child component (default implementation for leaf nodes)
     * @param component Pointer to the component to add
     */
    virtual void add(GardenComponent* component) {
        (void)component; // Suppress unused parameter warning
        // Default: do nothing (leaf nodes don't support this)
    }

    /**
     * @brief Remove a child component (default implementation for leaf nodes)
     * @param component Pointer to the component to remove
     */
    virtual void remove(GardenComponent* component) {
        (void)component; // Suppress unused parameter warning
        // Default: do nothing (leaf nodes don't support this)
    }

    /**
     * @brief Display the component hierarchy
     * @param depth Indentation depth for display formatting
     */
    virtual void display(int depth = 0) = 0;

    /**
     * @brief Get the name of the component
     * @return Component name as string
     */
    virtual std::string getName() = 0;

    /**
     * @brief Get the type of the component
     * @return Component type as string
     */
    virtual std::string getType() = 0;

    /**
     * @brief Get the total count of plants in this component
     * @return Number of plants
     */
    virtual int getPlantCount() = 0;

    /**
     * @brief Find a component by name in the hierarchy
     * @param name Name to search for
     * @return Pointer to the found component, nullptr if not found
     */
    virtual GardenComponent* findByName(const std::string& name) = 0;
};

#endif // GARDEN_COMPONENT_H