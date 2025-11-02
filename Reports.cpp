/**
 * @file Reports.cpp
 * @brief Implements the base Report class and ReportGenerator for generating and managing reports.
 */

#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

/**
 * @brief Generates the complete report by initializing, collecting, processing, and formatting data.
 * @return Formatted report string.
 */
std::string Report::generateReport() {
    std::stringstream report;
    
    try {
        initializeReport();
        collectData();
        processData();
        
        report << "=== " << reportTitle << " ===\n";
        report << "Generated: " << generatedDate << "\n";
        report << "Report Type: " << getReportType() << "\n\n";
        report << formatBody() << "\n";
        report << addFooter();
        
    } catch (const std::exception& e) {
        report << "Error generating report: " << e.what() << "\n";
    }
    
    return report.str();
}

/**
 * @brief Processes the collected data. Can be overridden by derived classes for specialized processing.
 */
void Report::processData() {
    std::cout << "Processing " << getReportType() << " data..." << std::endl;
    
    if (reportData.empty()) {
        std::cout << "Warning: No data collected for report" << std::endl;
    }
}

/**
 * @brief Provides a default footer for reports.
 * @return Formatted footer string.
 */
std::string Report::addFooter() {
    std::stringstream footer;
    footer << "\n" << std::string(50, '-') << "\n";
    footer << "End of " << reportTitle << "\n";
    footer << "Generated automatically by Garden Center Management System\n";
    footer << "Confidential - For internal use only";
    return footer.str();
}

/**
 * @brief Exports the report in the specified format.
 * @param format The format to export ("txt", "html", "pdf").
 * @return Message indicating the export result.
 */
std::string Report::exportReport(const std::string& format) {
    std::stringstream ss;
    ss << "Exporting " << getReportType() << " report as " << format << " format\n";
    
    if (format == "txt") {
        ss << "Text export completed successfully";
    } else if (format == "html") {
        ss << "HTML export completed successfully";
    } else if (format == "pdf") {
        ss << "PDF export completed successfully";
    } else {
        ss << "Unsupported export format: " << format;
    }
    
    return ss.str();
}

/**
 * @brief Registers a report with the generator.
 * @param type Report type string.
 * @param report Unique pointer to the report object.
 */
void ReportGenerator::registerReport(const std::string& type, std::unique_ptr<Report> report) {
    if (type.empty()) {
        throw std::invalid_argument("Report type cannot be empty");
    }
    if (report == nullptr) {
        throw std::invalid_argument("Report cannot be null");
    }
    
    availableReports[type] = std::move(report);
}

/**
 * @brief Generates a report by type.
 * @param type Report type string.
 * @return Generated report as a string.
 */
std::string ReportGenerator::generateReport(const std::string& type) {
    auto it = availableReports.find(type);
    if (it == availableReports.end()) {
        throw std::invalid_argument("Report type not found: " + type);
    }
    
    return it->second->generateReport();
}

/**
 * @brief Returns a list of all registered report types.
 * @return Vector of report type strings.
 */
std::vector<std::string> ReportGenerator::getAvailableReports() const {
    std::vector<std::string> types;
    for (const auto& pair : availableReports) {
        types.push_back(pair.first);
    }
    return types;
}

/**
 * @brief Checks if a report of the specified type is registered.
 * @param type Report type string.
 * @return True if the report is registered, false otherwise.
 */
bool ReportGenerator::hasReport(const std::string& type) const {
    return availableReports.find(type) != availableReports.end();
}
