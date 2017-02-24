/*
 * Quaternion.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: zxi
 */

#include <three/math/Quaternion.h>

#include <cmath>
#include <three/math/Euler.h>

namespace three {

Quaternion& Quaternion::setFromRotationMatrix(const Matrix4& m) {

  // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

  // assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

  auto te = m.elements;

  double m11 = te[0], m12 = te[4], m13 = te[8], m21 = te[1], m22 = te[5], m23 =
      te[9], m31 = te[2], m32 = te[6], m33 = te[10], trace = m11 + m22 + m33, s;

  if (trace > 0) {

    s = 0.5 / sqrt(trace + 1.0);

    this->w = 0.25 / s;
    this->x = (m32 - m23) * s;
    this->y = (m13 - m31) * s;
    this->z = (m21 - m12) * s;

  } else if (m11 > m22 && m11 > m33) {

    s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

    this->w = (m32 - m23) / s;
    this->x = 0.25 * s;
    this->y = (m12 + m21) / s;
    this->z = (m13 + m31) / s;

  } else if (m22 > m33) {

    s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

    this->w = (m13 - m31) / s;
    this->x = (m12 + m21) / s;
    this->y = 0.25 * s;
    this->z = (m23 + m32) / s;

  } else {

    s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

    this->w = (m21 - m12) / s;
    this->x = (m13 + m31) / s;
    this->y = (m23 + m32) / s;
    this->z = 0.25 * s;

  }

  return *this;
}

Quaternion& Quaternion::setFromEular(const Euler& e) {

  auto x = e.x, y = e.y, z = e.z;
  auto order = e.order;

  // http://www.mathworks.com/matlabcentral/fileexchange/
  //  20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
  //  content/SpinCalc.m

  auto c1 = cos(x / 2);
  auto c2 = cos(y / 2);
  auto c3 = cos(z / 2);

  auto s1 = sin(x / 2);
  auto s2 = sin(y / 2);
  auto s3 = sin(z / 2);

  if (order == EulerOrder::XYZ) {

    this->x = s1 * c2 * c3 + c1 * s2 * s3;
    this->y = c1 * s2 * c3 - s1 * c2 * s3;
    this->z = c1 * c2 * s3 + s1 * s2 * c3;
    this->w = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::YXZ) {

    this->x = s1 * c2 * c3 + c1 * s2 * s3;
    this->y = c1 * s2 * c3 - s1 * c2 * s3;
    this->z = c1 * c2 * s3 - s1 * s2 * c3;
    this->w = c1 * c2 * c3 + s1 * s2 * s3;

  } else if (order == EulerOrder::ZXY) {

    this->x = s1 * c2 * c3 - c1 * s2 * s3;
    this->y = c1 * s2 * c3 + s1 * c2 * s3;
    this->z = c1 * c2 * s3 + s1 * s2 * c3;
    this->w = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::ZYX) {

    this->x = s1 * c2 * c3 - c1 * s2 * s3;
    this->y = c1 * s2 * c3 + s1 * c2 * s3;
    this->z = c1 * c2 * s3 - s1 * s2 * c3;
    this->w = c1 * c2 * c3 + s1 * s2 * s3;

  } else if (order == EulerOrder::YZX) {

    this->x = s1 * c2 * c3 + c1 * s2 * s3;
    this->y = c1 * s2 * c3 + s1 * c2 * s3;
    this->z = c1 * c2 * s3 - s1 * s2 * c3;
    this->w = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::XZY) {

    this->x = s1 * c2 * c3 - c1 * s2 * s3;
    this->y = c1 * s2 * c3 - s1 * c2 * s3;
    this->z = c1 * c2 * s3 + s1 * s2 * c3;
    this->w = c1 * c2 * c3 + s1 * s2 * s3;

  }

  return *this;
}

} /* namespace three */
