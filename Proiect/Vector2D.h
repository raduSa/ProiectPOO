#pragma once
#include <iostream>

template <typename T>
class Vector2D {
	T x, y;
public:
	Vector2D(T x = 0, T y = 0) : x(x), y(y) {}
	Vector2D(const Vector2D& vec) { setX(vec.x); setY(vec.y); }
	~Vector2D() {}
	template <typename U>
	Vector2D<T>& Add(const Vector2D<U>& vec) {
		x += static_cast<T>(vec.x); y += static_cast<T>(vec.y);
		return *this;
	}
	template <typename U>
	Vector2D<T>& Subtract(const Vector2D<U>& vec) {
		x -= static_cast<T>(vec.x); y -= static_cast<T>(vec.y);
		return *this;
	}
	template <typename U>
	Vector2D<T>& Multiply(const Vector2D<U>& vec) {
		x *= static_cast<T>(vec.x); y *= static_cast<T>(vec.y);
		return *this;
	}
	template <typename U>
	Vector2D<T>& Divide(const Vector2D<U>& vec) {
		x /= static_cast<T>(vec.x); y /= static_cast<T>(vec.y);
		return *this;
	}

	template <typename U>
	Vector2D<T>& operator+=(const Vector2D<U>& vec) { return this->Add(vec); }
	template <typename U>
	Vector2D<T>& operator-=(const Vector2D<U>& vec) { return this->Subtract(vec); }
	template <typename U>
	Vector2D<T>& operator*=(const Vector2D<U>& vec) { return this->Multiply(vec); }
	template <typename U>
	Vector2D<T>& operator/=(const Vector2D<U>& vec) { return this->Divide(vec); }
	template <typename U>
	Vector2D<T>& operator*(const U& i) { x *= static_cast<T>(i); y *= static_cast<T>(i); return *this; }
	template <typename U>
	Vector2D<T>& operator=(Vector2D<U>* vec) { x = static_cast<T>(vec->x); y = static_cast<T>(vec->y); return *this; }
	template <typename U>
	Vector2D<T>& operator=(const Vector2D<U>& vec) { x = static_cast<T>(vec->x); y = static_cast<T>(vec->y); return *this; }

	friend Vector2D<T> operator+(Vector2D<T>& v1, const Vector2D<T>& v2);
	friend Vector2D<T> operator-(Vector2D<T>& v1, const Vector2D<T>& v2);
	friend Vector2D<T> operator*(Vector2D<T>& v1, const Vector2D<T>& v2);
	friend Vector2D<T> operator/(Vector2D<T>& v1, const Vector2D<T>& v2);
	friend std::ostream& operator<<(std::ostream& out, const Vector2D<T>& vec);

	T& getX() { return x; }
	T& getY() { return y; }
	template <typename U>
	void setX(const U& z) { x = static_cast<T>(z); }
	template <typename U>
	void setY(const U& z) { y = static_cast<T>(z); }
	void clear() { x = 0; y = 0; }
};