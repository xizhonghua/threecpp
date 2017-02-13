/*
 * Mesh.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <objects/Mesh.h>
#include <materials/MeshBasicMaterial.h>

namespace three {

Mesh::Mesh(Geometry* geometry, Material* material) :
    geometry_(geometry), material_(material) {

  if (geometry_ == nullptr) {
    own_geometry_ = true;
  }

  if (material_ == nullptr) {
    material_ = new MeshBasicMaterial();
    own_material_ = true;
  }
}

Mesh::~Mesh() {
  if (own_geometry_) {
    delete geometry_;
    own_geometry_ = false;
  }

  if (own_material_) {
    delete material_;
    own_material_ = false;
  }

  geometry_ = nullptr;
  material_ = nullptr;
}

} /* namespace three */
