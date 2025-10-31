/**
 * @file Command.h
 * @brief Command pattern interface and implementations for garden center operations
 * @details Defines the Command interface and concrete command classes for various plant operations
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Plant;

/**
 * @brief Abstract base class for all commands in the system
 * @details Follows the Command pattern to encapsulate all information needed to perform an action
 */
class Command {
public:
    virtual ~Command() = default;
    
    /**
     * @brief Execute the command
     * @return String describing the execution result
     */
    virtual std::string execute() = 0;
    
    /**
     * @brief Undo the command
     * @return String describing the undo result
     */
    virtual std::string undo() = 0;
    
    /**
     * @brief Get command description
     * @return Detailed description of the command
     */
    virtual std::string getDescription() const = 0;
    
    /**
     * @brief Get command type for categorization
     * @return String representing command type
     */
    virtual std::string getCommandType() const = 0;
    
    /**
     * @brief Check if command can be undone
     * @return True if command supports undo operation
     */
    virtual bool isUndoable() const { return true; }
};

/**
 * @brief Concrete command for watering plants
 */
class WaterPlantCommand : public Command {
private:
    Plant* plant;
    double waterAmount;
    std::string staffMember;
    double previousWaterLevel;
    bool executed;

public:
    /**
     * @brief Construct a new WaterPlantCommand object
     * @param plant Pointer to the plant to water
     * @param amount Amount of water in milliliters
     * @param staff Name of staff member performing the action
     */
    WaterPlantCommand(Plant* plant, double amount, const std::string& staff);
    
    std::string execute() override;
    std::string undo() override;
    std::string getDescription() const override;
    std::string getCommandType() const override;
};

/**
 * @brief Concrete command for selling plants
 */
class SellPlantCommand : public Command {
private:
    Plant* plant;
    std::string customerName;
    double salePrice;
    std::string staffMember;
    bool wasSold;
    std::string previousStatus;

public:
    /**
     * @brief Construct a new SellPlantCommand object
     * @param plant Pointer to the plant being sold
     * @param customer Name of the customer
     * @param price Sale price of the plant
     * @param staff Name of staff member processing the sale
     */
    SellPlantCommand(Plant* plant, const std::string& customer, double price, const std::string& staff);
    
    std::string execute() override;
    std::string undo() override;
    std::string getDescription() const override;
    std::string getCommandType() const override;
};

/**
 * @brief Manages command execution history and provides undo/redo functionality
 */
class CommandInvoker {
private:
    std::vector<Command*> commandHistory;
    std::vector<Command*> undoneCommands;
    static const size_t MAX_HISTORY_SIZE = 100;

public:
    /**
     * @brief Destroy the CommandInvoker and clean up commands
     */
    ~CommandInvoker();
    
    /**
     * @brief Execute a command and add it to history
     * @param command Pointer to command to execute
     * @return Execution result message
     */
    std::string executeCommand(Command* command);
    
    /**
     * @brief Undo the last executed command
     * @return Undo result message
     */
    std::string undo();
    
    /**
     * @brief Redo the last undone command
     * @return Redo result message
     */
    std::string redo();
    
    /**
     * @brief Get command history
     * @return Vector of command descriptions
     */
    std::vector<std::string> getCommandHistory() const;
    
    /**
     * @brief Clear all command history
     */
    void clearHistory();
    
    /**
     * @brief Check if undo is possible
     * @return True if commands can be undone
     */
    bool canUndo() const;
    
    /**
     * @brief Check if redo is possible
     * @return True if commands can be redone
     */
    bool canRedo() const;
    
    /**
     * @brief Get the number of commands in history
     * @return Size of command history
     */
    size_t getHistorySize() const { return commandHistory.size(); }
    
    /**
     * @brief Get the number of undone commands available for redo
     * @return Size of undone commands stack
     */
    size_t getRedoStackSize() const { return undoneCommands.size(); }
};

#endif // COMMAND_H