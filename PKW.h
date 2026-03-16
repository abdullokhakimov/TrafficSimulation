#ifndef PKW_H_
#define PKW_H_
#include "Fahrzeug.h"
#include <string>
#include <limits>
#include <iostream>
#include "Verhalten.h"
#include "Weg.h"

class PKW: public Fahrzeug {
	private:
		// const, weil Verbrauch und Tankvolumen sich nach der Erzeugung nicht mehr aendern
		const double p_dVerbrauch = 0;
		const double p_dTankvolumen = 55;

		// Als Default ist die Tankinhalt die Haelfte der Tankvolumen
		double p_dTankinhalt = 27.5;
	public:
		// Standardkonstruktor
		PKW();

		// Konstruktor mit Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen
		PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen=55);

		// Virtueller Destruktor, weil Objekte von Unterklassen korrekt geloescht werden
		virtual ~PKW();

		// override, weil es eigene spezifische Daten hat
		// Tankt PKW auf
		// dMenge Menge in Litern, als Default unendlich = volltanken
		double dTanken(double dMenge=std::numeric_limits<double>::infinity()) override;

		// Simulation vom PKW
		void vSimulieren() override;

		// Ausgabe von aktuellen Daten des PKWs mit Operator << Ueberladung
		void vAusgeben(std::ostream& os) const override;

		// Zuweisungsoperator "=" fuer PKW
		PKW& operator=(const PKW& other);

		double dGeschwindigkeit() const override;

		void vZeichnen(const Weg& weg) const override;
};

#endif
