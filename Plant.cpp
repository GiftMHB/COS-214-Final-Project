

// #include "Plant.h"
// #include "PlantState.h"
// #include "CareStrategy.h"
// #include "PlantObserver.h"
// #include <iostream>
// #include <algorithm>
// #include <cstdlib>
// #include <ctime>


// // PLANT BASE CLASS IMPLEMENTATION
// // ============================================================================

// int Plant::plantCount = 0;

// Plant::Plant(const std::string& name, const std::string& species, double price)
//     : name(name), species(species), price(price), classification("Unknown"),
//       waterLevel(50), sunlightLevel(50), nutrientLevel(50), age(0), 
//       health(100.0), currentState(nullptr), careStrategy(nullptr), 
//       isAlive(true), status("Available") {
    
//     // Generate unique ID
//     std::stringstream ss;
//     ss << "PLANT-" << ++plantCount;
//     id = ss.str();
    
//     std::cout << "Created new plant: " << name << " (ID: " << id << ")" << std::endl;
// }

// Plant::~Plant() {
//     // Note: State and Strategy pointers are managed by their respective systems
//     // Do not delete them here to avoid double deletion
// }


// // STATE PATTERN METHODS
// // ============================================================================

// void Plant::setState(PlantState* newState) {
//     if (currentState != newState && newState != nullptr) {
//         currentState = newState;
//         std::cout << name << " changed state to: " << getStateName() << std::endl;
//         notify("state_changed");
//     }
// }

// std::string Plant::getStateName() const {
//     return currentState ? currentState->getStateName() : "No State";
// }


// // STRATEGY PATTERN METHODS
// // ============================================================================

// void Plant::setCareStrategy(CareStrategy* strategy) {
//     careStrategy = strategy;
//     if (strategy) {
//         std::cout << name << " care strategy set to: " 
//                   << strategy->getStrategyName() << std::endl;
//     }
// }

// void Plant::applyCare() {
//     if (careStrategy) {
//         careStrategy->applyCare(this);
//         notify("care_applied");
//     } else {
//         std::cout << "No care strategy set for " << name << std::endl;
//     }
// }

// std::string Plant::getCareStrategyName() const {
//     return careStrategy ? careStrategy->getStrategyName() : "No Strategy";
// }


// // OBSERVER PATTERN METHODS
// // ============================================================================

// void Plant::attach(PlantObserver* observer) {
//     if (observer) {
//         observers.push_back(observer);
//     }
// }

// void Plant::detach(PlantObserver* observer) {
//     observers.erase(
//         std::remove(observers.begin(), observers.end(), observer),
//         observers.end()
//     );
// }

// void Plant::notify(const std::string& event) {
//     for (PlantObserver* observer : observers) {
//         if (observer) {
//             observer->update(this, event);
//         }
//     }
// }


// // CORE PLANT OPERATIONS
// // ============================================================================

// void Plant::water(int amount) {
//     if (!isAlive) {
//         std::cout << name << " is dead and cannot be watered." << std::endl;
//         return;
//     }
    
//     // Delegate to state if available
//     if (currentState) {
//         currentState->water(this);
//     } else {
//         // Fallback implementation
//         waterLevel = std::min(100, waterLevel + amount);
//         std::cout << "Watered " << name << " with " << amount 
//                   << " units. Water level: " << waterLevel << "%" << std::endl;
//     }
    
//     updateHealth();
//     notify("watered");
// }

// void Plant::fertilize(int amount) {
//     if (!isAlive) {
//         std::cout << name << " is dead and cannot be fertilized." << std::endl;
//         return;
//     }
    
//     // Delegate to state if available
//     if (currentState) {
//         currentState->fertilize(this);
//     } else {
//         // Fallback implementation
//         nutrientLevel = std::min(100, nutrientLevel + amount);
//         std::cout << "Fertilized " << name << " with " << amount 
//                   << " units. Nutrient level: " << nutrientLevel << "%" << std::endl;
//     }
    
//     updateHealth();
//     notify("fertilized");
// }

// void Plant::addSunlight(int amount) {
//     if (!isAlive) {
//         return;
//     }
    
//     sunlightLevel = std::min(100, sunlightLevel + amount);
//     std::cout << "Added " << amount << " units of sunlight to " << name 
//               << ". Sunlight level: " << sunlightLevel << "%" << std::endl;
    
