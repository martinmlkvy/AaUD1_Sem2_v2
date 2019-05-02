#pragma once
#include "Kandidat.h"
#include "UzemnaJednotka.h"
#include "multi_way_tree.h"
#include "Kriterium.h"
#include "Array.h"

class KHlasyZiskane : Kriterium<unsigned int, unsigned int>
{
private:
	int kolo;
	MultiWayTreeNode<UzemnaJednotka*>* jednotka;
public:
	void setKolo(int parm) {
		kolo = parm;
	}
	void setKandidat(MultiWayTreeNode<UzemnaJednotka*>* nieco) {
		jednotka = nieco;
	}

	unsigned int evaluate(unsigned int kandidat) {
		if (kolo == 1)
		{
			return jednotka->accessData()->kandidatiPrve->operator[](kandidat).pocetHlasov;
		}
		else if (kolo == 2)
		{
			return jednotka->accessData()->kandidatiDruhe->operator[](kandidat).pocetHlasov;
		}
		else if (kolo == 3)
		{
			return jednotka->accessData()->kandidatiPrve->operator[](kandidat).pocetHlasov +
				jednotka->accessData()->kandidatiDruhe->operator[](kandidat).pocetHlasov;
		}
		else
		{
			return -1;
		}
	}
};