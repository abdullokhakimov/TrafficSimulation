#include "Weg.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include "Fahrzeug.h"
#include "globale_uhr.h"
#include <memory>
#include "Fahrausnahme.h"
#include "Streckende.h"
#include "Kreuzung.h"

// Standardkonstruktor
Weg::Weg()
			: Simulationsobjekt(),
			  p_dLaenge(0),
			  p_eTempolimit(Tempolimit::Autobahn),
			  p_pZielkreuzung()
{
    // Используем static_cast<int> для вывода enum
    std::cout << "Weg mit ID " << getID()
              << ", Name " << getName()
              << ", Laenge " << p_dLaenge
              << ", Tempolimit " << static_cast<double>(p_eTempolimit)
              << " wurde erzeugt."
              << std::endl;
}

// Konstruktor mit Parametern
Weg::Weg(std::string name, double laenge, Tempolimit limit)
				: Simulationsobjekt(name),
				  p_dLaenge(laenge),
				  p_eTempolimit(limit),
				  p_pZielkreuzung()
{

    if (limit != Tempolimit::Innerorts &&
        limit != Tempolimit::Landstrasse &&
        limit != Tempolimit::Autobahn) {
        p_eTempolimit = Tempolimit::Autobahn;
    }

    std::cout << "Weg mit ID " << getID()
              << ", Name " << getName()
              << ", Laenge " << p_dLaenge
              << ", Tempolimit " << static_cast<double>(p_eTempolimit)
              << " wurde erzeugt."
              << std::endl;
}

// Destruktor
Weg::~Weg() {
    std::cout << "Weg mit ID " << getID()
              << ", Name " << getName()
              << ", Laenge " << p_dLaenge
              << ", Tempolimit " << static_cast<double>(p_eTempolimit)
              << " wurde geloescht."
              << std::endl;
}

void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren();

    for (auto fahrzeug = p_pFahrzeuge.begin(); fahrzeug != p_pFahrzeuge.end(); ++fahrzeug) {
        try {
            (*fahrzeug)->vSimulieren();
        }
        catch (Streckende& e) {
            e.vBearbeiten();

            std::shared_ptr<Kreuzung> pKreuzung = getZielkreuzung();

            if (pKreuzung != nullptr) {
                pKreuzung->vTanken(**fahrzeug);
                std::shared_ptr<Weg> pNeuerWeg = pKreuzung->pZufaelligerWeg(*this);

                std::cout << "ZEIT     : " << dGlobaleZeit << std::endl;
                std::cout << "KREUZUNG : " << pKreuzung->getName() << " " << pKreuzung->getTankstelle() << std::endl;
                std::cout << "WECHSEL  : " << this->getName() << " -> " << pNeuerWeg->getName() << std::endl;
                std::cout << "FAHRZEUG : " << **fahrzeug << std::endl;

                std::unique_ptr<Fahrzeug> pFzg = std::move(*fahrzeug);
                p_pFahrzeuge.erase(fahrzeug);
                pNeuerWeg->vAnnahme(std::move(pFzg));
            }
            else {
                std::cout << "ОШИБКА: Тупик на дороге " << getName() << "! Машина удаляется." << std::endl;
                p_pFahrzeuge.erase(fahrzeug);
            }
        }
        catch (Fahrausnahme& e) {
            e.vBearbeiten();

            std::unique_ptr<Fahrzeug> pFzg = std::move(*fahrzeug);
            p_pFahrzeuge.erase(fahrzeug);
            this->vAnnahme(std::move(pFzg));
        }
    }
    p_pFahrzeuge.vAktualisieren();
    p_dZeit = dGlobaleZeit;
}

// Ausgabe der Tabellenüberschrift
void Weg::vKopf() {
	std::cout << std::left << std::setw(5) << "ID";
	std::cout << std::left << std::setw(15) << "Name";
	std::cout << std::left << std::setw(10) << "Laenge";
	std::cout << std::left << std::setw(50) << "Fahrzeuge"
			  << std::endl;
	std::cout << std::string(80, '-') << std::endl;
}

// Gibt die Daten des Weges aus
void Weg::vAusgeben(std::ostream& os) const {
	Simulationsobjekt::vAusgeben(os);

	os << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left);

	os << std::setw(10) << std::fixed << std::setprecision(2) << p_dLaenge;
	os << " ( ";
	for (const auto& fahrzeug : p_pFahrzeuge) {
	    os << fahrzeug->getName() << ", ";
	}
	os << ")";
}


std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os);
    return os;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug){
	pFahrzeug->vNeueStrecke(*this);

	p_pFahrzeuge.push_back(std::move(pFahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit) {
	pFahrzeug->vNeueStrecke(*this, dStartzeit);

    p_pFahrzeuge.push_front(std::move(pFahrzeug));
}

void Weg::vZeichnen() const{
	for (auto const& fahrzeug : p_pFahrzeuge){
		fahrzeug->vZeichnen(*this);
	}
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& pFahrzeug){
	for (auto fahrzeug = p_pFahrzeuge.begin(); fahrzeug != p_pFahrzeuge.end(); ++fahrzeug){
		if (*fahrzeug != nullptr && pFahrzeug == **fahrzeug){
			std::unique_ptr<Fahrzeug> lokalFahrzeug = std::move(*fahrzeug);
			p_pFahrzeuge.erase(fahrzeug);
			return lokalFahrzeug;
		}
	}
	return nullptr;
}

void Weg::setZielkreuzung(std::shared_ptr<Kreuzung> kreuzung){
	p_pZielkreuzung = kreuzung;
}

void Weg::setRueckweg(std::shared_ptr<Weg> rueckweg){
	p_pRueckweg = rueckweg;
}

std::shared_ptr<Kreuzung> Weg::getZielkreuzung() const {
    return p_pZielkreuzung.lock();
}

std::shared_ptr<Weg> Weg::getRueckweg() const {
    return p_pRueckweg.lock();
}

