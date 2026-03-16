#include "Streckende.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>


Streckende::Streckende(Weg& weg, Fahrzeug& fahrzeug) : Fahrausnahme(weg, fahrzeug){
	std::cout << "Fahrausnahme Streckende wurde erzeugt" << std::endl;
}

Streckende::~Streckende() {
	std::cout << "Fahrausnahme Streckende wurde geluescht" << std::endl;
}

void Streckende::vBearbeiten(){
	std::cout << "Fahrzeug " << pFahrzeug.getName() << " hat Ende erreicht in " << pWeg.getName() << std::endl;
}
