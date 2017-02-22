/*
 * Matrix3.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: zxi
 */

#include <three/math/Matrix3.h>

#include <three/math/Matrix4.h>

namespace three {

Matrix3::Matrix3() {
  this->set(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

Matrix3::~Matrix3() {

}

Matrix3& Matrix3::getNormalMatrix(const Matrix4& m) {

  return *this;
}

Matrix3& Matrix3::transpose() {
  double tmp;
  auto m = this->elements;
  tmp = m[1];
  m[1] = m[3];
  m[3] = tmp;
  tmp = m[2];
  m[2] = m[6];
  m[6] = tmp;
  tmp = m[5];
  m[5] = m[7];
  m[7] = tmp;

  return *this;
}

} /* namespace three */
