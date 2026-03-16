#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "globale_uhr.h"
#include <cmath>
#include <iomanip>
#include "Fahrzeug.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "SimuClient.h"
using namespace std;
#include "vertagt_liste.h"
#include <random>
#include "Kreuzung.h"
#include "Fahrausnahme.h"
#include "Streckende.h"

void vAufgabe_1() {
    // Statische Objekte (Test von Standartkonstruktor und Konstruktor mit Parameter):
	// Wir nutzen PKW statt Fahrzeug, da Fahrzeug abstrakt geworden ist
	cout << "\n--- Statische Objekte ---" << endl;
    PKW tStatischesFahrzeug1;
    PKW tStatischesFahrzeug2("Statisches Fahrzeug", 100, 5, 50);

    // Dynamische Objekte
    cout << "\n--- Dynamische Objekte ---" << endl;
    Fahrzeug* pDynamischesFahrzeug = new PKW("Dynamisches Fahrzeug", 100, 5, 50);
    delete pDynamischesFahrzeug;

    // Smart Pointers (Unique)
    cout << "\n--- Smart Pointers (Unique) ---" << endl;
    unique_ptr<Fahrzeug> pUniqueTest1 = make_unique<PKW>("Unique PKW 1", 120, 6, 60);
    unique_ptr<Fahrzeug> pUniqueTest2 = make_unique<PKW>("Unique PKW 2", 130, 7, 70);

    // Smart Pointers (Shared)
    cout << "\n--- Smart Pointers (Shared) ---" << endl;
    shared_ptr<Fahrzeug> pSharedOriginal = make_shared<PKW>("Shared Original", 140, 8, 80);

    // Kopieren erhoeht die Anzahl der Referenzen
    shared_ptr<Fahrzeug> pSharedCopy = pSharedOriginal;

    // Test von use_count()
    // Mit Uique Pointer wuerde es nicht funktionieren, weil es immer 1 ist.
    cout << "Anzahl der Referenzen von "
         << pSharedOriginal->getName()
		 << ": "
		 << pSharedOriginal.use_count()
		 << endl;


    // Vektor mit Unique Pointers
    cout << "\n--- Vector mit Unique Pointers ---" << endl;
    vector<unique_ptr<Fahrzeug>> vpUniqueVector;
    // Nur Farhzeuge mit Unique Pointer koennen hier gespeichert werden

    // Besitz von pUniqueTest1 wird verschoben
    vpUniqueVector.push_back(std::move(pUniqueTest1));
    // Besitz von pUniqueTest2 wird verschoben
    vpUniqueVector.push_back(std::move(pUniqueTest2));
    // Die beiden Unique-Objekte werden hier zerstört
    vpUniqueVector.clear();

    // Vektor mit Shared Pointers
    cout << "\n--- Vector mit Shared Pointers ---" << endl;
    vector<shared_ptr<Fahrzeug>> vpSharedVector;
    // Nur Farhzeuge mit Shared Pointer koennen hier gespeichert werden

    shared_ptr<Fahrzeug> vpSharedVectorTestObject = make_shared<PKW>("Shared Vektor PKW", 100, 5, 50);

    // std::move uebertraegt Besitz, pSharedOriginal wird nullptr, Anzahl von Referenzen bleibt gleich
    vpSharedVector.push_back(std::move(pSharedOriginal));
    vpSharedVector.push_back(vpSharedVectorTestObject);

    cout << "Anzahl der Referenzen im Vektor [0] "
    	 << vpSharedVector[0]->getName()
		 << ": "
		 << vpSharedVector[0].use_count()
		 << endl;
    cout << "Anzahl der Referenzen im Vektor [1] "
    	 << vpSharedVector[1]->getName()
		 << ": "
		 << vpSharedVector[1].use_count()
		 << endl;

    // löscht Elemente von vorne nach hinten
    vpSharedVector.clear();

    // Sonst Program endet sich nicht
    // Überprüfung von pSharedOriginal nach move
    if (pSharedOriginal == nullptr) {
        cout << "pSharedOriginal ist nach move nullptr geworden" << endl;
    }

    cout << "Anzahl der Referenzen " << vpSharedVectorTestObject->getName() << ": " << vpSharedVectorTestObject.use_count() << endl;

}


