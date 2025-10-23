#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

// Forward declarations
class Plant;
class Inventory;
class SalesRecord;

/**
 * @brief Abstract base class for all report generators using Template Method pattern
 * 
 * Defines the skeleton of the report generation algorithm, allowing subclasses
 * to override specific steps while maintaining the overall structure.
 * This ensures consistent report formatting across different report types.
 */
class Report {
protected:
    string reportTitle;
    string generatedDate;
    map<string, string> reportData;
    
    /**
     * @brief Sets up report header and initial data (hook method)
     */
    virtual void initializeReport() = 0;
    
    /**
     * @brief Collects data specific to the report type (abstract method)
     */
    virtual void collectData() = 0;
    
    /**
     * @brief Processes and analyzes the collected data (hook method)
     */
    virtual void processData();
    
    /**
     * @brief Formats the report body content (abstract method)
     */
    virtual string formatBody() = 0;
    
    /**
     * @brief Adds common footer to all reports (hook method)
     */
    virtual string addFooter();

public:
    virtual ~Report() {}
    
    /**
     * @brief Template method that defines the report generation algorithm
     * 
     * This is the core template method that subclasses cannot override.
     * It defines the fixed sequence of steps for generating any report.
     * 
     * @return Complete formatted report as a string
     */
    string generateReport();
    
    /**
     * @brief Gets the report type for identification
     * @return Report type string
     */
    virtual string getReportType() const = 0;
    
    /**
     * @brief Exports report to different formats (hook method)
     * @param format The export format (txt, html, csv)
     * @return Export success message
     */
    virtual string exportReport(const string& format);
};

/**
 * @brief Concrete report for inventory status and stock levels
 */
class InventoryReport : public Report {
private:
    Inventory* inventory;
    
protected:
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    string formatBody() override;
    string addFooter() override;

public:
    InventoryReport(Inventory* inv);
    string getReportType() const override;
    string exportReport(const string& format) override;
};

/**
 * @brief Concrete report for sales performance and revenue
 */
class SalesReport : public Report {
private:
    SalesRecord* salesRecord;
    time_t startDate;
    time_t endDate;
    
protected:
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    string formatBody() override;

public:
    SalesReport(SalesRecord* sales, time_t start, time_t end);
    string getReportType() const override;
    string exportReport(const string& format) override;
};

/**
 * @brief Concrete report for plant health and growth metrics
 */
class PlantHealthReport : public Report {
private:
    vector<Plant*> plants;
    
protected:
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    string formatBody() override;

public:
    PlantHealthReport(const vector<Plant*>& plantList);
    string getReportType() const override;
    
    /**
     * @brief Adds health metrics analysis specific to plant reports
     */
    string addHealthMetrics();
};

/**
 * @brief Concrete report for staff performance and activities
 */
class StaffPerformanceReport : public Report {
private:
    vector<string> staffMembers;
    time_t reportPeriod;
    
protected:
    void initializeReport() override;
    void collectData() override;
    string formatBody() override;
    string addFooter() override;

public:
    StaffPerformanceReport(const vector<string>& staff, time_t period);
    string getReportType() const override;
};

#endif // REPORT_H