// #ifndef GARDENAREA_H
// #define GARDENAREA_H

// #include <vector>
// #include <string>

// class GardenSection; // Forward declaration

// class GardenArea {
// private:
//     static GardenArea* instance;
//     std::vector<GardenSection*> sections;
//     int totalCapacity;
//     double temperature;
//     int humidity;
    
//     // Private constructor for Singleton
//     GardenArea();
    
//     // Delete copy constructor and assignment operator
//     GardenArea(const GardenArea&) = delete;
//     GardenArea& operator=(const GardenArea&) = delete;

// public:
//     // Singleton access
//     static GardenArea* getInstance();
    
//     // Section management
//     void addSection(GardenSection* section);
//     bool removeSection(const std::string& sectionId);
//     GardenSection* getSection(const std::string& id);
//     std::vector<GardenSection*> getAllSections() const;
    
//     // Capacity
//     int getTotalCapacity() const;
    
//     // Environmental conditions
//     void setTemperature(double temp);
//     double getTemperature() const;
//     void setHumidity(int humidity);
//     int getHumidity() const;
    
//     // Destructor
//     ~GardenArea();
// };

// #endif // GARDENAREA_H
/**
 * @file GardenArea.h
 * @brief Composite root class representing the entire garden area (Singleton)
 * @details Implements both Composite and Singleton patterns to manage the top-level
 *          garden hierarchy with a single instance.
 */

#ifndef GARDEN_AREA_H
#define GARDEN_AREA_H

#include "GardenComponent.h"
#include <string>
#include <vector>
#include <list>  // Explicit include for std::list<Plant*>

class GardenArea : public GardenComponent {
private:
/**
* @brief Private constructor for Singleton pattern
*/
    static GardenArea* instance;  ///< Singleton instance pointer (for internal management)
    std::vector<GardenComponent*> sections;  ///< Child sections/beds (composite)
    int totalCapacity;
    double temperature;
    double humidity;
    std::string name;
    std::string id;

    GardenArea();
    GardenArea(const GardenArea&);
    GardenArea& operator=(const GardenArea&);

public:
/**
* @brief Get the singleton instance of GardenArea
* @return Reference to the GardenArea instance
*/
    static GardenArea& getInstance();

    ~GardenArea();
 /**
     * @brief Add a section to the garden
     * @param section Pointer to the section to add
     */

    void add(GardenComponent* section) override;
/**
     * @brief Remove a section from the garden
     * @param section Pointer to the section to remove
     */
    void remove(GardenComponent* section) override;
/**
     * @brief Display the entire garden hierarchy
     * @param depth Indentation depth for display formatting
     */
    void display(int depth = 0) override;
/**
     * @brief Get total plant count across all sections
     * @return Total number of plants
     */
    int getPlantCount() override;
/**
     * @brief Find a component by name in the hierarchy
     * @param name Name to search for
     * @return Pointer to found component, nullptr if not found
     */
    GardenComponent* findByName(const std::string& name) override;
/**
     * @brief Get all plants from all sections
     * @return List of plant pointers
     */
    std::list<Plant*> getAllPlants() override; //virtual std::list<Plant*> getAllPlants() = 0;
    std::string getType() override;
    std::string getName() override;

    void setTemperature(double temp);
/**
     * @brief Get the current temperature
     * @return Current temperature
     */
    double getTemperature() const;
    void setHumidity(double hum);
    double getHumidity() const;

    // Compatibility methods from simple version
    void addSection(GardenComponent* section);
    bool removeSection(const std::string& sectionId);
    GardenComponent* getSection(const std::string& id);
    std::vector<GardenComponent*> getAllSections() const;
    int getTotalCapacity() const;
};

#endif // GARDEN_AREA_H
