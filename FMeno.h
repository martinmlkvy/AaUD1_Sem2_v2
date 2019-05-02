#pragma once
#include "Filter_fi.h"
#include "Kandidat.h"
#include <string>

class FMeno : public Filter_fi <std::string, Kandidat*>
{
public:
	FMeno(std::string meno) {
		Filter_fi::setAlpha(meno);
	}
};