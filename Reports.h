/**
 * @file Reports.h
 * @brief Defines the base Report class and the ReportGenerator for creating and managing reports.
 */

#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <ctime>

/**
 * @class Report
 * @brief Abstract base class for generating different types of reports.
 *
 * Provides the framework for report generation including initialization, data collection,
 * processing, formatting, footer generation, and exporting in various formats.
 */
class Report {
protected:
    std::string reportTitle;                   /**< Title of the report */
    std::string generatedDate;                 /**< Date and time the report was generated */
    std::map<std::string, std::string> reportData; /**< Key-value map for storing report data */

public:
    virtual ~Report() = default;

    /**
     * @brief Generates the complete report as a string.
     * @return Formatted report string including body and footer.
     */
    std::string generateReport();

    /**
     * @brief Initializes report metadata such as title and date.
     */
    virtual void initializeReport() = 0;

    /**
     * @brief Collects the data required for the report.
     */
    virtual void collectData() = 0;

    /**
     * @brief Processes the collected data.
     *
     * Can be overridden by derived classes to perform specific data analysis.
     */
    virtual void processData();

    /**
     * @brief Formats the main body of the report.
     * @return Formatted body string.
     */
    virtual std::string formatBody() = 0;

    /**
     * @brief Adds a footer to the report.
     * @return Formatted footer string.
     */
    virtual std::string addFooter();

    /**
     * @brief Returns the type of the report.
     * @return Report type as a string.
     */
    virtual std::string getReportType() const = 0;

    /**
     * @brief Exports the report in the specified format.
     * @param format Format string ("txt", "html", "pdf", etc.)
     * @return Message indicating the result of the export.
     */
    virtual std::string exportReport(const std::string& format);
};

/**
 * @class ReportGenerator
 * @brief Manages and generates multiple reports by type.
 *
 * Allows registering reports, generating reports by type, listing available reports,
 * and checking for the existence of a specific report type.
 */
class ReportGenerator {
private:
    std::map<std::string, std::unique_ptr<Report>> availableReports; /**< Map of registered reports */

public:
    /**
     * @brief Registers a report with the generator.
     * @param type Type string for the report.
     * @param report Unique pointer to the report object.
     */
    void registerReport(const std::string& type, std::unique_ptr<Report> report);

    /**
     * @brief Generates a report of the specified type.
     * @param type Report type string.
     * @return Generated report string.
     */
    std::string generateReport(const std::string& type);

    /**
     * @brief Returns a list of all registered report types.
     * @return Vector of report type strings.
     */
    std::vector<std::string> getAvailableReports() const;

    /**
     * @brief Checks if a report of the given type is registered.
     * @param type Report type string.
     * @return True if the report exists, false otherwise.
     */
    bool hasReport(const std::string& type) const;
};

#endif
