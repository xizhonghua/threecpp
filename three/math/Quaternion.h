/*
 * Quaternion.h
 *
 *  Created on: Feb 12, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_QUATERNION_H_
#define THREE_MATH_QUATERNION_H_

#include <cmath>

#include <three/math/Vector3.h>
#include <three/math/Matrix4.h>

namespace three {
class Euler;
}

namespace three {


class Quaternion {
public:

  Quaternion(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) {
    this->set(x, y, z, w);
  }

  ~Quaternion() {
  }

  inline Quaternion& set(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;

    return *this;
  }

  Quaternion& setFromRotationMatrix(const Matrix4& m);
  Quaternion& setFromEular(const Euler& e);

  inline Quaternion& setFromAxisAngle(const Vector3& axis, double angle) {

    double halfAngle = angle / 2;
    double s = sin(halfAngle);

    this->x = axis.x * s;
    this->y = axis.y * s;
    this->z = axis.z * s;
    this->w = cos(halfAngle);

    return *this;
  }



  double x { 0.0 };
  double y { 0.0 };
  double z { 0.0 };
  double w { 0.0 };
};

} /* namespace three */

#endif /* THREE_MATH_QUATERNION_H_ */
