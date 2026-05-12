/*
 * OrthographicCamera.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include <three/cameras/OrthographicCamera.h>

namespace three {


OrthographicCamera::OrthographicCamera(double frustumSize, double aspect, double near,
      double far): left(-0.5 * frustumSize * aspect), right(0.5 * frustumSize * aspect), top(0.5 * frustumSize), bottom(-0.5 * frustumSize), near(near), far(far) {
  this->frustumSize = frustumSize;
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

void OrthographicCamera::onResize(int width, int height) {
  aspect = static_cast<double>(width) / height;
  if (frustumSize > 0) {
    left = -0.5 * frustumSize * aspect;
    right = 0.5 * frustumSize * aspect;
    top = frustumSize / 2;
    bottom = -frustumSize / 2;
  }
  updateProjectionMatrix();
}


} /* namespace three */
