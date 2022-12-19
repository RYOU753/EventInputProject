#pragma once
#include <string>

template<class T> class Vector2Template
{
public:
	T x;
	T y;

	Vector2Template():x(static_cast<T>(0)),y(static_cast<T>(0)){ };
	Vector2Template(T x, T y) :x(x), y(y) {};
	//constexpr Vector2Template(T x, T y) :x(x), y(y) {};
	Vector2Template(const Vector2Template& vec) { 
		x = vec.x;
		y = vec.y; 
	};
	~Vector2Template();

	//‘ã“ü‰‰Zq
	Vector2Template& operator= (const Vector2Template& vec);
	Vector2Template& operator+= (const Vector2Template& vec);
	Vector2Template& operator-= (const Vector2Template& vec);

	T& operator[] (int no)const;
	Vector2Template operator- ()const;
	//ŒvZ‰‰Zq
	Vector2Template operator+ (const Vector2Template& vec)const;
	Vector2Template operator- (const Vector2Template& vec)const;

	Vector2Template operator+ (const T& val)const;
	Vector2Template operator- (const T& val)const;
	Vector2Template operator* (const T& val)const;
	Vector2Template operator/ (const T& val)const;
	//˜_—‰‰Zq
	//’†g‚ªˆê’v‚µ‚Ä‚¢‚é‚©
	bool operator== (const Vector2Template& vec)const;
	//’†g‚ªˆê’v‚µ‚Ä‚¢‚È‚¢‚©
	bool operator!=(const Vector2Template& vec)const;
	//’·‚³‚ğ”äŠr
	bool operator<(const Vector2Template& vec)const;
	//’·‚³‚ğ”äŠr
	bool operator>(const Vector2Template& vec)const;
	//’·‚³‚ğ”äŠr
	bool operator<=(const Vector2Template& vec)const;
	//’·‚³‚ğ”äŠr
	bool operator>=(const Vector2Template& vec)const;

	//Œ^•ÏŠ·
	//Vector2Template& operator double()const;
	//cast‰‰Zq
	operator Vector2Template<int>() const{ return { static_cast<int>(this->x),static_cast<int>(this->y) }; };
	operator Vector2Template<float>() const{ return { static_cast<float>(this->x),static_cast<float>(this->y) }; };
	operator Vector2Template<double>() const{ return { static_cast<double>(this->x),static_cast<double>(this->y) }; };

	//•Ö—˜ŠÖ”
	T area(void)const;
	T length(void)const;
	T lengthSQ(void)const;
	T distance(const Vector2Template& vec)const;
	T distanceSQ(const Vector2Template& vec)const;
	T cross(const Vector2Template& vec)const;
	T dot(const Vector2Template& vec)const;
	void normal(void);
	Vector2Template normalized(void)const;
	bool isZero()const;
	std::string toStr(void);
private:
};

template<class T> constexpr
Vector2Template<T> operator*(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator*(T num, Vector2Template<T> vec);

template<class T> constexpr
Vector2Template<T> operator+(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator+(T num, Vector2Template<T> vec);

template<class T> constexpr
Vector2Template<T> operator-(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator-(T num, Vector2Template<T> vec);

using Vector2 = Vector2Template<int>;
using Vector2F = Vector2Template<float>;
using Vector2D = Vector2Template<double>;

using Position2 = Vector2;
using Position2F = Vector2F;
using Position2D = Vector2D;
#include "dateils/Vector2.h"


