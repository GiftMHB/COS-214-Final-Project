# 🌿 COS214 Final Project — Smart Garden Simulation System  
> _Can someone add a slogan😂_  
> by **Team [Iterator Innovators]**

---

## 👥 Team Members
| Name | Student Number | Assigned Patterns |
|------|----------------|------|
| Gift Mohuba  | 23545527 | Factory Method & Strategy & Iterator|
| Lufuno Mphagi| 22501445 | Abstract Factory & Command & Template Method|
|  | XXXXXXXX | X |
|  | XXXXXXXX | X |
|  | XXXXXXXX | X |

---

## 🌱 Project Overview
The **Smart Garden Simulation** is an object-oriented system built entirely in **C++**,  
designed to model real-world garden operations: plant growth, staff management, and maintenance automation.  

The system demonstrates mastery of **12 integrated Design Patterns**, carefully selected for scalability, maintainability, and real-world realism.  

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

---
## Branching Strategy

--
## Unit Testing


