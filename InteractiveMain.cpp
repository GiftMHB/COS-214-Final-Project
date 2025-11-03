/**
 * @file InteractiveMain.cpp
 * @brief Interactive user interface for the Plant Nursery Simulator
 */

#include "SimulationFacade.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

class InteractiveInterface {
private:
    SimulationFacade facade;

public:
    void run() {
        std::cout << "========================================\n";
        std::cout << "    PLANT NURSERY SIMULATOR \n";
        std::cout << "========================================\n\n";
        
        facade.initializeSystem();
        
        int choice;
        do {
            displayMainMenu();
            choice = getMenuChoice(0, 12);
            processMenuChoice(choice);
        } while (choice != 0);
        
        std::cout << "\nThank you for using Plant Nursery Simulator!\n";
    }

private:
    void displayMainMenu() {
        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Start Simulation\n";
        std::cout << "2. Stop Simulation\n";
        std::cout << "3. Simulate One Day\n";
        std::cout << "4. Simulate Multiple Days\n";
        std::cout << "5. Add New Plant\n";
        std::cout << "6. Remove Plant\n";
        std::cout << "7. Display All Plants\n";
        std::cout << "8. Plant Operations\n";
        std::cout << "9. Staff Operations\n";
        std::cout << "10. Generate Reports\n";
        std::cout << "11. System Status\n";
        std::cout << "12. Undo/Redo Operations\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
    }

    int getMenuChoice(int min, int max) {
        int choice;
        while (!(std::cin >> choice) || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter " << min << "-" << max << ": ";
        }
        std::cin.ignore();
        return choice;
    }

    void processMenuChoice(int choice) {
        switch (choice) {
            case 1: startSimulation(); break;
            case 2: stopSimulation(); break;
            case 3: simulateOneDay(); break;
            case 4: simulateMultipleDays(); break;
            case 5: addNewPlant(); break;
            case 6: removePlant(); break;
            case 7: displayAllPlants(); break;
            case 8: plantOperationsMenu(); break;
            case 9: staffOperationsMenu(); break;
            case 10: reportsMenu(); break;
            case 11: displaySystemStatus(); break;
            case 12: undoRedoMenu(); break;
            case 0: break;
            default: std::cout << "Invalid choice!\n";
        }
    }

    void startSimulation() {
        facade.startSimulation();
    }

    void stopSimulation() {
        facade.stopSimulation();
    }

    void simulateOneDay() {
        if (!facade.isRunning()) {
            std::cout << "Please start the simulation first!\n";
            return;
        }
        facade.simulateDay();
    }

    void simulateMultipleDays() {
        if (!facade.isRunning()) {
            std::cout << "Please start the simulation first!\n";
            return;
        }
        std::cout << "How many days to simulate? ";
        int days = getMenuChoice(1, 365);
        facade.runSimulation(days);
    }

    void addNewPlant() {
        std::vector<std::string> types = facade.getAvailablePlantTypes();
        
        std::cout << "\nAvailable plant types:\n";
        for (size_t i = 0; i < types.size(); ++i) {
            std::cout << i + 1 << ". " << types[i] << "\n";
        }
        
        std::cout << "Select plant type (1-" << types.size() << "): ";
        int typeChoice = getMenuChoice(1, types.size());
        
        std::cout << "Enter plant name: ";
        std::string name;
        std::getline(std::cin, name);
        
        std::cout << "Care level (Low/Medium/High): ";
        std::string careLevel;
        std::getline(std::cin, careLevel);
        
        facade.addPlant(types[typeChoice - 1], name, careLevel);
    }

    void removePlant() {
        auto plantIds = facade.getAllPlantIds();
        if (plantIds.empty()) {
            std::cout << "No plants available to remove!\n";
            return;
        }
        
        std::cout << "\nAvailable plants:\n";
        for (size_t i = 0; i < plantIds.size(); ++i) {
            std::cout << i + 1 << ". " << plantIds[i] << "\n";
        }
        
        std::cout << "Select plant to remove (1-" << plantIds.size() << "): ";
        int choice = getMenuChoice(1, plantIds.size());
        
        facade.removePlant(plantIds[choice - 1]);
    }

    void displayAllPlants() {
        facade.displayAllPlants();
    }

    void plantOperationsMenu() {
        int choice;
        do {
            std::cout << "\n=== PLANT OPERATIONS ===\n";
            std::cout << "1. Water Plant\n";
            std::cout << "2. Fertilize Plant\n";
            std::cout << "3. Sell Plant\n";
            std::cout << "4. Display Plant Status\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            choice = getMenuChoice(0, 4);
            
            switch (choice) {
                case 1: waterPlant(); break;
                case 2: fertilizePlant(); break;
                case 3: sellPlant(); break;
                case 4: displayPlantStatus(); break;
            }
        } while (choice != 0);
    }