void vAufgabe_1a(){
    // Vektor zur Speicherung Unique-Pointer
    vector<unique_ptr<Fahrzeug>> vpUniqueVector;

    const int iAnzahlFahrzeuge = 3;
    const int iAnzahlSchritte = 10;
    const double dZeittakt = 0.3;

    // Schleife fuer die Erzeugung 3 Fahrzeuge
    for (int i = 1; i < iAnzahlFahrzeuge; i++){
        string sFahrzeugsname = "";
        double sFahrzeugsMaxGeschwindigkeit = 0;

        cout << "Bitte geben Sie die Name fuer das " << i << ". neue Fahrzeug ein: ";
        cin >> sFahrzeugsname;

        // Ueberprufung richtiger Eingabe fuer maximale Geschindigkeit
        // Endlosschleife, bis eine gültige Zahl eingegeben wird
        while(true){
        	cout << "Bitte geben Sie die maximale Geschindigkeit fuer das " << i << ". neue Fahrzeug ein: ";
        	cin >> sFahrzeugsMaxGeschwindigkeit;

        	// Geschwindigkeit darf nicht negativ sein
        	if (sFahrzeugsMaxGeschwindigkeit < 0) {
        		cout << "Die Geschwindigkeit darf nicht negativ sein" << endl;
        	}
        	// Gueltige Eingabe
        	else{
        		break;
        	}
        }

        unique_ptr<Fahrzeug> pUniqueZeigerFahrzeug = make_unique<PKW>(sFahrzeugsname, sFahrzeugsMaxGeschwindigkeit, 5, 50);

        // Besitzübergabe an den Vektor
        vpUniqueVector.push_back(std::move(pUniqueZeigerFahrzeug));
    }

    // Simulation über 10 Schritte
    for (int i = 0; i < iAnzahlSchritte; i++){
        dGlobaleZeit += dZeittakt;

        // Alle Fahrzeuge simulieren
        for (auto& fahrzeug : vpUniqueVector){
            fahrzeug->vSimulieren();
        }

        // Tabelleueberschrift ausgeben
        Fahrzeug::vKopf();

        // Fahrzeugsdaten fuer alle Objekte ausgeben
        for (auto& fahrzeug : vpUniqueVector){
            cout<<endl;

            // Verwendung des überladenen Ausgabeoperators
            cout << *fahrzeug;
        }

        cout << "\nFahrzeuge wurden simuliert. Die globale Zeit ist " << dGlobaleZeit << '\n' << endl;
    }
}


