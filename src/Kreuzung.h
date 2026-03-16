#ifndef KREUZUNG_H_
#define KREUZUNG_H_
#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include <string>
#include "Tempolimit.h"

class Weg;
class Fahrzeug;

class Kreuzung: public Simulationsobjekt{
	private:
		std::list<std::shared_ptr<Weg>> p_pWege;
		double p_dTankstelle = 0.0;

	public:
		Kreuzung();
		Kreuzung(std::string sName, double p_dTankstelle);
		virtual ~Kreuzung();

		static void vVerbinde(std::shared_ptr<Kreuzung> pStartKreuzung,
							  std::shared_ptr<Kreuzung> pZielKreuzung,
							  std::string sHinWeg,
							  std::string sRueckWeg,
							  double dWegLaenge,
							  Tempolimit eGeschwindigkeitsbegrenzung);

		void vTanken(Fahrzeug& fahrzeug);

		void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartzeit);

		virtual void vSimulieren() override;

		std::shared_ptr<Weg> pZufaelligerWeg(Weg&);

		double getTankstelle() const {
		    return p_dTankstelle;
		}

		void setTankstelle(double volumen) {
		    p_dTankstelle = volumen;
		}

		void vZeichnen() const;
};



#endif
