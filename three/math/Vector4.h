/*
 * Vector4.h
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_VECTOR4_H_
#define THREE_MATH_VECTOR4_H_

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

  inline Vector4& operator+=(const Vector4& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;

    return *this;
  }

  inline Vector4 operator+(const Vector4& v) const {
    Vector4 out(*this);
    out += v;
    return out;
  }

  inline Vector4& operator-=(const Vector4& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;

    return *this;
  }

  inline Vector4 operator-(const Vector4& v) const {
    Vector4 out(*this);
    out -= v;
    return out;
  }

  // Dot product
  inline double operator*(const Vector4& v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
  }

  // Component-wise multiplication
  inline Vector4& operator^=(const Vector4& v) {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    this->w *= v.w;
    return *this;
  }

  inline Vector4 operator^(const Vector4& v) const {
    Vector4 out(*this);
    out ^= v;
    return out;
  }

  inline bool operator==(const Vector4& v) const {
    return (this->x == v.x) && (this->y == v.y) && (this->z == v.z)
        && (this->w == v.w);
  }

  inline bool operator!=(const Vector4& v) const {
    return (this->x != v.x) || (this->y != v.y) || (this->z != v.z)
        || (this->w != v.w);
  }

  double x = 0;
  double y = 0;
  double z = 0;
  double w = 0;
};

} /* namespace three */

#endif /* THREE_MATH_VECTOR4_H_ */
