/*
 * Mesh.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_OBJECTS_MESH_H_
#define SRC_OBJECTS_MESH_H_

#include <core/Geometry.h>
#include <materials/Material.h>
#include <objects/RenderableObject.h>

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

#endif /* SRC_OBJECTS_MESH_H_ */
