/**
 * @file GardenSection.h
 * @brief Composite class representing a section within the garden
 * @details This class can contain other sections or plant beds, forming the
 *          intermediate level in the composite hierarchy.
 */

#ifndef GARDEN_SECTION_H
#define GARDEN_SECTION_H

#include "GardenComponent.h"
#include <list>
#include <string>

/**
 * @class GardenSection
 * @brief Composite container for organizing plant beds and subsections
 * 
 * GardenSection acts as a composite node that can contain both other
 * sections and plant beds, allowing for hierarchical organization.
 */
class GardenSection : public GardenComponent {
private:
    std::string id; ///< Unique identifier for the section
    std::list<GardenComponent*> components; ///< Child components

public:
    /**
     * @brief Constructor
     * @param sectionName Name of the section
     * @param sectionId Unique identifier
     */
    GardenSection(const std::string& sectionName, const std::string& sectionId);

    /**
     * @brief Destructor - cleans up child components
     */
    ~GardenSection();

    /**
     * @brief Add a child component (section or bed)
     * @param component Pointer to the component to add
     */
    void add(GardenComponent* component);

    /**
     * @brief Remove a child component
     * @param component Pointer to the component to remove
     */
    void remove(GardenComponent* component);

    /**
     * @brief Display this section and its children
     * @param depth Indentation depth for formatting
     */
    void display(int depth = 0);

    /**
     * @brief Get total plant count in this section
     * @return Number of plants
     */
    int getPlantCount();

    /**
     * @brief Find a component by name
     * @param searchName Name to search for
     * @return Pointer to found component, nullptr if not found
     */
    GardenComponent* findByName(const std::string& searchName);

    /**
     * @brief Get a child component by index
     * @param index Index of the child
     * @return Pointer to child component, nullptr if index invalid
     */
    GardenComponent* getChild(size_t index);

    /**
     * @brief Get the component type
     * @return Type string "GardenSection"
     */
    std::string getType();

    /**
     * @brief Get the section name
     * @return Section name
     */
    std::string getName();
};

#endif // GARDEN_SECTION_H