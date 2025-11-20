/*
 * PKW.h
 *
 *  Created on: Oct 25, 2025
 *      Author: canercam
 */

#pragma once
#include "Fahrzeug.h"
#include "config.h"


class PKW : public Fahrzeug
{

private:
	double p_dVerbrauch  {0.0}; // l/100km
	double p_dTankvolumen {55.0};
	double p_dTankinhalt {27.5}; // initial Hälfte von Volumen

// -------------------------------------------------------------------------------------------------------/

public:
	explicit PKW(const std::string& aName,
				 double dMaxG,
		         double dVerbrauch,
				 double dTankvol = 55.0); // <-- 4. Parameter Default

	// PKW-spezifisch
	double dTanken(double dMenge) override;
	void vSimulieren() override; // Tank berücksichtigen
	double dGeschwindigkeit() const override {
		//  Bei leerem Tank fährt die Basisklasse nicht weiter (ds=0)
		return (p_dTankinhalt <= EPS) ? 0.0 : p_dMaxGeschwindigkeit;
	}

	void vAusgeben(std::ostream& os) const override;  // ruft Fahrzeug::vAusgeben() hängt Tank/Verbrauch an
};

// -------------------------------------------------------------------------------------------------------/
