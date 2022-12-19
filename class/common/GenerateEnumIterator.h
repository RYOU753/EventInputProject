#pragma once
#include <type_traits>

//enum classの拡張forループ生成マクロ(ヘッダ側)
#define GENERATE_ENUM_PROTOTYPE(T)\
T begin(T);\
T end(T);\
T operator++(T& id);\
T operator*(T& id);

//enum classの拡張forループ生成マクロ(ソース側)
#define GENERATE_ENUM_ITERATOR(T)\
T begin(T)\
{\
	return static_cast<T>(0);\
}\
T end(T)\
{\
	return T::Max;\
}\
T operator++(T& id)\
{\
	id = static_cast<T>(std::underlying_type<T>::type(id) + 1);\
	return id;\
}\
T operator*(T& id)\
{\
	return id;\
}

#define GENERATE_ENUM_ITERATOR_HEADONRY(T)\
static T begin(T)\
{\
	return static_cast<T>(0);\
}\
static T end(T)\
{\
	return T::Max;\
}\
static T operator++(T& id)\
{\
	id = static_cast<T>(std::underlying_type<T>::type(id) + 1);\
	return id;\
}\
static T operator*(T& id)\
{\
	return id;\
}