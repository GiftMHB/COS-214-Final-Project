/**
 * @file GardenArea.h
 * @brief Composite root class representing the entire garden area (Singleton)
 * @details Implements both Composite and Singleton patterns to manage the top-level
 *          garden hierarchy with a single instance.
 */

#ifndef GARDEN_AREA_H
#define GARDEN_AREA_H

#include "GardenComponent.h"          // Composite base class
#include <list>
#include <string>
#include <vector>

// Forward declarations
class Plant;
class GardenSection;                  // for your original API

/**
 * @class GardenArea
 * @brief Singleton composite root managing all garden sections
 */
class GardenArea : public GardenComponent {
private:
    static GardenArea* instance;               ///< Singleton instance
    std::list<GardenComponent*> sections;      ///< Composite children (list as teammate used)
    std::vector<GardenSection*> sectionVec;    ///< Compatibility view for your old API

    int totalCapacity;        ///< Maximum capacity of the garden
    double temperature;       ///< Current temperature
    double humidity;          ///< Current humidity level
    std::string id;           ///< Unique identifier
    std::string name;         ///< Human-readable name (used by findByName / getName)

    /** Private constructor – Singleton */
    GardenArea();

    /** Deleted copy / assignment – Singleton */
    GardenArea(const GardenArea&) = delete;
    GardenArea& operator=(const GardenArea&) = delete;

    /** Helper – keep the vector view in sync with the list */
    void syncVectorView();

public:
    /** -------------------------------------------------------------
     *  Singleton access
     *  ------------------------------------------------------------- */
    static GardenArea& getInstance();          // returns reference (teammate style)
    static GardenArea* getInstancePtr();       // your original pointer version

    /** -------------------------------------------------------------
     *  Composite interface (required by teammate)
     *  ------------------------------------------------------------- */
    void add(GardenComponent* section) override;
    void remove(GardenComponent* section) override;
    void display(int depth = 0) override;

    int getPlantCount() override;
    GardenComponent* findByName(const std::string& name) override;
    std::list<Plant*> getAllPlants() override;

    std::string getType() override { return "GardenArea"; }
    std::string getName() override { return name; }

    /** -------------------------------------------------------------
     *  Your original API (kept fully functional)
     *  ------------------------------------------------------------- */
    void addSection(GardenSection* section);
    bool removeSection(const std::string& sectionId);
    GardenSection* getSection(const std::string& id);
    std::vector<GardenSection*> getAllSections() const;

    int getTotalCapacity() const { return totalCapacity; }

    void setTemperature(double temp) { temperature = temp; }
    double getTemperature() const { return temperature; }

    void setHumidity(double hum) { humidity = hum; }
    double getHumidity() const { return humidity; }

    /** -------------------------------------------------------------
     *  Destructor – cleans up all children
     *  ------------------------------------------------------------- */
    ~GardenArea() override;
};

#endif // GARDEN_AREA_H