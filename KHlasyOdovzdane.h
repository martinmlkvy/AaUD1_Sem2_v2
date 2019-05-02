#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"
#include "multi_way_tree.h"
#include "Kandidat.h"

class KHlasyOdovzdane : Kriterium <unsigned int, MultiWayTreeNode<UzemnaJednotka*>*>
{
private:
	int kolo;
	int kandidat;

public:
	void setKolo(unsigned int parm) {
		kolo = parm;
	}
	void setKandidat(int parm) {
		  kandidat = parm;
	}

	unsigned int evaluate(MultiWayTreeNode<UzemnaJednotka*>* parm) {
		if (kolo == 1)
		{
			return parm->accessData()->kandidatiPrve->operator[](kandidat).pocetHlasov;
		}
		else if (kolo == 2)
		{
			return parm->accessData()->kandidatiDruhe->operator[](kandidat).pocetHlasov;
		}
		else if (kolo == 3)
		{
			return parm->accessData()->kandidatiDruhe->operator[](kandidat).pocetHlasov + parm->accessData()->kandidatiPrve->operator[](kandidat).pocetHlasov;
		}
		else
		{
			//preco mi to nebere cout???? 
			//std::cout << "Nezadal si dedinu v kriteriu Kprislusnostobce" << std::endl;
			return -1;
		}
	}
};


