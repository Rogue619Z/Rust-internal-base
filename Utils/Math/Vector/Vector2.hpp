#pragma once

class Vector2 {
public:
	float x, y;

	Vector2() { /* If no value has been set use 0.f */
		x = y = 0.f;
	}

	Vector2(float newX, float newY) { /* If value has been set, set the Vector to the value. */
		x = newX;
		y = newY;
	}

	Vector2 operator+(float fInput) const {/* Allows Vector to add itself to a float */
		return Vector2{ x + fInput, y + fInput };
	}

	Vector2 operator-(float fInput) const { /* Allows Vector to subtract itself to a float */
		return Vector2{ x - fInput, y - fInput };
	}

	Vector2 operator/(float fInput) const {/* Allows Vector to divide itself from a float */
		return Vector2{ x / fInput, y / fInput };
	}

	Vector2 operator*(float fInput) const { /* Allows Vector to multiply itself from a float */
		return Vector2{ x * fInput, y * fInput };
	}

	Vector2 operator+(const Vector2& vInput) const {  /* Allows Vector to add itself to another Vector */
		return Vector2{ x + vInput.x, y + vInput.y };
	}

	Vector2 operator-(const Vector2& vInput) const { /* Allows Vector to subtract itself by another Vector */
		return Vector2{ x - vInput.x, y - vInput.y };
	}

	Vector2 operator*(Vector2 vInput) const { /* Allows Vector to multiply itself by another Vector */
		return Vector2{ x * vInput.x, y * vInput.y };
	}

	Vector2 operator/(Vector2 vInput) const { /* Allows Vector to divide itself by another Vector */
		return Vector2{ x / vInput.x, y / vInput.y };
	}

	Vector2& operator-=(const Vector2& vInput) {/* Allows Vector to be subtracted by another Vector */
		x -= vInput.x;
		y -= vInput.y;

		return *this;
	}

	Vector2& operator+=(const Vector2& vInput) { /* Allows Vector to be added to another Vector */
		x += vInput.x;
		y += vInput.y;

		return *this;
	}

	Vector2& operator*=(const Vector2& vInput) { /* Allows Vector to be multiplied by another Vector */
		x *= vInput.x;
		y *= vInput.y;

		return *this;
	}

	Vector2& operator/=(const Vector2& vInput) { /* Allows Vector to be multiplied by another Vector */
		x /= vInput.x;
		y /= vInput.y;

		return *this;
	}

	Vector2& operator/=(float fInput) { /* Allows Vector to be divided by a float */
		x /= fInput;
		y /= fInput;

		return *this;
	}

	Vector2& operator*=(float fInput) { /* Allows Vector to be multiplied by a float */
		x *= fInput;
		y *= fInput;

		return *this;
	}

	Vector2& operator-=(float fInput) { /* Allows Vector to be subtracted by a float */
		x -= fInput;
		y -= fInput;

		return *this;
	}

	Vector2& operator+=(float fInput) { /* Allows Vector to be added to a float */
		x += fInput;
		y += fInput;

		return *this;
	}

	bool operator==(const Vector2& vInput) const { /* Checks if Vector is Equal with another Vector */
		return x == vInput.x && y == vInput.y;
	}

	bool operator!=(const Vector2& vInput) const {  /* Checks if Vector is NOT Equal with another Vector */
		if (x != vInput.x || y != vInput.y)
			return true;

		return false;
	}

	//void Abs() {
	//	x = abs(x);
	//	y = abs(y);
	//}
	static Vector2 Zero()
	{
		return Vector2(0, 0);
	}
	float Length() const {
		return sqrt((x * x) + (y * y));
	}

	float Distance(Vector2 vInput) const {
		return (*this - vInput).Length();
	}

	float Distance2D(Vector2 vInput) const {
		return sqrt(powf(x - vInput.x, 2) + powf(y - vInput.y, 2));
	}

	float Magnitude() {
		return sqrt(this->x * this->x + this->y * this->y);
	}

	float Magnitude2D() {
		return sqrt(this->x * this->x);
	}

	Vector2 Normalized() const {
		return { x / Length(), y / Length() };
	}

	bool Empty() const {
		return x == 0.f && y == 0.f;
	}
};