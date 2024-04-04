#pragma once
#include <iostream>
class Vector2D {
	float x;
	float y;
public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float a, float b) : x(a), y(b) {}
	Vector2D(const Vector2D& vec) { setX(vec.x); setY(vec.y); }
	~Vector2D() {}
	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	Vector2D& operator+=(const Vector2D& vec) { return this->Add(vec); }
	Vector2D& operator-=(const Vector2D& vec) { return this->Subtract(vec); }
	Vector2D& operator*=(const Vector2D& vec) { return this->Multiply(vec); }
	Vector2D& operator/=(const Vector2D& vec) { return this->Divide(vec); }
	Vector2D& operator*(const int& i) { x *= i; y *= i; return *this; }
	Vector2D& operator=(Vector2D* vec) { x = vec->x; y = vec->y; return *this; }

	friend Vector2D operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator/(Vector2D& v1, const Vector2D& v2);
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);

	int getX() const { return int(x); }
	int getY() const { return int(y); }
	void setX(float z) { x = z; }
	void setY(float z) { y = z; }
	void clear() { x = 0; y = 0; }
};