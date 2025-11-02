// // GardenArea.cpp
// #include "GardenArea.h"
// #include "GardenSection.h" // Assuming this header exists; forward declaration in .h

// GardenArea* GardenArea::instance = nullptr;

// GardenArea::GardenArea() : totalCapacity(1000), temperature(25.0), humidity(60) {} // Defaults from project plan inference

// GardenArea* GardenArea::getInstance() {
//     if (instance == nullptr) {
//         instance = new GardenArea();
//     }
//     return instance;
// }

// void GardenArea::addSection(GardenSection* section) {
//     sections.push_back(section);
//     // Could update totalCapacity here if sections contribute to it
// }

// bool GardenArea::removeSection(const std::string& sectionId) {
//     for (auto it = sections.begin(); it != sections.end(); ++it) {
//         if ((*it)->getId() == sectionId) { // Assuming GardenSection has getId()
//             delete *it; // Memory management; beware
//             sections.erase(it);
//             return true;
//         }
//     }
//     return false;
// }

// GardenSection* GardenArea::getSection(const std::string& id) {
//     for (auto section : sections) {
//         if (section->getId() == id) {
//             return section;
//         }
//     }
//     return nullptr;
// }

// std::vector<GardenSection*> GardenArea::getAllSections() const {
//     return sections;
// }

// int GardenArea::getTotalCapacity() const {
//     return totalCapacity;
// }

// void GardenArea::setTemperature(double temp) {
//     temperature = temp;
// }

// double GardenArea::getTemperature() const {
//     return temperature;
// }

// void GardenArea::setHumidity(int hum) {
//     humidity = hum;
// }

// int GardenArea::getHumidity() const {
//     return humidity;
// }

// GardenArea::~GardenArea() {
//     for (auto section : sections) {
//         delete section;
//     }
//     sections.clear();
// }

#include "GardenArea.h"
#include "GardenSection.h"  // For dynamic_cast<GardenSection*>
#include <iostream>
#include <algorithm>  // for std::find
#include <sstream>

GardenArea* GardenArea::instance = nullptr;

GardenArea::GardenArea() 
    : totalCapacity(1000), temperature(22.0), humidity(60.0), id("GA001"), name("Main Garden Area") {}

GardenArea& GardenArea::getInstance() {
    if (instance == nullptr) {
        instance = new GardenArea();
    }
    return *instance;
}

GardenArea::~GardenArea() {
    for (auto* section : sections) {
        delete section;
    }
    sections.clear();
}

void GardenArea::add(GardenComponent* section) {
    if (section != nullptr) {
        sections.push_back(section);
    }
}

void GardenArea::remove(GardenComponent* section) {
    auto it = std::find(sections.begin(), sections.end(), section);
    if (it != sections.end()) {
        sections.erase(it);
        delete section;
    }
}

void GardenArea::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << " " << name << " [" << getType() << "]" << std::endl;
    std::cout << indent << "   Temperature: " << temperature << "°C, "
              << "Humidity: " << humidity << "%" << std::endl;
    std::cout << indent << "   Total Plants: " << getPlantCount() << std::endl;
    for (auto* section : sections) {
        section->display(depth + 1);
    }
}

int GardenArea::getPlantCount() {
    int total = 0;
    for (auto* section : sections) {
        total += section->getPlantCount();
    }
    return total;
}

GardenComponent* GardenArea::findByName(const std::string& searchName) {
    if (name == searchName) {
        return this;
    }
    for (auto* section : sections) {
        GardenComponent* found = section->findByName(searchName);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::list<Plant*> GardenArea::getAllPlants() {
    std::list<Plant*> all;
    for (auto* c : sections) {
        std::list<Plant*> sub = c->getAllPlants();
        all.insert(all.end(), sub.begin(), sub.end());
    }
    return all;
}

std::string GardenArea::getType() {
    return "GardenArea";
}

std::string GardenArea::getName() {
    return name;
}

void GardenArea::setTemperature(double temp) {
    temperature = temp;
}

double GardenArea::getTemperature() const {
    return temperature;
}

void GardenArea::setHumidity(double hum) {
    humidity = hum;
}

double GardenArea::getHumidity() const {
    return humidity;
}

void GardenArea::addSection(GardenComponent* section) {
    add(section);
}

bool GardenArea::removeSection(const std::string& sectionId) {
    for (auto it = sections.begin(); it != sections.end(); ++it) {
        if (GardenSection* sec = dynamic_cast<GardenSection*>(*it)) {
            if (sec->getId() == sectionId) {
                delete *it;
                sections.erase(it);
                return true;
            }
        }
    }
    return false;
}

GardenComponent* GardenArea::getSection(const std::string& id) {
    for (auto* c : sections) {
        if (GardenSection* sec = dynamic_cast<GardenSection*>(c)) {
            if (sec->getId() == id) return sec;
        }
    }
    return nullptr;
}

std::vector<GardenComponent*> GardenArea::getAllSections() const {
    std::vector<GardenComponent*> secs;
    for (auto* c : sections) {
        if (dynamic_cast<GardenSection*>(c)) secs.push_back(c);
    }
    return secs;
}

int GardenArea::getTotalCapacity() const {
    return totalCapacity;
}