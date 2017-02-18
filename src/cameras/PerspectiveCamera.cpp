/*
 * PerspectiveCamera.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <cameras/PerspectiveCamera.h>

namespace three {

PerspectiveCamera::PerspectiveCamera(double fov, double aspect, double near,
    double far) :
    fov(fov), aspect(aspect), near(near), far(far) {
  this->updateProjectionMatrix();
}

} /* namespace three */
