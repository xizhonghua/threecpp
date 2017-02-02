/*
 * Ojbect3D.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef CORE_OBJECT3D_H_
#define CORE_OBJECT3D_H_

#include <vector>

#include "math/Vector3.h"

namespace three {

class Object3D {
public:
  Object3D();
  ~Object3D();



  Vector3 position;
  Vector3 scale { 1, 1, 1 };

  Object3D* parent = nullptr;
  std::vector<Object3D*> children;

  static long long object3DId;
};

} /* namespace three */

#endif /* CORE_OBJECT3D_H_ */
