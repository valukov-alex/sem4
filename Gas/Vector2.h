#pragma once
#include <iostream>
#include <cmath> 

struct Vector2 {
	double y, x;
	Vector2();
	Vector2(double _x, double _y);
	Vector2 operator * (double k) const;
	Vector2 operator / (double k) const;
	Vector2 operator + (const Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2& operator += (const Vector2& other);
	Vector2& operator -= (const Vector2& other);
	Vector2& operator *= (double k);
	Vector2& operator /= (double k);
	friend Vector2 operator * (double k, const Vector2& v);
	friend std::ostream& operator << (std::ostream& stream, const Vector2& v);
	friend std::istream& operator >> (std::istream& stream, Vector2& v);
	double Len() const;
	double squareLen() const;
	Vector2 Norm() const;
	Vector2 Perpendicular() const;
	double operator * (const Vector2& other) const;
	double operator ^ (const Vector2& other) const;
	Vector2 operator - () const;
	Vector2& rotate(double angle);
	Vector2 getRotated(double angle) const;
};