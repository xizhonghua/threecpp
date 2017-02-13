/*
 * Euler.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_MATH_EULER_H_
#define SRC_MATH_EULER_H_

namespace three {

enum class EulerOrder {
  XYZ = 1, YZX = 2, ZXY = 3, XZY = 4, YXZ = 5, ZYX = 6
};

class Euler {
public:
  Euler() {

  }

  inline Euler& set(double x, double y, double z, EulerOrder order) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->order = order;

    return *this;
  }

  ~Euler();

  double x { 0 };
  double y { 0 };
  double z { 0 };
  EulerOrder order { EulerOrder::XYZ };
};

} /* namespace three */

#endif /* SRC_MATH_EULER_H_ */
