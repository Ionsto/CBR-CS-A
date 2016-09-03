#pragma once
#include <iostream>
class Vector {
public:
	float X;
	float Y;
	Vector(float x = 0, float y = 0);
	float Dot(const Vector v);
	Vector operator+(const Vector v);
	void operator+=(const Vector v);
	void operator-=(const Vector v);
	Vector operator/(const Vector v);
	Vector operator*(const Vector v);
	Vector operator-(const Vector v);
	Vector operator*(const float v);
	Vector operator/(const float v);
	friend std::ostream& operator<<(std::ostream& ios, const Vector& einf);
	friend std::istream& operator>>(std::istream& ios, Vector& einf);
};
