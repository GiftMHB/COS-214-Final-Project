/**
 * @file Report.h
 * @brief Template Method pattern for report generation with customizable steps
 * @details Defines the report generation algorithm skeleton with customizable steps
 */

#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <ctime> // Add this for time_t

// Forward declarations
class Inventory;
class SalesRecord;

/**
 * @brief Abstract base class for all reports using Template Method pattern
 * @details Defines the skeleton of report generation algorithm with customizable steps
 */
class Report {
protected:
    std::string reportTitle;
    std::string generatedDate;
    std::map<std::string, std::string> reportData;

    /**
     * @brief Initialize report with basic information
     */
    virtual void initializeReport() = 0;
    
    /**
     * @brief Collect data needed for the report
     */
    virtual void collectData() = 0;
    
    /**
     * @brief Process and analyze collected data
     */
    virtual void processData();
    
    /**
     * @brief Format the main body of the report
     * @return Formatted report body as string
     */
    virtual std::string formatBody() = 0;
    
    /**
     * @brief Add footer to the report
     * @return Formatted footer as string
     */
    virtual std::string addFooter();

public:
    virtual ~Report() = default;
    
    /**
     * @brief Generate the complete report (Template Method)
     * @return Complete formatted report as string
     */
    virtual std::string generateReport();
    
    /**
     * @brief Export report in specific format
     * @param format Export format (txt, html, pdf, etc.)
     * @return Export status message
     */
    virtual std::string exportReport(const std::string& format);
    
    /**
     * @brief Get report type identifier
     * @return Report type string
     */
    virtual std::string getReportType() const = 0;
    
    /**
     * @brief Get report title
     * @return Report title
     */
    std::string getTitle() const { return reportTitle; }
    
    /**
     * @brief Get generation date
     * @return Date when report was generated
     */
    std::string getGenerationDate() const { return generatedDate; }
};

/**
 * @brief Concrete report for inventory status
 */
class InventoryReport : public Report {
private:
    Inventory* inventory;

public:
    /**
     * @brief Construct a new InventoryReport object
     * @param inv Pointer to inventory system
     */
    explicit InventoryReport(Inventory* inv);
    
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    std::string formatBody() override;
    std::string addFooter() override;
    std::string getReportType() const override;
    
    /**
     * @brief Set custom title for inventory report
     * @param title Custom report title
     */
    void setCustomTitle(const std::string& title) { reportTitle = title; }
};

/**
 * @brief Concrete report for sales performance
 */
class SalesReport : public Report {
private:
    SalesRecord* salesRecord;
    std::time_t startDate;
    std::time_t endDate;

public:
    /**
     * @brief Construct a new SalesReport object
     * @param sales Pointer to sales record system
     * @param start Start date for report period
     * @param end End date for report period
     */
    SalesReport(SalesRecord* sales, std::time_t start, std::time_t end);
    
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    std::string formatBody() override;
    std::string getReportType() const override;
    
    /**
     * @brief Set report period dates
     * @param start Start date for report
     * @param end End date for report
     */
    void setReportPeriod(std::time_t start, std::time_t end) {
        startDate = start;
        endDate = end;
    }
};

/**
 * @brief Report generator facade for creating and managing reports
 */
class ReportGenerator {
private:
    std::map<std::string, std::unique_ptr<Report>> availableReports;

public:
    /**
     * @brief Register a report type with the generator
     * @param type Report type identifier
     * @param report Unique pointer to report instance
     */
    void registerReport(const std::string& type, std::unique_ptr<Report> report);
    
    /**
     * @brief Generate a report of specified type
     * @param type Type of report to generate
     * @return Generated report content
     * @throws std::invalid_argument if report type not found
     */
    std::string generateReport(const std::string& type);
    
    /**
     * @brief Get list of available report types
     * @return Vector of available report type strings
     */
    std::vector<std::string> getAvailableReports() const;
    
    /**
     * @brief Check if report type is available
     * @param type Report type to check
     * @return True if report type is available
     */
    bool hasReport(const std::string& type) const;
};

#endif // REPORT_H