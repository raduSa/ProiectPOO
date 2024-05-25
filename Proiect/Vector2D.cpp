#include <iostream>
#include "Vector2D.h"

template <typename T>
Vector2D<T> operator+(Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.x + v2.x, v1.y + v2.y); }

template <typename T>
Vector2D<T> operator-(Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.x - v2.x, v1.y - v2.y); }

template <typename T>
Vector2D<T> operator*(Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.x * v2.x, v1.y * v2.y); }

template <typename T>
Vector2D<T> operator/(Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D(v1.x / v2.x, v1.y / v2.y); }

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector2D<T>& vec) { out << "(" << vec.x << "," << vec.y << ")"; return out; }

