/*
 * main.cpp
 *  Created on: Oct 5, 2025
 *      Author: canercam
 */

#include <memory>      // smart pointer
#include <vector>      // std::vector
#include <iostream>
#include <limits>      // std::numeric_limits
#include <string>      // std::string
#include <algorithm>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "config.h"


using std::cout;
using std::string;

// *** Global clock: ***
double dGlobaleZeit = 0.0; // h

// -------------------------------------------------------------------------------------------------------/

void testStaticVsDynamic()
{
    cout << "== Statisches und dynamisches Erzeugen-Loeschen=\n";
    // Statische Speicherverwaltung
    Fahrzeug f0;
    Fahrzeug f1("PKW-Alpha");

    // Dynamische Speicherverwaltung
    Fahrzeug* pF2 = new Fahrzeug("Bike-Beta");
    delete pF2;

    cout << "\n== Smartpointer: unique_ptr / shared_ptr, use_count, move ==\n";

    // unique_ptr
    auto upA = std::make_unique<Fahrzeug>("UP-A");
    auto upB = std::make_unique<Fahrzeug>("UP-B");

    // std::unique_ptr<Fahrzeug> upX = upA; // kompiliert nicht (Copy verboten)
    std::unique_ptr<Fahrzeug> upX;
    upX = std::move(upA); // Besitzerwechsel

    // shared_ptr
    auto spA = std::make_shared<Fahrzeug>("SP-A");
    auto spB = std::make_shared<Fahrzeug>("SP-B");
    cout << "spA.use_count() vor  copy:  " << spA.use_count() << "\n";
    std::shared_ptr<Fahrzeug> spA2 = spA; // Kopie
    cout << "spA.use_count() nach copy:  " << spA.use_count() << "\n";

    cout << "\n== vector<unique_ptr<Fahrzeug>>: nur mit move ==\n";
    std::vector<std::unique_ptr<Fahrzeug>> vU;
    vU.push_back(std::move(upX));
    vU.push_back(std::make_unique<Fahrzeug>("UP-C"));
    vU.push_back(std::move(upB)); // upB wird nullptr

    cout << "vector<unique_ptr<...>>::clear() wird aufgerufen...\n";
    vU.clear(); // DTOR der beinhalteten Objekte

    // --- vector<shared_ptr<Fahrzeug>>: copy vs move ---
    cout << "\n== vector<shared_ptr<Fahrzeug>>: copy vs move ==\n";
    std::vector<std::shared_ptr<Fahrzeug>> vS;
    vS.push_back(spA);               // Kopie -> use_count steigt
    vS.push_back(std::move(spB));    // Move -> spB wird leer
    cout << "spA.use_count() in vector: " << spA.use_count() << "\n";
    cout << "spB ist " << (spB ? "NICHT leer" : "leer (nach move)") << "\n";
    vS.clear(); // Referenzen im Vector fallen weg

    cout << "\n== Die Ausgabe der Tabelle (vKopf + vAusgeben) ==\n";

    Fahrzeug t1("AUTO3", 30.0);
    Fahrzeug t2("PKW1",  40.0);

    Fahrzeug::vKopf();

    std::cout << t1 << '\n'
              << t2 << '\n';
}

// -------------------------------------------------------------------------------------------------------/

void testBasicSimulation()
{
    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
    fahrzeuge.reserve(3);

    // 3 Fahrzeuge aus Konsole einlesen
    for (int i = 0; i < 3; ++i)
    {
        cout << "Name des Fahrzeugs #" << (i+1) << ": ";
        string name;
        std::getline(std::cin >> std::ws, name); // std::ws frisst führende Whitespaces

        cout << "Maximalgeschwindigkeit [km/h] fuer \"" << name << "\": ";
        double vmax{};
        std::cin >> vmax;
        // Eingabepuffer bis Zeilenende leeren:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Konstruktor stellt Positivität per ?: sicher (negativ -> 0.0)
        fahrzeuge.push_back(std::make_unique<Fahrzeug>(name, vmax));
    }

    // Simulationstart
    cout << "\n--- Aufgabe1a: Simulation startet ---\n";
    const double dt    = 0.25; // 15 Minuten
    const double T_end = 2.00; // 2 Stunden Gesamtdauer (Beispiel)

    // Schleife: Uhr erhöhen, dann simulieren, dann ausgeben
    while (dGlobaleZeit < T_end)
    {
        dGlobaleZeit += dt;

        // Fortbewegen
        for (auto& f : fahrzeuge) {
            f->vSimulieren();
        }

        // Ausgabe
        cout << "\nZeit = " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();
        for (auto& f : fahrzeuge) {
            std::cout << *f << '\n';
        }
    }

}

// -------------------------------------------------------------------------------------------------------/

