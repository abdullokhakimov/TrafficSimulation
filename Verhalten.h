#ifndef VERHALTEN_H_
#define VERHALTEN_H_

class Weg;
class Fahrzeug;

class Verhalten {
	protected:
		Weg& p_rWeg;

	public:
		// Konstruktor mit Parametern
		Verhalten(Weg& p_rWeg);

		// Destruktor
		virtual ~Verhalten();

		virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const = 0;

		Weg& getWeg() const {
			return p_rWeg;
		}
};

#endif
