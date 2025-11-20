/*
 * Fahrrad.h
 *
 *  Created on: Oct 29, 2025
 *      Author: canercam
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"


class Fahrrad : public Fahrzeug
{
public:
	explicit Fahrrad(const std::string& aName, double dMaxG)
	: Fahrzeug(aName, dMaxG) {}

	// Ermüdungsmodell
	double dGeschwindigkeit() const override;
	void vAusgeben(std::ostream& os) const override; // ruft Basis und hängt 0/0 als Tank/Verbrauch an

};




#endif /* FAHRRAD_H_ */
