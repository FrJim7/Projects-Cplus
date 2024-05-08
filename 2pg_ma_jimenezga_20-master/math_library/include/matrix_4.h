#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"

class Matix4x4{
 public:

  Matix4x4();
  Matix4x4(float a[16]);
  Matix4x4(float value);
  Matix4x4(const Matix4x4& copy);
  ~Matix4x4();

  Matix4x4 Identity() const;
  Matix4x4 Multiply(const Matix4x4& other) const;

  float Determinant() const;
  Matix4x4 Adjoint() const;
  bool GetInverse(Matix4x4* out) const;
  bool Inverse();

  Matix4x4 Transpose() const;


  static Matix4x4 Translate(const Vector3& distance);
  static Matix4x4 Translate(float x, float y, float z);

  static Matix4x4 Scale(const Vector3& scale);
  static Matix4x4 Scale(float x, float y, float z);

  static Matix4x4 RotateX(float radians);
  static Matix4x4 RotateY(float radians);
  static Matix4x4 RotateZ(float radians);

  static Matix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Matix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Matix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Matix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matix4x4 operator+(const Matix4x4& other) const;
  Matix4x4& operator+=(const Matix4x4& other);
  Matix4x4 operator+(float value) const;
  Matix4x4& operator+=(float value);
  Matix4x4 operator-(const Matix4x4& other) const;
  Matix4x4& operator-=(const Matix4x4& other);
  Matix4x4 operator-(float value) const;
  Matix4x4& operator-=(float value);
  Matix4x4& operator*=(float value);
  Matix4x4 operator*(float value) const;
  Matix4x4& operator/=(float value);
  Matix4x4 operator/(float value) const;
  bool operator==(const Matix4x4& other);
  bool operator!=(const Matix4x4& other);
  void operator=(const Matix4x4& other);

  float m[16];
};


inline Matix4x4::Matix4x4() {

}

inline Matix4x4::Matix4x4(float array[16]) {
}

inline Matix4x4::Matix4x4(float value) {
	
}

inline Matix4x4::Matix4x4(const Matix4x4& copy) {
	
}

inline Matix4x4::~Matix4x4() {

}

inline Matix4x4 Matix4x4::Identity() const {
	return Matix4x4();
}

inline Matix4x4 Matix4x4::Multiply(const Matix4x4& other)const  {
	return Matix4x4();
}


inline float Matix4x4::Determinant() const {
	
	return 0.0f;
}


inline Matix4x4 Matix4x4::Adjoint() const {
	
	Matix4x4 result;
	return result;
}

inline bool Matix4x4::Inverse() {
	return true;
}

inline bool Matix4x4::GetInverse(Matix4x4* out) const {
	return true;

}

inline Matix4x4 Matix4x4::Transpose() const {
		
	return Matix4x4();
}

inline Matix4x4 Matix4x4::Translate(const Vector3& distance){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::Translate(float x, float y, float z){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::Scale(const Vector3& scale){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::Scale(float x, float y, float z){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::RotateX(float radians){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::RotateY(float radians){
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::RotateZ(float radians) {
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::GetTransform(const Vector3& translate,
								const Vector3& scale,
								float rotateX, float rotateY,
								float rotateZ)   {
	return Matix4x4();
}

inline Matix4x4 Matix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_Z,
	float rotateX, float rotateY, float rotateZ)  {
	
	return Matix4x4();
}

inline Vector4 Matix4x4::GetColum(int colum) const {
	return Vector4();
}

inline Vector4 Matix4x4::GetLine(int line) const {
	return Vector4();
}

inline Matix4x4 Matix4x4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) const {
	
	return Matix4x4();
}

inline Matix4x4 Matix4x4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {

	return Matix4x4();
}



inline Matix4x4 Matix4x4::operator+(const Matix4x4& other) const {
	return Matix4x4();
}

inline Matix4x4& Matix4x4::operator+=(const Matix4x4& other) {
	
}

inline Matix4x4 Matix4x4::operator+(float value) const {
	return Matix4x4();
}

inline Matix4x4& Matix4x4::operator+=(float value) {	
}


inline Matix4x4 Matix4x4::operator-(const Matix4x4& other) const  {
	return Matix4x4();
}

inline Matix4x4& Matix4x4::operator-=(const Matix4x4& other) {
}

inline Matix4x4 Matix4x4::operator-(float value) const  {
	return Matix4x4();
}

inline Matix4x4& Matix4x4::operator-=(float value) {
}

inline Matix4x4& Matix4x4::operator*=(float value) {
}

inline Matix4x4 Matix4x4::operator*(float value) const  {
	return Matix4x4();
}

inline Matix4x4& Matix4x4::operator/=(float value) {
	
}

inline Matix4x4 Matix4x4::operator/(float value) const {
	return Matix4x4();
}

inline bool Matix4x4::operator==(const Matix4x4& other) {
	return true;
}

inline bool Matix4x4::operator!=(const Matix4x4& other) {
	return false;
}

inline void Matix4x4::operator=(const Matix4x4& other) {
}

#endif
