#include <iostream>
#include "Vector2D.h"

Vector2D& Vector2D::Add(const Vector2D& vec) {
	x += vec.x; y += vec.y;
	return *this;
}
Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	x -= vec.x; y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	x *= vec.x; y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec) {
	x /= vec.x; y /= vec.y;
	return *this;
}
Vector2D operator+(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x + v2.x, v1.y + v2.y); }
Vector2D operator-(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x - v2.x, v1.y - v2.y); }
Vector2D operator*(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x * v2.x, v1.y * v2.y); }
Vector2D operator/(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x / v2.x, v1.y / v2.y); }
std::ostream& operator<<(std::ostream& out, const Vector2D& vec) { out << "(" << vec.x << "," << vec.y << ")"; return out; }

