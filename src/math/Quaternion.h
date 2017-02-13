/*
 * Quaternion.h
 *
 *  Created on: Feb 12, 2017
 *      Author: zxi
 */

#ifndef SRC_MATH_QUATERNION_H_
#define SRC_MATH_QUATERNION_H_

#include <cmath>

#include "math/Vector3.h"
#include "math/Matrix4.h"

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

  inline Quaternion& setFromRotationMatrix(const Matrix4& m) {
    //TODO(zxi)
    return *this;
  }

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

#endif /* SRC_MATH_QUATERNION_H_ */
