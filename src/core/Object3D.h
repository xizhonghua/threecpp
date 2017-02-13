/*
 * Ojbect3D.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef CORE_OBJECT3D_H_
#define CORE_OBJECT3D_H_

#include <vector>
#include <functional>

#include "math/Euler.h"
#include "math/Quaternion.h"
#include "math/Vector3.h"

namespace three {

class Object3D {
public:
  Object3D();
  ~Object3D();

  Object3D& add(Object3D* child);
  Object3D& remove(Object3D* child);

  // Traverse the object and all its children recursively
  void traverse(std::function<void(Object3D* object)> callback);

  // Traverse the object and all its children recursively if visible
  void traverseVisible(std::function<void(Object3D* object)> callback);

  bool visible { true };
  Vector3 position { 0, 0, 0 };
  Vector3 up { defaultUp };

  Euler rotation { 0, 0, 0, EulerOrder::XYZ };
  Vector3 scale { 1, 1, 1 };
  Quaternion quaternion { 0, 0, 0, 1 };

  Object3D* parent { nullptr };
  std::vector<Object3D*> children;

  // Default is {0, 1, 0}
  const static Vector3 defaultUp;

  static long long object3DId;
};

} /* namespace three */

#endif /* CORE_OBJECT3D_H_ */