void vAufgabe_2(){
	// Initialisierung von Epsilon fuer das Vergleich von doubles
	const double dEpsilon = 1e-8;

	// jede 3 Stunden tanken
	const double dTankPeriode = 3.0;

	const int dSimulationsschritte = 10;

    // Vektor für alle Fahrzeuge
	vector<unique_ptr<Fahrzeug>> vpUniqueVector;

	// Eingabe und Erzeugung der PKWs
    int iPKWAnzahl = 0;

    // Ueberprufung richtiger Eingabe fuer die Anzahl neuer PKWs
    // Endlosschleife, bis eine gültige Zahl eingegeben wird
    while(true) {
    	cout << "Bitte geben Sie die Anzahl neuer PKWs ein: ";
        cin >> iPKWAnzahl;

        // Anzahl darf nicht negativ sein
        if (iPKWAnzahl < 0) {
        	cout << "Die Anzahl darf nicht negativ sein" << endl;
        }
        // Gueltige Eingabe
        else {
            break;
        }
    }

    for (int i = 0; i < iPKWAnzahl; i++){
        vpUniqueVector.push_back(make_unique<PKW>("PKW_" + to_string(i + 1), 180.0, 30, 10));
    }

    // Eingabe und Erzeugung der Fahrraeder
    int iFahrradAnzahl = 0;

    // Ueberprufung richtiger Eingabe fuer die Anzahl neuer Fahrraeder
    // Endlosschleife, bis eine gültige Zahl eingegeben wird
    while(true) {
    	cout << "Bitte geben Sie die Anzahl neuer Fahrraeder ein: ";
        cin >> iFahrradAnzahl;

        // Anzahl darf nicht negativ sein
        if (iPKWAnzahl < 0) {
            cout << "Die Anzahl darf nicht negativ sein" << endl;
        }
        // Gueltige Eingabe
        else {
        	break;
        }
    }

    for (int i = 0; i < iFahrradAnzahl; i++){
        vpUniqueVector.push_back(make_unique<Fahrrad>("Fahrrad_" + to_string(i + 1), 25));
    }

    // Simulationseinstellungen
    double dZeittakt = 0.5;

    cout << "Bitte geben Sie den Zeittakt (in Stunden, z.B. 0.5) für die Simulation ein: ";
    cin >> dZeittakt;

    cout << "\n--- Starte Simulation über " << dSimulationsschritte << " Schritte, Zeittakt: " << dZeittakt << " h ---\n";

    // Simulationsschleife
    for (int i = 0; i < dSimulationsschritte; i++){
    	// Alte Zeit speichern für die Intervall-Berechnung
    	double dZeitVorher = dGlobaleZeit;
        dGlobaleZeit += dZeittakt;

        cout << endl;
        cout << "Schritt " << i + 1 << "; Globale Zeit: " << dGlobaleZeit << " h\n";

        for (auto& fahrzeug : vpUniqueVector) {
        	// Fahren simulieren
        	fahrzeug->vSimulieren();

        	// Prüfen, ob im aktuellen Zeitschritt eine 3-Stunden-Grenze überschritten wurde.
        	// Wenn Zeit_jetzt / 3 Z.B. eine neue Ganzzahl erreicht hat im Vergleich zu Zeit_vorher / 3
        	bool bMussTanken = floor((dGlobaleZeit - dEpsilon) / dTankPeriode) > floor((dZeitVorher - dEpsilon) / dTankPeriode);

        	if (bMussTanken) {
        		double dGetankteMenge = fahrzeug->dTanken();

        		// Wenn nur PKW getankt wurde, weil wir sonst 0 bekommen
        		if (dGetankteMenge > 0.0) {
        			cout << fahrzeug->getName() << " hat " << dGetankteMenge << " Liter getankt." << endl;
        		}
            }
        }

        // Ausgabe der Tabelle
        Fahrzeug::vKopf();
        for (auto& fahrzeug : vpUniqueVector) {
            cout<<endl;
            cout << *fahrzeug;
        }
    }
    cout << "\n\n--- Simulation abgeschlossen ---\n";
}


void vAufgabe_3() {
    // Statische Fahrzeuge
	// Wir brauchen 2 PKWs, um auch Zuweisungsoperator testen zu koennen
    PKW tStatischesPKW1("Statisches PKW 1", 200, 10);
    PKW tStatischesPKW2("Statisches PKW 2", 50, 5);

    // Simulation
    // Nur Statisches PKW 1 faehrt, damit sie unterschiedliche Strecken haben
    dGlobaleZeit = 1.0; // 1 Stunde vergeht

    // Statisches PKW 1 faehrt 200 km, beim Statischen PKW 2 bleibt 0 km
    tStatischesPKW1.vSimulieren();

    // Test Ausgabeoperator <<
    cout << "--- Test Ausgabeoperator << ---" << endl;
    Fahrzeug::vKopf();
    cout<<endl;
    cout << tStatischesPKW1 << endl;
    cout << tStatischesPKW2 << endl;

    // Test Vergleichsoperator <
    cout << "\n--- Test Vergleichsoperator < ---" << endl;
    if (tStatischesPKW2 < tStatischesPKW1) {
        cout << "Die Gesamtstrecke von " << tStatischesPKW2.getName() << " ist kleiner als die Gesamtstrecke von " << tStatischesPKW1.getName() << endl;
    } else {
    	cout << tStatischesPKW2.getName() << " ist nicht kleiner als " << tStatischesPKW1.getName() << endl;
    }

    // Test uweisungsoperator =
    cout << "\n--- Test uweisungsoperator = ---" << endl;
    tStatischesPKW2 = tStatischesPKW1;

    cout << tStatischesPKW2.getName() << " nach Zuweisung: " << endl;
    Fahrzeug::vKopf();
    cout<<endl;
    cout << tStatischesPKW2 << endl;

    // Vergleicht IDs
    if (tStatischesPKW1.getID() != tStatischesPKW2.getID()) {
        cout << "IDs sind unterschiedlich geblieben." << endl;
    } else {
        cout << "ID wurde mitkopiert. Fehler" << endl;
    }
}

