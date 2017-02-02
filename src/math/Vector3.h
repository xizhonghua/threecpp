/*
 * Vector3.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

namespace three {

class Vector3 {
public:
  Vector3();
  Vector3(double x, double y, double z);
  Vector3(const Vector3& v);
  Vector3(Vector3&& v) = default;
  Vector3& operator=(const Vector3& v) = default;
  ~Vector3();

  inline Vector3& set(double x = 0, double y = 0, double z = 0);

  double x = 0;
  double y = 0;
  double z = 0;
};

} /* namespace three */

#endif /* MATH_VECTOR3_H_ */
