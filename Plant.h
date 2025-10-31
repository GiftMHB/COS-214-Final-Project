/**
 * @file Plant.h
 * @brief Abstract base class for plants in the Garden Center Management System
 * @details Merges the project plan's detailed Plant design with Gift's implementation,
 *          adding missing methods, Observer pattern, and ensuring compatibility with
 *          all patterns (Factory, State, Strategy, Observer, Decorator, etc.).
 *          id changed to string for plan compatibility. Added sunlightLevel.
 *          exposeToSunlight updates sunlightLevel. Added plan ctors and methods.
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <list>
#include "PlantState.h"
// #include "CareStrategy.h"
#include "Observer.h"  // For Observer pattern (assume teammate provides)

class CareStrategy;  

using namespace std;

/**
 * @struct PlantInfo
 * @brief Bundles plant attributes (from Gift's design, with additions)
 */
struct PlantInfo {
    std::string id;  // Changed to string to match plan
    std::string name;
    std::string classification;  // Equivalent to species in plan
    std::string addedDate;
    double purchasePrice;
    double salePrice;
    
    // Static plant counter for auto ID generation
    static int plantCount;

    // Resource levels (defaults from Gift, added sunlightLevel from plan)
    int waterLevel = 20;
    int sunlightLevel = 0;  // Added to match plan's current sunlight tracking
    int healthLevel = 100;
    int sunlightNeed = 5;
    int fertilizerNeed = 2;
    int nutrientLevel = 50;
    
    // Growth tracking
    double currentHeight = 0.0;
    double maturityHeight = 100.0;
    int currentAgeDays = 0;
    int daysToMaturity = 365;
};

/**
 * @class Plant
 * @brief Abstract Plant class implementing State, Strategy, and Observer patterns
 */
class Plant {
protected:
    PlantInfo info;
    CareStrategy* careStrategy;
    PlantState* state;
    std::list<Observer*> observers;  // Added for Observer pattern (Tiego)

    // Protected methods from plan
    virtual void updateResourceLevels();  // Added
    virtual double calculateGrowthRate();  // Added

public:
    /**
     * @brief Constructor from PlantInfo (Gift's style)
     */
    Plant(PlantInfo& info);

    /**
     * @brief Constructor from plan (name, species/classification, price)
     */
    Plant(const std::string& name, const std::string& classification, double price);

    Plant(const Plant& other); 

    virtual ~Plant();

    // Price management (Gift + plan)
    void setPrice(double price);
    virtual double getPrice() const;
    

    // Pure virtual from plan/Gift
    virtual std::string getDescription() const = 0;

    // State management (Gift + plan)
    int getID() const;
    PlantState* getState() const;
    void setState(PlantState* newState);
    std::string getCurrentStateName() const;

    // Strategy management (Gift + plan: renamed applyCareStrategy to applyCare)
    void setCareStrategy(CareStrategy* strategy);
    void applyCare();  // Delegates to strategy (plan name)
    std::string getCareStrategyName() const;

    // Observer pattern (added from plan)
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notifyObservers(const std::string& eventType);

    // Basic getters (Gift + plan)
    std::string getName() const;
    std::string getClassification() const;  // species
    std::string getDate() const;
    
    // Level getters/setters (Gift + plan)
    int getWaterLevel() const;
    void setWaterLevel(int level);
    int getSunlightLevel() const;  // Added
    void setSunlightLevel(int level);  // Added
    int getHealthLevel() const;
    void setHealthLevel(int level);
    int getNutrientLevel() const;
    void setNutrientLevel(int level);
    
    // Age management (Gift + plan)
    int getAge() const;
    void setAge(int newAge);

    // Plant actions (Gift + plan: made virtual for Decorator)
    virtual void water(int amount);
    virtual void fertilize(int amount);
    virtual void addSunlight(int amount);  // Added alias for plan
    virtual void exposeToSunlight(int hours);  // Gift's, updates sunlightLevel
    virtual void grow();
    void printStatus() const;  // Gift's

    // Additional from plan
    void checkHealth();  // Added: checks levels, notifies if needed
};

#endif // PLANT_H