//     updateHealth();
// }

// void Plant::exposeToSunlight(int hours) {
//     if (!isAlive) {
//         return;
//     }
    
//     std::cout << name << " exposed to sunlight for " << hours << " hours." << std::endl;
    
//     // Simulate sunlight effect
//     if (hours < 4) {
//         health = std::max(0.0, health - 2.0);  // Not enough sunlight
//     } else if (hours > 10) {
//         health = std::max(0.0, health - 1.0);  // Too much sunlight
//     } else {
//         health = std::min(100.0, health + 1.0); // Ideal sunlight
//         sunlightLevel = std::min(100, sunlightLevel + (hours * 5));
//     }
    
//     updateHealth();
// }

// void Plant::grow() {
//     if (!isAlive) {
//         return;
//     }
    
//     // Delegate to state if available
//     if (currentState) {
//         currentState->grow(this);
//     } else {
//         // Fallback implementation
//         age++;
//         updateResourceLevels();
//         updateHealth();
//     }
    
//     notify("grew");
// }

// // ============================================================================
// // SETTERS WITH VALIDATION
// // ============================================================================

// void Plant::setWaterLevel(int level) {
//     waterLevel = std::max(0, std::min(100, level));
//     updateHealth();
// }

// void Plant::setSunlightLevel(int level) {
//     sunlightLevel = std::max(0, std::min(100, level));
//     updateHealth();
// }

// void Plant::setNutrientLevel(int level) {
//     nutrientLevel = std::max(0, std::min(100, level));
//     updateHealth();
// }

// void Plant::setAge(int newAge) {
//     age = std::max(0, newAge);
// }

// void Plant::setHealth(double newHealth) {
//     health = std::max(0.0, std::min(100.0, newHealth));
//     if (health <= 0.0) {
//         isAlive = false;
//         notify("died");
//     }
// }

// // ============================================================================
// // HELPER METHODS
// // ============================================================================

// void Plant::updateResourceLevels() {
//     // Simulate natural resource depletion
//     waterLevel = std::max(0, waterLevel - 5);
//     nutrientLevel = std::max(0, nutrientLevel - 3);
//     sunlightLevel = std::max(0, sunlightLevel - 2);
// }

// void Plant::updateHealth() {
//     // Calculate health based on resource levels
//     double resourceAverage = (waterLevel + sunlightLevel + nutrientLevel) / 3.0;
    
//     if (resourceAverage >= 80) {
//         health = std::min(100.0, health + 5.0);
//     } else if (resourceAverage >= 60) {
//         health = std::min(100.0, health + 2.0);
//     } else if (resourceAverage >= 40) {
//         // Maintain current health
//     } else if (resourceAverage >= 20) {
//         health = std::max(0.0, health - 5.0);
//     } else {
//         health = std::max(0.0, health - 10.0);
//     }
    
//     // Check if plant died
//     if (health <= 0.0) {
//         isAlive = false;
//         notify("died");
//     }
    
//     // Notify if health is critical
//     if (health < 30.0 && isAlive) {
//         notify("health_low");
//     }
// }

// double Plant::calculateGrowthRate() const {
//     // Growth rate based on resource levels and health
//     double resourceFactor = (waterLevel + sunlightLevel + nutrientLevel) / 300.0;
//     double healthFactor = health / 100.0;
//     return resourceFactor * healthFactor;
// }

// void Plant::checkHealth() {
//     updateHealth();
// }

// // ============================================================================
// // UTILITY METHODS
// // ============================================================================

// bool Plant::isReadyForSale() const {
//     return isAlive && health >= 70.0 && waterLevel >= 40 && 
//            nutrientLevel >= 40 && status == "Available";
// }

// std::string Plant::getHealthStatus() const {
//     if (health >= 80) return "Excellent";
//     if (health >= 60) return "Good";
//     if (health >= 40) return "Fair";
//     if (health >= 20) return "Poor";
//     return "Critical";
// }

