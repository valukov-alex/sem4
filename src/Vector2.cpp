#include "Vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float x1, float y1) {
	x = x1;
	y = y1;
}

Vector2 Vector2::operator * (float f) const {
	return Vector2(x * f, y * f);
}

Vector2 Vector2::operator / (float f) const {
	return Vector2(x / f, y / f);
}

Vector2 Vector2::operator + (const Vector2& sbj) const {
	Vector2 v;
	v.x = sbj.x + x;
	v.y = sbj.y + y;
	return v;
}

Vector2 Vector2::operator - (const Vector2& sbj) const {
	Vector2 v;
	v.x = x - sbj.x;
	v.y = y - sbj.y;
	return v;
}

Vector2& Vector2::operator += (const Vector2& sbj) {
	return *this = *this + sbj;
}

Vector2& Vector2::operator -= (const Vector2& sbj) {
	return *this = *this - sbj;
}

Vector2& Vector2::operator *= (float f) {
	return *this = *this * f;
}

Vector2& Vector2::operator /= (float f) {
	return *this = *this / f;
}

std::ostream& operator << (std::ostream& stream, const Vector2& v) {
	stream << v.x << " " << v.y;
	return stream;
}

std::istream& operator >> (std::istream& stream, Vector2& v) {
	stream >> v.x >> v.y;
	return stream;
}

Vector2 operator * (float f, const Vector2& v) {
	return Vector2(v.x * f, v.y * f);
}

float Vector2::Len() const {
	return sqrt(x * x + y * y);
}

float Vector2::squareLen() const {
	return (x * x + y * y);
}

Vector2 Vector2::Norm() const {
	Vector2 result;
	result.x = x / Len();
	result.y = y / Len();
	return result;
}

Vector2 Vector2::Perpendicular() const {
	return Vector2(-y, x);
}

float Vector2::operator * (const Vector2& sbj) const {
	float result = sbj.x * x + sbj.y * y;
	return result;
}

float Vector2::operator ^ (const Vector2& sbj) const {
	float result = x * sbj.y - y * sbj.x;
	return result;
}

Vector2 Vector2::operator - () const {
	return Vector2(-x, -y);
}

Vector2 Vector2::getRotated(float angle) const {
	Vector2 result;
	result.x = x * cos(angle) - y * sin(angle);
	result.y = x * sin(angle) + y * cos(angle);
	return result;
}

Vector2& Vector2::rotate(float angle) {
	return *this = (*this).getRotated(angle);
}
