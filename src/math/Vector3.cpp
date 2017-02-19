/*
 * Vector3.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include "math/Vector3.h"

#include "math/Matrix4.h"
#include "math/Quaternion.h"

namespace three {

Vector3::Vector3() {

}

Vector3::Vector3(double x, double y, double z) {
  this->set(x, y, z);
}

Vector3::Vector3(const Vector3& v) {
  this->set(v.x, v.y, v.z);
}

Vector3::~Vector3() {

}

Vector3 Vector3::operator*(const Matrix4& m) const {
  return Vector3(*this) *= m;
}

Vector3& Vector3::operator*=(const Matrix4& m) {
  double tx = this->x;
  double ty = this->y;
  double tz = this->z;

  auto& e = m.elements;

  this->x = e[0] * tx + e[4] * ty + e[8] * tz + e[12];
  this->y = e[1] * tx + e[5] * ty + e[9] * tz + e[13];
  this->z = e[2] * tx + e[6] * ty + e[10] * tz + e[14];
  double w = e[3] * tx + e[7] * ty + e[11] * tz + e[15];

  return *this /= w;
}

Vector3 Vector3::operator*(const Quaternion& q) const {
  return Vector3(*this) *= q;
}

Vector3& Vector3::operator*=(const Quaternion& q) {
  //TODO(zxi) implement this
  return *this;
}

std::ostream& operator<<(std::ostream& out, const Vector3& v) {
  out << v.x << " " << v.y << " " << v.z;
  return out;
}

} /* namespace three */
