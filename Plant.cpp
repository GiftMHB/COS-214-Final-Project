/**
 * @file Plant.cpp
 * @brief Implementation of Plant class hierarchy and related products
 */

#include "Plant.h"

// ============================================================================
// PLANT CLASS IMPLEMENTATIONS
// ============================================================================

// Base Plant implementation
Plant::Plant(const std::string& name, const std::string& species, double price) 
    : name(name), species(species), price(price), waterLevel(50), 
      sunlightLevel(50), nutrientLevel(50), status("Available") {
    // Generate simple ID based on name and species
    std::stringstream ss;
    ss << name.substr(0, 3) << "_" << species.substr(0, 3) << "_" 
       << (std::rand() % 10000);
    id = ss.str();
}

void Plant::water(int amount) {
    waterLevel = std::min(100, waterLevel + amount);
    std::cout << "Watered " << name << " with " << amount << "ml. Water level: " << waterLevel << "%\n";
}

void Plant::addSunlight(int amount) {
    sunlightLevel = std::min(100, sunlightLevel + amount);
    std::cout << "Added " << amount << " units of sunlight to " << name << ". Sunlight level: " << sunlightLevel << "%\n";
}

void Plant::fertilize(int amount) {
    nutrientLevel = std::min(100, nutrientLevel + amount);
    std::cout << "Fertilized " << name << " with " << amount << " units. Nutrient level: " << nutrientLevel << "%\n";
}

std::string Plant::getHealthStatus() const {
    int averageHealth = (waterLevel + sunlightLevel + nutrientLevel) / 3;
    if (averageHealth >= 80) return "Excellent";
    if (averageHealth >= 60) return "Good";
    if (averageHealth >= 40) return "Fair";
    if (averageHealth >= 20) return "Poor";
    return "Critical";
}

void Plant::displayInfo() const {
    std::cout << "=== " << name << " ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Species: " << species << "\n";
    std::cout << "Type: " << getPlantType() << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    std::cout << "Status: " << status << "\n";
    std::cout << "Health: " << getHealthStatus() << "\n";
    std::cout << "Water: " << waterLevel << "%, Sunlight: " << sunlightLevel 
              << "%, Nutrients: " << nutrientLevel << "%\n";
    std::cout << "Description: " << getDescription() << "\n";
    std::cout << "Care: " << getCareInstructions() << "\n";
}

// Flower implementation
Flower::Flower(const std::string& name, const std::string& species, double price,
       const std::string& color, const std::string& bloomSeason, 
       bool isFragrant, int petalCount)
    : Plant(name, species, price), color(color), bloomSeason(bloomSeason),
      isFragrant(isFragrant), petalCount(petalCount) {}

std::string Flower::getPlantType() const { return "Flower"; }

std::string Flower::getDescription() const {
    std::stringstream ss;
    ss << "Beautiful " << color << " " << name << " that blooms in " << bloomSeason 
       << ". " << (isFragrant ? "Has a lovely fragrance." : "No significant fragrance.");
    return ss.str();
}

std::string Flower::getCareInstructions() const {
    return "Water daily, provide 6+ hours of sunlight, fertilize weekly during growing season.";
}

bool Flower::isInBloom(const std::string& currentSeason) const {
    return bloomSeason == "All" || bloomSeason == currentSeason;
}

void Flower::displayInfo() const {
    Plant::displayInfo();
    std::cout << "Color: " << color << "\n";
    std::cout << "Bloom Season: " << bloomSeason << "\n";
    std::cout << "Fragrant: " << (isFragrant ? "Yes" : "No") << "\n";
    std::cout << "Petal Count: " << petalCount << "\n";
}

// Tree implementation
Tree::Tree(const std::string& name, const std::string& species, double price,
     double height, double trunkDiameter, const std::string& treeType, 
     bool isEvergreen)
    : Plant(name, species, price), height(height), trunkDiameter(trunkDiameter),
      treeType(treeType), isEvergreen(isEvergreen) {}

std::string Tree::getPlantType() const { return "Tree"; }

std::string Tree::getDescription() const {
    std::stringstream ss;
    ss << "Majestic " << name << " tree standing " << height 
       << "m tall with " << trunkDiameter << "m trunk diameter. "
       << (isEvergreen ? "Evergreen" : "Deciduous") << " " << treeType << " tree.";
    return ss.str();
}

std::string Tree::getCareInstructions() const {
    return "Water deeply weekly, provide full sunlight, fertilize seasonally, prune annually.";
}

void Tree::grow(double heightIncrease) {
    height += heightIncrease;
    std::cout << name << " grew " << heightIncrease << "m. Current height: " << height << "m\n";
}

void Tree::prune() {
    std::cout << "Pruned " << name << " for better shape and health.\n";
    nutrientLevel = std::max(0, nutrientLevel - 10);
}

void Tree::displayInfo() const {
    Plant::displayInfo();
    std::cout << "Height: " << height << "m\n";
    std::cout << "Trunk Diameter: " << trunkDiameter << "m\n";
    std::cout << "Tree Type: " << treeType << "\n";
    std::cout << "Evergreen: " << (isEvergreen ? "Yes" : "No") << "\n";
}

// ============================================================================
// CARE KIT IMPLEMENTATIONS
// ============================================================================

