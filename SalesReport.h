#ifndef SALES_REPORT_H
#define SALES_REPORT_H

#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Forward declarations
class SalesRecord;

/**
 * @file SalesReport.h
 * @brief Declares the SalesReport class for generating sales reports within a specified date range.
 *
 * @class SalesReport
 * @brief Generates a report summarizing sales records for a given time period.
 *
 * The SalesReport class implements the Report interface and provides functionality
 * to initialize, collect, process, and format sales data for reporting purposes.
 */
class SalesReport : public Report {
private:
    /**
     * @brief Pointer to the SalesRecord containing sales data.
     */
    SalesRecord* salesRecord;

    /**
     * @brief Start date of the reporting period.
     */
    std::time_t startDate;

    /**
     * @brief End date of the reporting period.
     */
    std::time_t endDate;

public:
    /**
     * @brief Constructs a SalesReport object for a given sales record and date range.
     * @param sales Pointer to the SalesRecord containing sales data.
     * @param start Start date of the reporting period.
     * @param end End date of the reporting period.
     */
    SalesReport(SalesRecord* sales, std::time_t start, std::time_t end);

    /**
     * @brief Initializes the report (e.g., prepares data structures, headers).
     */
    void initializeReport() override;

    /**
     * @brief Collects the necessary sales data for the report.
     */
    void collectData() override;

    /**
     * @brief Processes the collected data (e.g., calculations, aggregations).
     */
    void processData() override;

    /**
     * @brief Formats the body of the report into a human-readable string.
     * @return A string representing the formatted report body.
     */
    std::string formatBody() override;

    /**
     * @brief Returns the type of the report.
     * @return A string indicating the report type (e.g., "SalesReport").
     */
    std::string getReportType() const override;
};

#endif
