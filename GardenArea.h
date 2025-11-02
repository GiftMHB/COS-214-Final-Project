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

#ifndef GARDEN_AREA_H
#define GARDEN_AREA_H

#include "GardenComponent.h"
#include <string>
#include <vector>
#include <list>  // Explicit include for std::list<Plant*>

class GardenArea : public GardenComponent {
private:
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
    static GardenArea& getInstance();

    ~GardenArea();

    void add(GardenComponent* section) override;
    void remove(GardenComponent* section) override;
    void display(int depth = 0) override;
    int getPlantCount() override;
    GardenComponent* findByName(const std::string& name) override;
    std::list<Plant*> getAllPlants() override; //virtual std::list<Plant*> getAllPlants() = 0;
    std::string getType() override;
    std::string getName() override;

    void setTemperature(double temp);
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