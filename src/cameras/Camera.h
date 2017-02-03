/*
 * Camera.h
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#ifndef CAMERAS_CAMERA_H_
#define CAMERAS_CAMERA_H_

#include "core/Object3D.h"

namespace three {

class Camera: public Object3D {
public:
  Camera();
  ~Camera();
};

} /* namespace three */

#endif /* CAMERAS_CAMERA_H_ */
