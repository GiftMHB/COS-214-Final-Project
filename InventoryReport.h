/**
 * @file InventoryReport.h
 * @brief Declares the InventoryReport class for generating inventory reports.
 */

#ifndef INVENTORY_REPORT_H
#define INVENTORY_REPORT_H

#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Forward declaration
class Inventory;

/**
 * @class InventoryReport
 * @brief Generates a report summarizing the current inventory status.
 *
 * The InventoryReport class implements the Report interface and provides
 * methods to initialize, collect, process, and format inventory data, 
 * including a footer for additional information.
 */
class InventoryReport : public Report {
private:
    /**
     * @brief Pointer to the Inventory containing inventory data.
     */
    Inventory* inventory;

public:
    /**
     * @brief Constructs an InventoryReport for a given inventory.
     * @param inv Pointer to the Inventory object containing inventory data.
     */
    InventoryReport(Inventory* inv);

    /**
     * @brief Initializes the report, preparing headers or required data structures.
     */
    void initializeReport() override;

    /**
     * @brief Collects the necessary inventory data for the report.
     */
    void collectData() override;

    /**
     * @brief Processes the collected inventory data (e.g., aggregations, calculations).
     */
    void processData() override;

    /**
     * @brief Formats the body of the inventory report into a human-readable string.
     * @return A string representing the formatted report body.
     */
    std::string formatBody() override;

    /**
     * @brief Adds a footer section to the report, such as totals or summary information.
     * @return A string representing the footer of the report.
     */
    std::string addFooter() override;

    /**
     * @brief Returns the type of the report.
     * @return A string indicating the report type (e.g., "InventoryReport").
     */
    std::string getReportType() const override;
};

#endif
