/*
 * Vector3.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

#include <cmath>

namespace three {

class Vector3 {
public:
  Vector3();
  Vector3(double x, double y, double z);
  Vector3(const Vector3& v);
  Vector3(Vector3&& v) = default;
  Vector3& operator=(const Vector3& v) = default;
  ~Vector3();

  inline Vector3& set(double x = 0, double y = 0, double z = 0) {
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
  }

  // The squared length of the vector
  inline double lengthSqr() const {
    return x * x + y * y + z * z;
  }

  inline double length() const {
    return sqrt(lengthSqr());
  }

  // Modify this
  inline Vector3& normalize() {
    double length = this->length();
    if (length == 0) {
      return this->set(0, 0, 0);
    } else {
      return (*this) *= (1.0 / length);
    }
  }

  inline Vector3 operator+(const Vector3& v) const {
    return Vector3 { x + v.x, y + v.y, z + v.z };
  }

  inline Vector3& operator+=(const Vector3& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;

    return *this;
  }

  inline Vector3 operator-(const Vector3& v) const {
    return Vector3 { x - v.x, y - v.y, z - v.z };
  }

  inline Vector3& operator-=(const Vector3& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;

    return *this;
  }

  // Dot product
  inline double operator*(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  //
  inline Vector3& operator*=(double s) {
    this->x *= s;
    this->y *= s;
    this->z *= s;

    return *this;
  }

  double x = 0;
  double y = 0;
  double z = 0;
};

} /* namespace three */

#endif /* MATH_VECTOR3_H_ */
