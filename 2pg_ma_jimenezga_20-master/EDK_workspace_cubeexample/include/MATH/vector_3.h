#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include "math_utils.h"
#include <cmath>

class Vector3 {
public:

	Vector3();
	Vector3(float a);
	Vector3(float x, float y, float z);
	Vector3(const Vector3& copy);
	~Vector3();

	Vector3 operator+(const Vector3& b) const;
	Vector3 operator+(float b) const;
	Vector3& operator+=(const Vector3& b);
	Vector3& operator+=(float b);
	Vector3 operator-(const Vector3& b) const;
	Vector3 operator-(float b) const;
	Vector3& operator-=(const Vector3& b);
	Vector3& operator-=(float b);
	bool operator==(const Vector3& b) const;
	bool operator!=(const Vector3& b) const;
	void operator=(const Vector3& b);
	void operator=(float& b);
	Vector3 operator*(float b) const;
	Vector3& operator*=(float b);
	Vector3 operator/(float b) const;
	Vector3& operator/=(float b);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Max(const Vector3& a, const Vector3& b);
	static Vector3 Min(const Vector3& a, const Vector3& b);
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static Vector3 ClampMagnitude(const Vector3& a, float maxLen);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& vec, const Vector3& normal);

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
inline Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

inline Vector3::Vector3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

inline Vector3::Vector3(float a) {
	x = a;
	y = a;
	z = a;
}

inline Vector3::Vector3(const Vector3& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

inline Vector3::~Vector3() {}

inline float Vector3::Magnitude() const {
	return sqrtf(SqrMagnitude());
}

inline void Vector3::Normalize() {
	float magnitude = 1 / Magnitude();
	x = x * magnitude;
	y = y * magnitude;
	z = z * magnitude;
}

inline Vector3 Vector3::Normalized() const {
	Vector3 vector(x, y, z);
	vector.Normalize();
	return vector;
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& b)  {
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

inline float Vector3::Angle(const Vector3& a, const Vector3& b)  {
	return acos(DotProduct(a, b) / (a.Magnitude() * b.Magnitude()));;
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)  {
	Vector3 vector((a.y * b.z - a.z * b.y), ((a.z * b.x) - (a.x * b.z)), (a.x * b.y - a.y * b.x));
	return vector;
}

inline float Vector3::SqrMagnitude() const {
	return (x * x) + (y * y) + (z * z);
}

inline void Vector3::Scale(const Vector3& other) {	
	x = x * other.x;
	y = y * other.y;
	z = z * other.z;
}

inline Vector3 Vector3::Max(const Vector3& a, const Vector3& b) {
	return a.Magnitude() > b.Magnitude() ? a : b;
}

inline Vector3 Vector3::Min(const Vector3& a, const Vector3& b) {
	return a.Magnitude() < b.Magnitude() ? a : b;
}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	return LerpUnclamped(a , b, MathUtils::Clamp(t, 0, 1));
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	Vector3 vector(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t, a.z + (b.z - a.z)*t);
	return vector;
}

inline Vector3 Vector3::ClampMagnitude(const Vector3& a, float MaxLen) {
	return Vector3();
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	float a_x = b.x - a.x;
	float a_y = b.y - a.y;
	float a_z = b.z - a.z;
	return sqrt((a_x * a_x) + (a_y * a_y) + (a_z * a_z));
}

inline Vector3 Vector3::Reflect(const Vector3& vec, const Vector3& normal) {
	Vector3 vector;
	vector = vec - (normal * (DotProduct(vec, normal)) * 2);
	return vector;
}

inline Vector3 Vector3::operator+(const Vector3& b) const {
	Vector3 vector(x + b.x, y + b.y, z + b.z);
	return vector;
}

inline Vector3 Vector3::operator+(float b) const {
	Vector3 vector(x + b, y + b, z + b);
	return vector;
}

inline Vector3& Vector3::operator+=(const Vector3& b) {
	x = x + b.x;
	y = y + b.y;
	z = z + b.z;
	return *this;
}

inline Vector3& Vector3::operator+=(float b) {
	x = x + b;
	y = y + b;
	z = z + b;
	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& b) const {
	Vector3 vector(x - b.x, y - b.y, z - b.z);
	return vector;
}

inline Vector3 Vector3::operator-(float b) const {
	Vector3 vector(x - b, y - b, z - b);
	return vector;
}

inline Vector3& Vector3::operator-=(const Vector3& b) {
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;
	return *this;
}

inline Vector3& Vector3::operator-=(float b) {
	x = x - b;
	y = y - b;
	z = z - b;
	return *this;
}

inline bool Vector3::operator==(const Vector3& b) const {
	return (x == b.x && y == b.y && z == b.z);
}

inline bool Vector3::operator!=(const Vector3& b) const {
	return (x != b.x || y != b.y || z != b.z);
}

inline void Vector3::operator=(const Vector3& b) {
	x = b.x;
	y = b.y;
	z = b.z;
}

inline void Vector3::operator=(float& b) {
	x = b;
	y = b;
	z = b;
}

inline Vector3 Vector3::operator*(float b) const {
	Vector3 vector(x * b, y * b, z * b);
	return vector;
}

inline Vector3& Vector3::operator*=(float b) {
	x = x * b;
	y = y * b;
	z = z * b;
	return *this;
}

inline Vector3 Vector3::operator/(float b) const {
	Vector3 vector(x / b, y / b, z / b);
	return vector;
}

inline Vector3& Vector3::operator/=(float b) {
	x = x / b;
	y = y / b;
	z = z / b;
	return *this;
}

#endif 
