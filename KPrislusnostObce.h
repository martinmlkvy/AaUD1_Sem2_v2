#pragma once
#include "UzemnaJednotka.h"
#include "Kriterium.h"
#include "multi_way_tree.h"
#include <string>
//vracia ci ta dedina patri do urciteho kraju alebo okresu

class KPrislusnostObce : Kriterium< bool, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	void setVyssiCelok(int parm) {
		vysCelok = parm;
	}
	bool evaluate(MultiWayTreeNode<UzemnaJednotka*>* t) override {
		if (t->accessData()->uJednotka != DEDINA)
		{
			std::cout << "Nezadal si dedinu v kriteriu Kprislusnostobce" << std::endl;
			return false;
		}

		if (vysCelok > 100)
		{
			return t->getParent()->accessData()->kod == vysCelok;
		}
		else
		{
			return t->getParent()->getParent()->accessData()->kod == vysCelok;
		}		
	}
private:
	int vysCelok = 0;	
};