// void Plant::displayInfo() const {
//     std::cout << "\n=== " << name << " ===\n";
//     std::cout << "ID: " << id << "\n";
//     std::cout << "Species: " << species << "\n";
//     std::cout << "Type: " << getPlantType() << "\n";
//     std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
//     std::cout << "Status: " << status << "\n";
//     std::cout << "State: " << getStateName() << "\n";
//     std::cout << "Health: " << getHealthStatus() << " (" << health << "%)\n";
//     std::cout << "Age: " << age << " days\n";
//     std::cout << "Water: " << waterLevel << "%, Sunlight: " << sunlightLevel 
//               << "%, Nutrients: " << nutrientLevel << "%\n";
//     std::cout << "Alive: " << (isAlive ? "Yes" : "No") << "\n";
//     std::cout << "Description: " << getDescription() << "\n";
//     std::cout << "Care: " << getCareInstructions() << "\n";
// }

// void Plant::printStatus() const {
//     std::cout << "\n=== " << name << " Status ===\n";
//     std::cout << "ID: " << id << "\n";
//     std::cout << "Species: " << species << "\n";
//     std::cout << "Price: R" << std::fixed << std::setprecision(2) << price << "\n";
//     std::cout << "State: " << getStateName() << "\n";
//     std::cout << "Age: " << age << " days\n";
//     std::cout << "Water: " << waterLevel << "/100\n";
//     std::cout << "Sunlight: " << sunlightLevel << "/100\n";
//     std::cout << "Nutrients: " << nutrientLevel << "/100\n";
//     std::cout << "Health: " << health << "%\n";
//     std::cout << "Status: " << (isAlive ? "Alive" : "Dead") << "\n";
//     std::cout << "==========================\n";
// }

// // ============================================================================
// // FLOWER CLASS IMPLEMENTATION
// // ============================================================================

// Flower::Flower(const std::string& name, const std::string& species, double price,
//                const std::string& color, const std::string& bloomSeason, 
//                bool isFragrant, int petalCount)
//     : Plant(name, species, price), color(color), bloomSeason(bloomSeason),
//       isFragrant(isFragrant), petalCount(petalCount) {
//     classification = "Flower";
// }

// std::string Flower::getPlantType() const { 
//     return "Flower"; 
// }

// std::string Flower::getDescription() const {
//     std::stringstream ss;
//     ss << "Beautiful " << color << " " << name << " that blooms in " << bloomSeason 
//        << ". " << (isFragrant ? "Has a lovely fragrance." : "No significant fragrance.")
//        << " Features " << petalCount << " delicate petals.";
//     return ss.str();
// }

// std::string Flower::getCareInstructions() const {
//     return "Water daily during growing season, provide 6+ hours of sunlight, "
//            "fertilize weekly with bloom-promoting fertilizer. Deadhead spent flowers.";
// }

// bool Flower::isInBloom(const std::string& currentSeason) const {
//     return bloomSeason == "All" || bloomSeason == currentSeason;
// }

// void Flower::displayInfo() const {
//     Plant::displayInfo();
//     std::cout << "Color: " << color << "\n";
//     std::cout << "Bloom Season: " << bloomSeason << "\n";
//     std::cout << "Fragrant: " << (isFragrant ? "Yes" : "No") << "\n";
//     std::cout << "Petal Count: " << petalCount << "\n";
// }

// // ============================================================================
// // TREE CLASS IMPLEMENTATION
// // ============================================================================

// Tree::Tree(const std::string& name, const std::string& species, double price,
//            double height, double trunkDiameter, const std::string& treeType, 
//            bool isEvergreen)
//     : Plant(name, species, price), height(height), trunkDiameter(trunkDiameter),
//       treeType(treeType), isEvergreen(isEvergreen) {
//     classification = "Tree";
// }

// std::string Tree::getPlantType() const { 
//     return "Tree"; 
// }

// std::string Tree::getDescription() const {
//     std::stringstream ss;
//     ss << "Majestic " << name << " tree standing " << std::fixed 
//        << std::setprecision(2) << height << "m tall with " << trunkDiameter 
//        << "m trunk diameter. " << (isEvergreen ? "Evergreen" : "Deciduous") 
//        << " " << treeType << " tree.";
//     return ss.str();
// }

// std::string Tree::getCareInstructions() const {
//     return "Water deeply weekly, provide full sunlight exposure, fertilize "
//            "seasonally with slow-release fertilizer. Prune annually for shape.";
// }

