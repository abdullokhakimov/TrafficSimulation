#include "Fahrausnahme.h"
#include "Weg.h"
#include "Fahrzeug.h"

Fahrausnahme::Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug) : pWeg(weg), pFahrzeug(fahrzeug){
	std::cout << "Fahrausnahme wurde erzeugt" << std::endl;
}

Fahrausnahme::~Fahrausnahme() {
	std::cout << "Fahrausnahme wurde geloescht" << std::endl;
}