// Base CareKit implementation
CareKit::CareKit(const std::string& plantType, double price) 
    : plantType(plantType), price(price) {
    std::stringstream ss;
    ss << "KIT_" << plantType << "_" << (std::rand() % 10000);
    id = ss.str();
}

void CareKit::displayInfo() const {
    std::cout << "=== " << plantType << " Care Kit ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    std::cout << "Description: " << getKitDescription() << "\n";
    std::cout << "Tools included: ";
    for (size_t i = 0; i < tools.size(); ++i) {
        std::cout << tools[i];
        if (i < tools.size() - 1) std::cout << ", ";
    }
    std::cout << "\nInstructions: " << instructions << "\n";
}

// FlowerCareKit implementation
FlowerCareKit::FlowerCareKit() 
    : CareKit("Flower", 25.99), fertilizerType("Flower Boost Liquid Fertilizer"), 
      pesticide("Organic Flower Guard") {
    
    tools = {"Pruning Shears", "Watering Can", "Spray Bottle", "Plant Labels"};
    instructions = "Water daily with watering can. Fertilize weekly with Flower Boost. "
                  "Spray pesticide monthly. Prune dead flowers regularly.";
}

void FlowerCareKit::applyCare(Plant* plant) {
    if (plant && plant->getPlantType() == "Flower") {
        std::cout << "Applying flower care kit to " << plant->getName() << "...\n";
        plant->water(20);
        plant->fertilize(25);
        std::cout << "Used " << fertilizerType << " and " << pesticide << " for optimal flower growth.\n";
    } else {
        std::cout << "Error: This care kit is only suitable for flowers.\n";
    }
}

std::string FlowerCareKit::getKitDescription() const {
    return "Complete flower care package with specialized fertilizer and organic pesticide. "
           "Perfect for maintaining vibrant blooms and healthy foliage.";
}

// TreeCareKit implementation
TreeCareKit::TreeCareKit() 
    : CareKit("Tree", 45.99), treeFood("Slow-Release Tree Fertilizer Spikes"), 
      mulchType("Cedar Wood Chip Mulch") {
    
    tools = {"Pruning Saw", "Tree Stakes", "Watering Bag", "Soil Test Kit"};
    instructions = "Water deeply weekly using watering bag. Insert fertilizer spikes seasonally. "
                  "Apply mulch around base. Use pruning saw for maintenance pruning.";
}

void TreeCareKit::applyCare(Plant* plant) {
    if (plant && plant->getPlantType() == "Tree") {
        std::cout << "Applying tree care kit to " << plant->getName() << "...\n";
        plant->water(40);
        plant->fertilize(30);
        std::cout << "Applied " << treeFood << " and " << mulchType << " for strong tree growth.\n";
    } else {
        std::cout << "Error: This care kit is only suitable for trees.\n";
    }
}

std::string TreeCareKit::getKitDescription() const {
    return "Comprehensive tree care system with slow-release nutrition and proper tools "
           "for tree maintenance. Ideal for both young and mature trees.";
}

// ============================================================================
// SOIL IMPLEMENTATIONS
// ============================================================================

// Base Soil implementation
Soil::Soil(const std::string& soilType, double phLevel, double price) 
    : soilType(soilType), phLevel(phLevel), price(price) {
    
    std::stringstream ss;
    ss << "SOIL_" << soilType.substr(0, 3) << "_" << (std::rand() % 1000);
    id = ss.str();
}

void Soil::addNutrient(const std::string& nutrient, int amount) {
    nutrientContent[nutrient] = amount;
}

void Soil::displayInfo() const {
    std::cout << "=== " << soilType << " ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "pH Level: " << phLevel << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    std::cout << "Description: " << getSoilDescription() << "\n";
    std::cout << "Nutrient Content: ";
    for (const auto& nutrient : nutrientContent) {
        std::cout << nutrient.first << "(" << nutrient.second << "ppm) ";
    }
    std::cout << "\n";
}

// FlowerSoil implementation
FlowerSoil::FlowerSoil() : Soil("Acidic Potting Mix", 6.0, 15.99) {
    nutrientContent = {{"Nitrogen", 20}, {"Phosphorus", 30}, {"Potassium", 25}, {"Calcium", 15}};
}

bool FlowerSoil::isOptimalFor(const std::string& plantType) const {
    return plantType == "Flower";
}

std::string FlowerSoil::getSoilDescription() const {
    return "Specialized acidic potting mix optimized for flowering plants. "
           "Provides excellent drainage while retaining moisture. Enhanced with "
           "extra phosphorus for abundant blooms.";
}

// TreeSoil implementation
TreeSoil::TreeSoil() : Soil("Loamy Garden Soil", 6.5, 22.99) {
    nutrientContent = {{"Nitrogen", 25}, {"Phosphorus", 20}, {"Potassium", 20}, 
                      {"Magnesium", 15}, {"Sulfur", 10}};
}

bool TreeSoil::isOptimalFor(const std::string& plantType) const {
    return plantType == "Tree";
}

std::string TreeSoil::getSoilDescription() const {
    return "Rich loamy soil formulated for tree growth and root development. "
           "Contains mycorrhizal fungi to enhance nutrient uptake. Provides "
           "stable structure for strong root systems.";
}