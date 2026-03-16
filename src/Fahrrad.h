#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"
#include <string>
#include <limits>
#include <iostream>

class Fahrrad: public Fahrzeug {
	public:
		// Standardkonstruktor
		Fahrrad();

		// Konstruktor mit Name, maximale Geschwindigkeit
		Fahrrad(std::string name, double p_dMaxGeschwindigkeit);

		// Virtueller Destruktor, weil Objekte von Unterklassen korrekt geloescht werden
		virtual ~Fahrrad();

		// override, weil es eigene spezifische Daten hat
		// Ausgabe der Daten des Fahrrads mit Operator << Ueberladung
		void vAusgeben(std::ostream& os) const override;

		// Berechnet die aktuelle Geschwindigkeit des Fahrrads.
		// Die Geschwindigkeit nimmt pro 20 km um 10% ab, darf aber 12 km/h nicht unterschreiten.
		// const, weil es keine keine Variablen von der Klasse veraendert
		double dGeschwindigkeit() const override;

		void vZeichnen(const Weg& weg) const override;
};

#endif
