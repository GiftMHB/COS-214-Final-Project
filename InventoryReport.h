#ifndef INVENTORY_REPORT_H
#define INVENTORY_REPORT_H

#include "Reports.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Forward declaration
class Inventory;

class InventoryReport : public Report {
private:
    Inventory* inventory;

public:
    InventoryReport(Inventory* inv);
    void initializeReport() override;
    void collectData() override;
    void processData() override;
    std::string formatBody() override;
    std::string addFooter() override;
    std::string getReportType() const override;
};

#endif