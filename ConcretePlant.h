/**
 * @file ConcretePlant.h
 * @brief Concrete implementation of Plant that works with the unified system
 */

#ifndef CONCRETE_PLANT_H
#define CONCRETE_PLANT_H

#include "Plant.h"
#include <iostream>
#include <list>


// Concrete implementation of Plant
class ConcretePlant : public Plant {
public:
    // Use their constructors
    ConcretePlant(PlantInfo& info) : Plant(info) {}
    ConcretePlant(const std::string& name, const std::string& classification, double price) 
        : Plant(name, classification, price) {}
    
    // Override the pure virtual methods from Subject
    void attach(Observer* observer) override {
        // Simple implementation
    }
    
    void detach(Observer* observer) override {
        // Simple implementation  
    }
    
    void notify(const std::string& event) override {
        // Simple implementation
        std::cout << "Plant " << getName() << " event: " << event << std::endl;
    }
};

#endif // CONCRETE_PLANT_H