/**
 * @file Plant.h
 * @brief Header file for Plant class hierarchy
 * @details Implements Factory Method, State, Strategy, and Observer patterns
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>

// Forward declarations
class PlantState;
class CareStrategy;
class PlantObserver;

/**
 * @class Plant
 * @brief Abstract base class for all plant types
 * @details Implements the Subject in Observer pattern and Context for State/Strategy patterns
 */
class Plant {
protected:
    // Core attributes
    std::string id;
    std::string name;
    std::string species;
    std::string classification;
    double price;
    
    // Resource levels
    int waterLevel;        // 0-100
    int sunlightLevel;     // 0-100
    int nutrientLevel;     // 0-100
    int age;               // in days
    double health;         // 0-100
    
    // State management
    PlantState* currentState;
    CareStrategy* careStrategy;
    std::vector<PlantObserver*> observers;
    
    // Status
    bool isAlive;
    std::string status;    // "Available", "Sold", "Reserved"
    
    // Static counter for ID generation
    static int plantCount;
    
    // Protected helper methods
    void updateResourceLevels();
    double calculateGrowthRate() const;
    void checkHealth();
    void updateHealth();

public:
    // Constructor and Destructor
    Plant(const std::string& name, const std::string& species, double price);
    virtual ~Plant();
    
    // Pure virtual methods (must be implemented by derived classes)
    virtual std::string getPlantType() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getCareInstructions() const = 0;
    
    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    std::string getClassification() const { return classification; }
    double getPrice() const { return price; }
    int getWaterLevel() const { return waterLevel; }
    int getSunlightLevel() const { return sunlightLevel; }
    int getNutrientLevel() const { return nutrientLevel; }
    int getAge() const { return age; }
    double getHealth() const { return health; }
    bool getIsAlive() const { return isAlive; }
    std::string getStatus() const { return status; }
    PlantState* getState() const { return currentState; }
    std::string getStateName() const;
    CareStrategy* getCareStrategy() const { return careStrategy; }
    
    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setWaterLevel(int level);
    void setSunlightLevel(int level);
    void setNutrientLevel(int level);
    void setAge(int newAge);
    void setHealth(double newHealth);
    void setStatus(const std::string& newStatus) { status = newStatus; }
    
    // State Pattern methods
    void setState(PlantState* newState);
    
    // Strategy Pattern methods
    void setCareStrategy(CareStrategy* strategy);
    void applyCare();
    std::string getCareStrategyName() const;
    
    // Observer Pattern methods
    void attach(PlantObserver* observer);
    void detach(PlantObserver* observer);
    void notify(const std::string& event);
    
    // Core plant operations
    void water(int amount);
    void fertilize(int amount);
    void addSunlight(int amount);
    void exposeToSunlight(int hours);
    void grow();
    
    // Utility methods
    bool isReadyForSale() const;
    std::string getHealthStatus() const;
    virtual void displayInfo() const;
    void printStatus() const;
};

/**
 * @class Flower
 * @brief Concrete plant class for flowers
 */
class Flower : public Plant {
private:
    std::string color;
    std::string bloomSeason;
    int petalCount;
    bool isFragrant;

public:
    Flower(const std::string& name, const std::string& species, double price,
           const std::string& color, const std::string& bloomSeason, 
           bool isFragrant, int petalCount);
    
    // Implement pure virtual methods
    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;
    
    // Flower-specific methods
    std::string getColor() const { return color; }
    std::string getBloomSeason() const { return bloomSeason; }
    int getPetalCount() const { return petalCount; }
    bool getIsFragrant() const { return isFragrant; }
    bool isInBloom(const std::string& currentSeason) const;
    
    void displayInfo() const override;
};

/**
 * @class Tree
 * @brief Concrete plant class for trees
 */
class Tree : public Plant {
private:
    double height;           // in meters
    double trunkDiameter;    // in meters
    std::string treeType;    // "Deciduous", "Evergreen", "Fruit"
    bool isEvergreen;

public:
    Tree(const std::string& name, const std::string& species, double price,
         double height, double trunkDiameter, const std::string& treeType, 
         bool isEvergreen);
    
    // Implement pure virtual methods
    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;
    
    // Tree-specific methods
    double getHeight() const { return height; }
    double getTrunkDiameter() const { return trunkDiameter; }
    std::string getTreeType() const { return treeType; }
    bool getIsEvergreen() const { return isEvergreen; }
    void growHeight(double heightIncrease);
    void prune();
    
