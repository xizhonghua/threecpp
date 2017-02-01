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
  Vector2(const Vector2&& v) = default;
  Vector2& operator=(const Vector2& v) = default;
  ~Vector2();

  // get
  const double operator[](int index) const;
  // set
  double& operator[](int index);

  // return a new copy of this
  Vector2 clone();

  // return this
  Vector2& set(double x, double y);
  Vector2& copy(const Vector2& v);
  Vector2& min(const Vector2& v);
  Vector2& max(const Vector2& v);
  Vector2& clamp(const Vector2& min_v, const Vector2& max_v);

  // Operators
  Vector2 operator+(const double scalar) const;
  Vector2 operator-(const double scalar) const;
  Vector2 operator*(const double scalar) const;
  Vector2 operator/(const double scalar) const;

  Vector2 operator+(const Vector2& v) const;
  Vector2 operator-(const Vector2& v) const;
  Vector2 operator*(const Vector2& v) const;
  Vector2 operator/(const Vector2& v) const;



  double x;
  double y;
};

} /* namespace three */

#endif /* MATH_VECTOR2_H_ */
