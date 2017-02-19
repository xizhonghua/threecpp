/*
 * Mesh.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_OBJECTS_MESH_H_
#define SRC_OBJECTS_MESH_H_

#include <core/Object3D.h>
#include <core/Geometry.h>
#include <materials/Material.h>

namespace three {

class Mesh: public Object3D {
public:

  // Create a mesh with geometry and material
  // does not own any of non-null objects
  // if any of the parameter is null, will create and own it
  Mesh(Geometry* geometry, Material* material);
  ~Mesh();

  Geometry* const getGeomtry() const {
    return geometry_;
  }

  Material* const getMaterial() const {
    return material_;
  }

protected:
  Geometry* geometry_;
  bool own_geometry_ { false };
  Material* material_;
  bool own_material_ { false };
};

} /* namespace three */

#endif /* SRC_OBJECTS_MESH_H_ */
