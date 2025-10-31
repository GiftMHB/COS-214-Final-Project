// /**
//  * @file Plant.h
//  * @brief Header file for Plant class hierarchy
//  * @details Implements Factory Method, State, Strategy, and Observer patterns
//  */

// #ifndef PLANT_H
// #define PLANT_H

// #include <string>
// #include <vector>
// #include <map>
// #include <memory>
// #include <sstream>
// #include <iomanip>

// // Forward declarations
// class PlantState;
// class CareStrategy;
// class PlantObserver;

// /**
//  * @class Plant
//  * @brief Abstract base class for all plant types
//  * @details Implements the Subject in Observer pattern and Context for State/Strategy patterns
//  */
// class Plant {
// protected:
//     // Core attributes
//     std::string id;
//     std::string name;
//     std::string species;
//     std::string classification;
//     double price;
    
//     // Resource levels
//     int waterLevel;        // 0-100
//     int sunlightLevel;     // 0-100
//     int nutrientLevel;     // 0-100
//     int age;               // in days
//     double health;         // 0-100
    
//     // State management
//     PlantState* currentState;
//     CareStrategy* careStrategy;
//     std::vector<PlantObserver*> observers;
    
//     // Status
//     bool isAlive;
//     std::string status;    // "Available", "Sold", "Reserved"
    
//     // Static counter for ID generation
//     static int plantCount;
    
//     // Protected helper methods
//     void updateResourceLevels();
//     double calculateGrowthRate() const;
//     void checkHealth();
//     void updateHealth();

// public:
//     // Constructor and Destructor
//     Plant(const std::string& name, const std::string& species, double price);
//     virtual ~Plant();
    
//     // Pure virtual methods (must be implemented by derived classes)
//     virtual std::string getPlantType() const = 0;
//     virtual std::string getDescription() const = 0;
//     virtual std::string getCareInstructions() const = 0;
    
//     // Getters
//     std::string getId() const { return id; }
//     std::string getName() const { return name; }
//     std::string getSpecies() const { return species; }
//     std::string getClassification() const { return classification; }
//     double getPrice() const { return price; }
//     int getWaterLevel() const { return waterLevel; }
//     int getSunlightLevel() const { return sunlightLevel; }
//     int getNutrientLevel() const { return nutrientLevel; }
//     int getAge() const { return age; }
//     double getHealth() const { return health; }
//     bool getIsAlive() const { return isAlive; }
//     std::string getStatus() const { return status; }
//     PlantState* getState() const { return currentState; }
//     std::string getStateName() const;
//     CareStrategy* getCareStrategy() const { return careStrategy; }
    
//     // Setters
//     void setPrice(double newPrice) { price = newPrice; }
//     void setWaterLevel(int level);
//     void setSunlightLevel(int level);
//     void setNutrientLevel(int level);
//     void setAge(int newAge);
//     void setHealth(double newHealth);
//     void setStatus(const std::string& newStatus) { status = newStatus; }
    
//     // State Pattern methods
//     void setState(PlantState* newState);
    
//     // Strategy Pattern methods
//     void setCareStrategy(CareStrategy* strategy);
//     void applyCare();
//     std::string getCareStrategyName() const;
    
//     // Observer Pattern methods
//     void attach(PlantObserver* observer);
//     void detach(PlantObserver* observer);
//     void notify(const std::string& event);
    
//     // Core plant operations
//     void water(int amount);
//     void fertilize(int amount);
//     void addSunlight(int amount);
//     void exposeToSunlight(int hours);
//     void grow();
    
//     // Utility methods
//     bool isReadyForSale() const;
//     std::string getHealthStatus() const;
//     virtual void displayInfo() const;
//     void printStatus() const;
// };

// /**
//  * @class Flower
//  * @brief Concrete plant class for flowers
//  */
// class Flower : public Plant {
// private:
//     std::string color;
//     std::string bloomSeason;
//     int petalCount;
//     bool isFragrant;

// public:
//     Flower(const std::string& name, const std::string& species, double price,
//            const std::string& color, const std::string& bloomSeason, 
//            bool isFragrant, int petalCount);
    
//     // Implement pure virtual methods
//     std::string getPlantType() const override;
//     std::string getDescription() const override;
//     std::string getCareInstructions() const override;
    
//     // Flower-specific methods
//     std::string getColor() const { return color; }
//     std::string getBloomSeason() const { return bloomSeason; }
//     int getPetalCount() const { return petalCount; }
//     bool getIsFragrant() const { return isFragrant; }
//     bool isInBloom(const std::string& currentSeason) const;
    
//     void displayInfo() const override;
// };

// /**
//  * @class Tree
//  * @brief Concrete plant class for trees
//  */
// class Tree : public Plant {
// private:
//     double height;           // in meters
//     double trunkDiameter;    // in meters
//     std::string treeType;    // "Deciduous", "Evergreen", "Fruit"
//     bool isEvergreen;

// public:
//     Tree(const std::string& name, const std::string& species, double price,
//          double height, double trunkDiameter, const std::string& treeType, 
//          bool isEvergreen);
    
//     // Implement pure virtual methods
//     std::string getPlantType() const override;
//     std::string getDescription() const override;
//     std::string getCareInstructions() const override;
    
//     // Tree-specific methods
//     double getHeight() const { return height; }
//     double getTrunkDiameter() const { return trunkDiameter; }
//     std::string getTreeType() const { return treeType; }
//     bool getIsEvergreen() const { return isEvergreen; }
//     void growHeight(double heightIncrease);
//     void prune();
    
