#pragma once
#include <algorithm>
#include "../ValueRange.h"

template<class T>
ValueRangeTemplate<T>& ValueRangeTemplate<T>::operator=(const ValueRangeTemplate<T>& range)
{
	min_ = range.min_;
	max_ = range.max_;
	return *this;
}

template<class T>
T ValueRangeTemplate<T>::clamp(T val)
{
	return std::clamp(val,min_,max_);
}

template<class T>
T ValueRangeTemplate<T>::wrap(T val)
{
	return val > max_ ? min_ : val < min_ ? max_ : val;
}
