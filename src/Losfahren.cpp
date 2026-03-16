#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>


Losfahren::Losfahren(Weg& weg, Fahrzeug& fahrzeug) : Fahrausnahme(weg, fahrzeug){
	std::cout << "Fahrausnahme Losfahren wurde erzeugt" << std::endl;
}

Losfahren::~Losfahren() {
	std::cout << "Fahrausnahme Losfahren wurde geluescht" << std::endl;
}

void Losfahren::vBearbeiten(){
	std::cout << "\nException: Losfahren\n";

	std::cout << "Fahrzeug: " << pFahrzeug << "\nWeg: " << pWeg << std::endl;
}
