#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>



// Konstruktor mit Parameter
Verhalten::Verhalten(Weg& weg): p_rWeg(weg){
    // Используем static_cast<int> для вывода enum
    std::cout << "Verhalten wurde erzeugt." << std::endl;
}

// Destruktor
Verhalten::~Verhalten() {
	std::cout << "Verhalten wurde geloescht." << std::endl;
}

