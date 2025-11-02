#ifndef GARDENSECTION_H
#define GARDENSECTION_H

#include "GardenComponent.h"
#include <string>
#include <vector>
#include <list>  // Explicit include for std::list<Plant*>

class GardenSection : public GardenComponent {
private:
    std::string name;
    std::string id;
    std::vector<GardenComponent*> components;

public:
    GardenSection(const std::string& sectionName, const std::string& sectionId);
    ~GardenSection();

    void add(GardenComponent* component) override;
    void remove(GardenComponent* component) override;
    void display(int depth = 0) override;
    int getPlantCount() override;
    GardenComponent* findByName(const std::string& name) override;
    std::list<Plant*> getAllPlants() override;
    std::string getType() override;
    std::string getName() override;
    GardenComponent* getChild(size_t index) override;

    std::string getId() const;
};

#endif // GARDENSECTION_H