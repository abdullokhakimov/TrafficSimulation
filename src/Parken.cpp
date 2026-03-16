#include "Parken.h"
#include "globale_uhr.h" // Um auf dGlobaleZeit zuzugreifen
#include "Fahrzeug.h"
#include "Losfahren.h"

const double dEpsilon = 1e-8;

Parken::Parken(Weg& rWeg, double dStartzeit)
    : Verhalten(rWeg),      // Initialisierung der Basisklasse
      p_dStartzeit(dStartzeit)
{
	std::cout << "Parken wurde erzeugt" << std::endl;

}

Parken::~Parken() {
	std::cout << "Parken wurde geloescht" << std::endl;
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const {
	if (dGlobaleZeit < (p_dStartzeit - dEpsilon)) {
	    // Das Fahrzeug parkt noch, gefahrene Strecke ist 0
	    return 0.0;
	} else {
		// Startzeit erreicht!
		throw Losfahren(p_rWeg, aFzg);
	}
}
