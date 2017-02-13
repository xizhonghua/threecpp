/*
 * OpenGLRenderer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_OPENGLRENDERER_H_
#define SRC_RENDERERS_OPENGLRENDERER_H_

namespace three {
class Scene;
class Camera;
}

namespace three {

class OpenGLRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  void render(Scene* scene, Camera* camera);
};

} /* namespace three */

#endif /* SRC_RENDERERS_OPENGLRENDERER_H_ */
