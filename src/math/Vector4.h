/*
 * Vector4.h
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#ifndef MATH_VECTOR4_H_
#define MATH_VECTOR4_H_

namespace three {

class Vector4 {
public:
  Vector4();
  Vector4(double x, double y, double z, double w);
  Vector4(const Vector4& v) = default;
  Vector4(Vector4&& v) = default;
  Vector4& operator=(const Vector4& v) = default;
  ~Vector4();

  inline Vector4& set(double x = 0, double y = 0, double z = 0, double w = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
  }

  inline Vector4 operator+(const Vector4& v) const {
    return Vector4 { x + v.x, y + v.y, z + v.z, w + v.w };
  }

  inline Vector4& operator+=(const Vector4& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;

    return *this;
  }

  inline Vector4 operator-(const Vector4& v) const {
    return Vector4 { x - v.x, y - v.y, z - v.z, w - v.w };
  }

  inline Vector4& operator-=(const Vector4& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;

    return *this;
  }

  // Dot product
  inline double operator*(const Vector4& v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
  }

  double x = 0;
  double y = 0;
  double z = 0;
  double w = 0;
};

} /* namespace three */

#endif /* MATH_VECTOR4_H_ */
