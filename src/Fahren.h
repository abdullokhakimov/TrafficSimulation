#ifndef FAHREN_H_
#define FAHREN_H_
#include "Verhalten.h"

class Fahren: public Verhalten {
	public:
		using Verhalten::Verhalten;

		double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;
};

#endif
