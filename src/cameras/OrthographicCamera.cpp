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
    left_(left), right_(right), top_(top), bottom_(bottom), near_(near), far_(
        far) {

  this->updateProjectionMatrix();
}

OrthographicCamera::~OrthographicCamera() {

}

void OrthographicCamera::updateProjectionMatrix() {

  double dx = (this->right_ - this->left_) / (2 * this->zoom_);
  double dy = (this->top_ - this->bottom_) / (2 * this->zoom_);
  double cx = (this->right_ + this->left_) / 2;
  double cy = (this->top_ + this->bottom_) / 2;

  double left = cx - dx;
  double right = cx + dx;
  double top = cy + dy;
  double bottom = cy - dy;

  this->projectionMatrix_.asOrthographic(left, right, top, bottom, this->near_,
      this->far_);
}

} /* namespace three */
