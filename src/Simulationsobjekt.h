#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_
#include <string>
#include <iostream>

class Simulationsobjekt {
	protected:
		// Statische Variable fuer Zaehlung der IDs aller Fahrzeuge
		static int p_iMaxID;

		// const, weil ID, Name und Maximale Geschwindigkeit sich nach der Erzeugung nicht mehr aendern
		const int p_iID = 0;
		const std::string p_sName = "";

	public:
		double p_dZeit = 0;

		// Standardkonstruktor
		Simulationsobjekt();

		// Konstruktor mit Name und maximale Geschwindigkeit
		Simulationsobjekt(std::string name);

		// Virtueller Destruktor, weil Objekte von Unterklassen korrekt geloescht werden
		virtual ~Simulationsobjekt();

		// Kopierkonstruktor verbieten
		// Damit verhindern wir, dass Objekte kopiert werden und IDs doppelt vorkommen
		// Es wird implizit in Funktionen Call by Value aufgerufen, weil da der Wert kopiert wird
		Simulationsobjekt(const Simulationsobjekt&) = delete;

		// Zuweisungsoperator "=" deklarieren
		// const, weil wir verandern noch die andere Objekt nicht
		// virtual, damit Unterklasse spezifische Daten anddieren koennen
		virtual Simulationsobjekt& operator=(const Simulationsobjekt& other);

		// Getter-Methoden
		std::string getName() const {
			return p_sName;
		}
		int getID() const {
		    return p_iID;
		}


		// Ausgabe von aktuellen Daten des Fahrzeugs mit Operator << Ueberladung
		// virtual, damit Unterklasse spezifische Daten anddieren koennen
		virtual void vAusgeben(std::ostream& os) const;

		// Simulation vom Farhzeug
		virtual void vSimulieren() = 0;

		// Vergleichsoperator: true, wenn IDs gleich sind
		bool operator==(const Simulationsobjekt& other) const{
			return p_iID == other.p_iID;
		}
};

// Ueberladung des Ausgabeoperators << fuer Nutzung mit std::cout
std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& simulationsobjekt);

#endif
