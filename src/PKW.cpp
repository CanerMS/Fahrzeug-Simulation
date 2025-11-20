/*
 * PKW.cpp
 *
 *  Created on: Oct 25, 2025
 *      Author: canercam
 */

#include "PKW.h"
#include <iostream>
#include <iomanip>
#include <algorithm> // std::min
#include <limits>
#include "config.h"


// -------------------------------------------------------------------------------------------------------/

PKW::PKW(const std::string& aName,
		 double dMaxG,
		 double dVerbrauch,
		 double dTankvol)
: Fahrzeug(aName, dMaxG),
  p_dVerbrauch( dVerbrauch > 0.0 ? dVerbrauch : 0.0),
  p_dTankvolumen( dTankvol > 0.0 ? dTankvol : 55.0)
{
	p_dTankinhalt = 0.5 * p_dTankvolumen;
}

// -------------------------------------------------------------------------------------------------------/

double PKW::dTanken(double dMenge) {
    // Default: volltanken
    if (dMenge == std::numeric_limits<double>::infinity()) { // Prüfen, ob Defaultwert
        const double getankt = p_dTankvolumen - p_dTankinhalt; // Freier Platz im Tank
        p_dTankinhalt = p_dTankvolumen; // Tank Vollmachen
        return std::max(0.0, getankt); // Getankte Menge Zurück, nie negativ
    }
    // Wunschmenge, aber Deckelung auf Tankvolumen
    const double frei = p_dTankvolumen - p_dTankinhalt; // wie viel passt noch rein
    const double real = std::max(0.0, std::min(frei, dMenge)); // min von (frei, gewünscht)
    p_dTankinhalt += real; // Tank auffüllen
    return real; // Tatsächlich getankte Menge
}

// -------------------------------------------------------------------------------------------------------/

// aktualisiert
void PKW::vSimulieren() {
    const double s_alt = getGesamtStrecke();
    const double t_alt = getZeit();

    // Einzige Quelle für dDelta/Zeiten/Strecke
    Fahrzeug::vSimulieren();

    if (getZeit() == t_alt) return; // in diesem Tick nichts passiert

    // Tatsächlich gefahrene strecke
    const double ds = getGesamtStrecke() - s_alt;
    if (ds <= 0.0) return;

    // Verbrauch aus realem ds (l/100km)
    const double fuel = (p_dVerbrauch / 100.0) * ds;
    p_dTankinhalt -= fuel;
    if (p_dTankinhalt < 0.0) p_dTankinhalt = 0.0; // nie negativ
}

// -------------------------------------------------------------------------------------------------------/

void PKW::vAusgeben(std::ostream& os) const {
    using std::setw;
    using std::setprecision;
    using std::fixed;

    Fahrzeug::vAusgeben(os); // gemeinsame Spalten
    const double gesamtVerbrauch = (p_dVerbrauch / 100.0) * p_dGesamtStrecke;

    os << setw(14) << fixed << setprecision(2) << p_dTankinhalt
         << setw(18) << fixed << setprecision(2) << gesamtVerbrauch;
}

// -------------------------------------------------------------------------------------------------------/


