#pragma once
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"
#include "Filter_VelkeFI.h"

class FUcast : public Filter_VelkeFI<double, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	FUcast(double spodne, double horne) {
		Filter_VelkeFI::setAlpha(spodne);
		Filter_VelkeFI::setBeta(horne);
	}
};