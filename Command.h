#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
using namespace std;

// Forward declarations to avoid circular dependencies
class Plant;
class Inventory;
class Staff;

/**
 * @brief Abstract base class for all garden management commands
 * 
 * Implements the Command Pattern to encapsulate all staff actions as objects.
 * This allows for queuing, logging, undo/redo functionality, and transactional
 * operations throughout the garden simulation.
 */
class Command {
public:
    virtual ~Command() {}
    
    /**
     * @brief Executes the command operation
     * 
     * Performs the specific action this command represents (water, fertilize, sell, etc.)
     * and returns a success status message.
     * 
     * @return String describing the execution result
     */
    virtual string execute() = 0;
    
    /**
     * @brief Reverses the command operation
     * 
     * Restores the system to the state before this command was executed.
     * Essential for undo functionality.
     * 
     * @return String describing the undo result
     */
    virtual string undo() = 0;
    
    /**
     * @brief Gets a description of what this command does
     * @return Human-readable command description
     */
    virtual string getDescription() const = 0;
    
    /**
     * @brief Gets the type of command for categorization
     * @return Command type string
     */
    virtual string getCommandType() const = 0;
};

/**
 * @brief Command for watering a specific plant
 */
class WaterPlantCommand : public Command {
private:
    Plant* plant;
    double waterAmount;
    string staffMember;

public:
    WaterPlantCommand(Plant* plant, double amount, const string& staff);
    string execute() override;
    string undo() override;
    string getDescription() const override;
    string getCommandType() const override;
};

/**
 * @brief Command for fertilizing a specific plant
 */
class FertilizePlantCommand : public Command {
private:
    Plant* plant;
    string fertilizerType;
    string staffMember;

public:
    FertilizePlantCommand(Plant* plant, const string& fertilizer, const string& staff);
    string execute() override;
    string undo() override;
    string getDescription() const override;
    string getCommandType() const override;
};

/**
 * @brief Command for pruning a specific plant
 */
class PrunePlantCommand : public Command {
private:
    Plant* plant;
    double pruneAmount; // Percentage or specific measurement
    string staffMember;

public:
    PrunePlantCommand(Plant* plant, double amount, const string& staff);
    string execute() override;
    string undo() override;
    string getDescription() const override;
    string getCommandType() const override;
};

/**
 * @brief Command for selling a plant to a customer
 */
class SellPlantCommand : public Command {
private:
    Plant* plant;
    string customerName;
    double salePrice;
    string staffMember;

public:
    SellPlantCommand(Plant* plant, const string& customer, double price, const string& staff);
    string execute() override;
    string undo() override;
    string getDescription() const override;
    string getCommandType() const override;
};

/**
 * @brief Command for restocking inventory
 */
class RestockCommand : public Command {
private:
    Inventory* inventory;
    string itemType;
    int quantity;
    string staffMember;

public:
    RestockCommand(Inventory* inventory, const string& item, int qty, const string& staff);
    string execute() override;
    string undo() override;
    string getDescription() const override;
    string getCommandType() const override;
};

/**
 * @brief Manages command execution and history for undo/redo functionality
 * 
 * The Invoker class in the Command Pattern that maintains command history
 * and handles the execution pipeline.
 */
class CommandInvoker {
private:
    vector<Command*> commandHistory;
    vector<Command*> undoneCommands;
    static const int MAX_HISTORY_SIZE = 100; // Prevent memory issues

public:
    ~CommandInvoker();
    
    /**
     * @brief Executes a command and adds it to history
     * @param command The command to execute
     * @return Result message from command execution
     */
    string executeCommand(Command* command);
    
    /**
     * @brief Undoes the most recent command
     * @return Result message from undo operation
     */
    string undo();
    
    /**
     * @brief Redoes the most recently undone command
     * @return Result message from redo operation
     */
    string redo();
    
    /**
     * @brief Gets the execution history
     * @return Vector of all executed commands in chronological order
     */
    vector<string> getCommandHistory() const;
    
    /**
     * @brief Clears all command history
     */
    void clearHistory();
    
    /**
     * @brief Checks if undo is possible
     * @return True if there are commands to undo
     */
    bool canUndo() const;
    
    /**
     * @brief Checks if redo is possible
     * @return True if there are commands to redo
     */
    bool canRedo() const;
};

#endif // COMMAND_H