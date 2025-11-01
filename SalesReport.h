#ifndef SALES_REPORT_H
#define SALES_REPORT_H

#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Forward declarations
class SalesRecord;

class SalesReport : public Report {
private:
    SalesRecord* salesRecord;
    std::time_t startDate;
    std::time_t endDate;

public:
    SalesReport(SalesRecord* sales, std::time_t start, std::time_t end);
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    std::string formatBody() override;
    std::string getReportType() const override;
};

#endif