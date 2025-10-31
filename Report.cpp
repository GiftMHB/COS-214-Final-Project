/**
 * @file Report.cpp
 * @brief Implementation of Template Method pattern for report generation
 */

#include "Report.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

// Placeholder implementations - replace with actual classes when available
class Inventory {
public:
    // Add actual inventory methods
};

class SalesRecord {
public:
    // Add actual sales record methods
};

// Base Report implementation
std::string Report::generateReport() {
    // Template Method - defines the algorithm skeleton
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
    // Default processing - can be overridden by subclasses
    std::cout << "Processing " << getReportType() << " data..." << std::endl;
    
    // Basic data validation
    if (reportData.empty()) {
        std::cout << "Warning: No data collected for report" << std::endl;
    }
}

std::string Report::addFooter() {
    // Default footer implementation
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

// InventoryReport implementation
InventoryReport::InventoryReport(Inventory* inv) : inventory(inv) {
    if (inv == nullptr) {
        // Allow nullptr for demonstration
        std::cout << "Warning: Inventory is null in InventoryReport constructor\n";
    }
}

void InventoryReport::initializeReport() {
    reportTitle = "Comprehensive Inventory Status Report";
    
    // Set current date/time with proper formatting
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);
    
    std::stringstream dateStream;
    dateStream << std::put_time(timeInfo, "%Y-%m-%d at %H:%M:%S");
    generatedDate = dateStream.str();
}

void InventoryReport::collectData() {
    std::cout << "Collecting comprehensive inventory data..." << std::endl;
    
    // Simulate data collection from inventory system
    // In actual implementation, this would query the inventory object
    
    reportData["TotalItems"] = "247";
    reportData["PlantsInStock"] = "189";
    reportData["SuppliesInStock"] = "58";
    reportData["LowStockItems"] = "23";
    reportData["OutOfStock"] = "7";
    reportData["TotalValue"] = "R8,425.50";
    reportData["AverageItemValue"] = "R34.11";
    reportData["InventoryTurnover"] = "2.8";
    
    std::cout << "Inventory data collection completed" << std::endl;
}

void InventoryReport::processData() {
    Report::processData(); // Call base implementation
    
    std::cout << "Performing inventory-specific data analysis..." << std::endl;
    
    // Calculate additional metrics
    int lowStock = std::stoi(reportData["LowStockItems"]);
    int totalItems = std::stoi(reportData["TotalItems"]);
    double lowStockPercentage = (static_cast<double>(lowStock) / totalItems) * 100;
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << lowStockPercentage;
    reportData["LowStockPercentage"] = ss.str() + "%";
    
    // Add risk assessment
    if (lowStockPercentage > 20) {
        reportData["StockRisk"] = "HIGH - Consider bulk ordering";
    } else if (lowStockPercentage > 10) {
        reportData["StockRisk"] = "MEDIUM - Monitor closely";
    } else {
        reportData["StockRisk"] = "LOW - Healthy inventory levels";
    }
}

std::string InventoryReport::formatBody() {
    std::stringstream body;
    
    body << "INVENTORY OVERVIEW:\n";
    body << std::string(40, '-') << "\n";
    body << "Total Items: " << reportData["TotalItems"] << "\n";
    body << "Plants in Stock: " << reportData["PlantsInStock"] << "\n";
    body << "Supplies in Stock: " << reportData["SuppliesInStock"] << "\n";
    body << "Total Inventory Value: " << reportData["TotalValue"] << "\n";
    body << "Average Item Value: " << reportData["AverageItemValue"] << "\n";
    body << "Inventory Turnover Rate: " << reportData["InventoryTurnover"] << "\n\n";
    
    body << "STOCK LEVEL ANALYSIS:\n";
    body << std::string(40, '-') << "\n";
    body << "Low Stock Items: " << reportData["LowStockItems"] << "\n";
    body << "Out of Stock Items: " << reportData["OutOfStock"] << "\n";
    body << "Low Stock Percentage: " << reportData["LowStockPercentage"] << "\n";
    body << "Risk Assessment: " << reportData["StockRisk"] << "\n\n";
    
    body << "RECOMMENDED ACTIONS:\n";
    body << std::string(40, '-') << "\n";
    body << "1. Restock out-of-stock items immediately\n";
    body << "2. Review low-stock items for reorder planning\n";
    body << "3. Consider seasonal demand for upcoming quarters\n";
    body << "4. Evaluate supplier performance for critical items\n";
    body << "5. Optimize inventory layout for fast-moving items\n";
    
    return body.str();
}

std::string InventoryReport::addFooter() {
    std::stringstream footer;
    footer << "\n" << std::string(50, '=') << "\n";
    footer << "INVENTORY MANAGEMENT CONTACTS:\n";
    footer << "• Inventory Manager: manager@gardencenter.com\n";
    footer << "• Procurement: procurement@gardencenter.com\n";
    footer << "• Emergency Orders: emergency@gardencenter.com\n";
    footer << std::string(50, '=') << "\n";
    footer << "Next scheduled inventory audit: 30 days\n";
    footer << "Report generated by Automated Inventory System v2.1";
    return footer.str();
}

