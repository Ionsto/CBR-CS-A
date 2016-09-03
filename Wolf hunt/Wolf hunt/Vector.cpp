#include "Vector.h"

Vector::Vector(float x, float y)
{
	this->X = x;
	this->Y = y;
};
float Vector::Dot(const Vector v)
{
	return (v.X * X) + (v.Y * Y);
}
Vector Vector::operator+(const Vector v)
{
	return Vector(X + v.X, Y + v.Y);
}
void Vector::operator+=(const Vector v)
{
	this->X += v.X;
	this->Y += v.Y;
}
void Vector::operator-=(const Vector v)
{
	this->X -= v.X;
	this->Y -= v.Y;
}
Vector Vector::operator/(const Vector v)
{
	return Vector(X / v.X, Y / v.Y);
}
Vector Vector::operator*(const Vector v)
{
	return Vector(X * v.X, Y * v.Y);
}
Vector Vector::operator-(const Vector v)
{
	return Vector(X - v.X, Y - v.Y);
}
Vector Vector::operator*(const float v)
{
	return Vector(X * v, Y * v);
}
Vector Vector::operator/(const float v)
{
	return Vector(X / v, Y / v);
}
std::ostream& operator<<(std::ostream& ios, const Vector& z) {
	ios << z.X;// << einf.Y;
	return ios;
};
std::istream& operator>>(std::istream& ios, Vector& einf) {
	ios >> einf.X >> einf.Y;
	return ios;
};