#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <string>
#include <limits>
#include <iostream>
#include <memory>
#include "Simulationsobjekt.h"

class Verhalten;
class Weg;

class Fahrzeug: public Simulationsobjekt{
    // protected, weil diese Variablen durch vSimulieren aktualisiert werden sollen
    protected:
		// Am Amnfang sind die Gesamtstrecke, gesamte Fahrzeit und letzte Zeit von Simulation gleich 0
		const double p_dMaxGeschwindigkeit = 0;
		double p_dGesamtStrecke = 0;
		double p_dGesamtZeit = 0;

		// Strecke in einem Weg
		double p_dAbschnittStrecke = 0;

		std::unique_ptr<Verhalten> p_pVerhalten;

    public:
		// Standardkonstruktor
        Fahrzeug();

        // Konstruktor mit Name und maximale Geschwindigkeit
        Fahrzeug(std::string name, double p_dMaxGeschwindigkeit);

        // Virtueller Destruktor, weil Objekte von Unterklassen korrekt geloescht werden
        virtual ~Fahrzeug();

        // Getter-Methoden
        double getMaxGeschwindigkeit() const {
        	return p_dMaxGeschwindigkeit;
        }
        double getAbschnittStrecke() const {
            return p_dAbschnittStrecke;
        }

        // Tabellenüberschrift für die Fahrzeugausgabe
        // static, weil es nicht zum Objekt gehoert, sondern zu der Klasse
        static void vKopf();

        // Ausgabe von aktuellen Daten des Fahrzeugs mit Operator << Ueberladung
        // virtual, damit Unterklasse spezifische Daten anddieren koennen
        virtual void vAusgeben(std::ostream& os) const override;

        // Simulation vom Farhzeug
        virtual void vSimulieren() override;

        // Tankt Fahrzeug auf
        virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

        // Berechnung von aktueller Geschwindigkeit
        // const, weil es keine Variablen von der Klasse veraendert
        virtual double dGeschwindigkeit() const;

        // Ueberladung des Vergleichsoperators "<" fuer das Vergleich der gesamten Strecke zwischen zwei Objekten
        bool operator<(const Fahrzeug& other) const {
            return p_dGesamtStrecke < other.p_dGesamtStrecke;
        }

        // Kopierkonstruktor verbieten
        // Damit verhindern wir, dass Objekte kopiert werden und IDs doppelt vorkommen
        // Es wird implizit in Funktionen Call by Value aufgerufen, weil da der Wert kopiert wird
        Fahrzeug(const Fahrzeug&) = delete;

        // Zuweisungsoperator "=" deklarieren
        // const, weil wir verandern noch die andere Objekt nicht
        // virtual, damit Unterklasse spezifische Daten anddieren koennen
        virtual Fahrzeug& operator=(const Fahrzeug& other);

        void vNeueStrecke(Weg& rWeg);
        void vNeueStrecke(Weg& rWeg, double dStartzeit);

        virtual void vZeichnen(const Weg&) const;
};



#endif
