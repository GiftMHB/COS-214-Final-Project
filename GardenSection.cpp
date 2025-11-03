#include "GardenSection.h"
#include <iostream>
#include <algorithm>

GardenSection::GardenSection(const std::string& sectionName, const std::string& sectionId)
    : name(sectionName), id(sectionId) {}

GardenSection::~GardenSection() {
    for (auto* comp : components) {
        delete comp;
    }
    components.clear();
}

void GardenSection::add(GardenComponent* component) {
    if (component != nullptr) {
        components.push_back(component);
    }
}

void GardenSection::remove(GardenComponent* component) {
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end()) {
        components.erase(it);
        delete component;
    }
}

void GardenSection::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << " " << name << " [" << getType() << "]" << std::endl;
    std::cout << indent << "   ID: " << id << ", Plants: " << getPlantCount() << std::endl;
    for (auto* comp : components) {
        comp->display(depth + 1);
    }
}

int GardenSection::getPlantCount() {
    int total = 0;
    for (auto* comp : components) {
        total += comp->getPlantCount();
    }
    return total;
}

GardenComponent* GardenSection::findByName(const std::string& searchName) {
    if (name == searchName) {
        return this;
    }
    for (auto* comp : components) {
        GardenComponent* found = comp->findByName(searchName);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::list<Plant*> GardenSection::getAllPlants() {
    std::list<Plant*> all;
    for (auto* c : components) {
        auto sub = c->getAllPlants();
        all.insert(all.end(), sub.begin(), sub.end());
    }
    return all;
}

std::string GardenSection::getType() {
    return "GardenSection";
}

std::string GardenSection::getName() {
    return name;
}

GardenComponent* GardenSection::getChild(size_t index) {
    if (index < components.size()) {
        return components[index];
    }
    return nullptr;
}

std::string GardenSection::getId() const {
    return id;
}