/*
 * Fahrrad.cpp
 *
 *  Created on: Oct 30, 2025
 *      Author: canercam
 */


#include "Fahrrad.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "config.h"

// -------------------------------------------------------------------------------------------------------/

double Fahrrad::dGeschwindigkeit() const {
	// pro 20 km 10% weniger, mind. 12 km/h
	const int     k = static_cast<int> ( std::floor(p_dGesamtStrecke / 20.0) ); // Anzahl der 20 km Abschnitte
	const double  f = std::pow(0.9, k); // Faktor
	const double  v = p_dMaxGeschwindigkeit * f; // Reduzierte Geschwindigkeit
	return (v < 12.0) ? 12.0 : v; // Minimum 12 km
}

// -------------------------------------------------------------------------------------------------------/

void Fahrrad::vAusgeben(std::ostream& os) const {
	using std::setw;
	using std::setprecision;
	using std::fixed;

	Fahrzeug::vAusgeben(os);

	// Fahrräder: kein Tank, kein Kraftstoffverbrauch
	os << setw(14) << fixed << setprecision(2) << 0.0  // Tank
		 << setw(18) << fixed << setprecision(2) << 0.0; // Verbrauch

}

// -------------------------------------------------------------------------------------------------------/