// void Tree::growHeight(double heightIncrease) {
//     height += heightIncrease;
//     std::cout << name << " grew " << heightIncrease << "m. Current height: " 
//               << height << "m\n";
//     notify("height_increased");
// }

// void Tree::prune() {
//     std::cout << "Pruned " << name << " for better shape and health.\n";
//     nutrientLevel = std::max(0, nutrientLevel - 10);
//     health = std::min(100.0, health + 5.0);  // Pruning improves health
//     notify("pruned");
// }

// void Tree::displayInfo() const {
//     Plant::displayInfo();
//     std::cout << "Height: " << height << "m\n";
//     std::cout << "Trunk Diameter: " << trunkDiameter << "m\n";
//     std::cout << "Tree Type: " << treeType << "\n";
//     std::cout << "Evergreen: " << (isEvergreen ? "Yes" : "No") << "\n";
// }

// // ============================================================================
// // SHRUB CLASS IMPLEMENTATION
// // ============================================================================

// Shrub::Shrub(const std::string& name, const std::string& species, double price,
//              int bushiness, bool canBeTrimmed, int branchCount)
//     : Plant(name, species, price), bushiness(bushiness), 
//       canBeTrimmed(canBeTrimmed), branchCount(branchCount) {
//     classification = "Shrub";
// }

// std::string Shrub::getPlantType() const { 
//     return "Shrub"; 
// }

// std::string Shrub::getDescription() const {
//     std::stringstream ss;
//     ss << "Lush " << name << " shrub with bushiness rating of " << bushiness 
//        << "/10 and " << branchCount << " branches. "
//        << (canBeTrimmed ? "Can be shaped and trimmed." : "Natural growth pattern.");
//     return ss.str();
// }

// std::string Shrub::getCareInstructions() const {
//     return "Water 2-3 times weekly, provide partial to full sunlight, "
//            "fertilize monthly. Trim as needed to maintain desired shape.";
// }

// void Shrub::trim() {
//     if (canBeTrimmed) {
//         std::cout << "Trimmed " << name << " to maintain shape.\n";
//         bushiness = std::max(1, bushiness - 1);
//         health = std::min(100.0, health + 3.0);
//         notify("trimmed");
//     } else {
//         std::cout << name << " cannot be trimmed.\n";
//     }
// }

// void Shrub::displayInfo() const {
//     Plant::displayInfo();
//     std::cout << "Bushiness: " << bushiness << "/10\n";
//     std::cout << "Can Be Trimmed: " << (canBeTrimmed ? "Yes" : "No") << "\n";
//     std::cout << "Branch Count: " << branchCount << "\n";
// }

// // ============================================================================
// // VEGETABLE CLASS IMPLEMENTATION
// // ============================================================================

// Vegetable::Vegetable(const std::string& name, const std::string& species, double price,
//                      int harvestTime, bool isEdible, double yield, 
//                      const std::string& vegetableType)
//     : Plant(name, species, price), harvestTime(harvestTime), 
//       isEdible(isEdible), yield(yield), vegetableType(vegetableType) {
//     classification = "Vegetable";
// }

// std::string Vegetable::getPlantType() const { 
//     return "Vegetable"; 
// }

// std::string Vegetable::getDescription() const {
//     std::stringstream ss;
//     ss << name << " " << vegetableType << " vegetable. "
//        << (isEdible ? "Edible" : "Non-edible") << " variety. "
//        << "Expected yield: " << yield << "kg per plant. "
//        << "Ready to harvest in " << harvestTime << " days.";
//     return ss.str();
// }

// std::string Vegetable::getCareInstructions() const {
//     return "Water consistently to keep soil moist, provide 6-8 hours of sunlight, "
//            "fertilize bi-weekly with vegetable fertilizer. Monitor for pests.";
// }

// bool Vegetable::isReadyToHarvest() const {
//     return age >= harvestTime && health >= 60.0;
// }

// double Vegetable::harvest() {
//     if (isReadyToHarvest()) {
//         std::cout << "Harvested " << yield << "kg of " << name << "!\n";
//         double harvestedAmount = yield;
//         yield = 0.0;
//         isAlive = false;
//         notify("harvested");
//         return harvestedAmount;
//     } else {
//         std::cout << name << " is not ready to harvest yet.\n";
//         return 0.0;
//     }
// }

