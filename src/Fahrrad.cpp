#include "Fahrrad.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "SimuClient.h"
#include <string>
#include "Weg.h"


// Standardkonstruktor
Fahrrad::Fahrrad() :
					// Standartkonstruktor von der Basisklasse
					Fahrzeug()
{
    std::cout << "Fahrrad mit ID " << getID()
    		  << ", Name " << getName()
			  << " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << " wurde erzeugt."
			  << std::endl;
}


// Konstruktor mit Parametern
Fahrrad::Fahrrad(std::string name,
				double maxGeschwindigkeit)
				:
				// Konstruktor von der Basisklasse
				Fahrzeug(name, maxGeschwindigkeit)
{
	std::cout << "Fahrrad mit ID " << getID()
			  << ", Name " << getName()
			  << " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << " wurde erzeugt."
			  << std::endl;
}

// Destruktor
Fahrrad::~Fahrrad() {
	std::cout << "Fahrrad mit ID " << getID()
			  << ", Name " << getName()
			  << " und maximaler Geschwindigkeit " << p_dMaxGeschwindigkeit
			  << " wurde geloescht."
			  << std::endl;
}

// Berechnung von der Geschwindigkeit
double Fahrrad::dGeschwindigkeit() const{
	// Konstante fuer die Mindestgeschwindigkeit 12 km/h
	const double dMinGeschwindigkeit = 12;

	// Berechnung der 20-km-Intervalle
	// Integer Division schneidet Nachkommastellen ab
	int iIntervale = (int)p_dGesamtStrecke / 20;

	// Geschwindigkeit nimmt um 10% pro Intervall ab
	double dReduzierteGeschwindigkeit = p_dMaxGeschwindigkeit * std::pow(0.9, iIntervale);

	// Die Geschwindigkeit darf 12 km/h nicht unterschreiten
	if (dReduzierteGeschwindigkeit <= dMinGeschwindigkeit){
		return dMinGeschwindigkeit;
	}else{
		return dReduzierteGeschwindigkeit;
	}
}

// Ausgabe der Daten des Fahrrads mit Operator << Ueberladung
void Fahrrad::vAusgeben(std::ostream& os) const{
	// Basisausgabe aufrufen
    Fahrzeug::vAusgeben(os);

    os << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right);

    // Ausgabe der Fahrrad-spezifischen Daten
    os << std::setw(20) << "-";
    os << std::setw(20) << "-";
}

void Fahrrad::vZeichnen(const Weg& weg) const{
	double dRelPosition = p_dAbschnittStrecke / weg.getLaenge();
	bZeichneFahrrad(p_sName, weg.getName(), dRelPosition, dGeschwindigkeit());
}


