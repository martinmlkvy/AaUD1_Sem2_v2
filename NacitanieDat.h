#pragma once
#include "array_list.h"
#include "UzemnaJednotka.h"
#include "sorted_sequence_table.h"
#include "unsorted_sequence_table.h"
#include "multi_way_tree.h"
#include "tree.h"
#include "Array.h"
#include "FNazov.h"
#include "KNazov.h"
#include "FVolici.h"
#include "KVolici.h"
#include "KUcast.h"
#include "FUcast.h"
#include <string>
#include <fstream>
#include <iostream>

#define CESTA_KRAJE1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab02a.csv"
#define CESTA_OKRES1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab02c.csv"
#define CESTA_DEDINY1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab02d.csv"
#define CESTA_KRAJE2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab02a.csv"
#define CESTA_OKRES2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab02c.csv"
#define CESTA_DEDINY2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab02d.csv"

#define CESTA_KRAJ_KAN1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab03b.csv"
#define CESTA_OKRES_KAN1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab03d.csv"
#define CESTA_DEDINA_KAN1 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\1. kolo\\PRE_2019_KOLO1_tab03e.csv"
#define CESTA_KRAJ_KAN2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab03b.csv"
#define CESTA_OKRES_KAN2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab03d.csv"
#define CESTA_DEDINA_KAN2 "c:\\Users\\Martin\\Desktop\\AaUD1_SEM_cdssubory\\2. kolo\\PRE_2019_KOLO2_tab03e.csv"

class NacitanieDat
{
private:
	MultiWayTree<UzemnaJednotka*>* stromUzeJednotiek;
public:
	SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* tabulkaKraje;
	SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* tabulkaOkres;
	SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* tabulkaDedina;
	UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* neuTabulkaKraje;
	UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* neuTabulkaOkresy;
	UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>* neuTabulkaDediny;

	NacitanieDat() : stromUzeJednotiek(new MultiWayTree<UzemnaJednotka*>()),
		tabulkaKraje(new SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()),
		tabulkaOkres(new SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()),
		tabulkaDedina(new SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()),
		neuTabulkaKraje(new UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()),
		neuTabulkaOkresy(new UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()),
		neuTabulkaDediny(new UnsortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*>()) {};

	~NacitanieDat() {
		for (auto item : *stromUzeJednotiek)
		{
			delete item;
		}
		delete tabulkaKraje;
		delete tabulkaOkres;
		delete tabulkaDedina;
		delete stromUzeJednotiek;
		delete neuTabulkaDediny;
		delete neuTabulkaOkresy;
		delete neuTabulkaKraje;
		neuTabulkaDediny = nullptr;
		neuTabulkaKraje = nullptr;
		neuTabulkaOkresy = nullptr;
		stromUzeJednotiek = nullptr;
		tabulkaKraje = nullptr;
		tabulkaOkres = nullptr;
		tabulkaDedina = nullptr;
	};

