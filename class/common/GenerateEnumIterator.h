#pragma once
#include <type_traits>

//enum class�̊g��for���[�v�����}�N��(�w�b�_��)
#define GENERATE_ENUM_PROTOTYPE(T)\
T begin(T);\
T end(T);\
T operator++(T& id);\
T operator*(T& id);

//enum class�̊g��for���[�v�����}�N��(�\�[�X��)
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