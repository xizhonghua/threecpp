/*
 * Matrix4.h
 *
 *  Created on: Feb 7, 2017
 *      Author: zxi
 */

#ifndef MATH_MATRIX4_H_
#define MATH_MATRIX4_H_

#include <array>

namespace three {

class Matrix4 {
public:
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

  // column wise
  std::array<double, 16> elements;
};

} /* namespace three */

#endif /* MATH_MATRIX4_H_ */
