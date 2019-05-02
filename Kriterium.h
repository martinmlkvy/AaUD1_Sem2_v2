#pragma once

// O-mnozina 
// T-vysledny vystup
template<typename T, typename O>
class Kriterium
{
public:	
	virtual T evaluate(O object) = 0;
};