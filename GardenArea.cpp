#include "GardenArea.h"
#include "GardenSection.h"
#include <algorithm>
#include <iostream>

GardenArea* GardenArea::instance = nullptr;

/* ------------------------------------------------------------------ */
/*  Construction                                                       */
/* ------------------------------------------------------------------ */
GardenArea::GardenArea()
    : totalCapacity(1000), temperature(25.0), humidity(60.0),
      id("GA-001"), name("Main Garden Area") {}

/* ------------------------------------------------------------------ */
/*  Singleton access                                                   */
/* ------------------------------------------------------------------ */
GardenArea& GardenArea::getInstance() {
    if (!instance) instance = new GardenArea();
    return *instance;
}

GardenArea* GardenArea::getInstancePtr() {
    return &getInstance();               // pointer version you used before
}

/* ------------------------------------------------------------------ */
/*  Helper – keep vector view in sync with list                        */
/* ------------------------------------------------------------------ */
void GardenArea::syncVectorView() {
    sectionVec.clear();
    for (auto* comp : sections) {
        if (auto* sec = dynamic_cast<GardenSection*>(comp))
            sectionVec.push_back(sec);
    }
}

/* ------------------------------------------------------------------ */
/*  Composite API (teammate)                                           */
/* ------------------------------------------------------------------ */
void GardenArea::add(GardenComponent* section) {
    sections.push_back(section);
    syncVectorView();
}

void GardenArea::remove(GardenComponent* section) {
    sections.remove(section);
    syncVectorView();
}

void GardenArea::display(int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << "[GardenArea] " << name
              << " (temp:" << temperature << "C, hum:" << humidity << "%)\n";
    for (auto* sec : sections)
        sec->display(depth + 1);
}

int GardenArea::getPlantCount() {
    int cnt = 0;
    for (auto* sec : sections) cnt += sec->getPlantCount();
    return cnt;
}

GardenComponent* GardenArea::findByName(const std::string& name) {
    if (this->name == name) return this;
    for (auto* sec : sections) {
        GardenComponent* found = sec->findByName(name);
        if (found) return found;
    }
    return nullptr;
}

std::list<Plant*> GardenArea::getAllPlants() {
    std::list<Plant*> all;
    for (auto* sec : sections) {
        std::list<Plant*> secPlants = sec->getAllPlants();
        all.splice(all.end(), secPlants);
    }
    return all;
}

/* ------------------------------------------------------------------ */
/*  Your original API (unchanged behaviour)                           */
/* ------------------------------------------------------------------ */
void GardenArea::addSection(GardenSection* section) {
    sections.push_back(section);      // treat as GardenComponent
    syncVectorView();
}

bool GardenArea::removeSection(const std::string& sectionId) {
    auto it = std::find_if(sections.begin(), sections.end(),
        [&sectionId](GardenComponent* c) {
            auto* sec = dynamic_cast<GardenSection*>(c);
            return sec && sec->getId() == sectionId;
        });
    if (it == sections.end()) return false;
    delete *it;
    sections.erase(it);
    syncVectorView();
    return true;
}

GardenSection* GardenArea::getSection(const std::string& id) {
    for (auto* comp : sections) {
        if (auto* sec = dynamic_cast<GardenSection*>(comp))
            if (sec->getId() == id) return sec;
    }
    return nullptr;
}

std::vector<GardenSection*> GardenArea::getAllSections() const {
    return sectionVec;                 // up-to-date view
}

/* ------------------------------------------------------------------ */
/*  Destructor                                                        */
/* ------------------------------------------------------------------ */
GardenArea::~GardenArea() {
    for (auto* sec : sections) delete sec;
    sections.clear();
    sectionVec.clear();
    if (instance == this) instance = nullptr;
}