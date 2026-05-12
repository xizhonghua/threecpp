/*
 * MeshBasicMatrial.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <three/materials/MeshBasicMaterial.h>

namespace three {

MeshBasicMaterial::MeshBasicMaterial() {
}

MeshBasicMaterial::MeshBasicMaterial(const Color& color, bool wireframe) {
  this->color(color);
  this->wireframe(wireframe);
}

MeshBasicMaterial::~MeshBasicMaterial() {
}

} /* namespace three */
