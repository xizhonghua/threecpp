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
    fov(fov), near(near), far(far) {

  this->aspect = aspect;
  this->updateProjectionMatrix();
}

void PerspectiveCamera::updateProjectionMatrix() {
  double near = this->near;
  double top = near * tan(0.5 * this->fov / 180 * M_PI) / this->zoom;
  double height = 2 * top;
  double width = this->aspect * height;
  double left = -0.5 * width;

  this->projectionMatrix_.asPerspective(left, left + width, top, top - height,
      near, this->far);
}

} /* namespace three */
