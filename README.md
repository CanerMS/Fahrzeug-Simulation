# Vehicle Simulation System

A C++ project demonstrating object-oriented programming concepts through a vehicle simulation system with polymorphic behavior and modern C++ features.

## ⚠️ Disclaimer / Haftungsausschluss

This project was created for educational purposes as part of my studies.

**Important Notes:**
- This implementation is my own work and interpretation
- No official course materials, scripts, or assignment texts are included
- This is a learning project demonstrating C++ OOP concepts
- Not intended for commercial use

**Wichtige Hinweise:**
- Diese Implementierung ist meine eigene Arbeit und Interpretation
- Keine offiziellen Kursmaterialien, Skripte oder Aufgabenstellungen enthalten
- Dies ist ein Lernprojekt zur Demonstration von C++ OOP-Konzepten
- Nicht für kommerzielle Zwecke gedacht

## 📚 Project Overview

This system models different types of vehicles with unique characteristics:

- **PKW (Cars)**: Fuel tank, consumption rate, and speed limit when tank is empty
- **Fahrrad (Bicycles)**: Fatigue model where speed decreases over distance

The implementation demonstrates key OOP concepts and modern C++ features.

## 🎯 Key Features

- Time-based simulation with global clock
- Polymorphic vehicle hierarchy
- Virtual functions for type-specific behavior
- Smart pointers (unique_ptr, shared_ptr) for automatic memory management
- Operator overloading (<<, <, =)
- Static member variables for ID management

## 🔧 Technical Stack

- **Language:** C++17
- **Build System:** Make/CMake
- **Standard Library:** STL (vector, string, iostream, algorithm)
- **Memory Management:** Smart Pointers

## 📦 Installation

### Prerequisites

```bash
# C++ Compiler (g++ 7.0+ or clang++ 5.0+)
g++ --version

# Make (optional)
make --version
```

### Building

```bash
# Compile all files
g++ -std=c++17 -Wall -Wextra -o simulation \
    main.cpp Fahrzeug.cpp PKW.cpp Fahrrad.cpp

# Run
./simulation
```

Or using Make:

```bash
make
./simulation
```

## 🚀 Usage Example

```cpp
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

int main() {
    // Create vehicles with smart pointers
    std::vector<std::unique_ptr<Fahrzeug>> vehicles;
    vehicles.push_back(std::make_unique<PKW>("BMW", 200.0, 6.0, 55.0));
    vehicles.push_back(std::make_unique<Fahrrad>("Trek", 30.0));
    
    // Simulate over time
    double globalTime = 0.0;
    const double dt = 0.25; // 15 minutes
    
    while (globalTime < 2.0) {
        globalTime += dt;
        for (auto& v : vehicles) {
            v->vSimulieren();
        }
        
        // Output results
        Fahrzeug::vKopf();
        for (auto& v : vehicles) {
            std::cout << *v << "\n";
        }
    }
    
    return 0;
}
```

## 🏗️ Project Structure

```
project/
├── README.md
├── LICENSE
├── config.h              # Configuration (EPS for comparisons)
├── Fahrzeug.h/.cpp       # Base vehicle class
├── PKW.h/.cpp            # Car implementation
├── Fahrrad.h/.cpp        # Bicycle implementation
└── main.cpp              # Main program with test scenarios
```

## 🔍 Core Concepts Demonstrated

### 1. Inheritance & Polymorphism

```
     ┌─────────────┐
     │  Fahrzeug   │  (Base Class)
     └──────┬──────┘
            │
      ┌─────┴─────┐
      │           │
   ┌──▼──┐   ┌───▼────┐
   │ PKW │   │Fahrrad │
   └─────┘   └────────┘
```

### 2. Virtual Functions

Polymorphic behavior through virtual dispatch:
- `dGeschwindigkeit()` - Returns current speed (type-specific)
- `vSimulieren()` - Updates vehicle state
- `vAusgeben()` - Outputs vehicle data

### 3. Smart Pointers

```cpp
// Unique ownership
std::vector<std::unique_ptr<Fahrzeug>> vec;
vec.push_back(std::make_unique<PKW>("Golf", 160.0));

// Shared ownership
auto shared = std::make_shared<Fahrzeug>("Test");
```

### 4. Operator Overloading

```cpp
// Output operator
std::ostream& operator<<(std::ostream&, const Fahrzeug&);

// Comparison operator
bool operator<(const Fahrzeug&) const;

// Assignment operator
Fahrzeug& operator=(const Fahrzeug&);
```

## 🧪 Testing

The main program includes test scenarios for:
- Static vs dynamic memory management
- Basic simulation mechanics
- Fuel consumption and bicycle fatigue
- Operator functionality and sorting

Run with:
```bash
./simulation
```

## 📖 Concepts Covered

- ✅ Object-Oriented Programming (OOP)
- ✅ Inheritance and Polymorphism
- ✅ Virtual Functions and Late Binding
- ✅ Smart Pointers (modern memory management)
- ✅ Operator Overloading
- ✅ STL Containers
- ✅ Lambda Functions
- ✅ const-correctness
- ✅ Static Members
- ✅ Header/Source Separation

## 🎨 Code Conventions

- **Hungarian Notation:** `p_iID`, `p_dMaxGeschwindigkeit`
  - `p_` = private/protected member
  - `i` = integer, `d` = double, `s` = string
- **Function Prefixes:** `v` = void, `d` = double
- **const-correctness:** Non-modifying methods marked `const`
- **Smart Pointers:** Preferred over raw pointers

## 🔮 Possible Extensions

- Input validation improvements
- Unit testing framework
- Graphical visualization
- Road/path management system
- Intersection and traffic light system
- Multi-lane highways
- Traffic flow optimization

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Caner**

---

**Version:** 1.0 - Basic Implementation Complete  
**Last Updated:** November 2024