void vAufgabe_4(){
	std::cout << "--- Тестирование класса Weg ---" << std::endl;

	// 1. Создаем несколько объектов дорог с разными лимитами
	Weg strasse1("A8", 50.5, Tempolimit::Autobahn);
	Weg strasse2("B10", 12.0, Tempolimit::Landstrasse);
	Weg strasse3("Hauptstrasse", 2.5, Tempolimit::Innerorts);

	// 2. Выводим заголовок таблицы (статический метод)
	Weg::vKopf();

	// 3. Выводим сами дороги с помощью оператора <<
	// Благодаря полиморфизму, вызовется Weg::vAusgeben
	cout << strasse1 << endl;
	cout << strasse2 << endl;
	cout << strasse3 << endl;

	std::cout << "\n--- Проверка старого функционала (Fahrzeug) ---" << std::endl;

	// 4. Проверяем, что старый вывод машин всё еще работает
	Fahrzeug::vKopf();
	Fahrzeug f1("Audi", 200);
	cout << f1 << endl;
}

void vAufgabe_5() {
    // Weg erstellen
    Weg pWeg("Weg 1", 50.5, Tempolimit::Landstrasse);

    // Fahrzeuge erstellen
    unique_ptr<Fahrzeug> pPKW1 = std::make_unique<PKW>("PKW 1", 120, 10);
    unique_ptr<Fahrzeug> pPKW2 = std::make_unique<PKW>("PKW 2", 100, 8);
    unique_ptr<Fahrzeug> pFahrrad = std::make_unique<Fahrrad>("Fahhrad", 30);

    // Fahrzeuge auf den Weg setzen
    pWeg.vAnnahme(std::move(pPKW1), 0.3);
    pWeg.vAnnahme(std::move(pPKW2));
    pWeg.vAnnahme(std::move(pFahrrad));

    // Tabellenkopf ausgeben
    Weg::vKopf();

    double dZeitschritt = 0.1;

    // Simulationsschleife
    for (int i = 0; i < 20; ++i) {
        dGlobaleZeit += dZeitschritt;
        pWeg.vSimulieren();
        cout << pWeg << endl;
    }
}

void vAufgabe_6() {
    // Grafik initialisieren
    bInitialisiereGrafik(800, 500);

    // Wege erstellen
    auto pWeg1 = std::make_shared<Weg>("Weg_Hin", 500.0, Tempolimit::Autobahn);
    auto pWeg2 = std::make_shared<Weg>("Weg_Rueck", 500.0, Tempolimit::Autobahn);

    // Straße zeichnen
    int coords[] = { 100, 250, 700, 250 };
    bZeichneStrasse(pWeg1->getName(), pWeg2->getName(), 500, 2, coords);

    // Fahrzeuge erstellen
    auto pPKW1 = std::make_unique<PKW>("Schoeller_PKW", 300.0, 10.0, 100.0);
    auto pPKW2 = std::make_unique<PKW>("Park_PKW", 150.0, 8.0, 100.0);
    auto pFahrrad = std::make_unique<Fahrzeug>("Fahrrad", 25.0);

    // Fahrzeuge auf Wege verteilen
    pWeg1->vAnnahme(std::move(pPKW1));
    pWeg2->vAnnahme(std::move(pPKW2), 2.0); // Startet erst nach 2 Stunden
    pWeg1->vAnnahme(std::move(pFahrrad));

    // Simulationsschleife
    double dZeitschritt = 0.1;

    while (dGlobaleZeit < 10.0) {
        dGlobaleZeit += dZeitschritt;
        vSetzeZeit(dGlobaleZeit); // Zeit im Fenster anzeigen

        // Simulation
        pWeg1->vSimulieren();
        pWeg2->vSimulieren();

        // Zeichnen
        pWeg1->vZeichnen();
        pWeg2->vZeichnen();

        vSleep(100);
    }

    vBeendeGrafik();
}

