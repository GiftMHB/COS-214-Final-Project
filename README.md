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
## 🔗UML Class Diagrams Links
>[Visual Paradigm .vpp file](https://github.com/GiftMHB/COS-214-Final-Project/blob/Documents/COS%20214%20Project%20%20UML%20Class%20Diagrams.vpp)
>
>[State Class Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/State.png)
>
>[Activity Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/Activity%20Diagram1.jpg)
>
>[Class Diagram for all patterns](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/Class%20Diagram1.jpg)
>
>[Report](https://docs.google.com/document/d/1d_wSwSUxNFVtXFbv_4fgMn0-bCimJWIoTOoVRXwM1wg/edit?usp=sharing)
>
>[Factory Method Part 1](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/FactoryPart1.png)
>
>[Factory Method Part 2](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/FacroryPart2.png)
>
>[Iterator Pattern](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/IteratorPattern.png)
>
>[Strategy Pattern](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/StrategyPattern.png)
>
>[Communication Diagram](https://github.com/GiftMHB/COS-214-Final-Project/blob/main/Images/Communication_Diagram.png)
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
|  | Singleton | Ensures one global `GardenArea` instance |
| **Structural** | Composite | Organizes garden hierarchy (Sections → Beds → Plants) |
|  | Decorator | Dynamically adds features to plants (e.g., pots, labels, gift wraps) |
|  | Facade | Simplifies subsystem interaction (Garden, Staff, Reports) |
|  | Composite | Treat individual plants and plant groups uniformly |
| **Behavioral** | State | Manages plant lifecycles (Seedling → Mature → Dead) |
|  | Strategy | Encapsulates care routines for different plant types |
|  | Command | Encapsulates staff actions (Water, Fertilize, Sell) |
|  | Observer | Automatically updates monitors and inventory when plants change |
|  | Iterator | Provide multiple ways to traverse inventory collections (all items, low stock, by category) |
|  | Template Method | Define report generation algorithm skeleton |
|  | State | Manage plant life cycle states and state-specific behavior |
|  | Memento | Capture and restore system state |

---
## Running our project
> Our project has a makefile,all you have to do is **make** to compile and **make run** to run

## 🧠 System Architecture Summary

### 🌳 Garden Hierarchy
- **GardenArea (Singleton)** — global controller for all sections  
- **GardenSection / PlantBed (Composite)** — structured grouping of plants  
- **Plant (Abstract Base)** — root for `Flower`, `Tree`, `Vegetable`, etc.  

### 🧩 Behavior & Interaction
- **State** controls how plants evolve over time  
- **Strategy** defines plant-specific care rules  
- **Command + Memento** handle staff actions and undo functionality  
- **Observer**  system monitoring  
- **Template Method + Iterator** Generation of reports

---

## ⚙️ Key Features

 Modular and reusable architecture  
 Undo/Redo system via Memento pattern  
 Automated plant lifecycle management  
 Scalable for additional plant and garden types  
 Pattern-rich code demonstrating OOP principles in C++  

---

## 🌿 Branching Strategy
###  Main Branch
- **`main`** → Protected branch, contains the stable production-ready code.

### 🧩 Development Branch
- **`dev`** → Integration branch where all other branches were merged , first it had all the .h files

### 🌱 Feature Branches
Each team member worked on their own branch under `dev`:
- `Lufuno-abstract_command_interface`
- `Gift-factory-Strategy-Iterator`
- `Christopher-State`
- `Lusanda-singleton-memento-decorator`
- `Tiego-composite-observer-facade`

### 📂 Documents
- The `documents` branch contains shared documentation and reference materials to make collaboration easier.
--
## Unit Testing
**Testing Framework** 
>**Framework**: doctest (header-only C++ testing)
>**Approach**: Test-Driven Development (TDD) where applicable
>**Coverage**: Unit tests for all major components and design patterns
