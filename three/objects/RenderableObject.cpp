/*
 * RenderableObject.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include <three/objects/RenderableObject.h>

#include <three/core/Geometry.h>
#include <three/materials/Material.h>


namespace three {

RenderableObject::RenderableObject(Geometry* geometry, Material* material) :
    geometry_(geometry), material_(material) {

  this->isMesh_ = true;
  this->type_ = "Mesh";

}


} /* namespace three */
