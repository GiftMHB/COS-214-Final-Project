/**
 * @file GardenArea.cpp
 * @brief Implementation of the GardenArea singleton composite root
 */

#include "GardenArea.h"
#include "PlantBed.h"
#include "Plant.h"
#include <iostream>
#include <sstream>


GardenArea* GardenArea::instance = nullptr;

GardenArea::GardenArea() 
    : totalCapacity(1000), temperature(22.0), humidity(60.0), id("GA001") {
    name = "Main Garden Area";
}

GardenArea& GardenArea::getInstance() {
    if (instance == nullptr) {
        instance = new GardenArea();
    }
    return *instance;
}

GardenArea::~GardenArea() {
    
    for (std::list<GardenComponent*>::iterator it = sections.begin(); 
         it != sections.end(); ++it) {
        delete *it;
    }
    sections.clear();
}

void GardenArea::add(GardenComponent* section) {
    if (section != nullptr) {
        sections.push_back(section);
    }
}

void GardenArea::remove(GardenComponent* section) {
    if (section != nullptr) {
        sections.remove(section);
        delete section;
    }
}

void GardenArea::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << " " << name << " [" << getType() << "]" << std::endl;
    std::cout << indent << "   Temperature: " << temperature << "°C, "
              << "Humidity: " << humidity << "%" << std::endl;
    std::cout << indent << "   Total Plants: " << getPlantCount() << std::endl;
    
    
    for (std::list<GardenComponent*>::iterator it = sections.begin(); 
         it != sections.end(); ++it) {
        (*it)->display(depth + 1);
    }
}

int GardenArea::getPlantCount() {
    int total = 0;
    for (std::list<GardenComponent*>::iterator it = sections.begin(); 
         it != sections.end(); ++it) {
        total += (*it)->getPlantCount();
    }
    return total;
}

GardenComponent* GardenArea::findByName(const std::string& searchName) {
    if (name == searchName) {
        return this;
    }
    
    
    for (std::list<GardenComponent*>::iterator it = sections.begin(); 
         it != sections.end(); ++it) {
        GardenComponent* found = (*it)->findByName(searchName);
        if (found != nullptr) {
            return found;
        }
    }
    
    return nullptr;
}

std::list<Plant*> GardenArea::getAllPlants() {
    std::list<Plant*> allPlants;
    
    for (std::list<GardenComponent*>::iterator it = sections.begin(); 
         it != sections.end(); ++it) {
        
        GardenComponent* component = *it;
        if (component->getType() == "PlantBed") {
            PlantBed* bed = dynamic_cast<PlantBed*>(component);
            if (bed != nullptr) {
                std::list<Plant*> bedPlants = bed->getPlants();
                allPlants.insert(allPlants.end(), bedPlants.begin(), bedPlants.end());
            }
        }
    }
    
    return allPlants;
}

void GardenArea::setTemperature(double temp) {
    temperature = temp;
}

double GardenArea::getTemperature() {
    return temperature;
}

void GardenArea::setHumidity(double hum) {
    humidity = hum;
}

double GardenArea::getHumidity() {
    return humidity;
}

std::string GardenArea::getType() {
    return "GardenArea";
}

std::string GardenArea::getName() {
    return name;
// GardenArea.cpp
#include "GardenArea.h"
#include "GardenSection.h" // Assuming this header exists; forward declaration in .h

GardenArea* GardenArea::instance = nullptr;

GardenArea::GardenArea() : totalCapacity(1000), temperature(25.0), humidity(60) {} // Defaults from project plan inference

GardenArea* GardenArea::getInstance() {
    if (instance == nullptr) {
        instance = new GardenArea();
    }
    return instance;
}

void GardenArea::addSection(GardenSection* section) {
    sections.push_back(section);
    // Could update totalCapacity here if sections contribute to it
}

bool GardenArea::removeSection(const std::string& sectionId) {
    for (auto it = sections.begin(); it != sections.end(); ++it) {
        if ((*it)->getId() == sectionId) { // Assuming GardenSection has getId()
            delete *it; // Memory management; beware
            sections.erase(it);
            return true;
        }
    }
    return false;
}

GardenSection* GardenArea::getSection(const std::string& id) {
    for (auto section : sections) {
        if (section->getId() == id) {
            return section;
        }
    }
    return nullptr;
}

std::vector<GardenSection*> GardenArea::getAllSections() const {
    return sections;
}

int GardenArea::getTotalCapacity() const {
    return totalCapacity;
}

void GardenArea::setTemperature(double temp) {
    temperature = temp;
}

double GardenArea::getTemperature() const {
    return temperature;
}

void GardenArea::setHumidity(int hum) {
    humidity = hum;
}

int GardenArea::getHumidity() const {
    return humidity;
}

GardenArea::~GardenArea() {
    for (auto section : sections) {
        delete section;
    }
    sections.clear();
}