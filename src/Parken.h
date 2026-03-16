#ifndef PARKEN_H_
#define PARKEN_H_
#include "Verhalten.h"

class Parken: public Verhalten{
	private:
    	double p_dStartzeit;

	public:
    	// Konstruktor mit Parametern
    	Parken(Weg& rWeg, double dStartzeit);

    	// Destruktor
		virtual ~Parken();

		double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;
};


#endif
