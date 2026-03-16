#include "Fahrzeug.h"
#include "Weg.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "globale_uhr.h"
#include <memory>
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include "Losfahren.h"
#include "Streckende.h"



// Initialisierung von Epsilon fuer das Vergleich von double
const double dEpsilon = 1e-8;

// Standardkonstruktor
Fahrzeug::Fahrzeug()
				: Simulationsobjekt(),
				  p_dMaxGeschwindigkeit(0)
{

	std::cout << "Fahrzeug mit ID " << p_iID
			  << ", Name " << p_sName
			  << " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << " wurde erzeugt."
			  << std::endl;
}

// Konstruktor mit Parametern
// Überprüft, ob die Geschwindigkeit negativ ist
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
				: Simulationsobjekt(name),
				  p_dMaxGeschwindigkeit(maxGeschwindigkeit < 0 ? 0 : maxGeschwindigkeit)
{
	std::cout << "Fahrzeug mit ID " << p_iID
			  << ", Name " << p_sName
			  << " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << " wurde erzeugt."
			  << std::endl;
}

// Destruktor
Fahrzeug::~Fahrzeug() {
	std::cout << "Fahrzeug mit ID " << p_iID
			<< ", Name " << p_sName
			<< " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			<< " wurde geloescht."
			<< std::endl;
}

// Ausgabe der Tabellenüberschrift
void Fahrzeug::vKopf() {
	std::cout << std::left << std::setw(5) << "ID";
	std::cout << std::left << std::setw(15) << "Name";
	std::cout << std::right << std::setw(20) << "MaxGeschwindigkeit";
	std::cout << std::right << std::setw(20) << "AktGeschwindigkeit";
	std::cout << std::right << std::setw(20) << "Abschnittstrecke";
	std::cout << std::right << std::setw(20) << "Gesamtstrecke";
	std::cout << std::right << std::setw(20) << "Gesamtverbrauch";
	std::cout << std::right << std::setw(20) << "Tankinhalt";
}

// Gibt die Daten des Fahrzeugs aus
void Fahrzeug::vAusgeben(std::ostream& os) const {
	double dAktuelleGeschwindigkeit = dGeschwindigkeit();

	Simulationsobjekt::vAusgeben(os);

	os << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right);

	os << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit;
	os << std::setw(20) << std::fixed << std::setprecision(2) << dAktuelleGeschwindigkeit;
	os << std::setw(20) << std::fixed << std::setprecision(2) << p_dAbschnittStrecke;
	os << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke;
}

// Simuliert die Bewegung des Fahrzeugs
// Aktualisiert Strecke und Zeit basierend auf der globalen Uhr
void Fahrzeug::vSimulieren(){
	// Wenn es an deisem Zeitpunkt schon eine Simulation gab, fuehren wir keine Simulation durch
	// Fuer die Vermeiden von Fehler mit double verwenden wir Epsilon
	if (std::abs(dGlobaleZeit - p_dZeit) < dEpsilon || dGlobaleZeit < p_dZeit) {
		return;
	}

	double dDeltaZeit = dGlobaleZeit - p_dZeit;

	double dGefahreneStrecke = p_pVerhalten->dStrecke(*this, dDeltaZeit);

	// Aktualisieren die Strecken
	p_dGesamtStrecke += dGefahreneStrecke;
	p_dAbschnittStrecke += dGefahreneStrecke;

	double dWegLaenge = p_pVerhalten->getWeg().getLaenge(); // Проверь, как называется геттер длины в Weg

	if (p_dAbschnittStrecke > dWegLaenge || std::abs(p_dAbschnittStrecke - dWegLaenge) < dEpsilon) {

	    throw Streckende(p_pVerhalten->getWeg(), *this);
	}


	p_dGesamtZeit += dDeltaZeit;

	// Aktualisiere den letzten Simulationszeitpunkt
	p_dZeit = dGlobaleZeit;
}

// Standardimplementierung fuers Tanken
double Fahrzeug::dTanken(double dMenge){
    return 0.0;
}

// Standardimplementierung fur die Berechnung von aktueller Geschwindigkeit
double Fahrzeug::dGeschwindigkeit() const{
    return p_dMaxGeschwindigkeit;
}

// Ueberladung des Ausgabeoperators << für Nutzung mit std::cout
std::ostream& operator<<(std::ostream& os, const Fahrzeug& fahrzeug) {
    fahrzeug.vAusgeben(os);
    return os;
}

// Ueberladung des Zuweisungsoperators
// Kopiert keine cosnt Variablen ID, Name, MaxGeschwindigkeit
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
	// Wenn sie nicht gleiche Objekte sind
    if (this != &other) {
        p_dGesamtStrecke = other.p_dGesamtStrecke;
        p_dGesamtZeit = other.p_dGesamtZeit;
        p_dZeit = other.p_dZeit;
    }

    // Aktualisierte Objekt
    return *this;
}

void Fahrzeug::vNeueStrecke(Weg& rWeg){
	// Beim Anfang neues Wegs die Strecke soll 0 sein
    p_dAbschnittStrecke = 0.0;

    // Neues Verhalten
    // Letzte Instanz wird automatisch geloescht
    p_pVerhalten = std::make_unique<Fahren>(rWeg);
}

void Fahrzeug::vNeueStrecke(Weg& rWeg, double dStartzeit){
	// Beim Anfang neues Wegs die Strecke soll 0 sein
    p_dAbschnittStrecke = 0.0;

    // Neues Verhalten
    // Letzte Instanz wird automatisch geloescht
    p_pVerhalten = std::make_unique<Parken>(rWeg, dStartzeit);
}

void Fahrzeug::vZeichnen(const Weg& rWeg) const {}
