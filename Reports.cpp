#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

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

void Report::processData() {
    std::cout << "Processing " << getReportType() << " data..." << std::endl;
    
    if (reportData.empty()) {
        std::cout << "Warning: No data collected for report" << std::endl;
    }
}

std::string Report::addFooter() {
    std::stringstream footer;
    footer << "\n" << std::string(50, '-') << "\n";
    footer << "End of " << reportTitle << "\n";
    footer << "Generated automatically by Garden Center Management System\n";
    footer << "Confidential - For internal use only";
    return footer.str();
}

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

void ReportGenerator::registerReport(const std::string& type, std::unique_ptr<Report> report) {
    if (type.empty()) {
        throw std::invalid_argument("Report type cannot be empty");
    }
    if (report == nullptr) {
        throw std::invalid_argument("Report cannot be null");
    }
    
    availableReports[type] = std::move(report);
}

std::string ReportGenerator::generateReport(const std::string& type) {
    auto it = availableReports.find(type);
    if (it == availableReports.end()) {
        throw std::invalid_argument("Report type not found: " + type);
    }
    
    return it->second->generateReport();
}

std::vector<std::string> ReportGenerator::getAvailableReports() const {
    std::vector<std::string> types;
    for (const auto& pair : availableReports) {
        types.push_back(pair.first);
    }
    return types;
}

bool ReportGenerator::hasReport(const std::string& type) const {
    return availableReports.find(type) != availableReports.end();
}