#include <tuple>
#include <cmath>
#include "..\Vector2.h"

template<class T>
Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
T& Vector2Template<T>::operator[](int no) const
{
	if (no == 0)
	{
		return x;
	}
	else if(no == 1)
	{
		return y;
	}

	return x;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return { -this->x,-this->y };
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+(const Vector2Template& vec)const
{
	return { x + vec.x ,y + vec.y };
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-(const Vector2Template& vec)const
{
	return { x - vec.x ,y - vec.y };
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+(const T& val)const
{
	return  { x + val, y + val };
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-(const T& val)const
{
	return  { x - val, y - val };
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator*(const T& val)const
{
	return { x * val, y * val };
	
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator/(const T& val) const
{
	return { x / val,y / val };
}

template<class T>
bool Vector2Template<T>::operator==(const Vector2Template& vec)const
{
	if (x == vec.x && y == vec.y) {
		return true;
	}
	return false;
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template& vec)const
{
	if (x != vec.x || y != vec.y) {
		return true;
	}
	return false;
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template& vec) const
{
	return this->distanceSQ() < vec.distanceSQ();
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template& vec) const
{
	return this->distanceSQ() > vec.distanceSQ();
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template& vec) const
{
	return this->distanceSQ() <= vec.distanceSQ();
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template& vec) const
{
	return this->distanceSQ() >= vec.distanceSQ();
}

template<class T>
T Vector2Template<T>::area(void) const
{
	return x*y;
}

template<class T>
T Vector2Template<T>::length(void) const
{
	return std::sqrt(x*x+y*y);
}

template<class T>
T Vector2Template<T>::lengthSQ(void) const
{
	return x*x+y*y;
}

template<class T>
T Vector2Template<T>::distance(const Vector2Template& vec) const
{
	return std::sqrt(distanceSQ(vec));
}

template<class T>
T Vector2Template<T>::distanceSQ(const Vector2Template& vec) const
{
	auto work = *this - vec;
	return work.x * work.x + work.y * work.y;
}

template<class T>
T Vector2Template<T>::cross(const Vector2Template& vec) const
{
	return x*vec.y-y*vec.x;
}

template<class T>
T Vector2Template<T>::dot(const Vector2Template& vec) const
{
	return x * vec.x + y* vec.y;
}

template<class T>
void Vector2Template<T>::normal(void)
{
	*this = *this / this->length();
}

template<class T>
Vector2Template<T> Vector2Template<T>::normalized(void) const
{
	return *this / this->length();
}

template<class T>
bool Vector2Template<T>::isZero() const
{
	return this->x == static_cast<T>(0)&&this->y == static_cast<T>(0);
}

template<class T>
std::string Vector2Template<T>::toStr(void)
{
	return "x:" + std::to_string(this->x) + "y:" + std::to_string(this->y);
}

template<class T>
Vector2Template<T>::~Vector2Template()
{
}

template<class T> constexpr
Vector2Template<T> operator*(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>{ vec.x* num, vec.y* num };
}

template<class T> constexpr
Vector2Template<T> operator*(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>{ vec.x* num, vec.y* num };
}

template<class T> constexpr
Vector2Template<T> operator+(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>{vec.x+num,vec.y+num};
}

template<class T> constexpr 
Vector2Template<T> operator+(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>{vec.x + num, vec.y + num};
}

template<class T> constexpr 
Vector2Template<T> operator-(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>{vec.x - num, vec.y - num};
}

template<class T> constexpr 
Vector2Template<T> operator-(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>{vec.x - num, vec.y - num};
}
