/*
 * Mesh.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_OBJECTS_MESH_H_
#define THREE_OBJECTS_MESH_H_

#include <three/core/Geometry.h>
#include <three/materials/Material.h>
#include <three/objects/RenderableObject.h>

namespace three {

class Mesh: public RenderableObject {
public:

  // Create a mesh with geometry and material
  // does not own any of non-null objects
  // if any of the parameter is null, will create and own it
  Mesh(Geometry* geometry, Material* material);
  ~Mesh();

};

} /* namespace three */

#endif /* THREE_OBJECTS_MESH_H_ */
