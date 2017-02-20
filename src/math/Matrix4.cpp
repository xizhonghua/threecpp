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
  if (z.lengthSq() == 0) {
    z.z = 1.0;
  }

  Vector3 x = (up % z).normalize();
  if (x.lengthSq() == 0) {
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

Matrix4& Matrix4::asPerspective(double left, double right, double top,
    double bottom, double near, double far) {

  auto te = this->elements;
  double x = 2 * near / (right - left);
  double y = 2 * near / (top - bottom);

  double a = (right + left) / (right - left);
  double b = (top + bottom) / (top - bottom);
  double c = -(far + near) / (far - near);
  double d = -2 * far * near / (far - near);

  te[0] = x;
  te[4] = 0;
  te[8] = a;
  te[12] = 0;
  te[1] = 0;
  te[5] = y;
  te[9] = b;
  te[13] = 0;
  te[2] = 0;
  te[6] = 0;
  te[10] = c;
  te[14] = d;
  te[3] = 0;
  te[7] = 0;
  te[11] = -1;
  te[15] = 0;

  return *this;
}

Matrix4& Matrix4::asOrthographic(double left, double right, double top,
    double bottom, double near, double far) {

  auto te = this->elements;
  auto w = 1.0 / (right - left);
  auto h = 1.0 / (top - bottom);
  auto p = 1.0 / (far - near);

  auto x = (right + left) * w;
  auto y = (top + bottom) * h;
  auto z = (far + near) * p;

  te[0] = 2 * w;
  te[4] = 0;
  te[8] = 0;
  te[12] = -x;
  te[1] = 0;
  te[5] = 2 * h;
  te[9] = 0;
  te[13] = -y;
  te[2] = 0;
  te[6] = 0;
  te[10] = -2 * p;
  te[14] = -z;
  te[3] = 0;
  te[7] = 0;
  te[11] = 0;
  te[15] = 1;

  return *this;
}

Matrix4& Matrix4::asLookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {

  double* te = this->elements;

  Vector3 z = (eye - target).normalize();

  if (z.lengthSq() == 0) {

    z.z = 1;

  }

  Vector3 x = (up % z).normalize();

  if (x.lengthSq() == 0) {

    z.z += 0.0001;
    x = (up % z).normalize();

  }

  Vector3 y = z % x;

  te[0] = x.x;
  te[4] = y.x;
  te[8] = z.x;
  te[1] = x.y;
  te[5] = y.y;
  te[9] = z.y;
  te[2] = x.z;
  te[6] = y.z;
  te[10] = z.z;

  te[12] = -(x * eye);
  te[13] = -(y * eye);
  te[14] = -(z * eye);

  return *this;
}

////////////////////////////////////////////////////////////
// Factory methods
////////////////////////////////////////////////////////////
Matrix4 Matrix4::makeTranslation(const Vector3& t) {
  return Matrix4().setPosition(t);
}

Matrix4 Matrix4::makePerspective(double left, double right, double top,
    double bottom, double near, double far) {

  return Matrix4().asPerspective(left, right, top, bottom, near, far);
}

Matrix4 Matrix4::makeOrthographic(double left, double right, double top,
    double bottom, double near, double far) {
  return Matrix4().asOrthographic(left, right, top, bottom, near, far);
}

Matrix4 Matrix4::makeLookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {
  return Matrix4().asLookAt(eye, target, up);
}

std::ostream& operator<<(std::ostream& out, const Matrix4& m) {
  auto& te = m.elements;
  out << te[0] << " " << te[4] << " " << te[8] << " " << te[12] << std::endl;
  out << te[1] << " " << te[5] << " " << te[9] << " " << te[13] << std::endl;
  out << te[2] << " " << te[6] << " " << te[10] << " " << te[14] << std::endl;
  out << te[3] << " " << te[7] << " " << te[11] << " " << te[15] << std::endl;
  return out;
}

} /* namespace three */
