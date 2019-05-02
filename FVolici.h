#pragma once
#include "Filter_VelkeFI.h"
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"

class FVolici : public Filter_VelkeFI <unsigned int, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	FVolici(unsigned int spodne, unsigned int horne) {
		Filter_VelkeFI::setAlpha(spodne);
		Filter_VelkeFI::setBeta(horne);
	}
};