/*
 * Quaternion.h
 *
 *  Created on: Feb 12, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_QUATERNION_H_
#define THREE_MATH_QUATERNION_H_

#include <cmath>

#include <three/core/Property.h>
#include <three/math/Vector3.h>
#include <three/math/Matrix4.h>

namespace three {
class Euler;
}

namespace three {

class Quaternion {
public:

  Quaternion(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) :
      x { 0 }, y { 0 }, z { 0 }, w { 1 } {
  }

  ~Quaternion() {
  }

  inline Quaternion& set(double x, double y, double z, double w) {
    this->x.set(x);
    this->y.set(y);
    this->z.set(z);
    this->w.set(w);

    if (callback_ != nullptr)
      this->callback_();

    return *this;
  }

  Quaternion& setFromRotationMatrix(const Matrix4& m);
  Quaternion& setFromEular(const Euler& e);

  inline Quaternion& setFromAxisAngle(const Vector3& axis, double angle) {

    double halfAngle = angle / 2;
    double s = sin(halfAngle);

    this->x.set(axis.x * s);
    this->y.set(axis.y * s);
    this->z.set(axis.z * s);
    this->w.set(cos(halfAngle));

    if (callback_ != nullptr)
      this->callback_();

    return *this;
  }

  void onChanged(CallbackFunc callback) {
    x.setCallbackFunc(callback);
    y.setCallbackFunc(callback);
    z.setCallbackFunc(callback);
    w.setCallbackFunc(callback);

    callback_ = callback;
  }

  Property<double> x { 0.0 };
  Property<double> y { 0.0 };
  Property<double> z { 0.0 };
  Property<double> w { 0.0 };

private:
  CallbackFunc callback_;

};

} /* namespace three */

#endif /* THREE_MATH_QUATERNION_H_ */
