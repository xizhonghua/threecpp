/*
 * Matrix4.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: zxi
 */

#include <math/Matrix4.h>

namespace three {

Matrix4::Matrix4() {
  this->identity();
}

Matrix4::~Matrix4() {
}

////////////////////////////////////////////////////////////////////
Matrix4& Matrix4::lookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {

  Vector3 z = (eye - target).normalize();
  if (z.lengthSqr() == 0) {
    z.z = 1.0;
  }

  Vector3 x = (up % z).normalize();
  if (x.lengthSqr() == 0) {
    z.z += 0.0001;
    x = up % z;
  }

  Vector3 y = z % x;

  auto& te = this->elements;

  te[0] = x.x;
  te[1] = x.y;
  te[2] = x.z;

  te[4] = y.x;
  te[5] = y.y;
  te[6] = y.z;

  te[8] = z.x;
  te[9] = z.y;
  te[10] = z.z;

  return *this;
}

Matrix4& Matrix4::toArray(std::vector<double>& array, int offset) {
  return this->toArray(&array[0], offset);
}

Matrix4& Matrix4::toArray(double* array, int offset) {
  for (int i = 0; i < 16; ++i) {
    array[offset + i] = this->elements[i];
  }

  return *this;
}

////////////////////////////////////////////////////////////
// Factory methods
////////////////////////////////////////////////////////////
Matrix4 Matrix4::makeTranslation(const Vector3& t) {
  Matrix4 m;
  m.setPosition(t);

  return m;
}

} /* namespace three */