// void Vegetable::displayInfo() const {
//     Plant::displayInfo();
//     std::cout << "Harvest Time: " << harvestTime << " days\n";
//     std::cout << "Edible: " << (isEdible ? "Yes" : "No") << "\n";
//     std::cout << "Expected Yield: " << yield << "kg\n";
//     std::cout << "Vegetable Type: " << vegetableType << "\n";
//     std::cout << "Ready to Harvest: " << (isReadyToHarvest() ? "Yes" : "No") << "\n";
// }

// // ============================================================================
// // CARE KIT IMPLEMENTATIONS
// // ============================================================================

// CareKit::CareKit(const std::string& plantType, double price) 
//     : plantType(plantType), price(price) {
//     std::stringstream ss;
//     ss << "KIT_" << plantType << "_" << (std::rand() % 10000);
//     id = ss.str();
// }

// void CareKit::displayInfo() const {
//     std::cout << "\n=== " << plantType << " Care Kit ===\n";
//     std::cout << "ID: " << id << "\n";
//     std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
//     std::cout << "Description: " << getKitDescription() << "\n";
//     std::cout << "Tools included: ";
//     for (size_t i = 0; i < tools.size(); ++i) {
//         std::cout << tools[i];
//         if (i < tools.size() - 1) std::cout << ", ";
//     }
//     std::cout << "\nInstructions: " << instructions << "\n";
// }

// FlowerCareKit::FlowerCareKit() 
//     : CareKit("Flower", 25.99) {
    
//     fertilizerType = "Flower Boost Liquid Fertilizer";
//     pesticide = "Organic Flower Guard";
//     tools = {"Pruning Shears", "Watering Can", "Spray Bottle", "Plant Labels"};
//     instructions = "Water daily with watering can. Fertilize weekly with Flower Boost. "
//                    "Spray pesticide monthly. Prune dead flowers regularly.";
// }

// void FlowerCareKit::applyCare(Plant* plant) {
//     if (plant && plant->getPlantType() == "Flower") {
//         std::cout << "Applying flower care kit to " << plant->getName() << "...\n";
//         plant->water(20);
//         plant->fertilize(25);
//         std::cout << "Used " << fertilizerType << " and " << pesticide 
//                   << " for optimal flower growth.\n";
//     } else {
//         std::cout << "Error: This care kit is only suitable for flowers.\n";
//     }
// }

// std::string FlowerCareKit::getKitDescription() const {
//     return "Complete flower care package with specialized fertilizer and organic pesticide. "
//            "Perfect for maintaining vibrant blooms and healthy foliage.";
// }

// TreeCareKit::TreeCareKit() 
//     : CareKit("Tree", 45.99) {
    
//     treeFood = "Slow-Release Tree Fertilizer Spikes";
//     mulchType = "Cedar Wood Chip Mulch";
//     tools = {"Pruning Saw", "Tree Stakes", "Watering Bag", "Soil Test Kit"};
//     instructions = "Water deeply weekly using watering bag. Insert fertilizer spikes seasonally. "
//                    "Apply mulch around base. Use pruning saw for maintenance pruning.";
// }

// void TreeCareKit::applyCare(Plant* plant) {
//     if (plant && plant->getPlantType() == "Tree") {
//         std::cout << "Applying tree care kit to " << plant->getName() << "...\n";
//         plant->water(40);
//         plant->fertilize(30);
//         std::cout << "Applied " << treeFood << " and " << mulchType 
//                   << " for strong tree growth.\n";
//     } else {
//         std::cout << "Error: This care kit is only suitable for trees.\n";
//     }
// }

// std::string TreeCareKit::getKitDescription() const {
//     return "Comprehensive tree care system with slow-release nutrition and proper tools "
//            "for tree maintenance. Ideal for both young and mature trees.";
// }

// // ============================================================================
// // SOIL IMPLEMENTATIONS
// // ============================================================================

// Soil::Soil(const std::string& soilType, double phLevel, double price) 
//     : soilType(soilType), phLevel(phLevel), price(price), drainageRate(50) {
    
//     std::stringstream ss;
//     ss << "SOIL_" << soilType.substr(0, 3) << "_" << (std::rand() % 1000);
//     id = ss.str();
// }