    void waterPlant() {
        auto plantIds = facade.getAllPlantIds();
        if (plantIds.empty()) {
            std::cout << "No plants available!\n";
            return;
        }
        
        std::cout << "\nSelect plant to water:\n";
        for (size_t i = 0; i < plantIds.size(); ++i) {
            std::cout << i + 1 << ". " << plantIds[i] << "\n";
        }
        
        std::cout << "Choice: ";
        int plantChoice = getMenuChoice(1, plantIds.size());
        
        std::cout << "Enter staff name: ";
        std::string staffName;
        std::getline(std::cin, staffName);
        
        facade.waterPlant(plantIds[plantChoice - 1], staffName);
    }

    void fertilizePlant() {
        auto plantIds = facade.getAllPlantIds();
        if (plantIds.empty()) {
            std::cout << "No plants available!\n";
            return;
        }
        
        std::cout << "\nSelect plant to fertilize:\n";
        for (size_t i = 0; i < plantIds.size(); ++i) {
            std::cout << i + 1 << ". " << plantIds[i] << "\n";
        }
        
        std::cout << "Choice: ";
        int plantChoice = getMenuChoice(1, plantIds.size());
        
        std::cout << "Enter staff name: ";
        std::string staffName;
        std::getline(std::cin, staffName);
        
        facade.fertilizePlant(plantIds[plantChoice - 1], staffName);
    }

    void sellPlant() {
        auto plantIds = facade.getAllPlantIds();
        if (plantIds.empty()) {
            std::cout << "No plants available to sell!\n";
            return;
        }
        
        std::cout << "\nSelect plant to sell:\n";
        for (size_t i = 0; i < plantIds.size(); ++i) {
            std::cout << i + 1 << ". " << plantIds[i] << "\n";
        }
        
        std::cout << "Choice: ";
        int plantChoice = getMenuChoice(1, plantIds.size());
        
        std::cout << "Enter customer name: ";
        std::string customerName;
        std::getline(std::cin, customerName);
        
        facade.sellPlant(plantIds[plantChoice - 1], customerName);
    }

    void displayPlantStatus() {
        auto plantIds = facade.getAllPlantIds();
        if (plantIds.empty()) {
            std::cout << "No plants available!\n";
            return;
        }
        
        std::cout << "\nSelect plant to view:\n";
        for (size_t i = 0; i < plantIds.size(); ++i) {
            std::cout << i + 1 << ". " << plantIds[i] << "\n";
        }
        
        std::cout << "Choice: ";
        int plantChoice = getMenuChoice(1, plantIds.size());
        
        facade.displayPlantStatus(plantIds[plantChoice - 1]);
    }

    void staffOperationsMenu() {
        int choice;
        do {
            std::cout << "\n=== STAFF OPERATIONS ===\n";
            std::cout << "1. Hire Staff\n";
            std::cout << "2. Assign Task\n";
            std::cout << "3. Display Staff\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            choice = getMenuChoice(0, 3);
            
            switch (choice) {
                case 1: hireStaff(); break;
                case 2: assignTask(); break;
                case 3: facade.displayStaff(); break;
            }
        } while (choice != 0);
    }

    void hireStaff() {
        std::vector<std::string> roles = facade.getAvailableStaffRoles();
        
        std::cout << "\nAvailable roles:\n";
        for (size_t i = 0; i < roles.size(); ++i) {
            std::cout << i + 1 << ". " << roles[i] << "\n";
        }
        
        std::cout << "Select role (1-" << roles.size() << "): ";
        int roleChoice = getMenuChoice(1, roles.size());
        
        std::cout << "Enter staff name: ";
        std::string name;
        std::getline(std::cin, name);
        
        facade.hireStaff(name, roles[roleChoice - 1]);
    }

    void assignTask() {
        std::cout << "Enter staff name: ";
        std::string staffName;
        std::getline(std::cin, staffName);
        
        std::cout << "Enter task: ";
        std::string task;
        std::getline(std::cin, task);
        
        facade.assignTask(staffName, task);
    }

    void reportsMenu() {
        int choice;
        do {
            std::cout << "\n=== REPORTS ===\n";
            std::cout << "1. Inventory Report\n";
            std::cout << "2. Sales Report\n";
            std::cout << "3. Plant Health Report\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            choice = getMenuChoice(0, 3);
            
            switch (choice) {
                case 1: facade.generateInventoryReport(); break;
                case 2: facade.generateSalesReport(); break;
                case 3: facade.generatePlantHealthReport(); break;
            }
        } while (choice != 0);
    }

    void displaySystemStatus() {
        facade.displaySystemStatus();
    }

    void undoRedoMenu() {
        int choice;
        do {
            std::cout << "\n=== UNDO/REDO ===\n";
            std::cout << "1. Undo Last Command\n";
            std::cout << "2. Redo Last Command\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            choice = getMenuChoice(0, 2);
            
            switch (choice) {
                case 1: facade.undoLastCommand(); break;
                case 2: facade.redoLastCommand(); break;
            }
        } while (choice != 0);
    }
};

int main() {
    InteractiveInterface interface;
    interface.run();
    return 0;
}