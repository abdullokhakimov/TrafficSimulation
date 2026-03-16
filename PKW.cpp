#include "PKW.h"
#include <limits>
#include <iostream>
#include <iomanip>
#include "globale_uhr.h"
#include "SimuClient.h"
#include "Weg.h"
#include <string>

// Initialisierung von Epsilon fuer das Vergleich von double
const double dEpsilon = 1e-8;

// Standardkonstruktor
PKW::PKW() :
			// Standartkonstruktor von der Basisklasse
			Fahrzeug(),
			p_dVerbrauch(0),
			p_dTankvolumen(55),
			// Die Haelfte der Tankvolumen
			p_dTankinhalt(27.5)
{

	std::cout << "PKW mit ID " << getID()
			  << ", Name " << getName()
			  << ", maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << ", Verbrauch " << p_dVerbrauch
			  << " Liter/100km, Tankvolumen" << p_dTankvolumen
			  << " l und Tankinhalt" << p_dTankinhalt << " l "
			  << "wurde erzeugt."
			  << std::endl;
}

// Konstruktor mit Parametern
PKW::PKW(std::string name,
		double maxGeschwindigkeit,
		double verbrauch,
		double tankvolumen)
		:
		// Konstruktor von der Basisklasse
		Fahrzeug(name, maxGeschwindigkeit),
		// Verbrauch darf nicht negativ sein
		p_dVerbrauch(verbrauch < 0 ? 0 : verbrauch),
		// Tankvolumen hat Mindestwert und darf nicht kleinergleich 0 sein
		p_dTankvolumen(tankvolumen < 55 ? 55 : tankvolumen),
		// Die Haelfte der Tankvolumen
		p_dTankinhalt(p_dTankvolumen/2.0)
{
	std::cout << "PKW mit ID " << getID()
			  << ", Name " << getName()
			  << ", maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << ", Verbrauch " << p_dVerbrauch
			  << " Liter/100km, Tankvolumen" << p_dTankvolumen
			  << " l und Tankinhalt" << p_dTankinhalt << " l "
			  << "wurde erzeugt."
			  << std::endl;
}

// Destruktor
PKW::~PKW() {
	std::cout << "PKW mit ID " << getID()
			  << ", Name " << getName()
			  << ", maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << ", Verbrauch " << p_dVerbrauch
			  << " Liter/100km, Tankvolumen" << p_dTankvolumen
			  << " l und Tankinhalt" << p_dTankinhalt << " l "
			  << "wurde geloescht."
			  << std::endl;
}

// Implementierung fuers Tanken
double PKW::dTanken(double dMenge){
	// Keine negative Betankung möglich
	if (dMenge < 0) return 0;

	double dFreierPlatz = p_dTankvolumen - p_dTankinhalt;

	// Wenn Menge unendlich, tanken wir voll
	if (dMenge == std::numeric_limits<double>::infinity()) {
	    dMenge = dFreierPlatz;
	}

	// Wir tanken das Minimum aus Wunschmenge und Freier Platz
	double dGetankteMenge = std::min(dMenge, dFreierPlatz);

	p_dTankinhalt += dGetankteMenge;

	return dGetankteMenge;
}

// Simuliert die Bewegung des PKWs
// Aktualisiert Strecke und Zeit basierend auf der globalen Uhr
void PKW::vSimulieren() {
	// Wenn es an deisem Zeitpunkt schon eine Simulation gab, fuehren wir keine Simulation durch
	// Fuer die Vermeiden von Fehler mit double verwenden wir Epsilon
	if (std::abs(dGlobaleZeit - p_dZeit) < dEpsilon || dGlobaleZeit < p_dZeit || p_dTankinhalt == 0) {
		return;
	}

	double dStreckeVorher = p_dGesamtStrecke;

	if (p_dTankinhalt > dEpsilon) {
		Fahrzeug::vSimulieren();
	} else {
	    p_dZeit = dGlobaleZeit;
	    return;
	}

	double dRealGefahreneStrecke = p_dGesamtStrecke - dStreckeVorher;

	double dVerbrauch = dRealGefahreneStrecke * (p_dVerbrauch / 100.0);

	p_dTankinhalt -= dVerbrauch;

	if (p_dTankinhalt < 0) p_dTankinhalt = 0;
}

// Ausgabe der Daten des PKWs mit Operator << Ueberladung
void PKW::vAusgeben(std::ostream& os) const{
	// Basisausgabe aufrufen
    Fahrzeug::vAusgeben(os);

    // Berechnung Gesamtverbrauch
    double dGesamtverbrauch = p_dGesamtStrecke * (p_dVerbrauch / 100.0);

    os << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right);

    // Ausgabe der PKW-spezifischen Daten
    os << std::setw(20) << std::fixed << std::setprecision(2) << dGesamtverbrauch;
    os << std::setw(20) << std::fixed << std::setprecision(2) << p_dTankinhalt;
}

// Ueberladung des Zuweisungsoperators
// Kopiert keine cosnt Variablen ID, Name, MaxGeschwindigkeit, p_dVerbrauch und p_dTankvolumen
// Kein override weil die Eingaben unterschiedlich sind
PKW& PKW::operator=(const PKW& other) {
    // Schutz vor Selbstzuweisung (a = a)
    if (this != &other) {
        // Anteile von der Basisklasse
        Fahrzeug::operator=(other);

        // PKW-spezifische Daten kopieren
        p_dTankinhalt = other.p_dTankinhalt;
    }

    // Aktualisierte Objekt
    return *this;
}

double PKW::dGeschwindigkeit() const{
	double dWegLimit = static_cast<double>(p_pVerhalten->getWeg().getTempolimit());

	if (dWegLimit < p_dMaxGeschwindigkeit) {
		return dWegLimit;
	} else {
	    return p_dMaxGeschwindigkeit;
	}
}

void PKW::vZeichnen(const Weg& weg) const{
	double dRelPosition = p_dAbschnittStrecke / weg.getLaenge();
	bZeichnePKW(p_sName, weg.getName(), dRelPosition, dGeschwindigkeit(), p_dTankinhalt);
}
