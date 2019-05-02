#pragma once
#include "Kriterium.h"
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"

class KOdovzdaneObalky : Kriterium<unsigned int, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	void setKolo(unsigned int parm) {
		kolo = parm;
	}
	//neviem ci sa ma tu rozhodovat na zaklade kola, alebo niekde vyssie 
	unsigned int evaluate(MultiWayTreeNode<UzemnaJednotka*>* nieco) {
		if (kolo == 1)
		{
			return nieco->accessData()->pocetOdoObalok;
		}
		else if (kolo == 2)
		{
			return nieco->accessData()->getPocetOdoObalok2();
		}
		else if (kolo == 3)
		{
			return nieco->accessData()->pocetVydObalok + nieco->accessData()->getPocetVydObalok2();
		}
		else
		{
			//preco mi to nebere cout???? 
			//std::cout << "Nezadal si dedinu v kriteriu Kprislusnostobce" << std::endl;
			return -1;
		}
	}
private:
	int kolo = 0;

};