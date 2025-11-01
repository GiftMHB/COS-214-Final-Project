#ifndef PLANT_HEALTH_REPORT_H
#define PLANT_HEALTH_REPORT_H

#include "Reports.h"
#include "Plant.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

class PlantHealthReport : public Report {
private:
    std::vector<Plant*> plants;

public:
    PlantHealthReport(const std::vector<Plant*>& plantList);
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    std::string formatBody() override;
    std::string addFooter() override;
    std::string getReportType() const override;
};

#endif