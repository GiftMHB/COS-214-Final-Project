#include "CommandInvoker.h"
#include <iostream>

CommandInvoker::~CommandInvoker() {
    clearAllCommands();
}

std::string CommandInvoker::executeCommand(Command* command) {
    if (command == nullptr) {
        return "Error: Cannot execute null command";
    }
    
    std::string result;
    
    try {
        result = command->execute();
        commandHistory.push_back(command);
        
        // Clear redo stack when new command is executed
        for (Command* cmd : undoneCommands) {
            delete cmd;
        }
        undoneCommands.clear();
        
        // Maintain history size limit
        if (commandHistory.size() > MAX_HISTORY_SIZE) {
            delete commandHistory.front();
            commandHistory.erase(commandHistory.begin());
        }
        
    } catch (const std::exception& e) {
        result = "Command execution failed: " + std::string(e.what());
        delete command;
    }
    
    return result;
}

std::string CommandInvoker::undo() {
    if (commandHistory.empty()) {
        return "No commands to undo";
    }
    
    Command* cmd = commandHistory.back();
    
    if (!cmd->isUndoable()) {
        return "Cannot undo this command";
    }
    
    std::string result = cmd->undo();
    commandHistory.pop_back();
    undoneCommands.push_back(cmd);
    
    return result;
}

std::string CommandInvoker::redo() {
    if (undoneCommands.empty()) {
        return "No commands to redo";
    }
    
    Command* cmd = undoneCommands.back();
    std::string result = cmd->execute();
    undoneCommands.pop_back();
    commandHistory.push_back(cmd);
    
    return result;
}

std::vector<std::string> CommandInvoker::getCommandHistory() const {
    std::vector<std::string> history;
    for (const Command* cmd : commandHistory) {
        history.push_back(cmd->getDescription());
    }
    return history;
}

void CommandInvoker::clearHistory() {
    clearAllCommands();
}

void CommandInvoker::clearAllCommands() {
    for (Command* cmd : commandHistory) {
        delete cmd;
    }
    commandHistory.clear();
    
    for (Command* cmd : undoneCommands) {
        delete cmd;
    }
    undoneCommands.clear();
}

bool CommandInvoker::canUndo() const {
    return !commandHistory.empty();
}

bool CommandInvoker::canRedo() const {
    return !undoneCommands.empty();
}