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
#include <three/math/Matrix3.h>
#include <three/math/Matrix4.h>


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

  // update the matrix of the object
  void updateMatrix();

  // update the world matrix of the object
  void updateMatrixWorld(bool force = false);

  Vector3 position { 0, 0, 0 };
  Vector3 up { DefaultUp };

  Euler rotation { 0, 0, 0, EulerOrder::XYZ };
  Vector3 scale { 1, 1, 1 };
  Quaternion quaternion { 0, 0, 0, 1 };

  Matrix4 matrix;
  Matrix4 matrixWorld;

  Matrix4 modelViewMatrix;
  Matrix3 normalMatrix;

  bool matrixAutoUpdate { DefaultMatrixAutoUpdate };
  bool matrixWorldNeedsUpdate { false };

  bool visible { true };

  bool castShadow { false };
  bool receiveShadow { false };

  bool frustumCulled { true };
  int renderOrder { 0 };

  /////////////////////////////////////////////////////////////////////////////
  // Parent/Children
  /////////////////////////////////////////////////////////////////////////////
  Object3D* parent { nullptr };
  std::vector<Object3D*> children;

  /////////////////////////////////////////////////////////////////////////////
  // Type of the object
  /////////////////////////////////////////////////////////////////////////////
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

  /////////////////////////////////////////////////////////////////////////////
  // Static members
  /////////////////////////////////////////////////////////////////////////////

  // Default is {0, 1, 0}
  const static Vector3 DefaultUp;
  // Default is true
  const static bool DefaultMatrixAutoUpdate;

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

private:

};

} /* namespace three */

#endif /* CORE_OBJECT3D_H_ */
