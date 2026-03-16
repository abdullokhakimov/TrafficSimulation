#include "Simulationsobjekt.h"
#include <iomanip>
#include <iostream>

// Initialisierung der statischen Variable
int Simulationsobjekt::p_iMaxID = 0;

// Standardkonstruktor
Simulationsobjekt::Simulationsobjekt()
				: p_iID(++p_iMaxID),
				  p_sName("")
{

	std::cout << "Simulationsobjekt mit ID " << p_iID
			  << ", Name " << p_sName
			  << " wurde erzeugt."
			  << std::endl;
}

// Konstruktor mit Parametern
// Überprüft, ob die Geschwindigkeit negativ ist
Simulationsobjekt::Simulationsobjekt(std::string name)
				: p_iID(++p_iMaxID),
				  p_sName(name)
{
	std::cout << "Simulationsobjekt mit ID " << p_iID
			  << ", Name " << p_sName
			  << " wurde erzeugt."
			  << std::endl;
}

// Destruktor
Simulationsobjekt::~Simulationsobjekt() {
	std::cout << "Simulationsobjekt mit ID " << p_iID
			  << ", Name " << p_sName
			  << " wurde geloescht."
			  << std::endl;
}

// Ueberladung des Zuweisungsoperators
// Kopiert keine cosnt Variablen ID, Name, MaxGeschwindigkeit
Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& other) {
	// Wenn sie nicht gleiche Objekte sind
    if (this != &other) {
        p_dZeit = other.p_dZeit;
    }

    // Aktualisierte Objekt
    return *this;
}

// Gibt die Daten des Simulationsobjekts aus
void Simulationsobjekt::vAusgeben(std::ostream& os) const {
    os << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left);
    os << std::setw(5) << p_iID;
    os << std::setw(15) << p_sName;
}

// Ueberladung des Ausgabeoperators << für Nutzung mit std::cout
std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& obj) {
    obj.vAusgeben(os);
    return os;
}
