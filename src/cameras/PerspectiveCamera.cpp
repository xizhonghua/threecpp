/*
 * PerspectiveCamera.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <cameras/PerspectiveCamera.h>

#include <iostream>

namespace three {

PerspectiveCamera::PerspectiveCamera(double fov, double aspect, double near,
    double far) :
    fov_(fov), aspect_(aspect), near_(near), far_(far) {
  this->updateProjectionMatrix();
}

void PerspectiveCamera::updateProjectionMatrix() {
  double near = this->near_;
  double top = near * tan(0.5 * this->fov_ / 180 * M_PI) / this->zoom_;
  double height = 2 * top;
  double width = this->aspect_ * height;
  double left = -0.5 * width;

  this->projectionMatrix_.asPerspective(left, left + width, top, top - height,
      near, this->far_);
}

} /* namespace three */
