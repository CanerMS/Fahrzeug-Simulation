/*
 * Fahrzeug.cpp
 *
 *  Created on: Oct 5, 2025
 *      Author: canercam
 */

#include "Fahrzeug.h"
#include <iomanip>
#include "config.h"



extern double dGlobaleZeit; // globale Uhr hier bekannt machen
							// die Variable wird genau einmal in main.cpp
							// definiert, überall sonst mit extern deklariert
							// so sieht Fahrzeug::vSimulieren(); die Uhr

// -------------------------------------------------------------------------------------------------------/

Fahrzeug::Fahrzeug()
: p_iID(++p_iMaxID), p_sName("")
{
	std::cout << "[CTOR] Fahrzeug ID=" << p_iID
			  << " Name=\"" << p_sName << "\"\n";
}

// -------------------------------------------------------------------------------------------------------/

Fahrzeug::Fahrzeug(const std::string& aName)
: p_iID(++p_iMaxID), p_sName(aName)
{
    std::cout << "[CTOR] Fahrzeug ID=" << p_iID
              << " Name=\"" << p_sName << "\"\n";
}

// -------------------------------------------------------------------------------------------------------/

Fahrzeug::Fahrzeug(const std::string& aName, double dMaxG)
: p_iID(++p_iMaxID),
  p_sName(aName),
  p_dMaxGeschwindigkeit( (dMaxG > 0.0) ? dMaxG : 0.0 ),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dZeit(0.0)
{
    std::cout << "[CTOR] Fahrzeug ID=" << p_iID
              << " Name=\"" << p_sName
              << "\" MaxG=" << p_dMaxGeschwindigkeit << "\n";
}

// -------------------------------------------------------------------------------------------------------/

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& rhs) {
    if (this != &rhs) {
        // Stammdaten: bei Erstellung festgelegt: Name + v_max
        p_sName               = rhs.p_sName;
        p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit;

        // ID bleibt unverändert (const)
        // Laufzeitdaten (Strecke/Zeit/Tank etc.)  (Aufgabenstellung so fordert)
    }
    return *this;
}

// -------------------------------------------------------------------------------------------------------/

bool Fahrzeug::operator<(const Fahrzeug& rhs) const {
	if (p_dGesamtStrecke != rhs.p_dGesamtStrecke)
	    return p_dGesamtStrecke < rhs.p_dGesamtStrecke;

	if (p_dZeit != rhs.p_dZeit)
	    return p_dZeit < rhs.p_dZeit;

	return p_iID < rhs.p_iID;
}

// -------------------------------------------------------------------------------------------------------/

Fahrzeug::~Fahrzeug() {
    std::cout << "[DTOR] Fahrzeug ID=" << p_iID
              << " Name=\"" << p_sName << "\"\n";
}


// ----------- Polymorphe Basıs-Implementationen ------------

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit; // PKW volle v, Fahrrad überschreibt
}

double Fahrzeug::dTanken(double /*dMenge*/)
{
    return 0.0; // Basisfahrzeuge und Fahrräder
}

// -------------------------------------------------------------------------------------------------------/

void Fahrzeug::vKopf()              // HIER KEIN 'static', KEIN 'const'
{
    using std::cout; using std::setw;
    using std::setiosflags; using std::resetiosflags;

    cout << resetiosflags(std::ios_base::adjustfield) << setiosflags(std::ios_base::left)
         << setw(6)  << "ID"
         << setw(16) << "Name"
         << resetiosflags(std::ios_base::adjustfield) << setiosflags(std::ios_base::right)
         << setw(18) << "MaxGeschwindigkeit"
         << setw(18) << "Gesamtstrecke"
         << setw(14) << "aktGeschw"
         << setw(14) << "Tankinhalt"
         << setw(18) << "Gesamtverbrauch"
         << "\n"
         << "----------------------------------------------------------------------------------------------------------\n";
}

// -------------------------------------------------------------------------------------------------------/

void Fahrzeug::vAusgeben(std::ostream& os) const {
    using std::setw;
    using std::setprecision;
    using std::fixed;
    using std::setiosflags;
    using std::resetiosflags;

    const double v = dGeschwindigkeit();

    os << resetiosflags(std::ios_base::adjustfield) << setiosflags(std::ios_base::left)
       << setw(6)  << p_iID
       << setw(16) << p_sName
       << resetiosflags(std::ios_base::adjustfield) << setiosflags(std::ios_base::right)
       << setw(18) << fixed << setprecision(2) << p_dMaxGeschwindigkeit
       << setw(18) << fixed << setprecision(2) << p_dGesamtStrecke
       << setw(14) << fixed << setprecision(2) << v;
}

// -------------------------------------------------------------------------------------------------------/

std::ostream& operator<<(std::ostream& os, const Fahrzeug& f) {
    f.vAusgeben(os);      // virtueller Aufruf: PKW/Fahrrad override funktioniert
    return os;
}

// -------------------------------------------------------------------------------------------------------/

void Fahrzeug::vSimulieren()
{
	// vergangene Zeit seit dem letzten Schritt
	const double dDelta = dGlobaleZeit - p_dZeit;

	// EPS in config.h definiert
	if (dDelta <= EPS) return;

	// Mit maximaler Geschwindigkeit fahren:
	const double dWeg = dGeschwindigkeit() * dDelta; // virtual dispatch

	// Zustände aktualisieren:
	p_dGesamtStrecke += dWeg;
	p_dGesamtZeit    += dDelta;

	// zuletzt simuliert = aktuelle globale Uhr
	p_dZeit           = dGlobaleZeit;
}
