#pragma once
#include "Array.h"
#include "Kandidat.h"
#include <string>

enum Jednotka { STAT, KRAJ, OKRES, DEDINA };

class UzemnaJednotka
{
private:
	int kolo2;
	int kod2;
	std::string nazov2;
	int unsigned pocetZapisanychVolicov2;
	int pocetVydObalok2;
	int pocetOdoObalok2;
	double ucastPerc2;
	double pocetPlatnychHlasovPerc2;
	Jednotka uJednotka2;
public:
	UzemnaJednotka(int pKod, std::string pNazov, int pocetZVolicov, int pocetVObalok,
		double pUcastPerc, int pocetOObalok, double pocetPHAllPerc, Jednotka parm, int pkolo) :
		kod(pKod), nazov(pNazov), pocetZapisanychVolicov(pocetZVolicov), pocetVydObalok(pocetVObalok), ucastPerc(pUcastPerc),
		pocetOdoObalok(pocetOObalok), pocetPlatnychHlasovPerc(pocetPHAllPerc), uJednotka(parm), kolo(pkolo) {
		(*kandidatiPrve)[0].meno = "Bela Bugar";
		(*kandidatiPrve)[1].meno = "Zuzana Caputova";
		(*kandidatiPrve)[2].meno = "Martin Dano";
		(*kandidatiPrve)[3].meno = "Stefan Harabin";
		(*kandidatiPrve)[4].meno = "Eduard Chmelar";
		(*kandidatiPrve)[5].meno = "Marian Kotleba;";
		(*kandidatiPrve)[6].meno = "Milan Krajniak";
		(*kandidatiPrve)[7].meno = "Jozsef Menyhart";
		(*kandidatiPrve)[8].meno = "Frantisek Miklosko";
		(*kandidatiPrve)[9].meno = "Robert Mistrik";
		(*kandidatiPrve)[10].meno = "Maros Sefcovic";
		(*kandidatiPrve)[11].meno = "Robert Svec";
		(*kandidatiPrve)[12].meno = "Bohumila Tauchmannova";
		(*kandidatiPrve)[13].meno = "Juraj Zabojnik";
		(*kandidatiPrve)[14].meno = "Ivan Zuzula";
		(*kandidatiDruhe)[0].meno = "Zuzana Caputova";
		(*kandidatiDruhe)[1].meno = "Maros Sefcovic";
	}
	~UzemnaJednotka() {
		//delete kandidatiPrve;
		//delete kandidatiDruhe;
		//kandidatiPrve = nullptr;
		//kandidatiDruhe = nullptr;
	}

	const int kolo;
	const int kod;
	const std::string nazov;
	const unsigned int pocetZapisanychVolicov;
	const int pocetVydObalok;
	const int pocetOdoObalok;
	const double ucastPerc;
	const double pocetPlatnychHlasovPerc;
	const Jednotka uJednotka;
	Array<Kandidat>* kandidatiPrve = new Array<Kandidat>(15);
	Array<Kandidat>* kandidatiDruhe = new Array<Kandidat>(2);

	void setAtributy2Kola(int pKod, std::string pNazov, int pocetZVolicov, int pocetVObalok,
		double pUcastPerc, int pocetOObalok, double pocetPHAllPerc, Jednotka parm, int pkolo) {
		kod2 = pKod;
		nazov2 = pNazov;
		pocetZapisanychVolicov2 = pocetZVolicov;
		pocetVydObalok2 = pocetVObalok;
		pocetOdoObalok2 = pocetOObalok;
		ucastPerc2 = pUcastPerc;
		pocetPlatnychHlasovPerc2 = pocetPHAllPerc;
		uJednotka2 = parm;
		kolo2 = pkolo;
	}

	std::string toStringFilterNazov() {
		return "Nazov: " + std::to_string(kod) + " " + nazov +
			"\n\t" + "Pocet volicov kolo1: " + std::to_string(pocetZapisanychVolicov) +
			"\tkolo2: " + std::to_string(pocetZapisanychVolicov2) + "\n\t"
			+ "Vydane obalky kolo1: " + std::to_string(pocetVydObalok) +
			"\tkolo2: " + std::to_string(pocetVydObalok2) + "\n\t" +
			"Ucast kolo1: " + std::to_string(ucastPerc) + "\t\tkolo2: " +
			std::to_string(ucastPerc2) + "\n\tOdovzdane obalky kolo1: " +
			std::to_string(pocetOdoObalok) + "\tkolo2: " + std::to_string(pocetOdoObalok2);
	}

	std::string toStringFilterPrve() {
		return "Nazov: " + std::to_string(kod) + " " + nazov +
			"\n\t" + "Pocet volicov kolo1: " + std::to_string(pocetZapisanychVolicov) +"\n\t"
			+ "Vydane obalky kolo1: " + std::to_string(pocetVydObalok) +"\n\t" +
			"Ucast kolo1: " + std::to_string(ucastPerc) + "\n\tOdovzdane obalky kolo1: " +
			std::to_string(pocetOdoObalok);
	}

	std::string toStringFilterDruhe() {
		return "Nazov: " + std::to_string(kod) + " " + nazov +
			"\n\t" + "Pocet volicov kolo2: " + std::to_string(pocetZapisanychVolicov2) + "\n\t"
			+ "Vydane obalky kolo2: " + std::to_string(pocetVydObalok2) + "\n\t" +
			"Ucast kolo2: " + std::to_string(ucastPerc2) + "\n\tOdovzdane obalky kolo2: " +
			std::to_string(pocetOdoObalok2);
	}

	int getKolo2() { return kolo2; }
	int getKod2() { return kod2; }
	std::string getNazo2() { return nazov2; }
	int getPocetZapisanychVolicov2() { return pocetZapisanychVolicov2; }
	int getPocetVydObalok2() { return pocetVydObalok2; }
	int getPocetOdoObalok2() { return pocetOdoObalok2; }
	double getUcastPerc2() { return ucastPerc2; }
	double getPocetPlatnychHlasovPerc2() { return pocetPlatnychHlasovPerc2; }
	Jednotka getUJednotka2() { return uJednotka2; }


};