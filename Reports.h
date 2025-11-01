#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <ctime>

class Report {
protected:
    std::string reportTitle;
    std::string generatedDate;
    std::map<std::string, std::string> reportData;

public:
    virtual ~Report() = default;
    std::string generateReport();
    virtual void initializeReport() = 0;
    virtual void collectData() = 0;
    virtual void processData();
    virtual std::string formatBody() = 0;
    virtual std::string addFooter();
    virtual std::string getReportType() const = 0;
    virtual std::string exportReport(const std::string& format);
};

class ReportGenerator {
private:
    std::map<std::string, std::unique_ptr<Report>> availableReports;

public:
    void registerReport(const std::string& type, std::unique_ptr<Report> report);
    std::string generateReport(const std::string& type);
    std::vector<std::string> getAvailableReports() const;
    bool hasReport(const std::string& type) const;
};

#endif