#pragma once
#include "NacitanieDat.h"
#include "multi_way_tree.h"
#include <iostream>
#include <string>
#include <stdio.h>

int main()
{
	NacitanieDat* aplikacia = new NacitanieDat();
	KNazov kriterium;
	FNazov* filter = new FNazov("Lucky");

	MultiWayTreeNode<UzemnaJednotka*>* nieco;

	aplikacia->nacitajData(1);
	aplikacia->nacitajData(2);
	aplikacia->nacitajKandidatov(1);
	aplikacia->nacitajKandidatov(2);
	//aplikacia->vypisInfoOJednotkachNazov("Pecenady", DEDINA);
	//aplikacia->vypisInfoOJednotkachVolici(100, 110, DEDINA);
	aplikacia->vypisInfoOJednotkachUcast(45.0, 46.0, DEDINA);
	
	delete aplikacia;
	aplikacia = nullptr;
	return 0;
	initHeapMonitor();
}
