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

  double w, x, y, z;

  if (trace > 0) {

    s = 0.5 / sqrt(trace + 1.0);

    w = 0.25 / s;
    x = (m32 - m23) * s;
    y = (m13 - m31) * s;
    z = (m21 - m12) * s;

  } else if (m11 > m22 && m11 > m33) {

    s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

    w = (m32 - m23) / s;
    x = 0.25 * s;
    y = (m12 + m21) / s;
    z = (m13 + m31) / s;

  } else if (m22 > m33) {

    s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

    w = (m13 - m31) / s;
    x = (m12 + m21) / s;
    y = 0.25 * s;
    z = (m23 + m32) / s;

  } else {

    s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

    w = (m21 - m12) / s;
    x = (m13 + m31) / s;
    y = (m23 + m32) / s;
    z = 0.25 * s;

  }

  // Trigger the callback
  this->set(x, y, z, w);

  return *this;
}

Quaternion& Quaternion::setFromEular(const Euler& e, bool update) {

  // Convert propoerty to double...
  double tx = e.x, ty = e.y, tz = e.z;
  auto order = e.order;

  // http://www.mathworks.com/matlabcentral/fileexchange/
  //  20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
  //  content/SpinCalc.m

  auto c1 = cos(tx / 2);
  auto c2 = cos(ty / 2);
  auto c3 = cos(tz / 2);

  auto s1 = sin(tx / 2);
  auto s2 = sin(ty / 2);
  auto s3 = sin(tz / 2);

  double tw;

  if (order == EulerOrder::XYZ) {

    tx = s1 * c2 * c3 + c1 * s2 * s3;
    ty = c1 * s2 * c3 - s1 * c2 * s3;
    tz = c1 * c2 * s3 + s1 * s2 * c3;
    tw = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::YXZ) {

    tx = s1 * c2 * c3 + c1 * s2 * s3;
    ty = c1 * s2 * c3 - s1 * c2 * s3;
    tz = c1 * c2 * s3 - s1 * s2 * c3;
    tw = c1 * c2 * c3 + s1 * s2 * s3;

  } else if (order == EulerOrder::ZXY) {

    tx = s1 * c2 * c3 - c1 * s2 * s3;
    ty = c1 * s2 * c3 + s1 * c2 * s3;
    tz = c1 * c2 * s3 + s1 * s2 * c3;
    tw = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::ZYX) {

    tx = s1 * c2 * c3 - c1 * s2 * s3;
    ty = c1 * s2 * c3 + s1 * c2 * s3;
    tz = c1 * c2 * s3 - s1 * s2 * c3;
    tw = c1 * c2 * c3 + s1 * s2 * s3;

  } else if (order == EulerOrder::YZX) {

    tx = s1 * c2 * c3 + c1 * s2 * s3;
    ty = c1 * s2 * c3 + s1 * c2 * s3;
    tz = c1 * c2 * s3 - s1 * s2 * c3;
    tw = c1 * c2 * c3 - s1 * s2 * s3;

  } else if (order == EulerOrder::XZY) {

    tx = s1 * c2 * c3 - c1 * s2 * s3;
    ty = c1 * s2 * c3 - s1 * c2 * s3;
    tz = c1 * c2 * s3 + s1 * s2 * c3;
    tw = c1 * c2 * c3 + s1 * s2 * s3;
  }

  if (update) {
    // Trigger the callback
    this->set(tx, ty, tz, tw);
  } else {
    this->x.set(tx);
    this->y.set(ty);
    this->z.set(tz);
    this->w.set(tw);
  }

  return *this;
}

} /* namespace three */
