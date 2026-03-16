#include "Kreuzung.h"
#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"
#include <memory>
#include <random>

const double dEpsilon = 1e-8;

Kreuzung::Kreuzung(std::string sName, double dTankstelle)
    : Simulationsobjekt(sName), p_dTankstelle(dTankstelle) {
    std::cout << "Kreuzung mit ID " << getID()
              << ", Name " << getName()
              << ", Tankstelle " << p_dTankstelle
              << " wurde erzeugt."
              << std::endl;
}

Kreuzung::~Kreuzung() {
    std::cout << "Kreuzung mit ID " << getID() // Исправил "Weg" на "Kreuzung" в выводе
              << ", Name " << getName()
              << ", Tankstelle " << p_dTankstelle
              << " wurde geloescht."
              << std::endl;
}


void Kreuzung::vTanken(Fahrzeug& fahrzeug){
    if (p_dTankstelle > dEpsilon){
        double dGetankteMenge = fahrzeug.dTanken(p_dTankstelle);

        p_dTankstelle = p_dTankstelle - dGetankteMenge;

        if (p_dTankstelle < dEpsilon) {
            p_dTankstelle = 0.0;
        }
    }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartzeit){
    vTanken(*fahrzeug);

    if (!p_pWege.empty()) {
        p_pWege.front()->vAnnahme(std::move(fahrzeug), dStartzeit);
    }
}

void Kreuzung::vSimulieren() {
    for (auto& pWeg : p_pWege) {
        pWeg->vSimulieren();
    }
}

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung> pStartKreuzung,
                         std::shared_ptr<Kreuzung> pZielKreuzung,
                         std::string sHinWeg,
                         std::string sRueckWeg,
                         double dWegLaenge,
                         Tempolimit eGeschwindigkeitsbegrenzung)
{
    auto pHinWeg = std::make_shared<Weg>(sHinWeg, dWegLaenge, eGeschwindigkeitsbegrenzung);
    auto pRueckWeg = std::make_shared<Weg>(sRueckWeg, dWegLaenge, eGeschwindigkeitsbegrenzung);

    pHinWeg->setRueckweg(pRueckWeg);
    pRueckWeg->setRueckweg(pHinWeg);

    pHinWeg->setZielkreuzung(pZielKreuzung);
    pRueckWeg->setZielkreuzung(pStartKreuzung);

    pStartKreuzung->p_pWege.push_back(pHinWeg);
    pZielKreuzung->p_pWege.push_back(pRueckWeg);

    std::cout << "VERBINDUNG: " << pStartKreuzung->getName() << " -> "
              << sHinWeg << " -> " << pZielKreuzung->getName() << std::endl;
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& pAnkunftsweg) {
    int iLaengeVonListe = p_pWege.size();

    if (iLaengeVonListe == 0) return nullptr;

    if (iLaengeVonListe == 1) return p_pWege.front();

    static std::mt19937 device(0);
    std::uniform_int_distribution<int> dist(0, iLaengeVonListe - 1);

    while (true) {
        int iZuf = dist(device);
        auto it = std::next(p_pWege.begin(), iZuf);
        std::shared_ptr<Weg> pGewaehlterWeg = *it;

        if (pGewaehlterWeg->getRueckweg()->getID() != pAnkunftsweg.getID()) {
            return pGewaehlterWeg;
        }
    }
}

void Kreuzung::vZeichnen() const {
    for (const auto& pWeg : p_pWege) {
        pWeg->vZeichnen();
    }
}
