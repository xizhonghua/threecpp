/*
 * Euler.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_EULER_H_
#define THREE_MATH_EULER_H_

#include <three/core/Property.h>

namespace three {

enum class EulerOrder {
  XYZ = 1, YZX = 2, ZXY = 3, XZY = 4, YXZ = 5, ZYX = 6
};

class Euler {
public:

  Euler(double x = 0, double y = 0, double z = 0, EulerOrder order =
      EulerOrder::XYZ) :
      x { x }, y { y }, z { z }, order { order } {

  }

  inline Euler& set(double x, double y, double z, EulerOrder order) {
    this->x.set(x);
    this->y.set(y);
    this->z.set(z);
    this->order = order;
    this->callback_();
    return *this;
  }

  ~Euler() {

  }

  // Only supports one callback
  void onChanged(CallbackFunc callback) {
    x.setCallbackFunc(callback);
    y.setCallbackFunc(callback);
    z.setCallbackFunc(callback);
    callback_ = callback;
  }

  Property<double> x;
  Property<double> y;
  Property<double> z;
  EulerOrder order { EulerOrder::XYZ };
private:
  CallbackFunc callback_;
};

} /* namespace three */

#endif /* THREE_MATH_EULER_H_ */