void vAufgabe_6a() {
    vertagt::VListe<int> Liste;

    static std::mt19937 device(0);
    std::uniform_int_distribution<int> dist(1, 10);

    // Liste mit Zufallszahlen füllen
    for (int i = 0; i < 10; i++) {
        int zuf = dist(device);
        Liste.push_back(zuf);
    }
    Liste.vAktualisieren();

    cout << "Meine Liste: ";
    for (auto it = Liste.begin(); it != Liste.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    // Elemente > 5 löschen
    for (auto it = Liste.begin(); it != Liste.end(); ++it) {
        if (*it > 5) {
            Liste.erase(it);
        }
    }

    cout << "Meine Liste nach dem Erase: ";
    for (auto it = Liste.begin(); it != Liste.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    Liste.vAktualisieren();

    cout << "Meine Liste nach dem Aktualisieren: ";
    for (auto it = Liste.begin(); it != Liste.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    // Elemente vorne und hinten hinzufügen
    for (int i = 0; i < 2; i++) {
        int zuf1 = dist(device);
        Liste.push_back(zuf1);
        int zuf2 = dist(device);
        Liste.push_front(zuf2);
    }

    Liste.vAktualisieren();

    cout << "Meine Liste nach dem PushFront(2x) und PushBack(2x): ";
    for (auto it = Liste.begin(); it != Liste.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
}

void vAufgabe_7() {
    // Grafik initialisieren (Großes Fenster für die Karte)
    bInitialisiereGrafik(1000, 600);

    // Kreuzungen erstellen
    auto pKr1 = make_shared<Kreuzung>("Kr1", 0);
    auto pKr2 = make_shared<Kreuzung>("Kr2", 0);
    auto pKr3 = make_shared<Kreuzung>("Kr3", 0);
    auto pKr4 = make_shared<Kreuzung>("Kr4", 0);

    // Tankstelle bei Kr2 setzen
    pKr2->setTankstelle(1000);

    // Straßen verbinden (Hin- und Rückweg)
    Kreuzung::vVerbinde(pKr1, pKr2, "W12", "W21", 40, Tempolimit::Innerorts);
    Kreuzung::vVerbinde(pKr2, pKr3, "W23a", "W32a", 115, Tempolimit::Autobahn);
    Kreuzung::vVerbinde(pKr2, pKr3, "W23b", "W32b", 40, Tempolimit::Innerorts);
    Kreuzung::vVerbinde(pKr2, pKr4, "W24", "W42", 55, Tempolimit::Innerorts);
    Kreuzung::vVerbinde(pKr3, pKr4, "W34", "W43", 85, Tempolimit::Autobahn);
    Kreuzung::vVerbinde(pKr4, pKr1, "W44a", "W44b", 130, Tempolimit::Landstrasse);

    // Statische Elemente zeichnen (Kreuzungen)
    bZeichneKreuzung(680, 40);  // Kr1
    bZeichneKreuzung(680, 300); // Kr2
    bZeichneKreuzung(680, 570); // Kr3
    bZeichneKreuzung(320, 300); // Kr4

    // Straßen zeichnen (Koordinaten)
    int k1[] = {680, 40, 680, 300};
    bZeichneStrasse("W12", "W21", 40, 2, k1);

    int k2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
    bZeichneStrasse("W23a", "W32a", 115, 6, k2);

    int k3[] = {680, 300, 680, 570};
    bZeichneStrasse("W23b", "W32b", 40, 2, k3);

    int k4[] = {680, 300, 320, 300};
    bZeichneStrasse("W24", "W42", 55, 2, k4);

    int k5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
    bZeichneStrasse("W34", "W43", 85, 5, k5);

    int k6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 680, 40};
    bZeichneStrasse("W44a", "W44b", 130, 7, k6);

    // Fahrzeuge erstellen
    auto p1 = make_unique<PKW>("Audi", 100, 10, 50);
    auto p2 = make_unique<PKW>("BMW", 120, 12, 60);
    auto b1 = make_unique<Fahrrad>("BMX", 25);

    // Start-Fahrzeuge annehmen (zeitversetzt)
    pKr1->vAnnahme(std::move(p1), 0.5);
    pKr1->vAnnahme(std::move(p2), 1.5);
    pKr1->vAnnahme(std::move(b1), 2.5);

    // Hauptschleife der Simulation
    dGlobaleZeit = 0.0;

    while (true) {
        dGlobaleZeit += 0.1;
        vSetzeZeit(dGlobaleZeit);

        // Simulation der Kreuzungen
        pKr1->vSimulieren();
        pKr2->vSimulieren();
        pKr3->vSimulieren();
        pKr4->vSimulieren();

        // Zeichnen
        pKr1->vZeichnen();
        pKr2->vZeichnen();
        pKr3->vZeichnen();
        pKr4->vZeichnen();

        vSleep(100);
    }
}

int main() {
    vAufgabe_7();
    return 0;
}
