/**
 * @file Subject.cpp
 * @brief Implementation of the Subject class
 */

#include "Subject.h"
#include "Plant.h"

void Subject::notify(const std::string& eventType) {
    
    Plant* plant = dynamic_cast<Plant*>(this);
    
    // Notify all observers
    for (std::list<Observer*>::iterator it = observers.begin(); 
         it != observers.end(); ++it) {
        (*it)->update(plant, eventType);
    }
}