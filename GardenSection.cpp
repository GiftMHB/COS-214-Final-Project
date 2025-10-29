/**
 * @file GardenSection.cpp
 * @brief Implementation of the GardenSection composite class
 */

#include "GardenSection.h"
#include <iostream>

GardenSection::GardenSection(const std::string& sectionName, const std::string& sectionId)
    : id(sectionId) {
    name = sectionName;
}

GardenSection::~GardenSection() {
    // Clean up all child components
    for (std::list<GardenComponent*>::iterator it = components.begin(); 
         it != components.end(); ++it) {
        delete *it;
    }
    components.clear();
}

void GardenSection::add(GardenComponent* component) {
    if (component != nullptr) {
        components.push_back(component);
    }
}

void GardenSection::remove(GardenComponent* component) {
    if (component != nullptr) {
        components.remove(component);
        delete component;
    }
}

void GardenSection::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << " " << name << " [" << getType() << "]" << std::endl;
    std::cout << indent << "   ID: " << id << ", Plants: " << getPlantCount() << std::endl;
    
    // Display all child components
    for (std::list<GardenComponent*>::iterator it = components.begin(); 
         it != components.end(); ++it) {
        (*it)->display(depth + 1);
    }
}

int GardenSection::getPlantCount() {
    int total = 0;
    for (std::list<GardenComponent*>::iterator it = components.begin(); 
         it != components.end(); ++it) {
        total += (*it)->getPlantCount();
    }
    return total;
}

GardenComponent* GardenSection::findByName(const std::string& searchName) {
    if (name == searchName) {
        return this;
    }
    
    // Search in all child components
    for (std::list<GardenComponent*>::iterator it = components.begin(); 
         it != components.end(); ++it) {
        GardenComponent* found = (*it)->findByName(searchName);
        if (found != nullptr) {
            return found;
        }
    }
    
    return nullptr;
}

GardenComponent* GardenSection::getChild(size_t index) {
    if (index >= components.size()) {
        return nullptr;
    }
    
    std::list<GardenComponent*>::iterator it = components.begin();
    std::advance(it, index);
    return *it;
}

std::string GardenSection::getType() {
    return "GardenSection";
}

std::string GardenSection::getName() {
    return name;
}