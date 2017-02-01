/*
 * Vector2.h
 *
 *  Created on: Feb 1, 2017
 *      Author: zxi
 */

#ifndef MATH_VECTOR2_H_
#define MATH_VECTOR2_H_

namespace three {

class Vector2 {
public:
  Vector2();
  Vector2(double x, double y);
  Vector2(const Vector2& v);
  Vector2(Vector2&& v) = default;
  Vector2& operator=(const Vector2& v) = default;
  ~Vector2();

  // get
  const double operator[](int index) const;
  // set
  double& operator[](int index);

  // properties
  inline double lengthSq() const;
  inline double length() const;
  inline double lengthManhattan() const;

  // computes the angle in radians with respect to the positive x-axis
  inline double angle() const;

  // return a new copy of this
  Vector2 clone();

  // return this
  inline Vector2& set(double x, double y);

  Vector2& copy(const Vector2& v);
  Vector2& min(const Vector2& v);
  Vector2& max(const Vector2& v);
  Vector2& clamp(const Vector2& min_v, const Vector2& max_v);

  inline Vector2& normailize();

  // Operators


  Vector2 operator+(const double scalar) const;
  Vector2 operator-(const double scalar) const;
  Vector2 operator*(const double scalar) const;
  Vector2 operator/(const double scalar) const;

  Vector2& operator+=(const double scalar);
  Vector2& operator-=(const double scalar);
  Vector2& operator*=(const double scalar);
  Vector2& operator/=(const double scalar);

  Vector2 operator+(const Vector2& v) const;
  Vector2 operator-(const Vector2& v) const;
  Vector2 operator*(const Vector2& v) const;
  Vector2 operator/(const Vector2& v) const;

  bool operator==(const Vector2& v) const;
  bool operator!=(const Vector2& v) const;

  Vector2& operator+=(const Vector2& v);
  Vector2& operator-=(const Vector2& v);
  Vector2& operator*=(const Vector2& v);
  Vector2& operator/=(const Vector2& v);

  double x;
  double y;
};

} /* namespace three */

#endif /* MATH_VECTOR2_H_ */
