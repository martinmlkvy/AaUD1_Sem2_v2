#pragma once
#include "Kandidat.h"
#include "Kriterium.h"

class KMeno : Kriterium <std::string, Kandidat>
{
public:
	std::string evaluate(Kandidat* nieco) {
		return nieco->meno;
	}
};