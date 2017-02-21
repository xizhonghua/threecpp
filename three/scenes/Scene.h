/*
 * Scene.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_SCENES_SCENE_H_
#define THREE_SCENES_SCENE_H_

#include <three/core/Object3D.h>

namespace three {

class Scene: public Object3D {
public:
  Scene();
  ~Scene();

  bool autoUpdate { true };
};

} /* namespace three */

#endif /* THREE_SCENES_SCENE_H_ */