// void Soil::addNutrient(const std::string& nutrient, int amount) {
//     nutrientContent[nutrient] = amount;
// }

// void Soil::displayInfo() const {
//     std::cout << "\n=== " << soilType << " ===\n";
//     std::cout << "ID: " << id << "\n";
//     std::cout << "pH Level: " << phLevel << "\n";
//     std::cout << "Drainage Rate: " << drainageRate << "%\n";
//     std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
//     std::cout << "Description: " << getSoilDescription() << "\n";
//     std::cout << "Nutrient Content: ";
//     for (const auto& nutrient : nutrientContent) {
//         std::cout << nutrient.first << "(" << nutrient.second << "ppm) ";
//     }
//     std::cout << "\n";
// }

// FlowerSoil::FlowerSoil() : Soil("Acidic Potting Mix", 6.0, 15.99) {
//     nutrientContent = {
//         {"Nitrogen", 20}, 
//         {"Phosphorus", 30}, 
//         {"Potassium", 25}, 
//         {"Calcium", 15}
//     };
//     drainageRate = 70;
// }

// bool FlowerSoil::isOptimalFor(const std::string& plantType) const {
//     return plantType == "Flower";
// }

// std::string FlowerSoil::getSoilDescription() const {
//     return "Specialized acidic potting mix optimized for flowering plants. "
//            "Provides excellent drainage while retaining moisture. Enhanced with "
//            "extra phosphorus for abundant blooms.";
// }

// TreeSoil::TreeSoil() : Soil("Loamy Garden Soil", 6.5, 22.99) {
//     nutrientContent = {
//         {"Nitrogen", 25}, 
//         {"Phosphorus", 20}, 
//         {"Potassium", 20}, 
//         {"Magnesium", 15}, 
//         {"Sulfur", 10}
//     };
//     drainageRate = 60;
// }

// bool TreeSoil::isOptimalFor(const std::string& plantType) const {
//     return plantType == "Tree";
// }

// std::string TreeSoil::getSoilDescription() const {
//     return "Rich loamy soil formulated for tree growth and root development. "
//            "Contains mycorrhizal fungi to enhance nutrient uptake. Provides "
//            "stable structure for strong root systems.";
// }

#include "Plant.h"
#include <iostream>
#include <ctime>  // For date if needed

int PlantInfo::plantCount = 0;

Plant::Plant(PlantInfo& pInfo) : info(pInfo), careStrategy(nullptr), state(nullptr) {
    if (info.id.empty()) {  // Auto-generate ID if not provided
        info.id = "P" + std::to_string(++PlantInfo::plantCount);
    }
    if (info.addedDate.empty()) {  // Set current date if not provided
        time_t now = time(0);
        tm* ltm = localtime(&now);
        info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                         std::to_string(1 + ltm->tm_mon) + "-" +
                         std::to_string(ltm->tm_mday);
    }
}

Plant::Plant(const std::string& name, const std::string& classification, double price) 
    : careStrategy(nullptr), state(nullptr) {
    info.id = "P" + std::to_string(++PlantInfo::plantCount);
    info.name = name;
    info.classification = classification;
    info.salePrice = price;
    info.purchasePrice = price * 0.7;  // Example default
    time_t now = time(0);
    tm* ltm = localtime(&now);
    info.addedDate = std::to_string(1900 + ltm->tm_year) + "-" +
                     std::to_string(1 + ltm->tm_mon) + "-" +
                     std::to_string(ltm->tm_mday);
}

Plant::~Plant() {
    delete careStrategy;
    delete state;
    for (auto obs : observers) {
        // Detach or cleanup if needed; assume observers outlive
    }
}

void Plant::setCareStrategy(CareStrategy* strategy) {
    delete careStrategy;  // Assume ownership; adjust if shared
    careStrategy = strategy;
}

void Plant::applyCare() {
    if (careStrategy) {
        careStrategy->applyCare(this);
    } else {
        std::cout << "No care strategy set for " << info.name << ".\n";
    }
}

std::string Plant::getCareStrategyName() const {
    return careStrategy ? careStrategy->getStrategyName() : "No Strategy";
}

void Plant::attach(PlantObserver* observer) {
    observers.push_back(observer);
}

void Plant::detach(PlantObserver* observer) {
    observers.remove(observer);
}