void testTankingAndFatigue()
{
    int nPKW{}, nRad{};
    cout << "Anzahl PKW: ";   std::cin >> nPKW;
    cout << "Anzahl Fahrrad: "; std::cin >> nRad;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::unique_ptr<Fahrzeug>> vec;
    vec.reserve(nPKW + nRad);

    // PKW-Daten einlesen
    for (int i=0; i<nPKW; ++i) {
        string name;  double vmax{}, verbrauch{}, tankvol = 55.0;
        cout << "PKW#" << (i+1) << " Name: ";
        std::getline(std::cin >> std::ws, name);
        cout << "  MaxGeschwindigkeit [km/h]: "; std::cin >> vmax;
        cout << "  Verbrauch [l/100km]: ";       std::cin >> verbrauch;
        cout << "  Tankvolumen [l] (Enter fuer 55): ";
        if (std::cin.peek()=='\n') { /* 55 lassen */ }
        else { std::cin >> tankvol; }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        vec.push_back(std::make_unique<PKW>(name, vmax, verbrauch, tankvol));
    }

    // Fahrrad-Daten einlesen
    for (int i=0; i<nRad; ++i) {
        string name;  double vmax{};
        cout << "Fahrrad#" << (i+1) << " Name: ";
        std::getline(std::cin >> std::ws, name);
        cout << "  MaxGeschwindigkeit [km/h]: "; std::cin >> vmax;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        vec.push_back(std::make_unique<Fahrrad>(name, vmax));
    }

    // Simulation
    cout << "\n--- Aufgabe 2: Simulation startet ---\n";
    const double dt    = 0.25; // 15 min
    const double T_end = 5.00; // z.B. 5 h
    bool   schonGetankt = false;

    while (dGlobaleZeit + EPS < T_end) {
        dGlobaleZeit += dt;

        // allgemeine Simulation – virtueller Dispatch
        for (auto& f : vec) f->vSimulieren();

        // Nach genau 3 Stunden: PKW volltanken (im Testprogramm triggern!)
        if (!schonGetankt && dGlobaleZeit + EPS >= 3.0) {
            for (auto& f : vec) f->dTanken(); // Fahrrad/„andere“: 0.0
            schonGetankt = true;
            cout << "\n*** Tanken nach 3.00 h: Alle PKW vollgetankt ***\n";
        }

        // Ausgabe
        cout << "\nZeit = " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();
        for (auto& f : vec) { std::cout << *f << "\n"; } // << Operator verwenden
    }
}

// -------------------------------------------------------------------------------------------------------/

void testOperators() {
    using std::cout;

    std::vector<std::unique_ptr<Fahrzeug>> v;
    v.push_back(std::make_unique<PKW>("Golf",   160.0, 6.0));     // 55 l default
    v.push_back(std::make_unique<Fahrrad>("Trek", 30.0));
    v.push_back(std::make_unique<PKW>("M3",     250.0, 9.5, 60.0));

    // kleine Simulation
    double dGlobaleZeitLocalBackup = dGlobaleZeit;
    const double dt = 0.5;    // 30 min
    for (int i = 0; i < 4; ++i) {
        dGlobaleZeit += dt;
        for (auto& f : v) f->vSimulieren();

        cout << "\nZeit = " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();
        for (auto& f : v) cout << *f << "\n";   // *** nur << ***
    }

    // sortiere nach Gesamtstrecke via operator<
    std::sort(v.begin(), v.end(),
              [](const auto& a, const auto& b){ return *a < *b; });

    cout << "\n-- Sortiert (operator< auf Gesamtstrecke) --\n";
    Fahrzeug::vKopf();
    for (auto& f : v) cout << *f << "\n";

    cout << "\n-- TEST OPERATOR (Copy Zuweisung) f1 = f2 --\n";

    Fahrzeug f10("BMW", 200);
    Fahrzeug f20("VW", 180);

    // Kleine Simulation für unterschiedliche Strecken
    dGlobaleZeit += 1;
    f10.vSimulieren();
    f20.vSimulieren();

    Fahrzeug::vKopf();
    cout << f10 << "\n"; // BMW
    cout << f20 << "\n"; // VW

    f10 = f20; // Test der Copy-Operator

    cout << "\n-- Nach Zuweisung f1 = f2 --\n";

    Fahrzeug::vKopf();
    cout << f10 << "\n";
    cout << f20 << "\n";


    dGlobaleZeit = dGlobaleZeitLocalBackup; // Uhr wiederherstellen, wenn nötig
}

// -------------------------------------------------------------------------------------------------------/

int main()
{
    // vAufgabe1();
    // vAufgabe1a();
    // vAufgabe2();
	vAufgabe3();
    return 0;
}

// -------------------------------------------------------------------------------------------------------/



