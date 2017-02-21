/*
 * OrthographicCamera.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include <cameras/OrthographicCamera.h>

namespace three {

OrthographicCamera::OrthographicCamera(double left, double right, double top,
    double bottom, double near, double far) :
    left(left), right(right), top(top), bottom(bottom), near(near), far(
        far) {

  this->type_ = "OrthographicCamera";

  this->updateProjectionMatrix();
}

OrthographicCamera::~OrthographicCamera() {

}

void OrthographicCamera::updateProjectionMatrix()  {

  double dx = (this->right - this->left) / (2 * this->zoom);
  double dy = (this->top - this->bottom) / (2 * this->zoom);
  double cx = (this->right + this->left) / 2;
  double cy = (this->top + this->bottom) / 2;

  double left = cx - dx;
  double right = cx + dx;
  double top = cy + dy;
  double bottom = cy - dy;

  this->projectionMatrix_.asOrthographic(left, right, top, bottom, this->near,
      this->far);
}

} /* namespace three */
