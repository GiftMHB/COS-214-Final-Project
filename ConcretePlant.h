/**
 * @file ConcretePlant.h
 * @brief Defines the ConcretePlant class, a concrete implementation of the Plant class with observer support.
 */

#ifndef CONCRETE_PLANT_H
#define CONCRETE_PLANT_H

#include "Plant.h"
#include <iostream>
#include <list>

/**
 * @class ConcretePlant
 * @brief Represents a specific plant that supports the Observer pattern.
 *
 * The ConcretePlant class extends the Plant base class and manages a list of observers.
 * It allows observers to attach and detach, and notifies them of specific events.
 */
class ConcretePlant : public Plant {
private:
    /**
     * @brief List of observers that are notified when events occur.
     */
    std::list<Observer*> observers;

public:
    /**
     * @brief Constructs a ConcretePlant using detailed plant information.
     * @param info A reference to a PlantInfo object containing plant details.
     */
    ConcretePlant(PlantInfo& info) : Plant(info) {}

    /**
     * @brief Constructs a ConcretePlant using name, classification, and price.
     * @param name The name of the plant.
     * @param classification The classification or species of the plant.
     * @param price The price of the plant.
     */
    ConcretePlant(const std::string& name, const std::string& classification, double price) 
        : Plant(name, classification, price) {}

    /**
     * @brief Custom constructor for a ConcretePlant using name and species.
     * @param plantName The name of the plant.
     * @param plantSpecies The species of the plant.
     */
    ConcretePlant(const std::string& plantName, const std::string& plantSpecies)
        : Plant(plantName, plantSpecies) {}

    /**
     * @brief Attaches an observer to the plant.
     * @param observer Pointer to the Observer object to attach.
     */
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    /**
     * @brief Detaches an observer from the plant.
     * @param observer Pointer to the Observer object to remove.
     */
    void detach(Observer* observer) override {
        observers.remove(observer);
    }

    /**
     * @brief Notifies all attached observers of an event.
     * @param event A string describing the event that occurred.
     */
    void notify(const std::string& event) override {
        for (Observer* observer : observers) {
            observer->update(event);
        }
    }
};

#endif // CONCRETE_PLANT_H
