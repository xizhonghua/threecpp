/*
 * Matrix4.h
 *
 *  Created on: Feb 7, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_MATRIX4_H_
#define THREE_MATH_MATRIX4_H_

#include <cmath>
#include <array>
#include <vector>
#include <iostream>

#include <three/math/Vector3.h>
#include <three/math/Vector4.h>

namespace three {
class Quaternion;

class Matrix4 {
public:
  // Create an identity matrix
  Matrix4();

  ~Matrix4();
  Matrix4(const Matrix4& m) = default;
  Matrix4(Matrix4&& m) = default;

  Matrix4& operator=(const Matrix4& m) = default;

  inline Matrix4& set(double n11, double n12, double n13, double n14,
      double n21, double n22, double n23, double n24, double n31, double n32,
      double n33, double n34, double n41, double n42, double n43, double n44) {

    elements[0] = n11;
    elements[1] = n21;
    elements[2] = n31;
    elements[3] = n41;

    elements[4] = n12;
    elements[5] = n22;
    elements[6] = n32;
    elements[7] = n42;

    elements[8] = n13;
    elements[9] = n23;
    elements[10] = n33;
    elements[11] = n43;

    elements[12] = n14;
    elements[13] = n24;
    elements[14] = n34;
    elements[15] = n44;

    return *this;
  }

  inline Matrix4& setPosition(const Vector3& v) {
    return this->setPosition(v.x, v.y, v.z);
  }

  inline Matrix4& setPosition(double x, double y, double z) {
    elements[12] = x;
    elements[13] = y;
    elements[14] = z;
    return *this;
  }

  // Set self to identity matrix
  inline Matrix4& identity() {
    return set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  }

  // access
  inline double& operator()(int row, int col) {
    return elements[col * 4 + row];
  }

  inline const double operator()(int row, int col) const {
    return elements[col * 4 + row];
  }

  // operators

  // Matrix Multiplication
  inline Matrix4 operator*(const Matrix4& m) const {
    Matrix4 out;
    auto ae = this->elements;
    auto be = m.elements;
    auto te = out.elements;

    auto a11 = ae[0], a12 = ae[4], a13 = ae[8], a14 = ae[12];
    auto a21 = ae[1], a22 = ae[5], a23 = ae[9], a24 = ae[13];
    auto a31 = ae[2], a32 = ae[6], a33 = ae[10], a34 = ae[14];
    auto a41 = ae[3], a42 = ae[7], a43 = ae[11], a44 = ae[15];

    auto b11 = be[0], b12 = be[4], b13 = be[8], b14 = be[12];
    auto b21 = be[1], b22 = be[5], b23 = be[9], b24 = be[13];
    auto b31 = be[2], b32 = be[6], b33 = be[10], b34 = be[14];
    auto b41 = be[3], b42 = be[7], b43 = be[11], b44 = be[15];

    te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
    te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
    te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
    te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

    te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
    te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
    te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
    te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

    te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
    te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
    te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
    te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

    te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
    te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
    te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
    te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

    return out;
  }

  inline Matrix4& operator*=(const Matrix4& m) {

    // Make this more efficient...
    *this = (*this) * m;
    return *this;
  }

  // Scalar Multiplication
  inline Matrix4 operator*(double s) const {
    Matrix4 n(*this);
    return n *= s;
  }

  //
  inline Matrix4& operator*=(double s) {
    for (int i = 0; i < 16; ++i)
      elements[i] *= s;
    return *this;
  }

  inline Matrix4 operator+(const Matrix4& m) const {
    Matrix4 n(*this);
    return n += m;
  }

  inline Matrix4& operator+=(const Matrix4& m) {
    for (int i = 0; i < 16; ++i) {
      this->elements[i] += m.elements[i];
    }
    return *this;
  }

  ////////////////////////////////////////////////////////////
  // Matrix4 * Vector4 (4x4)(4x1) = 4x1
  ////////////////////////////////////////////////////////////
  inline Vector4 operator*(const Vector4& v) {
    double x = elements[0] * v.x + elements[4] * v.y + elements[8] * v.z
        + elements[12] * v.w;
    double y = elements[1] * v.x + elements[5] * v.y + elements[9] * v.z
        + elements[13] * v.w;
    double z = elements[2] * v.x + elements[6] * v.y + elements[10] * v.z
        + elements[14] * v.w;
    double w = elements[3] * v.x + elements[7] * v.y + elements[11] * v.z
        + elements[15] * v.w;

    return Vector4(x, y, z, w);
  }

  inline Matrix4& scale(double s) {
    return ((*this) *= s);
  }

  double determinant() const;

  /////////////////////////////////////////////////////////////////////////////

  // Modify this as a rotation matrix, will not modify translation part
  Matrix4& lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

  // this->asXXX modifies this, use Matrix::makeXXX to create a new matrix
  Matrix4& asPerspective(double left, double right, double top, double bottom,
      double near, double far);
  Matrix4& asOrthographic(double left, double right, double top, double bottom,
      double near, double far);
  Matrix4& asLookAt(const Vector3& eye, const Vector3& target,
      const Vector3& up);

  Matrix4& asRotation(const Quaternion& quaternion);
  Matrix4& asCompose(const Vector3& position, const Quaternion& quaternion,
      double scale);

  // Decompose this matrix into position, rotation(as a Quaternion), and scale.
  Matrix4& decompose(Vector3* position, Quaternion* q, Vector3* scale);

  /////////////////////////////////////////////////////////////////////////////
  // Convert to array
  /////////////////////////////////////////////////////////////////////////////
  Matrix4& toArray(std::vector<double>& array, int offset = 0);
  Matrix4& toArray(double* array, int offset = 0);

  ////////////////////////////////////////////////////////////
  // Factory methods
  ////////////////////////////////////////////////////////////
  static Matrix4 makeTranslation(const Vector3& t);
  static Matrix4 makePerspective(double left, double right, double top,
      double bottom, double near, double far);
  static Matrix4 makeOrthographic(double left, double right, double top,
      double bottom, double near, double far);
  static Matrix4 makeLookAt(const Vector3& eye, const Vector3& target,
      const Vector3& up);

  /////////////////////////////////////////////////////////////////////////////
  // Data members
  /////////////////////////////////////////////////////////////////////////////

  // column wise
  double elements[16];

  friend std::ostream& operator<<(std::ostream& out, const Matrix4& m);
};

} /* namespace three */

#endif /* THREE_MATH_MATRIX4_H_ */
