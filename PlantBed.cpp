/**
 * @file PlantBed.cpp
 * @brief Implementation of the PlantBed leaf class
 */

#include "PlantBed.h"
#include "Plant.h"
#include <iostream>
#include <algorithm>

PlantBed::PlantBed(const std::string& bedName, const std::string& bedId, int maxCapacity)
    : id(bedId), capacity(maxCapacity) {
    name = bedName;
}

PlantBed::~PlantBed() {
    // Note: We don't delete plants here as they may be managed by inventory
    // or other systems. Just clear the list.
    plants.clear();
}

bool PlantBed::assignPlant(Plant* plant) {
    if (plant == nullptr) {
        return false;
    }
    
    if ((int)plants.size() >= capacity) {
        std::cout << "PlantBed '" << name << "' is at full capacity!" << std::endl;
        return false;
    }
    
    plants.push_back(plant);
    return true;
}

bool PlantBed::removePlant(const std::string& plantId) {
    for (std::list<Plant*>::iterator it = plants.begin(); 
         it != plants.end(); ++it) {
        if ((*it)->getId() == plantId) {
            plants.erase(it);
            return true;
        }
    }
    return false;
}

Plant* PlantBed::getPlant(const std::string& plantId) {
    for (std::list<Plant*>::iterator it = plants.begin(); 
         it != plants.end(); ++it) {
        if ((*it)->getId() == plantId) {
            return *it;
        }
    }
    return nullptr;
}

std::list<Plant*> PlantBed::getPlants() {
    return plants;
}

void PlantBed::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << " " << name << " [" << getType() << "]" << std::endl;
    std::cout << indent << "   ID: " << id << ", Capacity: " << plants.size() 
              << "/" << capacity << std::endl;
    
    // Display all plants
    for (std::list<Plant*>::iterator it = plants.begin(); 
         it != plants.end(); ++it) {
        std::cout << indent << "     • " << (*it)->getName() 
                  << " (ID: " << (*it)->getId() << ")" << std::endl;
    }
}

int PlantBed::getPlantCount() {
    return plants.size();
}

GardenComponent* PlantBed::findByName(const std::string& searchName) {
    if (name == searchName) {
        return this;
    }
    
    
    for (std::list<Plant*>::iterator it = plants.begin(); 
         it != plants.end(); ++it) {
        if ((*it)->getName() == searchName) {
            return this; 
        }
    }
    
    return nullptr;
}

std::string PlantBed::getType() {
    return "PlantBed";
}

std::string PlantBed::getName() {
    return name;
}