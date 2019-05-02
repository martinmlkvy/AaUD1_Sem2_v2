#pragma once
#include "Filter.h"

template <typename T, typename O>
class Filter_fi : public Filter<T, O>
{
private:
	T alpha;
public:
	bool evaulate(O o, Kriterium<T, O> *c) override {
		return c->evaluate(o) == alpha;
	}

	void setAlpha(T parm) {
		alpha = parm;
	}
};