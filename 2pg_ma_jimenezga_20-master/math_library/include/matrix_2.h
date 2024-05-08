#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "vector_2.h"

class Matrix2x2 {
public:

	Matrix2x2();
	Matrix2x2(float a[4]);
	Matrix2x2(float value);
	Matrix2x2(const Vector2& a, const Vector2& b); 
	Matrix2x2(const Matrix2x2& copy);
	~Matrix2x2();
	Matrix2x2 Identity() const;
	Matrix2x2 Multiply(const Matrix2x2& other) const;
	float Determinant() const;
	Matrix2x2 Adjoint() const;
	Vector2 GetLine(int line) const;
	Vector2 GetColum(int line) const;

	Matrix2x2 Inverse() const;
	Matrix2x2 Transpose() const;

	inline Matrix2x2 operator+(const Matrix2x2& other) const;
	inline void operator+=(const Matrix2x2& other);
	inline Matrix2x2 operator+(float value) const;
	inline void operator+=(float value);
	inline Matrix2x2 operator-(const Matrix2x2& other) const;
	inline void operator-=(const Matrix2x2& other);
	inline Matrix2x2 operator-(float value) const;
	inline void operator-=(float value);

	inline Matrix2x2 operator*(float value) const;
	inline void operator*=(float value);
	inline Matrix2x2 operator/(float value) const;
	inline void operator/=(float value);

	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	inline void operator=(const Matrix2x2& other);

	float m[4];
};


inline Matrix2x2::Matrix2x2() {
}

inline Matrix2x2::Matrix2x2(float a[4]) {
	for (int i = 0; i < 4; ++i) {
		m[i] = a[i];
	}
}

inline Matrix2x2::Matrix2x2(float a) {
	for (int i = 0; i < 4; ++i) {
		m[i] = a;
	}
}

inline Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	m[0] = a.x;
	m[1] = a.y;
	m[2] = b.x;
	m[3] = b.y;
}

inline Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	for (int i = 0; i < 4; ++i) {
		m[i] = copy.m[i];
	}
}

inline Matrix2x2::~Matrix2x2() {

}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] + other.m[i];
	}

	return a_m;
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	for (int i = 0; i < 4; ++i) {
		m[i] += other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] + value;
	}

	return a_m;
}

inline void Matrix2x2::operator+=(float value) {
	for (int i = 0; i < 4; ++i) {
		m[i] += value;
	}
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] - other.m[i];
	}

	return a_m;
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	for (int i = 0; i < 4; ++i) {
		m[i] -= other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {	
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] - value;
	}

	return a_m;
}

inline void Matrix2x2::operator-=(float value) {
	for (int i = 0; i < 4; ++i) {
		m[i] -= value;
	}
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] - value;
	}

	return a_m;
}

inline void Matrix2x2::operator*=(float value) {
	for (int i = 0; i < 4; ++i) {
		m[i] *= value;
	}
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	Matrix2x2 a_m;

	for (int i = 0; i < 4; ++i) {
		a_m.m[i] = m[i] / value;
	}

	return a_m;
}

inline void Matrix2x2::operator/=(float value) {
	for (int i = 0; i < 4; ++i) {
		m[i] /= value;
	}
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const {
	bool equal = true;

	for (int i = 0; equal != true && i < 4; i++) {
		equal = m[i] == other.m[i];
	}

	return equal;
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	bool equal = false;

	for (int i = 0; equal != true && i < 4; i++) {
		equal = m[i] == other.m[i];
	}

	return equal;
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++) {
		m[i] = other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::Identity() const {
	return Matrix2x2(Vector2(1, 0), Vector2(0, 1));
}

inline float Matrix2x2::Determinant() const {
	return ((m[0] * m[3]) - (m[1] * m[2]));
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	Matrix2x2 a_m = Matrix2x2(Vector2(m[3], -m[1]), Vector2(-m[2], m[0]));

	return a_m / Determinant();
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	Matrix2x2 a_m;

	a_m.m[0] = ((m[0] * other.m[0]) + (m[1] * other.m[2]));
	a_m.m[1] = ((m[0] * other.m[1]) + (m[1] * other.m[3]));
	a_m.m[2] = ((m[2] * other.m[0]) + (m[3] * other.m[2]));
	a_m.m[3] = ((m[2] * other.m[1]) + (m[3] * other.m[3]));

	return a_m;
}

inline Matrix2x2 Matrix2x2::Adjoint() const {

	return Matrix2x2(Vector2(m[3], -m[1]), Vector2(-m[2], m[0]));
}

inline Matrix2x2 Matrix2x2::Transpose() const {
	return Matrix2x2(Vector2(m[0], m[2]), Vector2(m[1], m[3]));
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	return Vector2(m[2 * line], m[2 * line + 1]);
}

inline Vector2 Matrix2x2::GetColum(int line) const {	
	return Vector2(m[line], m[line + 2]);
}


#endif
