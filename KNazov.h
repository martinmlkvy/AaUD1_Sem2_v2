#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"
#include <string>


class KNazov : public Kriterium<std::string, MultiWayTreeNode<UzemnaJednotka*>*>
{
public:
	std::string evaluate(MultiWayTreeNode<UzemnaJednotka*>* t) override {
		return t->accessData()->nazov;
	}
};