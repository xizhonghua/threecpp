/*
 * RenderableObject.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include <objects/RenderableObject.h>

#include <core/Geometry.h>
#include <materials/Material.h>


namespace three {

RenderableObject::RenderableObject(Geometry* geometry, Material* material) :
    geometry_(geometry), material_(material) {

  this->isMesh_ = true;
  this->type_ = "Mesh";

}

RenderableObject::~RenderableObject() {
}

} /* namespace three */