    void displayInfo() const override;
};

/**
 * @class Shrub
 * @brief Concrete plant class for shrubs
 */
class Shrub : public Plant {
private:
    int bushiness;          // 1-10 scale
    bool canBeTrimmed;
    int branchCount;

public:
    Shrub(const std::string& name, const std::string& species, double price,
          int bushiness, bool canBeTrimmed, int branchCount);
    
    // Implement pure virtual methods
    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;
    
    // Shrub-specific methods
    int getBushiness() const { return bushiness; }
    bool getCanBeTrimmed() const { return canBeTrimmed; }
    int getBranchCount() const { return branchCount; }
    void trim();
    
    void displayInfo() const override;
};

/**
 * @class Vegetable
 * @brief Concrete plant class for vegetables
 */
class Vegetable : public Plant {
private:
    int harvestTime;        // days until ready to harvest
    bool isEdible;
    double yield;           // kg per plant
    std::string vegetableType;

public:
    Vegetable(const std::string& name, const std::string& species, double price,
              int harvestTime, bool isEdible, double yield, 
              const std::string& vegetableType);
    
    // Implement pure virtual methods
    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;
    
    // Vegetable-specific methods
    int getHarvestTime() const { return harvestTime; }
    bool getIsEdible() const { return isEdible; }
    double getYield() const { return yield; }
    std::string getVegetableType() const { return vegetableType; }
    bool isReadyToHarvest() const;
    double harvest();
    
    void displayInfo() const override;
};

// ============================================================================
// RELATED PRODUCT CLASSES (Abstract Factory Pattern)
// ============================================================================

/**
 * @class CareKit
 * @brief Base class for plant care kits
 */
class CareKit {
protected:
    std::string id;
    std::string plantType;
    std::string fertilizerType;
    std::string pesticide;
    std::vector<std::string> tools;
    std::string instructions;
    double price;

public:
    CareKit(const std::string& plantType, double price);
    virtual ~CareKit() = default;
    
    virtual void applyCare(Plant* plant) = 0;
    virtual std::string getKitDescription() const = 0;
    
    std::string getId() const { return id; }
    std::string getPlantType() const { return plantType; }
    std::string getFertilizerType() const { return fertilizerType; }
    std::string getPesticide() const { return pesticide; }
    std::vector<std::string> getTools() const { return tools; }
    std::string getInstructions() const { return instructions; }
    double getPrice() const { return price; }
    
    void displayInfo() const;
};

/**
 * @class FlowerCareKit
 * @brief Care kit specialized for flowers
 */
class FlowerCareKit : public CareKit {
public:
    FlowerCareKit();
    void applyCare(Plant* plant) override;
    std::string getKitDescription() const override;
};

/**
 * @class TreeCareKit
 * @brief Care kit specialized for trees
 */
class TreeCareKit : public CareKit {
private:
    std::string treeFood;
    std::string mulchType;

public:
    TreeCareKit();
    void applyCare(Plant* plant) override;
    std::string getKitDescription() const override;
};

/**
 * @class Soil
 * @brief Base class for soil products
 */
class Soil {
protected:
    std::string id;
    std::string soilType;
    double phLevel;
    std::map<std::string, int> nutrientContent;
    int drainageRate;
    double price;

public:
    Soil(const std::string& soilType, double phLevel, double price);
    virtual ~Soil() = default;
    
    virtual bool isOptimalFor(const std::string& plantType) const = 0;
    virtual std::string getSoilDescription() const = 0;
    
    std::string getId() const { return id; }
    std::string getSoilType() const { return soilType; }
    double getPhLevel() const { return phLevel; }
    void setPhLevel(double ph) { phLevel = ph; }
    std::map<std::string, int> getNutrientContent() const { return nutrientContent; }
    int getDrainageRate() const { return drainageRate; }
    double getPrice() const { return price; }
    
    void addNutrient(const std::string& nutrient, int amount);
    void displayInfo() const;
};

/**
 * @class FlowerSoil
 * @brief Soil optimized for flowers
 */
class FlowerSoil : public Soil {
public:
    FlowerSoil();
    bool isOptimalFor(const std::string& plantType) const override;
    std::string getSoilDescription() const override;
};

/**
 * @class TreeSoil
 * @brief Soil optimized for trees
 */
class TreeSoil : public Soil {
public:
    TreeSoil();
    bool isOptimalFor(const std::string& plantType) const override;
    std::string getSoilDescription() const override;
};

#endif // PLANT_H