// Weg.h
#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg: public Simulationsobjekt {
private:
    double p_dLaenge = 0;
    Tempolimit p_eTempolimit;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    std::weak_ptr<Weg> p_pRueckweg;
    std::weak_ptr<Kreuzung> p_pZielkreuzung;

public:
    Weg();
    Weg(std::string name, double p_dLaenge, Tempolimit p_eTempolimit);
    virtual ~Weg();

    double getTempolimit() const { return static_cast<double>(p_eTempolimit); }
    double getLaenge() const { return p_dLaenge; }

    virtual void vSimulieren() override;
    static void vKopf();
    virtual void vAusgeben(std::ostream& os) const override;

    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartzeit);

    void vZeichnen() const;
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& pFahrzeug);

    std::shared_ptr<Kreuzung> getZielkreuzung() const;
    std::shared_ptr<Weg> getRueckweg() const;

    void setZielkreuzung(std::shared_ptr<Kreuzung> kreuzung);
    void setRueckweg(std::shared_ptr<Weg> rueckweg);
};

std::ostream& operator<<(std::ostream& os, const Weg& Weg);

#endif
