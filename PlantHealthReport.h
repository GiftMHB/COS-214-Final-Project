/**
 * @file PlantHealthReport.h
 * @brief Defines the PlantHealthReport class for generating health reports of plants.
 */

#ifndef PLANT_HEALTH_REPORT_H
#define PLANT_HEALTH_REPORT_H

#include "Reports.h"
#include "Plant.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * @class PlantHealthReport
 * @brief Generates a detailed report on the health status of a collection of plants.
 *
 * The report includes health metrics such as water levels, nutrient levels,
 * and readiness for sale. It provides formatted output and a footer with
 * relevant contact information or guidance.
 */
class PlantHealthReport : public Report {
private:
    /**
     * @brief List of plants to be included in the health report.
     */
    std::vector<Plant*> plants;

public:
    /**
     * @brief Constructs a PlantHealthReport with a list of plants.
     * @param plantList Vector of pointers to Plant objects to include in the report.
     */
    PlantHealthReport(const std::vector<Plant*>& plantList);

    /**
     * @brief Initializes the report by setting the title and generated date.
     */
    void initializeReport() override;

    /**
     * @brief Collects necessary data from all plants in the report.
     */
    void collectData() override;

    /**
     * @brief Processes collected data to compute derived health metrics.
     */
    void processData() override;

    /**
     * @brief Formats the body of the report as a string.
     * @return Formatted report body.
     */
    std::string formatBody() override;

    /**
     * @brief Adds a footer with additional information or contacts.
     * @return Formatted footer string.
     */
    std::string addFooter() override;

    /**
     * @brief Returns the type of report.
     * @return String representing the report type ("PlantHealth").
     */
    std::string getReportType() const override;
};

#endif
