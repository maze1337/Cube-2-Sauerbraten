#pragma once
#include <cmath>


struct Vector2
{
	float x, y;

	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }

	float Length() const { return sqrtf(x * x + y * y); }
	float Distance(const Vector2& rhs) const { return (*this - rhs).Length(); }
};

struct Vector3
{
	float x, y, z;

	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }

	float Length() const { return std::sqrt(x * x + y * y + z * z); }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
};

struct Vector4
{
	float x, y, z, w;
};