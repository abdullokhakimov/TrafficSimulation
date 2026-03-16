#ifndef STRECKENDE_H_
#define STRECKENDE_H_
#include "Fahrausnahme.h"

class Streckende: public Fahrausnahme {
public:
	Streckende(Weg& weg, Fahrzeug& fahrzeug);

	virtual ~Streckende();

	void vBearbeiten() override;

};

#endif
