#pragma once
#include "Kriterium.h"
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"

class KUcast : public Kriterium<double, MultiWayTreeNode<UzemnaJednotka*>*>
{
private:
	int kolo = 0;
public:
	void setKolo(unsigned int parm) {
		kolo = parm;
	}
	//neviem ci sa ma tu rozhodovat na zaklade kola, alebo niekde vyssie 
	double evaluate(MultiWayTreeNode<UzemnaJednotka*>* nieco) {
		if (kolo == 1)
		{
			return nieco->accessData()->ucastPerc;
		}
		else if (kolo == 2)
		{
			return nieco->accessData()->getUcastPerc2();
		}
		else
		{
			return -1.0;
		}
	}
};