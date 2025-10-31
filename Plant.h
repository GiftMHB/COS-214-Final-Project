/**
 * @file Plant.h
 * @brief Plant class hierarchy and related product classes
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// ============================================================================
// PLANT CLASS HIERARCHY
// ============================================================================

/**
 * @brief Base Plant class with common properties and methods
 */


class Plant {
protected:
    std::string id;
    std::string name;
    std::string species;
    double price;
    int waterLevel;
    int sunlightLevel;
    int nutrientLevel;
    std::string status;

public:
    Plant(const std::string& name, const std::string& species, double price);
    virtual ~Plant() = default;

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    double getPrice() const { return price; }
    int getWaterLevel() const { return waterLevel; }
    int getSunlightLevel() const { return sunlightLevel; }
    int getNutrientLevel() const { return nutrientLevel; }
    std::string getStatus() const { return status; }

    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setWaterLevel(int level) { waterLevel = std::max(0, std::min(100, level)); }
    void setSunlightLevel(int level) { sunlightLevel = std::max(0, std::min(100, level)); }
    void setNutrientLevel(int level) { nutrientLevel = std::max(0, std::min(100, level)); }
    void setStatus(const std::string& newStatus) { status = newStatus; }

    // Plant care methods
    virtual void water(int amount);
    virtual void addSunlight(int amount);
    virtual void fertilize(int amount);

    // Sales methods
    void markAsSold() { status = "Sold"; }
    void markAsAvailable() { status = "Available"; }

    virtual std::string getPlantType() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getCareInstructions() const = 0;

    // Health assessment
    virtual std::string getHealthStatus() const;
    virtual void displayInfo() const;
};

/**
 * @brief Flower plant specialization
 */
class Flower : public Plant {
private:
    std::string color;
    std::string bloomSeason;
    bool isFragrant;
    int petalCount;

public:
    Flower(const std::string& name, const std::string& species, double price,
           const std::string& color, const std::string& bloomSeason, 
           bool isFragrant = false, int petalCount = 5);

    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;

    // Flower-specific methods
    std::string getColor() const { return color; }
    std::string getBloomSeason() const { return bloomSeason; }
    bool isFragrantFlower() const { return isFragrant; }
    int getPetalCount() const { return petalCount; }

    bool isInBloom(const std::string& currentSeason) const;
    void displayInfo() const override;
};

/**
 * @brief Tree plant specialization
 */
class Tree : public Plant {
private:
    double height;
    double trunkDiameter;
    std::string treeType;
    bool isEvergreen;

public:
    Tree(const std::string& name, const std::string& species, double price,
         double height, double trunkDiameter, const std::string& treeType, 
         bool isEvergreen = false);

    std::string getPlantType() const override;
    std::string getDescription() const override;
    std::string getCareInstructions() const override;

    // Tree-specific methods
    double getHeight() const { return height; }
    double getTrunkDiameter() const { return trunkDiameter; }
    std::string getTreeType() const { return treeType; }
    bool isEvergreenTree() const { return isEvergreen; }

    void grow(double heightIncrease = 0.1);
    void prune();
    void displayInfo() const override;
};

// ============================================================================
// CARE KIT CLASS HIERARCHY
// ============================================================================

/**
 * @brief Base CareKit class
 */
class CareKit {
protected:
    std::string id;
    std::string plantType;
    std::vector<std::string> tools;
    std::string instructions;
    double price;

public:
    CareKit(const std::string& plantType, double price);
    virtual ~CareKit() = default;

    std::string getId() const { return id; }
    std::string getPlantType() const { return plantType; }
    double getPrice() const { return price; }
    std::vector<std::string> getTools() const { return tools; }
    std::string getInstructions() const { return instructions; }

    virtual void applyCare(Plant* plant) = 0;
    virtual std::string getKitDescription() const = 0;
    void displayInfo() const;
};

/**
 * @brief Flower-specific care kit
 */
class FlowerCareKit : public CareKit {
private:
    std::string fertilizerType;
    std::string pesticide;

public:
    FlowerCareKit();
    void applyCare(Plant* plant) override;
    std::string getKitDescription() const override;
};

/**
 * @brief Tree-specific care kit
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

// ============================================================================
// SOIL CLASS HIERARCHY
// ============================================================================

/**
 * @brief Base Soil class
 */
class Soil {
protected:
    std::string id;
    std::string soilType;
    double phLevel;
    std::map<std::string, int> nutrientContent;
    double price;

public:
    Soil(const std::string& soilType, double phLevel, double price);
    virtual ~Soil() = default;

    std::string getId() const { return id; }
    std::string getSoilType() const { return soilType; }
    double getPhLevel() const { return phLevel; }
    double getPrice() const { return price; }
    std::map<std::string, int> getNutrientContent() const { return nutrientContent; }

    virtual bool isOptimalFor(const std::string& plantType) const = 0;
    virtual std::string getSoilDescription() const = 0;

    void addNutrient(const std::string& nutrient, int amount);
    void displayInfo() const;
};

/**
 * @brief Flower-optimized soil
 */
class FlowerSoil : public Soil {
public:
    FlowerSoil();
    bool isOptimalFor(const std::string& plantType) const override;
    std::string getSoilDescription() const override;
};

/**
 * @brief Tree-optimized soil
 */
class TreeSoil : public Soil {
public:
    TreeSoil();
    bool isOptimalFor(const std::string& plantType) const override;
    std::string getSoilDescription() const override;
};

#endif // PLANT_H