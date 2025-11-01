#ifndef CONCRETE_PLANT_H
#define CONCRETE_PLANT_H

#include "Plant.h"
#include <iostream>
#include <list>

class ConcretePlant : public Plant {
private:
    std::list<Observer*> observers;

public:
    // All constructors
    ConcretePlant(PlantInfo& info) : Plant(info) {}
    
    ConcretePlant(const std::string& name, const std::string& classification, double price) 
        : Plant(name, classification, price) {}
    
    // YOUR constructor - add this
    ConcretePlant(const std::string& plantName, const std::string& plantSpecies)
        : Plant(plantName, plantSpecies) {}
    
    // Implement the pure virtual methods from Subject
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }
    
    void detach(Observer* observer) override {
        observers.remove(observer);
    }
    
    void notify(const std::string& event) override {
        for (Observer* observer : observers) {
            observer->update(event);
        }
    }
};

#endif // CONCRETE_PLANT_H