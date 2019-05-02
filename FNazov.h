#pragma once
#include "Filter_fi.h"
#include "multi_way_tree.h"
#include "UzemnaJednotka.h"

class FNazov : public Filter_fi <std::string, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	//kosntruktor 
	FNazov(std::string nazov) {
		Filter_fi::setAlpha(nazov);
	}
};