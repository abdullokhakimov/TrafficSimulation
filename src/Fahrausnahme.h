#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_
#include <stdexcept>

class Fahrzeug;
class Weg;

class Fahrausnahme: std::exception {
	protected:
		Weg& pWeg;
		Fahrzeug& pFahrzeug;

	public:
		Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug);

		virtual ~Fahrausnahme();

		virtual void vBearbeiten() = 0;
};

#endif
