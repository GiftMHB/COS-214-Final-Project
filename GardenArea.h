#ifndef GARDENAREA_H
#define GARDENAREA_H

#include <vector>
#include <string>

class GardenSection; // Forward declaration

class GardenArea {
private:
    static GardenArea* instance;
    std::vector<GardenSection*> sections;
    int totalCapacity;
    double temperature;
    int humidity;
    
    // Private constructor for Singleton
    GardenArea();
    
    // Delete copy constructor and assignment operator
    GardenArea(const GardenArea&) = delete;
    GardenArea& operator=(const GardenArea&) = delete;

public:
    // Singleton access
    static GardenArea* getInstance();
    
    // Section management
    void addSection(GardenSection* section);
    bool removeSection(const std::string& sectionId);
    GardenSection* getSection(const std::string& id);
    std::vector<GardenSection*> getAllSections() const;
    
    // Capacity
    int getTotalCapacity() const;
    
    // Environmental conditions
    void setTemperature(double temp);
    double getTemperature() const;
    void setHumidity(int humidity);
    int getHumidity() const;
    
    // Destructor
    ~GardenArea();
};

#endif // GARDENAREA_H