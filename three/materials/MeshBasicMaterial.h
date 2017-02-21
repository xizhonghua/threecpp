/*
 * MeshBasicMatrial.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_MATERIALS_MESHBASICMATERIAL_H_
#define THREE_MATERIALS_MESHBASICMATERIAL_H_

#include <three/materials/Material.h>

#include <three/math/Color.h>

namespace three {

class MeshBasicMaterial: public Material {
public:
  MeshBasicMaterial();
  ~MeshBasicMaterial();
};

} /* namespace three */

#endif /* THREE_MATERIALS_MESHBASICMATERIAL_H_ */
