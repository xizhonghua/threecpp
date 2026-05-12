/*
 * MeshPhongMaterial.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <three/materials/MeshPhongMaterial.h>

namespace three {

MeshPhongMaterial::MeshPhongMaterial() {
}

MeshPhongMaterial::MeshPhongMaterial(const Color& color, const Color& emissive,
                                     const Color& specular, float shininess) {
  this->color(color);
  this->emissive(emissive);
  this->specular(specular);
  this->shininess(shininess);
}

MeshPhongMaterial::~MeshPhongMaterial() {
}

} /* namespace three */