#pragma once
#include <cmath>
#include <string>

struct Vector2D
{
	float x, y;

	Vector2D() :x(0), y(0) {}
	Vector2D(float pX, float pY): x(pX), y(pY){}
	Vector2D(float size): x(size), y(size){}

	static const Vector2D Zero, One, UnitX, UnitY;

	inline void operator += (Vector2D& right) {
		x += right.x;
		y += right.y;
	}
	inline void operator -= (Vector2D& right) {
		x -= right.x;
		y -= right.y;
	}
	inline void operator *= (float scalar) {
		x *= scalar;
		y *= scalar;
	}
	inline void operator /= (float scalar) {
		x /= scalar;
		y /= scalar;
	}
	inline void operator = (float scalar) {
		x = scalar;
		y = scalar;
	}
	friend Vector2D operator + (Vector2D& left, Vector2D& right) {
		return { left.x + right.x, left.y + right.y };
	}
	friend Vector2D operator - (Vector2D& left, Vector2D& right) {
		return { left.x - right.x, left.y - right.y };
	}
	friend Vector2D operator * (Vector2D& left, float scalar) {
		return { left.x * scalar, left.y * scalar };
	}
	friend Vector2D operator * (float scalar, Vector2D& right) {
		return { scalar * right.x, scalar * right.y };
	}
	friend Vector2D operator / (Vector2D& left, float scalar) {
		return { left.x / scalar, left.y / scalar };
	}
	friend Vector2D operator / (float scalar, Vector2D& right) {
		return { scalar / right.x, scalar / right.y };
	}
	friend bool operator == (Vector2D& left, Vector2D& right) {
		if (left.x == right.x && left.y == right.y) {
			return true;
		}
		else {
			return false;
		}
	}
	friend bool operator != (Vector2D& left, Vector2D& right) {
		if (left.x == right.x && left.y == right.y) {
			return false;
		}
		else {
			return true;
		}
	}

	inline float Length() const {
		float sum = (x*x) + (y*y);
		return sqrt(sum);
	}
	inline void Normalize() {
		(*this) /= Length();
	}
	inline Vector2D Normalize(Vector2D temp) {
		return temp / temp.Length();
	}
	friend float Dot(Vector2D& left, Vector2D& right) {
		return left.x * right.x + left.y * right.y;
	}
	inline void Clamp(Vector2D& min, Vector2D& max) {
		if ((*this).x < min.x) (*this).x = min.x;
		if ((*this).x > max.x) (*this).x = max.x;

		if ((*this).y < min.y) (*this).y = min.y;
		if ((*this).y > max.y) (*this).y = max.y;
	}
	inline Vector2D Clamp(Vector2D temp, Vector2D& min, Vector2D& max) {
		if (temp.x < min.x) temp.x = min.x;
		if (temp.x > max.x) temp.x = max.x;

		if (temp.y < min.y) temp.y = min.y;
		if (temp.y > max.y) temp.y = max.y;

		return temp;
	}
	inline float Distance(Vector2D& vec) {
		return sqrt(((*this).x - vec.x) * ((*this).x - vec.x) + ((*this).y - vec.y) * ((*this).y - vec.y));
	}

	inline bool Equals(Vector2D& right, float acceptance) {
		if (x < right.x - acceptance || x > right.y + acceptance || y < right.y - acceptance || y > right.y + acceptance) return true;
		else return false;
	}

	inline std::string ToString() {
		return "( " + std::to_string(x) + " , " + std::to_string(y) + " )";
	}
};

