/*
 * Vector3.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

#include <cmath>
#include <iostream>

// forward declaration
namespace three {
class Matrix4;
class Quaternion;
}

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
  inline double lengthSq() const {
    return x * x + y * y + z * z;
  }

  inline double length() const {
    return sqrt(lengthSq());
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

  // Cross product
  inline Vector3 operator%(const Vector3& v) const {
    Vector3 a(*this);

    return a %= v;
  }

  inline Vector3& operator%=(const Vector3& v) {

    double tx = x;
    double ty = y;
    double tz = z;

    this->x = ty * v.z - tz * v.y;
    this->y = tz * v.x - tx * v.z;
    this->z = tx * v.y - ty * v.x;

    return *this;
  }

  // Dot product
  inline double operator*(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  // Scalar multiplication
  inline Vector3& operator*=(double s) {
    this->x *= s;
    this->y *= s;
    this->z *= s;

    return *this;
  }

  inline Vector3 operator*(double s) const {
    Vector3 v(*this);
    return v *= s;
  }

  // Scalar division
  inline Vector3& operator/=(double s) {
    if (s == 0) {
      this->set(0, 0, 0);
    } else {
      *this *= (1 / s);
    }
    return *this;
  }

  inline Vector3 operator/(double s) {
    return Vector3(*this) /= s;
  }

  // Component-wise multiplication
  inline Vector3& operator^=(const Vector3& v) {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    return *this;
  }

  inline Vector3 operator^(const Vector3& v) const {
    Vector3 out(*this);
    return out ^= v;
  }

  inline bool operator==(const Vector3& v) const {
    return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
  }

  inline bool operator!=(const Vector3& v) const {
    return (this->x != v.x) || (this->y != v.y) || (this->z != v.z);
  }

  /////////////////////////////////////////////////////////////////////
  // Matrix / Quaternion operations
  /////////////////////////////////////////////////////////////////////
  Vector3 operator*(const Matrix4& m) const;
  Vector3& operator*=(const Matrix4& m);

  Vector3 operator*(const Quaternion& q) const;
  Vector3& operator*=(const Quaternion& q);

  double x = 0;
  double y = 0;
  double z = 0;


  friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
};

} /* namespace three */

#endif /* MATH_VECTOR3_H_ */
