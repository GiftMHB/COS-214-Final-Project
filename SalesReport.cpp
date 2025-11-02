#include "SalesReport.h"
#include <stdexcept>

// Simple SalesRecord stub for compilation
class SalesRecord {
public:
    // Stub methods
};

SalesReport::SalesReport(SalesRecord* sales, std::time_t start, std::time_t end) 
    : salesRecord(sales), startDate(start), endDate(end) {
        
    if (sales == nullptr) {
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
    std::cout << "Collecting sales data..." << std::endl;
    
    // Simulate data collection
    reportData["TotalSales"] = "$12,847.25";
    reportData["UnitsSold"] = "324";
    reportData["Transactions"] = "187";
    reportData["AverageTransaction"] = "$68.70";
    reportData["BestSeller"] = "Rose Bush 'Peace'";
    reportData["BestSellerUnits"] = "45";
    reportData["GrowthRate"] = "+18.7%";
    reportData["CustomerCount"] = "156";
    reportData["ReturningCustomers"] = "89";
    
    std::cout << "Sales data collection completed" << std::endl;
}

void SalesReport::processData() {
    Report::processData();
    
    std::cout << "Analyzing sales trends and performance metrics..." << std::endl;
    
    int returning = std::stoi(reportData["ReturningCustomers"]);
    int totalCustomers = std::stoi(reportData["CustomerCount"]);
    double loyaltyRate = (static_cast<double>(returning) / totalCustomers) * 100;
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << loyaltyRate;
    reportData["CustomerLoyaltyRate"] = ss.str() + "%";
    
    double growth = 18.7;
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