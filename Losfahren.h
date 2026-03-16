#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_
#include "Fahrausnahme.h"

class Fahrzeug;
class Weg;

class Losfahren: public Fahrausnahme {
	public:
		Losfahren(Weg& weg, Fahrzeug& fahrzeug);

		virtual ~Losfahren();

		void vBearbeiten() override;
};

#endif