std::string InventoryReport::getReportType() const {
    return "Inventory";
}

// SalesReport implementation
SalesReport::SalesReport(SalesRecord* sales, std::time_t start, std::time_t end) 
    : salesRecord(sales), startDate(start), endDate(end) {
        
    if (sales == nullptr) {
        // Allow nullptr for demonstration
        std::cout << "Warning: SalesRecord is null in SalesReport constructor\n";
    }
    if (startDate > endDate) {
        throw std::invalid_argument("Start date cannot be after end date");
    }
}

void SalesReport::initializeReport() {
    reportTitle = "Sales Performance Analysis Report";
    
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);
    
    std::stringstream dateStream;
    dateStream << std::put_time(timeInfo, "%Y-%m-%d at %H:%M:%S");
    generatedDate = dateStream.str();
}

void SalesReport::collectData() {
    std::cout << "Collecting sales data from period " << startDate << " to " << endDate << std::endl;
    
    // Simulate data collection from sales system
    reportData["TotalSales"] = "R12,847.25";
    reportData["UnitsSold"] = "324";
    reportData["Transactions"] = "187";
    reportData["AverageTransaction"] = "R68.70";
    reportData["BestSeller"] = "Rose Bush 'Peace'";
    reportData["BestSellerUnits"] = "45";
    reportData["GrowthRate"] = "+18.7%";
    reportData["CustomerCount"] = "156";
    reportData["ReturningCustomers"] = "89";
    
    std::cout << "Sales data collection completed" << std::endl;
}

void SalesReport::processData() {
    Report::processData(); // Call base implementation
    
    std::cout << "Analyzing sales trends and performance metrics..." << std::endl;
    
    // Calculate customer loyalty metrics
    int returning = std::stoi(reportData["ReturningCustomers"]);
    int totalCustomers = std::stoi(reportData["CustomerCount"]);
    double loyaltyRate = (static_cast<double>(returning) / totalCustomers) * 100;
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << loyaltyRate;
    reportData["CustomerLoyaltyRate"] = ss.str() + "%";
    
    // Performance rating
    double growth = 18.7; // Extract from GrowthRate in real implementation
    if (growth > 15) {
        reportData["Performance"] = "EXCELLENT - Exceeding targets";
    } else if (growth > 5) {
        reportData["Performance"] = "GOOD - Meeting expectations";
    } else {
        reportData["Performance"] = "NEEDS IMPROVEMENT - Below targets";
    }
}

std::string SalesReport::formatBody() {
    std::stringstream body;
    
    // Format date range
    std::tm* startInfo = std::localtime(&startDate);
    std::tm* endInfo = std::localtime(&endDate);
    
    std::stringstream periodStream;
    periodStream << std::put_time(startInfo, "%Y-%m-%d") << " to " 
                 << std::put_time(endInfo, "%Y-%m-%d");
    
    body << "SALES PERFORMANCE SUMMARY:\n";
    body << std::string(40, '-') << "\n";
    body << "Reporting Period: " << periodStream.str() << "\n";
    body << "Total Revenue: " << reportData["TotalSales"] << "\n";
    body << "Units Sold: " << reportData["UnitsSold"] << "\n";
    body << "Total Transactions: " << reportData["Transactions"] << "\n";
    body << "Average Transaction Value: " << reportData["AverageTransaction"] << "\n";
    body << "Growth Rate vs Previous Period: " << reportData["GrowthRate"] << "\n";
    body << "Overall Performance: " << reportData["Performance"] << "\n\n";
    
    body << "CUSTOMER ANALYSIS:\n";
    body << std::string(40, '-') << "\n";
    body << "Total Customers: " << reportData["CustomerCount"] << "\n";
    body << "Returning Customers: " << reportData["ReturningCustomers"] << "\n";
    body << "Customer Loyalty Rate: " << reportData["CustomerLoyaltyRate"] << "\n\n";
    
    body << "PRODUCT PERFORMANCE:\n";
    body << std::string(40, '-') << "\n";
    body << "Best Selling Item: " << reportData["BestSeller"] << "\n";
    body << "Units Sold (Best Seller): " << reportData["BestSellerUnits"] << "\n\n";
    
    body << "TREND ANALYSIS AND INSIGHTS:\n";
    body << std::string(40, '-') << "\n";
    body << "• Flowering plants showed strongest growth (+25%)\n";
    body << "• Tree sales remained stable with seasonal patterns\n";
    body << "• Premium plant varieties outperforming expectations\n";
    body << "• Weekend sales account for 45% of total revenue\n";
    body << "• Online inquiries converting at 18% rate\n";
    
    return body.str();
}

std::string SalesReport::getReportType() const {
    return "Sales";
}

// ReportGenerator implementation
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