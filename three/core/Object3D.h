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
#include <string>

#include <three/core/Object3D.h>
#include <three/math/Euler.h>
#include <three/math/Quaternion.h>
#include <three/math/Vector3.h>

namespace three {

class Object3D {
public:
  Object3D();
  virtual ~Object3D();

  Object3D& add(Object3D* child);
  Object3D& remove(Object3D* child);

  // Traverse the object and all its children recursively
  void traverse(std::function<void(Object3D* object)> callback);

  // Traverse the object and all its children recursively if visible
  void traverseVisible(std::function<void(Object3D* object)> callback);

  // Type of the object
  std::string type() const {
    return this->type_;
  }

  bool isCamera() const {
    return this->isCamera_;
  }

  bool isLight() const {
    return this->isLight_;
  }

  bool isLine() const {
    return this->isLine_;
  }

  bool isMesh() const {
    return this->isMesh_;
  }

  bool isPoint() const {
    return this->isPoint_;
  }

  unsigned long long id() const {
    return this->id_;
  }

  bool visible { true };
  Vector3 position { 0, 0, 0 };
  Vector3 up { defaultUp };

  Euler rotation { 0, 0, 0, EulerOrder::XYZ };
  Vector3 scale { 1, 1, 1 };
  Quaternion quaternion { 0, 0, 0, 1 };

  Object3D* parent { nullptr };
  std::vector<Object3D*> children;

  /////////////////////////////////////////////////////////////////////////////
  // Static members
  /////////////////////////////////////////////////////////////////////////////

  // Default is {0, 1, 0}
  const static Vector3 defaultUp;

  static unsigned long long object3DId;

protected:

  std::string type_ { "Object3D" };

  unsigned long long id_ { 0 };

  // Object categories
  bool isCamera_ { false };
  bool isLight_ { false };
  bool isLine_ { false };
  bool isMesh_ { false };
  bool isPoint_ { false };

};

} /* namespace three */

#endif /* CORE_OBJECT3D_H_ */
