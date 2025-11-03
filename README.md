# 🌿 COS214 Final Project — Smart Garden Simulation System  
> "Nurturing Patterns, Harvesting Excellence"  
> by **Team [Iterator Innovators]**

---

## 👥 Team Members
| Name | Student Number | Assigned Patterns |
|------|----------------|------|
| Gift Mohuba  | 23545527 | Factory Method & Strategy & Iterator|
| Lufuno Mphagi| 22501445 | Abstract Factory & Command & Template Method|
| Tiego Mokwena | 22496336 | Composite & Observer & Facade |
| Christopher Adolph | 23535548 | State |
| Lusanda Mtembu | 23602016 | Memento & Decorator & Singleton |

Christopher Adolph - Also completed the Presentation & Report

---

## 🌱 Project Overview
The **Smart Garden Simulation** is an object-oriented system built entirely in **C++**,  
designed to model real-world garden operations: plant growth, staff management, and maintenance automation.  

The system demonstrates mastery of **13 integrated Design Patterns**, carefully selected for scalability, maintainability, and real-world realism.  

---
## 🔗Class Diagrams Links
>[State Class Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/State.png)
>[Activity Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/Documents/Activity%20Diagram1.jpg)
>[Sequence Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/Documents/Sequence%20Diagram1.jpg)
---

## 🧩 Design Philosophy
> “Grow your code like a garden — organized, adaptable, and sustainable.”

Each component of this project mimics an element of a real garden ecosystem.  
The goal is not just functionality but **architectural elegance** — using design patterns as the “soil and roots” of maintainable software.

---

## 🏗️ Implemented Design Patterns (12 Total)

| Category | Pattern | Purpose |
|-----------|----------|----------|
| **Creational** | Factory Method | Creates specific plant types (Flower, Tree, Vegetable) |
|  | Abstract Factory | Builds themed gardens with multiple related plants |
|  | Builder | Configures complex garden setups step-by-step |
|  | Singleton | Ensures one global `GardenArea` instance |
| **Structural** | Composite | Organizes garden hierarchy (Sections → Beds → Plants) |
|  | Decorator | Dynamically adds features to plants (e.g., pots, labels, gift wraps) |
|  | Facade | Simplifies subsystem interaction (Garden, Staff, Reports) |
| **Behavioral** | State | Manages plant lifecycles (Seedling → Mature → Dead) |
|  | Strategy | Encapsulates care routines for different plant types |
|  | Command | Encapsulates staff actions (Water, Fertilize, Sell) |
|  | Observer | Automatically updates monitors and inventory when plants change |
|  | Iterator |  |
|  | Template Method | Used to create reports |

---

## 🧠 System Architecture Summary

### 🌳 Garden Hierarchy
- **GardenArea (Singleton)** — global controller for all sections  
- **GardenSection / PlantBed (Composite)** — structured grouping of plants  
- **Plant (Abstract Base)** — root for `Flower`, `Tree`, `Vegetable`, etc.  

### 🧩 Behavior & Interaction
- **State** controls how plants evolve over time  
- **Strategy** defines plant-specific care rules  
- **Command + Memento** handle staff actions and undo functionality  
- **Observer + Mediator**  system monitoring  
- **Template Method + Iterator** Generation of reports

---

## ⚙️ Key Features

 Modular and reusable architecture  
 Undo/Redo system via Memento pattern  
 Automated plant lifecycle management  
 Scalable for additional plant and garden types  
 Pattern-rich code demonstrating OOP principles in C++  

---

## 📁 Project Structure
smart-garden-system/ ├── Plant.h ├── Plant.cpp ├── PlantFactory.h ├── PlantFactory.cpp ├── PlantAbstractFactory.h ├── PlantAbstractFactory.cpp ├── PlantState.h ├── PlantState.cpp ├── CareStrategy.h ├── CareStrategy.cpp ├── GardenArea.h ├── GardenArea.cpp ├── GardenSection.h ├── GardenSection.cpp ├── PlantDecorator.h ├── PlantDecorator.cpp ├── Command.h ├── Command.cpp ├── Staff.h ├── Staff.cpp ├── PlantObserver.h ├── PlantObserver.cpp ├── Inventory.h ├── Inventory.cpp ├── InventoryIterator.h ├── InventoryIterator.cpp ├── Customer.h ├── Customer.cpp ├── Transaction.h ├── Transaction.cpp ├── Report.h ├── Report.cpp ├── SimulationFacade.h ├── SimulationFacade.cpp ├── Memento.h ├── Memento.cpp ├── main.cpp ├── Makefile ├── doctest.h
---
## Branching Strategy
main (protected) 
├── dev (integration branch) 
│ ├── feature/Lufuno-abstract_command_interface 
│ ├── feature/Gift-factory-Strategy-Iterator 
│ ├── feature/Christopher-State 
│ ├── feature/Lusanda-singleton-memento-decorator 
│ └── feature/Tiego-composite-observer-facade 
└── documents 
 ├── class-diagram 
 ├── sequence-diagram 
 ├── activity-diagram 
 ├── object-diagram 
 ├── state-diagram
--
## Unit Testing
**Testing Framework** 
**Framework**: doctest (header-only C++ testing)

**Approach**: Test-Driven Development (TDD) where applicable

**Coverage**: Unit tests for all major components and design patterns