//     void displayInfo() const override;
// };

// /**
//  * @class Shrub
//  * @brief Concrete plant class for shrubs
//  */
// class Shrub : public Plant {
// private:
//     int bushiness;          // 1-10 scale
//     bool canBeTrimmed;
//     int branchCount;

// public:
//     Shrub(const std::string& name, const std::string& species, double price,
//           int bushiness, bool canBeTrimmed, int branchCount);
    
//     // Implement pure virtual methods
//     std::string getPlantType() const override;
//     std::string getDescription() const override;
//     std::string getCareInstructions() const override;
    
//     // Shrub-specific methods
//     int getBushiness() const { return bushiness; }
//     bool getCanBeTrimmed() const { return canBeTrimmed; }
//     int getBranchCount() const { return branchCount; }
//     void trim();
    
//     void displayInfo() const override;
// };

// /**
//  * @class Vegetable
//  * @brief Concrete plant class for vegetables
//  */
// class Vegetable : public Plant {
// private:
//     int harvestTime;        // days until ready to harvest
//     bool isEdible;
//     double yield;           // kg per plant
//     std::string vegetableType;

// public:
//     Vegetable(const std::string& name, const std::string& species, double price,
//               int harvestTime, bool isEdible, double yield, 
//               const std::string& vegetableType);
    
//     // Implement pure virtual methods
//     std::string getPlantType() const override;
//     std::string getDescription() const override;
//     std::string getCareInstructions() const override;
    
//     // Vegetable-specific methods
//     int getHarvestTime() const { return harvestTime; }
//     bool getIsEdible() const { return isEdible; }
//     double getYield() const { return yield; }
//     std::string getVegetableType() const { return vegetableType; }
//     bool isReadyToHarvest() const;
//     double harvest();
    
//     void displayInfo() const override;
// };

// // ============================================================================
// // RELATED PRODUCT CLASSES (Abstract Factory Pattern)
// // ============================================================================

// /**
//  * @class CareKit
//  * @brief Base class for plant care kits
//  */
// class CareKit {
// protected:
//     std::string id;
//     std::string plantType;
//     std::string fertilizerType;
//     std::string pesticide;
//     std::vector<std::string> tools;
//     std::string instructions;
//     double price;

// public:
//     CareKit(const std::string& plantType, double price);
//     virtual ~CareKit() = default;
    
//     virtual void applyCare(Plant* plant) = 0;
//     virtual std::string getKitDescription() const = 0;
    
//     std::string getId() const { return id; }
//     std::string getPlantType() const { return plantType; }
//     std::string getFertilizerType() const { return fertilizerType; }
//     std::string getPesticide() const { return pesticide; }
//     std::vector<std::string> getTools() const { return tools; }
//     std::string getInstructions() const { return instructions; }
//     double getPrice() const { return price; }
    
//     void displayInfo() const;
// };

// /**
//  * @class FlowerCareKit
//  * @brief Care kit specialized for flowers
//  */
// class FlowerCareKit : public CareKit {
// public:
//     FlowerCareKit();
//     void applyCare(Plant* plant) override;
//     std::string getKitDescription() const override;
// };

// /**
//  * @class TreeCareKit
//  * @brief Care kit specialized for trees
//  */
// class TreeCareKit : public CareKit {
// private:
//     std::string treeFood;
//     std::string mulchType;

// public:
//     TreeCareKit();
//     void applyCare(Plant* plant) override;
//     std::string getKitDescription() const override;
// };

// /**
//  * @class Soil
//  * @brief Base class for soil products
//  */
// class Soil {
// protected:
//     std::string id;
//     std::string soilType;
//     double phLevel;
//     std::map<std::string, int> nutrientContent;
//     int drainageRate;
//     double price;

// public:
//     Soil(const std::string& soilType, double phLevel, double price);
//     virtual ~Soil() = default;
    
//     virtual bool isOptimalFor(const std::string& plantType) const = 0;
//     virtual std::string getSoilDescription() const = 0;
    
//     std::string getId() const { return id; }
//     std::string getSoilType() const { return soilType; }
//     double getPhLevel() const { return phLevel; }
//     void setPhLevel(double ph) { phLevel = ph; }
//     std::map<std::string, int> getNutrientContent() const { return nutrientContent; }
//     int getDrainageRate() const { return drainageRate; }
//     double getPrice() const { return price; }
    
//     void addNutrient(const std::string& nutrient, int amount);
//     void displayInfo() const;
// };

// /**
//  * @class FlowerSoil
//  * @brief Soil optimized for flowers
//  */
// class FlowerSoil : public Soil {
// public:
//     FlowerSoil();
//     bool isOptimalFor(const std::string& plantType) const override;
//     std::string getSoilDescription() const override;
// };

// /**
//  * @class TreeSoil
//  * @brief Soil optimized for trees
//  */
// class TreeSoil : public Soil {
// public:
//     TreeSoil();
//     bool isOptimalFor(const std::string& plantType) const override;
//     std::string getSoilDescription() const override;
// };

// #endif // PLANT_H 

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
#include "CareStrategy.h"
#include "PlantObserver.h"  // For Observer pattern (assume teammate provides)

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
    std::list<PlantObserver*> observers;  // Added for Observer pattern (Tiego)

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

    virtual ~Plant();

    // Price management (Gift + plan)
    void setPrice(double price);
    double getPrice() const;

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
    void attach(PlantObserver* observer);
    void detach(PlantObserver* observer);
    void notifyObservers();

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