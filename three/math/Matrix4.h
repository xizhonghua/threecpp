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
    Matrix4 n(*this);
    return n *= m;
  }

  //
  inline Matrix4& operator*=(const Matrix4& m) {
    //TODO(zxi) implement this
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
  // Non-inline methods
  ////////////////////////////////////////////////////////////

  // Modify this as a rotation matrix, will not modify translation part
  Matrix4& lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

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

  Matrix4& asPerspective(double left, double right, double top, double bottom,
      double near, double far);
  Matrix4& asOrthographic(double left, double right, double top, double bottom, double near, double far);

  Matrix4& asLookAt(const Vector3& eye, const Vector3& target,
      const Vector3& up);

  /////////////////////////////////////////////////////////////
  // Convert to array
  /////////////////////////////////////////////////////////////
  Matrix4& toArray(std::vector<double>& array, int offset = 0);
  Matrix4& toArray(double* array, int offset = 0);

  ////////////////////////////////////////////////////////////
  // Factory methods
  ////////////////////////////////////////////////////////////
  static Matrix4 makeTranslation(const Vector3& t);
  static Matrix4 makePerspective(double left, double right, double top,
      double bottom, double near, double far);
  static Matrix4 makeOrthographic(double left, double right, double top, double bottom, double near, double far);
  static Matrix4 makeLookAt(const Vector3& eye, const Vector3& target,
      const Vector3& up);

  ////////////////////////////////////////////////////////////
  // Data members
  ////////////////////////////////////////////////////////////

  // column wise
  double elements[16];

  friend std::ostream& operator<<(std::ostream& out, const Matrix4& m);
};

} /* namespace three */

#endif /* THREE_MATH_MATRIX4_H_ */
