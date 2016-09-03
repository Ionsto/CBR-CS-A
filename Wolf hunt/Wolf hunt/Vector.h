#pragma once
#include <iostream>
class Vector {
public:
	float X, Y;
	Vector(float x = 0,float y = 0)
	{
		this->X = x;
		this->Y = y;
	};
	float Dot(const Vector v) 
	{
		return (v.X * X) + (v.Y * Y);
	}
	Vector operator+(const Vector v)
	{
		return Vector(X + v.X, Y + v.Y);
	}
	void operator+=(const Vector v)
	{
		this->X += v.X;
		this->Y += v.Y;
	}
	void operator-=(const Vector v)
	{
		this->X -= v.X;
		this->Y -= v.Y;
	}
	Vector operator/(const Vector v)
	{
		return Vector(X / v.X, Y / v.Y);
	}
	Vector operator*(const Vector v)
	{
		return Vector(X * v.X, Y * v.Y);
	}
	Vector operator-(const Vector v)
	{
		return Vector(X - v.X, Y - v.Y);
	}
	Vector operator*(const float v)
	{
		return Vector(X * v, Y * v);
	}
	Vector operator/(const float v)
	{
		return Vector(X / v, Y / v);
	}
	friend std::iostream& operator<<(std::iostream& ios, const Vector& einf){
		ios << einf.X << einf.Y;
		return ios;
	};
	friend std::iostream& operator>>(std::iostream& ios, const Vector& einf){
		ios >> einf.X >> einf.Y;
		return ios;
	};
};