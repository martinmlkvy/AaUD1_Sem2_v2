#pragma once
#include "Filter.h"
#include "Kriterium.h"

template<typename T, typename O>
class Filter_VelkeFI : public Filter<T, O>
{
private:
	T alpha;
	T beta;
public:
	bool evaulate(O o, Kriterium<T, O> *c) override {
		T result = c->evaluate(o);
		return result >= alpha && result <= beta;
	}
	void setAlpha(T parm) {
		alpha = parm;
	}
	void setBeta(T parm) {
		beta = parm;
	}
};