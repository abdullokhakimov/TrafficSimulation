#include "Fahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>

// Initialisierung von Epsilon fuer das Vergleich von double
const double dEpsilon = 1e-8;

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const{
	// Bekommen Tempolimit im Weg
	double dTempolimit = p_rWeg.getTempolimit();
	double dWegLaenge = p_rWeg.getLaenge();
	double dAktuelleGeschwindigkeit = aFzg.dGeschwindigkeit();
	double dAbschnittstrecke = aFzg.getAbschnittStrecke();

    // Geschwindigkeit begraenzen
	if (dAktuelleGeschwindigkeit > dTempolimit) {
		dAktuelleGeschwindigkeit = dTempolimit;
	}

	// Wie viele Strecke geblieben ist
	double dReststrecke = dWegLaenge - dAbschnittstrecke;

	if (dReststrecke < dEpsilon) {
		std::cout << "Fahrzeug '" << aFzg.getName()
	              << "' hat das Ende des Weges '" << p_rWeg.getName()
	              << "' erreicht." << std::endl;
		return 0.0;
	}

	// s = t * v
	double dMöglicheStrecke = dAktuelleGeschwindigkeit * dZeitIntervall;

	// Moegliche Strecke begraenzen
	if (dMöglicheStrecke > dReststrecke) {
		return dReststrecke;
	}

	return dMöglicheStrecke;
}



