/**
 * @file Plant.h
 * @brief Unified Plant class combining both implementations
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
#include "PlantState.h"
#include "CareStrategy.h"
#include "Observer.h"
#include "Subject.h"

using namespace std;

/**
 * @struct PlantInfo
 * @brief Their complex plant attributes structure
 */
struct PlantInfo {
    std::string id;
    std::string name;
    std::string classification;
    std::string species;
    std::string addedDate;
    double purchasePrice;
    double salePrice;
    
    static int plantCount;

    // Resource levels
    int waterLevel = 20;
    int sunlightLevel = 0;
    int healthLevel = 100;
    int sunlightNeed = 5;
    int fertilizerNeed = 2;
    int nutrientLevel = 50;
    
    // Growth tracking
    double currentHeight = 0.0;
    double maturityHeight = 100.0;
    int currentAgeDays = 0;
    int daysToMaturity = 365;
    
    // YOUR ADDITION: isAlive boolean
    bool isAlive = true;
    bool readyForSale = false;
};

/**
 * @class Plant
 * @brief Unified Plant class with both implementations
 */
class Plant : public Subject {
protected:
    PlantInfo info;
    CareStrategy* careStrategy;
    PlantState* state;

public:
    // === BOTH CONSTRUCTORS ===
    
    // THEIR constructor
    Plant(PlantInfo& info);
    Plant(const std::string& name, const std::string& classification, double price);
    
    // YOUR constructor
    Plant(const std::string& plantName, const std::string& plantSpecies);
    
    Plant(const Plant& other);
    virtual ~Plant();

    // === YOUR METHODS (added to their class) ===
    
    // Your core methods
    void changeState(PlantState* newState);  // YOUR METHOD
    double getHealth() const;  // YOUR METHOD (returns double)
    bool getIsAlive() const;  // YOUR METHOD
    
    // === THEIR METHODS (keep all of theirs) ===
    
    // Identification
    std::string getId() const;
    std::string getName() const;
    std::string getSpecies() const;
    std::string getClassification() const;
    std::string getDate() const;

    // Price management
    virtual double getPrice() const;
    void setPrice(double price);
    double getSalePrice() const;

    // State management
    PlantState* getState() const;
    void setState(PlantState* newState);
    std::string getCurrentStateName() const;
    int getHealthPercentage() const;  // THEIR METHOD (returns int)

    // Strategy management
    void setCareStrategy(CareStrategy* strategy);
    void applyCare();
    std::string getCareStrategyName() const;

    // Resource level management
    int getWaterLevel() const;
    void setWaterLevel(int level);
    int getSunlightLevel() const;
    void setSunlightLevel(int level);
    void setHealthLevel(int level);  // THEIR METHOD (takes int)
    int getNutrientLevel() const;
    void setNutrientLevel(int level);

    // Growth & age management
    int getAge() const;
    void setAge(int newAge);
    double getCurrentHeight() const;
    double getMaturityHeight() const;
    void setCurrentHeight(double height);

    // Plant actions
    virtual void water(int amount);
    virtual void fertilize(int amount);
    virtual void addSunlight(int amount);
    virtual void exposeToSunlight(int hours);
    virtual void grow();
    virtual void checkHealth();
    
    // Composite pattern
    virtual std::string getDescription() const;
    
    // Observer pattern (inherited from Subject)
    
    // Additional methods
    bool isReadyForSale() const;  // BOTH HAVE THIS
    void setReadyForSale(bool ready);
    void printStatus() const;
    
protected:
    virtual void updateResourceLevels();
    virtual double calculateGrowthRate();
    void notifyHealthChange();
    void notifyGrowth();
    void notifyCareApplied(const std::string& careType);
};

#endif // PLANT_H