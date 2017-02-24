/*
 * Euler.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_EULER_H_
#define THREE_MATH_EULER_H_

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
    this->x = x;
    this->y = y;
    this->z = z;
    this->order = order;

    return *this;
  }

  ~Euler() {

  }

  // Check whether the object changed or not.
  bool changed() const {
    return x != lx_ || y != ly_ || z != lz_;
  }

  // Make the object as fresh
  void markAsUpdated() {
    lx_ = x;
    ly_ = y;
    lz_ = z;
  }

  double x { 0 };
  double y { 0 };
  double z { 0 };
  EulerOrder order { EulerOrder::XYZ };

private:
  double lx_ { 0 };
  double ly_ { 0 };
  double lz_ { 0 };
};

} /* namespace three */

#endif /* THREE_MATH_EULER_H_ */
