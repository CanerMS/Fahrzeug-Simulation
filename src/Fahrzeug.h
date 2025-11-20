/*
 * Fahrzeug.h
 *
 *  Created on: Oct 25, 2025
 *      Author: canercam
 */

#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include "config.h"



class Fahrzeug
{
protected:

	inline static int p_iMaxID = 0;

	const int p_iID; // zu jedem Objekt zugewiesen
	std::string p_sName; // Name des Wagens

	double           p_dMaxGeschwindigkeit {0.0};
	double           p_dGesamtStrecke      {0.0};
	double           p_dGesamtZeit         {0.0};
	double           p_dZeit               {0.0}; // Zeitpunkt der letzten Abfertigung

// -------------------------------------------------------------------------------------------------------/

public:
	Fahrzeug();
	explicit Fahrzeug(const std::string& aName);
	Fahrzeug(const std::string& aName, double dMaxG);
	virtual ~Fahrzeug();

	// Polymorphe Schnittstellen
	virtual double dGeschwindigkeit() const; // Basis: volle v_max
	virtual void   vSimulieren();          // Verändert Zeit und Strecke
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()); // Basis: 0 Verändert Tankinhalt

	// Ausgabe ohne endl!
	static void vKopf();
	virtual void vAusgeben(std::ostream& os) const;

	// Vergleich
	bool operator<(const Fahrzeug& rhs) const;

	// Kopie/Zuordnung
	Fahrzeug(const Fahrzeug&) = delete;
	Fahrzeug& operator=(const Fahrzeug& rhs);


	// Ein paare Getter, möglich viele const
	int                   getID()             const { return p_iID;                 }
	const std::string&    getName()           const { return p_sName;               }
	double                getMaxGeschw()      const { return p_dMaxGeschwindigkeit; }
	double                getGesamtStrecke()  const { return p_dGesamtStrecke;      }
	double                getGesamtZeit()     const { return p_dGesamtZeit;         }
	double                getZeit()           const { return p_dZeit;               }

};

// -------------------------------------------------------------------------------------------------------/

// Freier Ausgabeoperator (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Fahrzeug& f);
