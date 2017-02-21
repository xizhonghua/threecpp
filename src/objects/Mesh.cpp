/*
 * Mesh.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <objects/Mesh.h>

namespace three {

Mesh::Mesh(Geometry* geometry, Material* material) :
    RenderableObject(geometry, material) {

  this->isMesh_ = true;
  this->type_ = "Mesh";
}

Mesh::~Mesh() {

}

} /* namespace three */