void Plant::notifyObservers() {
    for (auto obs : observers) {
        obs->update(this);
    }
}

void Plant::water(int amount) {
    int newWaterLevel = info.waterLevel + amount;
    info.waterLevel = std::max(0, std::min(100, newWaterLevel));
    std::cout << info.name << " watered by " << amount
              << " units. Current water level: " << info.waterLevel << "\n";

    if (info.waterLevel >= 40 && info.waterLevel <= 80) {
        info.healthLevel = std::min(100, info.healthLevel + 2);
    } else if (info.waterLevel > 90) {
        info.healthLevel = std::max(0, info.healthLevel - 3);  // Overwatering
    }
    checkHealth();
}

void Plant::fertilize(int amount) {
    int newNutrientLevel = info.nutrientLevel + amount;
    info.nutrientLevel = std::max(0, std::min(100, newNutrientLevel));
    std::cout << info.name << " fertilized by " << amount
              << " units. Nutrient level: " << info.nutrientLevel << "\n";

    if (info.nutrientLevel > 40) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.5);
    }
    checkHealth();
}

void Plant::addSunlight(int amount) {
    exposeToSunlight(amount);  // Alias for plan compatibility
}

void Plant::exposeToSunlight(int hours) {
    info.sunlightLevel += hours;  // Accumulate current exposure
    std::cout << info.name << " exposed to sunlight for " << hours << " hours.\n";

    if (hours < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 2);
    } else if (hours > info.sunlightNeed + 3) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
    } else {
        info.healthLevel = std::min(100, info.healthLevel + 1);
    }

    if (info.healthLevel > 70) {
        info.currentHeight = std::min(info.maturityHeight, info.currentHeight + 0.2);
    }
    checkHealth();
}

void Plant::grow() {
    if (state) {
        state->grow(this);
    }
    info.currentAgeDays++;
    updateResourceLevels();  // From plan
    checkHealth();
}

void Plant::checkHealth() {
    // Example impl: check levels and transition state/notify
    if (info.healthLevel < 30) {
        if (state) state->handle(this);  // Assume state has handle() for transitions
    } else if (info.waterLevel < 20 || info.nutrientLevel < 20 || info.sunlightLevel < info.sunlightNeed) {
        info.healthLevel = std::max(0, info.healthLevel - 1);
    }
    notifyObservers();  // Notify on health check
}

void Plant::updateResourceLevels() {
    // Simulate daily decay (plan protected method)
    info.waterLevel = std::max(0, info.waterLevel - 5);
    info.sunlightLevel = 0;  // Reset daily?
    info.nutrientLevel = std::max(0, info.nutrientLevel - 2);
}

double Plant::calculateGrowthRate() {
    // Plan protected: example calculation
    return (info.healthLevel / 100.0) * (info.nutrientLevel / 50.0);
}

int Plant::getID() const { return std::stoi(info.id.substr(1)); }  // If needed as int

double Plant::getPrice() const { return info.salePrice; }

void Plant::setPrice(double price) { info.salePrice = price; }

std::string Plant::getName() const { return info.name; }

std::string Plant::getClassification() const { return info.classification; }

std::string Plant::getDate() const { return info.addedDate; }

int Plant::getWaterLevel() const { return info.waterLevel; }

void Plant::setWaterLevel(int level) { info.waterLevel = level; }

int Plant::getSunlightLevel() const { return info.sunlightLevel; }

void Plant::setSunlightLevel(int level) { info.sunlightLevel = level; }

int Plant::getHealthLevel() const { return info.healthLevel; }

void Plant::setHealthLevel(int level) { info.healthLevel = level; }

int Plant::getNutrientLevel() const { return info.nutrientLevel; }

void Plant::setNutrientLevel(int level) { info.nutrientLevel = level; }

int Plant::getAge() const { return info.currentAgeDays; }

void Plant::setAge(int newAge) { info.currentAgeDays = newAge; }

void Plant::printStatus() const {
    std::cout << "Plant: " << info.name << " (" << info.classification << ")\n"
              << "Health: " << info.healthLevel << ", Water: " << info.waterLevel
              << ", Sunlight: " << info.sunlightLevel << ", Nutrients: " << info.nutrientLevel
              << ", Age: " << info.currentAgeDays << " days\n";
    // Add more as needed
}