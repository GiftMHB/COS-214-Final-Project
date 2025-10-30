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