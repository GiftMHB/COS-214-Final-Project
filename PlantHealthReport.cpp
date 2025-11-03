#include "PlantHealthReport.h"
#include <algorithm>
#include <numeric>

PlantHealthReport::PlantHealthReport(const std::vector<Plant*>& plantList) 
    : plants(plantList) {
    
    if (plants.empty()) {
        std::cout << "Warning: Empty plant list provided to PlantHealthReport\n";
    }
}

void PlantHealthReport::initializeReport() {
    reportTitle = "Comprehensive Plant Health Status Report";
    
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);
    
    std::stringstream dateStream;
    dateStream << std::put_time(timeInfo, "%Y-%m-%d at %H:%M:%S");
    generatedDate = dateStream.str();
}

void PlantHealthReport::collectData() {
    std::cout << "Collecting plant health data for " << plants.size() << " plants..." << std::endl;
    
    if (plants.empty()) {
        reportData["TotalPlants"] = "0";
        reportData["HealthyPlants"] = "0";
        reportData["UnhealthyPlants"] = "0";
        reportData["DeadPlants"] = "0";
        reportData["AverageHealth"] = "0";
        return;
    }
    
    int healthyCount = 0;
    int unhealthyCount = 0;
    int deadCount = 0;
    double totalHealth = 0.0;
    
    for (const Plant* plant : plants) {
        double health = plant->getHealth();
        totalHealth += health;
        
        if (health >= 70) {
            healthyCount++;
        } else if (health >= 30) {
            unhealthyCount++;
        } else {
            deadCount++;
        }
    }
    
    reportData["TotalPlants"] = std::to_string(plants.size());
    reportData["HealthyPlants"] = std::to_string(healthyCount);
    reportData["UnhealthyPlants"] = std::to_string(unhealthyCount);
    reportData["DeadPlants"] = std::to_string(deadCount);
    reportData["AverageHealth"] = std::to_string(totalHealth / plants.size());
    
    std::cout << "Plant health data collection completed" << std::endl;
}

void PlantHealthReport::processData() {
    Report::processData();
    
    std::cout << "Analyzing plant health trends..." << std::endl;
    
    int total = std::stoi(reportData["TotalPlants"]);
    int healthy = std::stoi(reportData["HealthyPlants"]);
    int dead = std::stoi(reportData["DeadPlants"]);
    
    if (total > 0) {
        double healthyPercentage = (static_cast<double>(healthy) / total) * 100;
        double deadPercentage = (static_cast<double>(dead) / total) * 100;
        
        std::stringstream ss1, ss2;
        ss1 << std::fixed << std::setprecision(1) << healthyPercentage;
        ss2 << std::fixed << std::setprecision(1) << deadPercentage;
        
        reportData["HealthyPercentage"] = ss1.str() + "%";
        reportData["DeadPercentage"] = ss2.str() + "%";
        
        if (deadPercentage > 20) {
            reportData["HealthRisk"] = "HIGH - Immediate attention required";
        } else if (deadPercentage > 10) {
            reportData["HealthRisk"] = "MEDIUM - Monitor closely";
        } else {
            reportData["HealthRisk"] = "LOW - Healthy plant population";
        }
    }
}

std::string PlantHealthReport::formatBody() {
    std::stringstream body;
    
    body << "PLANT HEALTH OVERVIEW:\n";
    body << std::string(40, '-') << "\n";
    body << "Total Plants Monitored: " << reportData["TotalPlants"] << "\n";
    body << "Healthy Plants (≥70% health): " << reportData["HealthyPlants"] 
         << " (" << reportData["HealthyPercentage"] << ")\n";
    body << "Unhealthy Plants (30-69% health): " << reportData["UnhealthyPlants"] << "\n";
    body << "Dead Plants (<30% health): " << reportData["DeadPlants"] 
         << " (" << reportData["DeadPercentage"] << ")\n";
    body << "Average Health Score: " << reportData["AverageHealth"] << "%\n";
    body << "Overall Health Risk: " << reportData["HealthRisk"] << "\n\n";
    
    body << "HEALTH DISTRIBUTION:\n";
    body << std::string(40, '-') << "\n";
    
    if (plants.empty()) {
        body << "No plants available for health analysis.\n";
    } else {
        // Sample individual plant health
        body << "Sample Plant Health Status:\n";
        int sampleSize = std::min(5, static_cast<int>(plants.size()));
        for (int i = 0; i < sampleSize; i++) {
            body << "  • " << plants[i]->getName() << ": " 
                 << plants[i]->getHealthPercentage() << "% health"
                 << (plants[i]->getIsAlive() ? "" : " (DEAD)") << "\n";
        }
        if (plants.size() > 5) {
            body << "  ... and " << (plants.size() - 5) << " more plants\n";
        }
    }
    
    body << "\nRECOMMENDED ACTIONS:\n";
    body << std::string(40, '-') << "\n";
    body << "1. Review care procedures for unhealthy plants\n";
    body << "2. Isolate dead plants to prevent disease spread\n";
    body << "3. Adjust watering schedules based on health data\n";
    body << "4. Consider environmental factors affecting plant health\n";
    body << "5. Schedule regular health assessments\n";
    
    return body.str();
}

std::string PlantHealthReport::addFooter() {
    std::stringstream footer;
    footer << "\n" << std::string(50, '=') << "\n";
    footer << "PLANT CARE CONTACTS:\n";
    footer << "• Head Gardener: gardener@gardencenter.com\n";
    footer << "• Plant Health Specialist: health@gardencenter.com\n";
    footer << "• Emergency Care: emergency-care@gardencenter.com\n";
    footer << std::string(50, '=') << "\n";
    footer << "Next scheduled health assessment: 7 days\n";
    footer << "Report generated by Plant Health Monitoring System v1.5";
    return footer.str();
}

std::string PlantHealthReport::getReportType() const {
    return "Plant Health";
}