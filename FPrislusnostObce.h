#pragma once
#include "Filter_fi.h"
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"

class FPrislusnostObce : public Filter_fi <unsigned int, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	//kosntruktor 
	FPrislusnostObce(unsigned int parm) {
		Filter_fi::setAlpha(parm);
	}
};