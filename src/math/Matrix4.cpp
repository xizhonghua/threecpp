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
Matrix4& Matrix4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{

  const Vector3 direction = eye - target;

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

} /* namespace three */
