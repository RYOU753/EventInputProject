#pragma once
template<class T> class ValueRangeTemplate
{
public:
	ValueRangeTemplate() :min_(static_cast<T>(0)), max_(static_cast<T>(0)) {};
	ValueRangeTemplate(T min, T max) :min_(min),max_(max) {};
	ValueRangeTemplate(const ValueRangeTemplate& range) { *this = range; };

	~ValueRangeTemplate(){};
	//‘ã“ü‰‰Zq
	ValueRangeTemplate& operator= (const ValueRangeTemplate& range);

	//•Ö—˜ŠÖ”
	T clamp(T val);
	T wrap(T val);
	T min()const { return min_; };
	T max()const { return max_; };
private:
	T min_;
	T max_;
};

using RangeInt = ValueRangeTemplate<int>;
using RangeFloat = ValueRangeTemplate<float>;
using RangeDouble = ValueRangeTemplate<double>;

#include "dateils/ValueRange.h"