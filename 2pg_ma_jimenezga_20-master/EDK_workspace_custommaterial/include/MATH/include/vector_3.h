#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include <cmath>
#include "math_utils.h"

class Vector3 {

public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(float* values_array);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(float value) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(float value);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(float value) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(float value);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	void operator=(const Vector3& other);
	void operator=(float value);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};
inline Vector3::Vector3() {}

inline Vector3::Vector3(float x, float y, float z) {

	this->x = x;
	this->y = y;
	this->z = z;

}

inline Vector3::Vector3(float * values_array) {

	x = values_array[0];
	y = values_array[1];
	z = values_array[2];

}

inline Vector3::Vector3(float value) {

	x = value;
	y = value;
	z = value;

}

inline Vector3::Vector3(const Vector3& other) {

	x = other.x;
	y = other.y;
	z = other.z;

}

inline Vector3::~Vector3() {}

inline float Vector3::Magnitude() const {
	return sqrtf(SqrMagnitude());
}

inline void Vector3::Normalize() {	

	float inverseMagnitude = 1.0f / Magnitude();
	*this *= inverseMagnitude;

}

inline Vector3 Vector3::Normalized() const {

	Vector3 vector(x, y, z);
	vector.Normalize();

	return vector;
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& other)  {
	return ((a.x * other.x) + (a.y * other.y) + (a.z * other.z));
}

inline float Vector3::Angle(const Vector3& a, const Vector3& other)  {
	return acosf(DotProduct(a, other) / (a.Magnitude() * other.Magnitude()));;
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& other)  {
	return Vector3((a.y * other.z - a.z * other.y), ((a.z * other.x) - (a.x * other.z)), (a.x * other.y - a.y * other.x));;
}

inline float Vector3::SqrMagnitude() const {
	return ((x * x) + (y * y) + (z * z));
}

inline void Vector3::Scale(const Vector3& other) {

	x *= other.x;
	y *= other.y;
	z *= other.z;

}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	return LerpUnclamped(a, b, MathUtils::Clamp(t, 0.0f, 1.0f));
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	return Vector3(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t, a.z + (b.z - a.z)*t);
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	return Vector3(b.x - a.x, b.y - a.y, b.z - a.z).Magnitude();
}

inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {

	Vector3 reflect;
	reflect = direction - (normal * (DotProduct(direction, normal)) * 2.0f);

	return reflect;
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

inline Vector3 Vector3::operator+(float value) const {
	return Vector3(x + value, y + value, z + value);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
	
	x += other.x;
	y += other.y;
	z += other.z;
	
	return *this;
}

inline Vector3& Vector3::operator+=(float value) {
	
	x += value;
	y += value;
	z += value;

	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y -other.y, z - other.z);
}

inline Vector3 Vector3::operator-(float value) const {
	return Vector3(x - value, y - value, z -value);
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
	
	x -= other.x;
	y -= other.y;
	z -= other.y;
	
	return *this;
}

inline Vector3& Vector3::operator-=(float value) {
	
	x -= value;
	y -= value;
	z -= value;
	
	return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
	return (x == other.x) && (y == other.y) && (z == other.y);
}

inline bool Vector3::operator!=(const Vector3& other) const {
	return (x != other.x) || (y != other.y) || (z != other.y);
}

inline void Vector3::operator=(const Vector3& other) {	
	x = other.x;
	y = other.y;
	z = other.z;
}

inline void Vector3::operator=(float value) {	
	x = value;
	y = value;
	z = value;
}

inline Vector3 Vector3::operator*(float value) const {
	return Vector3(x * value, y * value, z * value);
}

inline Vector3& Vector3::operator*=(float value) {
	
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

inline Vector3 Vector3::operator/(float value) const {
	return Vector3(x/value, y/value, z/value);
}

inline Vector3& Vector3::operator/=(float value) {
	
	x = x / value;
	x = y / value;
	x = z / value;
	
	return *this;
}

#endif 