	void nacitajData(int kolo) {
		MultiWayTreeNode<UzemnaJednotka*>* slovensko = new MultiWayTreeNode<UzemnaJednotka*>
			(new UzemnaJednotka(1, "slovenkso", 2, 3, 4.0, 5, 6.0, STAT, kolo));
		stromUzeJednotiek->replaceRoot(slovensko);
		int krokovac = 0;
		int pocitadlo = 0;
		int krokovacOkres = 0;
		bool prve = true;
		std::string riadok;
		int pomocna;
		std::string nieco;
		std::string cestaKraj;
		std::string cestaOkres;
		std::string cestaDedina;
		if (kolo == 1)
			cestaKraj = CESTA_KRAJE1,
			cestaOkres = CESTA_OKRES1,
			cestaDedina = CESTA_DEDINY1;
		else
			cestaKraj = CESTA_KRAJE2,
			cestaOkres = CESTA_OKRES2,
			cestaDedina = CESTA_DEDINY2;

		int kod;
		std::string nazov;
		int pocetZapVol;
		int pocetVydOba;
		double ucastVolicovPerc;
		int pocetOdoOba;
		double platneHlasyPerc;

		std::ifstream nacitajKraje(cestaKraj, std::ifstream::in);
		while (!nacitajKraje.eof())
		{
			switch (pocitadlo)
			{
			case 0:
				if (prve)
				{
					getline(nacitajKraje, nieco, ';');
					std::rotate(nieco.begin(), nieco.begin() + 3, nieco.end());
					nieco.resize(1);
					kod = std::stoi(nieco);
					prve = false;
				}
				else
				{
					getline(nacitajKraje, nieco, ';');
					kod = std::stoi(nieco);
				}
				break;

			case 1:
				getline(nacitajKraje, nazov, ';');
				break;

			case 2:
				getline(nacitajKraje, nieco, ';');
				pocetZapVol = std::stoi(nieco);
				break;

			case 3:
				getline(nacitajKraje, nieco, ';');
				pocetVydOba = std::stoi(nieco);
				break;

			case 4:
				getline(nacitajKraje, nieco, ';');
				ucastVolicovPerc = std::stod(nieco);
				break;

			case 5:
				getline(nacitajKraje, nieco, ';');
				pocetOdoOba = std::stoi(nieco);
				break;

			case 6:
				getline(nacitajKraje, nieco, '\n');
				platneHlasyPerc = std::stod(nieco);
				pocitadlo = -1;
				break;

			default:
				getline(nacitajKraje, nieco, ';');
				break;
			}
			if (pocitadlo == -1)
			{
				if (kolo == 1)
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					nieco = dynamic_cast<MultiWayTreeNode<UzemnaJednotka*>*>(stromUzeJednotiek->createTreeNodeInstance());
					nieco = new MultiWayTreeNode<UzemnaJednotka*>(new UzemnaJednotka(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, KRAJ, kolo));
					stromUzeJednotiek->getRoot()->insertSon(nieco, krokovac);
					tabulkaKraje->insert(kod, nieco);
				}
				else
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					tabulkaKraje->tryFind(kod, nieco);
					nieco->accessData()->setAtributy2Kola(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, KRAJ, kolo);
					//nemusim to menit aj v tabulke, lebo ta obsahuje iba pointre na te node a ked to zmenim v strome => hotovo aspon myslim :D 
				}
				krokovac++;
			}
			pocitadlo++;
		}
		nacitajKraje.close();

		//NACITANIE OKRESOV
		pocitadlo = 0;
		krokovac = 0;
		prve = true;
		std::ifstream nacitajOkres(cestaOkres, std::ifstream::in);
		while (!nacitajOkres.eof())
		{
			switch (pocitadlo)
			{
			case 0:
				if (prve)
				{
					getline(nacitajOkres, nieco, ';');
					std::rotate(nieco.begin(), nieco.begin() + 3, nieco.end());
					nieco.resize(1);
					pomocna = std::stoi(nieco);
					prve = false;
				}
				else
				{
					getline(nacitajOkres, nieco, ';');
					int prem = std::stoi(nieco);
					if (prem != pomocna)
					{
						krokovac = 0;
					}
					pomocna = std::stoi(nieco);
				}
				break;

			case 4:
				getline(nacitajOkres, nieco, ';');
				kod = std::stoi(nieco);
				break;

			case 5:
				getline(nacitajOkres, nazov, ';');
				break;

			case 7:
				getline(nacitajOkres, nieco, ';');
				pocetZapVol = std::stoi(nieco);
				break;

			case 8:
				getline(nacitajOkres, nieco, ';');
				pocetVydOba = std::stoi(nieco);
				break;

			case 9:
				getline(nacitajOkres, nieco, ';');
				ucastVolicovPerc = std::stod(nieco);
				break;

			case 10:
				getline(nacitajOkres, nieco, ';');
				pocetOdoOba = std::stoi(nieco);
				break;

			case 13:
				getline(nacitajOkres, nieco, '\n');
				platneHlasyPerc = std::stod(nieco);
				pocitadlo = -1;
				break;

			default:
				getline(nacitajOkres, nieco, ';');
				break;
			}
			if (pocitadlo == -1)
			{
				if (kolo == 1)
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					nieco = dynamic_cast<MultiWayTreeNode<UzemnaJednotka*>*>(stromUzeJednotiek->createTreeNodeInstance());
					nieco = new MultiWayTreeNode<UzemnaJednotka*>(new UzemnaJednotka(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, OKRES, kolo));
					stromUzeJednotiek->getRoot()->getSon(pomocna - 1)->insertSon(nieco, krokovac);
					tabulkaOkres->insert(kod, nieco);
				}
				else
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					tabulkaOkres->tryFind(kod, nieco);
					nieco->accessData()->setAtributy2Kola(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, OKRES, kolo);
				}
				krokovac++;
			}
			pocitadlo++;
		}
		nacitajOkres.close();

		//NACITAJ OBCE
		pocitadlo = 0;
		int krokovacObce = 0;
		int krokovacOkres1 = 0;
		int prem = 101;
		prve = true;
		std::ifstream nacitajDediny(cestaDedina, std::ifstream::in);
		while (!nacitajDediny.eof())
		{
			switch (pocitadlo)
			{
			case 0:
				if (prve)
				{
					getline(nacitajDediny, nieco, ';');
					std::rotate(nieco.begin(), nieco.begin() + 3, nieco.end());
					nieco.resize(1);
					pomocna = std::stoi(nieco);
					prve = false;
				}
				else
				{
					getline(nacitajDediny, nieco, ';');
					int prem = std::stoi(nieco);
					if (prem != pomocna)
					{
						krokovacOkres1 = -1;
					}
					pomocna = std::stoi(nieco);
				}
				break;

			case 4:
				getline(nacitajDediny, nieco, ';');
				krokovacOkres = std::stoi(nieco);
				if (prem != krokovacOkres)
				{
					prem = krokovacOkres;
					krokovacOkres1++;
					krokovacObce = 0;
				}
				break;

			case 6:
				getline(nacitajDediny, nieco, ';');
				kod = std::stoi(nieco);
				break;

			case 7:
				getline(nacitajDediny, nazov, ';');
				break;

			case 9:
				getline(nacitajDediny, nieco, ';');
				pocetZapVol = std::stoi(nieco);
				break;

			case 10:
				getline(nacitajDediny, nieco, ';');
				pocetVydOba = std::stoi(nieco);
				break;

			case 11:
				getline(nacitajDediny, nieco, ';');
				ucastVolicovPerc = std::stod(nieco);
				break;

			case 12:
				getline(nacitajDediny, nieco, ';');
				pocetOdoOba = std::stoi(nieco);
				break;

			case 15:
				getline(nacitajDediny, nieco, '\n');
				platneHlasyPerc = std::stod(nieco);
				pocitadlo = -1;
				break;

			default:
				getline(nacitajDediny, nieco, ';');
				break;
			}
			if (pocitadlo == -1)
			{
				if (kolo == 1)
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					nieco = dynamic_cast<MultiWayTreeNode<UzemnaJednotka*>*>(stromUzeJednotiek->createTreeNodeInstance());
					nieco = new MultiWayTreeNode<UzemnaJednotka*>(new UzemnaJednotka(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, DEDINA, kolo));
					stromUzeJednotiek->getRoot()->getSon(pomocna - 1)->getSon(krokovacOkres1)->insertSon(nieco, krokovacObce);
					tabulkaDedina->insert(kod, nieco);
				}
				else
				{
					MultiWayTreeNode<UzemnaJednotka*>* nieco;
					tabulkaDedina->tryFind(kod, nieco);
					nieco->accessData()->setAtributy2Kola(kod, nazov, pocetZapVol, pocetVydOba, ucastVolicovPerc, pocetOdoOba, platneHlasyPerc, DEDINA, kolo);
				}
				krokovacObce++;
			}
			pocitadlo++;
		}
		nacitajDediny.close();
	};

	void nacitajKandidatov(int kolo) {		

		std::string cestaKraj;
		std::string cestaOkres;
		std::string cestaDedina;
		if (kolo == 1)
			cestaKraj = CESTA_KRAJ_KAN1,
			cestaOkres = CESTA_OKRES_KAN1,
			cestaDedina = CESTA_DEDINA_KAN1;
		else
			cestaKraj = CESTA_KRAJ_KAN2,
			cestaOkres = CESTA_OKRES_KAN2,
			cestaDedina = CESTA_DEDINA_KAN2;

		std::string nieco;
		bool prvy = true;
		int kodKraju;
		int kanditat1;

		MultiWayTreeNode<UzemnaJednotka*>* pomocnaUzemnaJedno;
		std::ifstream nacitajKraje(cestaKraj, std::ifstream::in);
		while (!nacitajKraje.eof())
		{
			if (kolo == 1)
			{
				if (prvy)
				{
					getline(nacitajKraje, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajKraje, nieco, ';');
					kodKraju = std::stoi(nieco);
				}
				tabulkaKraje->tryFind(kodKraju, pomocnaUzemnaJedno);

				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](1).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](2).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](3).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](4).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](5).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](6).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](7).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](8).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](9).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](10).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](11).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](12).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](13).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](14).pocetHlasov = kanditat1;
			}
			else
			{
				if (prvy)
				{
					getline(nacitajKraje, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajKraje, nieco, ';');
					kodKraju = std::stoi(nieco);
				}
				tabulkaKraje->tryFind(kodKraju, pomocnaUzemnaJedno);

				getline(nacitajKraje, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajKraje, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](1).pocetHlasov = kanditat1;
			}
		}
		nacitajKraje.close();

		int krokovacOkresu;
		int kodOkresu;
		int predchadzajuciOkres = 0;
		prvy = true;
		std::ifstream nacitajOkresy(cestaOkres, std::ifstream::in);
		while (!nacitajOkresy.eof())
		{
			if (kolo == 1)
			{
				if (prvy)
				{
					getline(nacitajOkresy, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajOkresy, nieco, ';');
					kodKraju = std::stoi(nieco);
				}

				getline(nacitajOkresy, nieco, ';');
				kodOkresu = std::stoi(nieco);
				if (kodOkresu != predchadzajuciOkres)
				{
					tabulkaOkres->tryFind(kodOkresu, pomocnaUzemnaJedno);
				}

				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](1).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](2).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](3).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](4).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](5).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](6).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](7).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](8).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](9).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](10).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](11).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](12).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](13).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](14).pocetHlasov = kanditat1;
			}
			else
			{
				if (prvy)
				{
					getline(nacitajOkresy, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajOkresy, nieco, ';');
					kodKraju = std::stoi(nieco);
				}

				getline(nacitajOkresy, nieco, ';');
				kodOkresu = std::stoi(nieco);
				if (kodOkresu != predchadzajuciOkres)
				{
					tabulkaOkres->tryFind(kodOkresu, pomocnaUzemnaJedno);
				}

				getline(nacitajOkresy, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajOkresy, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](1).pocetHlasov = kanditat1;
			}
		}
		nacitajOkresy.close();

		prvy = true;
		std::ifstream nacitajDediny(cestaDedina, std::ifstream::in);
		while (!nacitajDediny.eof())
		{
			if (kolo == 1)
			{
				if (prvy)
				{
					getline(nacitajDediny, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajDediny, nieco, ';');
					kodKraju = std::stoi(nieco);
				}
				tabulkaDedina->tryFind(kodKraju, pomocnaUzemnaJedno);

				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](1).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](2).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](3).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](4).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](5).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](6).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](7).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](8).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](9).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](10).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](11).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](12).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](13).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiPrve->operator[](14).pocetHlasov = kanditat1;
			}
			else
			{
				if (prvy)
				{
					getline(nacitajDediny, nieco, ';');
					nieco.erase(0, 3);
					kodKraju = std::stoi(nieco);
					prvy = false;
				}
				else
				{
					getline(nacitajDediny, nieco, ';');
					kodKraju = std::stoi(nieco);
				}
				tabulkaDedina->tryFind(kodKraju, pomocnaUzemnaJedno);

				getline(nacitajDediny, nieco, ';');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](0).pocetHlasov = kanditat1;
				getline(nacitajDediny, nieco, '\n');
				kanditat1 = std::stoi(nieco);
				pomocnaUzemnaJedno->accessData()->kandidatiDruhe->operator[](1).pocetHlasov = kanditat1;
			}
		}
		nacitajDediny.close();
	};

	void vypisKraje() {

		for (auto item : *stromUzeJednotiek)
		{
			if (item->uJednotka == KRAJ)
			{
				std::cout << item->nazov << std::endl;
				std::cout << item->kod << std::endl;
			}
			if (item->uJednotka == OKRES)
			{
				std::cout << "\t" << item->nazov << std::endl;
				std::cout << "\t" << item->kod << std::endl;
			}
			if (item->uJednotka == DEDINA)
			{
				std::cout << "\t\t" << item->nazov << std::endl;
				std::cout << "\t\t" << item->kod << std::endl;
			}
		}
	};

	void vypisInfoOJednotkachNazov(std::string kodJednotky, Jednotka enumcek) {

		KNazov kriterium;
		FNazov* filter = new FNazov(kodJednotky);
		UzemnaJednotka* jednotka;
		SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*> tabulka;
		if (enumcek == DEDINA)
		{
			tabulka = *tabulkaDedina;
		}
		else if (enumcek == OKRES)
		{
			tabulka = *tabulkaOkres;
		}
		else if (enumcek == KRAJ)
		{
			tabulka = *tabulkaKraje;
		}
		else
		{
			throw std::logic_error("Zadal si zly enum!");
		}
		for (auto item : tabulka)
		{
			bool nieco = filter->evaulate(item->accessData(), &kriterium);
			if (nieco)
			{
				std::cout << item->accessData()->accessData()->toStringFilterNazov() << std::endl;
			}
		}
		delete filter;
		filter = nullptr;
	}

	void vypisInfoOJednotkachVolici(unsigned int dolne, unsigned  int horne, Jednotka enumcek) {
		FVolici* filter = new FVolici(dolne, horne);
		KVolici kriterium;
		UzemnaJednotka* jednotka;
		SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*> tabulka;
		if (enumcek == DEDINA)
		{
			tabulka = *tabulkaDedina;
		}
		else if (enumcek == OKRES)
		{
			tabulka = *tabulkaOkres;
		}
		else if (enumcek == KRAJ)
		{
			tabulka = *tabulkaKraje;
		}
		else
		{
			throw std::logic_error("Zadal si zly enum!");
		}
		for (auto item : tabulka)
		{
			kriterium.setKolo(1);
			bool nieco = filter->evaulate(item->accessData(), &kriterium);
			if (nieco)
			{
				std::cout << item->accessData()->accessData()->toStringFilterPrve() << std::endl;
			}

			kriterium.setKolo(2);
			nieco = filter->evaulate(item->accessData(), &kriterium);
			if (nieco)
			{
				std::cout << item->accessData()->accessData()->toStringFilterDruhe() << std::endl;
			}
		}
		delete filter;
		filter = nullptr;
	}

	void vypisInfoOJednotkachUcast(double dolne, double horne, Jednotka enumcek) {
		FUcast* filter = new FUcast(dolne, horne);
		KUcast kriterium;
		UzemnaJednotka* jednotka;
		SortedSequenceTable<int, MultiWayTreeNode<UzemnaJednotka*>*> tabulka;

		if (enumcek == DEDINA)
		{
			tabulka = *tabulkaDedina;
		}
		else if (enumcek == OKRES)
		{
			tabulka = *tabulkaOkres;
		}
		else if (enumcek == KRAJ)
		{
			tabulka = *tabulkaKraje;
		}
		else
		{
			throw std::logic_error("Zadal si zly enum!");
		}
		for (auto item : tabulka)
		{
			kriterium.setKolo(1);
			bool nieco = filter->evaulate(item->accessData(), &kriterium);
			if (nieco)
			{
				std::cout << item->accessData()->accessData()->toStringFilterPrve() << std::endl;
			}

			kriterium.setKolo(2);
			nieco = filter->evaulate(item->accessData(), &kriterium);
			if (nieco)
			{
				std::cout << item->accessData()->accessData()->toStringFilterDruhe() << std::endl;
			}
		}
		delete filter;
		filter = nullptr;
	}
};