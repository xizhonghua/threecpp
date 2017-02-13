/*
 * Scene.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_SCENES_SCENE_H_
#define SRC_SCENES_SCENE_H_

#include "core/Object3D.h"

namespace three {

class Scene: public Object3D {
public:
  Scene();
  ~Scene();

  bool autoUpdate { true };
};

} /* namespace three */

#endif /* SRC_SCENES_SCENE_H_ */
