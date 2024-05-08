#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

class Matrix3x3 {
public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(float value);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

	float m[9];
};


inline Matrix3x3::Matrix3x3() {
}

inline Matrix3x3::Matrix3x3(float value) {
}

inline Matrix3x3::Matrix3x3(float *values_array) {
}

inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
}

inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
}

inline Matrix3x3::~Matrix3x3() {
}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator*=(float value) {
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return true;
}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return true;
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
}

inline Matrix3x3 Matrix3x3::Identity(){
	return Matrix3x3();
}

inline float Matrix3x3::Determinant() const {
	return 0.0f;
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	return true;
}

inline bool Matrix3x3::Inverse() {	
	return true;
}

inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {	
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	return Matrix3x3();
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	return Vector3();
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	return Vector3();
}

#endif 