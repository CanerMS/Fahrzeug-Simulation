# 🚗 Fahrzeug-Simulationssystem

Ein objektorientiertes C++ Projekt zur Simulation verschiedener Fahrzeugtypen (PKW, Fahrräder) mit Fokus auf moderne C++-Konzepte und Best Practices.

## 📋 Inhaltsverzeichnis

- [Überblick](#überblick)
- [Features](#features)
- [Technologien](#technologien)
- [Installation](#installation)
- [Verwendung](#verwendung)
- [Projektstruktur](#projektstruktur)
- [Konzepte](#konzepte)
- [Beispiele](#beispiele)
- [Autor](#autor)

## 🎯 Überblick

Dieses Projekt implementiert ein Verkehrssimulationssystem, das verschiedene Fahrzeugtypen mit unterschiedlichen Eigenschaften modelliert:

- **PKW**: Mit Tankinhalt, Verbrauch und Geschwindigkeitsbegrenzung bei leerem Tank
- **Fahrrad**: Mit Ermüdungsmodell (Geschwindigkeit nimmt mit Strecke ab)

Das System demonstriert zentrale OOP-Konzepte wie Vererbung, Polymorphie, virtuelle Funktionen und moderne C++-Features wie Smart Pointers.

## ✨ Features

### Kern-Funktionalität
- ✅ Zeitbasierte Simulation mit globaler Uhr
- ✅ Polymorphe Fahrzeughierarchie (Basisklasse → PKW/Fahrrad)
- ✅ Virtuelle Funktionen für typspezifisches Verhalten
- ✅ Smart Pointer (`unique_ptr`, `shared_ptr`) für automatisches Speichermanagement
- ✅ Operator-Überladung (`<<`, `<`, `=`)
- ✅ ID-Verwaltung mit statischen Membervariablen

### Fahrzeug-Spezifika

#### PKW
- Tankinhalt und Verbrauch (Liter/100km)
- Tanken-Funktion mit optionaler Menge
- Geschwindigkeit = 0 bei leerem Tank
- Verbrauchsberechnung basierend auf gefahrener Strecke

#### Fahrrad
- Ermüdungsmodell: -10% Geschwindigkeit pro 20km
- Minimale Geschwindigkeit: 12 km/h
- Kein Tank oder Verbrauch

## 🛠 Technologien

- **Sprache**: C++17
- **Build-System**: Make/CMake
- **IDE**: Eclipse CDT / Visual Studio Code
- **Standard Library**: STL (vector, string, iostream, algorithm)
- **Speicherverwaltung**: Smart Pointers (unique_ptr, shared_ptr)

## 📦 Installation

### Voraussetzungen
```bash
# C++-Compiler (g++ 7.0+ oder clang++ 5.0+)
g++ --version

# Make (optional)
make --version
```

### Kompilierung

```bash
# Alle Dateien kompilieren
g++ -std=c++17 -Wall -Wextra -o simulation \
    main.cpp Fahrzeug.cpp PKW.cpp Fahrrad.cpp

# Ausführen
./simulation
```

### Mit Makefile (falls vorhanden)
```bash
make
./simulation
```

## 🚀 Verwendung

### Grundlegende Simulation

```cpp
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

int main() {
    // Globale Uhr
    double dGlobaleZeit = 0.0;
    
    // Fahrzeuge erstellen
    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
    fahrzeuge.push_back(std::make_unique<PKW>("BMW", 200.0, 6.0, 55.0));
    fahrzeuge.push_back(std::make_unique<Fahrrad>("Trek", 30.0));
    
    // Simulation über 2 Stunden in 15-Minuten-Schritten
    const double dt = 0.25;  // 15 Minuten
    while (dGlobaleZeit < 2.0) {
        dGlobaleZeit += dt;
        
        // Alle Fahrzeuge simulieren
        for (auto& f : fahrzeuge) {
            f->vSimulieren();
        }
        
        // Ausgabe
        Fahrzeug::vKopf();
        for (auto& f : fahrzeuge) {
            std::cout << *f << "\n";
        }
    }
    
    return 0;
}
```

### Verfügbare Test-Funktionen

```cpp
vAufgabe1();   // Statische vs. dynamische Speicherverwaltung
vAufgabe1a();  // Grundlegende Simulation mit Eingabe
vAufgabe2();   // PKW und Fahrrad Simulation mit Tanken
vAufgabe3();   // Operatoren testen (<<, <, =) und Sortierung
```

## 📁 Projektstruktur

```
projekt/
├── README.md
├── config.h              # Konfiguration (EPS für Vergleiche)
├── Fahrzeug.h            # Basisklasse Header
├── Fahrzeug.cpp          # Basisklasse Implementation
├── PKW.h                 # PKW Header
├── PKW.cpp               # PKW Implementation
├── Fahrrad.h             # Fahrrad Header
├── Fahrrad.cpp           # Fahrrad Implementation
└── main.cpp              # Hauptprogramm mit Test-Funktionen
```

### Klassendiagramm

```
┌─────────────────┐
│   Fahrzeug      │  (Basisklasse)
├─────────────────┤
│ - p_iID         │
│ - p_sName       │
│ - p_dMaxGeschw  │
│ - p_dGesamtStr  │
├─────────────────┤
│ + vSimulieren() │ ← virtual
│ + dGeschw()     │ ← virtual
│ + vAusgeben()   │ ← virtual
│ + dTanken()     │ ← virtual
└────────┬────────┘
         │
    ┌────┴────┐
    │         │
┌───▼────┐ ┌──▼────────┐
│  PKW   │ │  Fahrrad  │
├────────┤ ├───────────┤
│ - Tank │ │           │
│ - Verbr│ │           │
├────────┤ ├───────────┤
│ + dGe..│ │ + dGesch..│ ← override
│ + dTan.│ │           │ ← override
└────────┘ └───────────┘
```

## 💡 Konzepte

### 1. Spätbindung (Late Binding)

```cpp
// In Fahrzeug::vSimulieren():
const double dWeg = dGeschwindigkeit() * dDelta;
//                  ^^^^^^^^^^^^^^^^^
// Virtueller Aufruf - zur Laufzeit entschieden:
// - PKW    → PKW::dGeschwindigkeit()
// - Fahrrad → Fahrrad::dGeschwindigkeit()
```

### 2. Smart Pointers

```cpp
// unique_ptr - exklusiver Besitz
std::vector<std::unique_ptr<Fahrzeug>> vec;
vec.push_back(std::make_unique<PKW>("Golf", 160.0, 6.0));
// Automatische Freigabe bei Scope-Ende

// shared_ptr - gemeinsamer Besitz
auto sp = std::make_shared<Fahrzeug>("Test");
auto sp2 = sp;  // use_count = 2
```

### 3. Operator-Überladung

```cpp
// Ausgabeoperator (freie Funktion)
std::ostream& operator<<(std::ostream& os, const Fahrzeug& f) {
    f.vAusgeben(os);  // Virtueller Dispatch
    return os;
}

// Vergleichsoperator (Member-Funktion)
bool Fahrzeug::operator<(const Fahrzeug& rhs) const {
    return p_dGesamtStrecke < rhs.p_dGesamtStrecke;
}
```

### 4. Virtuelle Funktionen

```cpp
// Basisklasse
class Fahrzeug {
    virtual double dGeschwindigkeit() const;
    virtual void vSimulieren();
};

// Abgeleitete Klasse
class PKW : public Fahrzeug {
    double dGeschwindigkeit() const override {
        return (p_dTankinhalt <= EPS) ? 0.0 : p_dMaxGeschwindigkeit;
    }
};
```

### 5. Statische Member

```cpp
class Fahrzeug {
    inline static int p_iMaxID = 0;  // Klassenweite Variable
    const int p_iID;                 // Eindeutige ID pro Objekt
    
    Fahrzeug() : p_iID(++p_iMaxID) {}  // Auto-Inkrement
};
```

## 📊 Beispiele

### Beispiel 1: PKW mit Tankberechnung

```cpp
PKW bmw("BMW", 200.0, 7.5, 60.0);  // Name, MaxV, Verbrauch, Tank
dGlobaleZeit = 0.0;

// Fahren für 1 Stunde
dGlobaleZeit = 1.0;
bmw.vSimulieren();
// Strecke: 200 km
// Verbrauch: 200 * 7.5/100 = 15 Liter
// Tank: 30 - 15 = 15 Liter

std::cout << bmw << "\n";  // Zeigt alle Daten
```

### Beispiel 2: Fahrrad-Ermüdung

```cpp
Fahrrad trek("Trek", 30.0);  // MaxV = 30 km/h
dGlobaleZeit = 0.0;

// Nach 0 km
trek.dGeschwindigkeit();  // 30 km/h (100%)

// Nach 20 km fahren
dGlobaleZeit = 20.0/30.0;  // ~0.67h
trek.vSimulieren();
trek.dGeschwindigkeit();  // 27 km/h (90%)

// Nach 40 km total
dGlobaleZeit = 40.0/27.0;
trek.vSimulieren();
trek.dGeschwindigkeit();  // 24.3 km/h (81%)
```

### Beispiel 3: Polymorphe Ausgabe

```cpp
std::vector<std::unique_ptr<Fahrzeug>> mix;
mix.push_back(std::make_unique<PKW>("Golf", 160.0, 6.0));
mix.push_back(std::make_unique<Fahrrad>("BMX", 25.0));

for (auto& f : mix) {
    std::cout << *f << "\n";  // Ruft richtige vAusgeben() auf
}
// Output:
// 1  Golf   160.00  0.00  160.00  27.50  0.00
// 2  BMX     25.00  0.00   25.00   0.00  0.00
```

### Beispiel 4: Sortierung mit operator<

```cpp
std::vector<std::unique_ptr<Fahrzeug>> v;
v.push_back(std::make_unique<PKW>("Schnell", 250.0, 8.0));
v.push_back(std::make_unique<Fahrrad>("Langsam", 20.0));

// Simulation...
// Schnell: 500 km
// Langsam: 40 km

std::sort(v.begin(), v.end(),
          [](const auto& a, const auto& b){ return *a < *b; });

// Jetzt sortiert: Langsam (40km) vor Schnell (500km)
```

## 🧪 Testing

### Manuelle Tests durchführen

```bash
# Kompilieren mit Debug-Symbolen
g++ -std=c++17 -g -o simulation *.cpp

# Ausführen
./simulation

# Im Programm: vAufgabe3() aufrufen für Operator-Tests
```

### Wichtige Test-Szenarien

1. **Tanken bei leerem Tank**: PKW bleibt stehen (v=0)
2. **Fahrrad-Ermüdung**: Geschwindigkeit sinkt, min. 12 km/h
3. **Operator=**: ID bleibt, Stammdaten werden kopiert
4. **Sortierung**: Korrekte Reihenfolge nach Strecke

## 🎓 Lernziele

Dieses Projekt demonstriert folgende C++-Konzepte:

- ✅ Objektorientierte Programmierung (OOP)
- ✅ Vererbung und Polymorphie
- ✅ Virtuelle Funktionen und Spätbindung
- ✅ Smart Pointers (moderne Speicherverwaltung)
- ✅ Operator-Überladung
- ✅ STL-Container (vector)
- ✅ Lambda-Funktionen
- ✅ const-Korrektheit
- ✅ Static Members
- ✅ Header/Source-Trennung

## 🐛 Bekannte Probleme / TODOs

- [ ] Eingabevalidierung verbessern
- [ ] Unit-Tests hinzufügen
- [ ] Grafische Ausgabe implementieren
- [ ] Weg-Klasse für Aufgabenblock 2
- [ ] Kreuzungen-System für vollständige Simulation

## 📚 Dokumentation

### Wichtige Dateien

- `config.h`: Konfigurationskonstanten (z.B. EPS für Float-Vergleiche)
- `main.cpp`: Test-Funktionen für verschiedene Aufgaben
- `Fahrzeug.h/cpp`: Basisklasse mit gemeinsamer Funktionalität
- `PKW.h/cpp`: Spezialisierung für motorisierte Fahrzeuge
- `Fahrrad.h/cpp`: Spezialisierung für muskelbetriebene Fahrzeuge

### Coding-Stil

- **Ungarische Notation**: `p_iID`, `p_dMaxGeschwindigkeit`, `p_sName`
  - `p_` = private/protected member
  - `i` = integer, `d` = double, `s` = string, `e` = enum
- **Funktionspräfixe**: `v` = void, `d` = double
- **const-Korrektheit**: Methoden die nicht verändern sind `const`
- **Smart Pointers**: Bevorzugt über raw pointers

## 👤 Autor

**Caner**


## ⚠️ Disclaimer / Haftungsausschluss

This project was created for educational purposes as part of my Computer Science 
studies at RWTH Aachen University. 

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

## 📚 Concepts Demonstrated

- Object-Oriented Programming in C++
- Inheritance and Polymorphism
- Smart Pointers (unique_ptr, shared_ptr)
- Operator Overloading
- Virtual Functions
- STL Containers



## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.
**Letztes Update**: November 2024  
**Version**: 1.0 (Aufgabenblock 1 komplett)
