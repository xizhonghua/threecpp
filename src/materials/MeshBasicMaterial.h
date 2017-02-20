/*
 * MeshBasicMatrial.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef MATERIALS_MESHBASICMATERIAL_H_
#define MATERIALS_MESHBASICMATERIAL_H_

#include <materials/Material.h>

#include <math/Color.h>

namespace three {

class MeshBasicMaterial: public Material {
public:
  MeshBasicMaterial();
  ~MeshBasicMaterial();
};

} /* namespace three */

#endif /* MATERIALS_MESHBASICMATERIAL_H_ */
