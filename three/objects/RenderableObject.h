/*
 * RenderableObject.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef THREE_OBJECTS_RENDERABLEOBJECT_H_
#define THREE_OBJECTS_RENDERABLEOBJECT_H_

#include <three/core/Object3D.h>

// An interface of renderable objects, which has geometry and materials...
namespace three {

class Geometry;
class Material;

class RenderableObject: public Object3D {
public:
  RenderableObject(Geometry* geometry, Material* material);
  virtual ~RenderableObject();

  Geometry* const getGeomtry() const {
    return geometry_;
  }

  Material* const getMaterial() const {
    return material_;
  }

protected:
  Geometry* geometry_;
  Material* material_;
};

} /* namespace three */

#endif /* THREE_OBJECTS_RENDERABLEOBJECT_H_ */
