/*
 * OpenGLRenderer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_OPENGLRENDERER_H_
#define SRC_RENDERERS_OPENGLRENDERER_H_

namespace three {
class Camera;
class Mesh;
class Object3D;
class Scene;
}

namespace three {

class OpenGLRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  void render(Scene* scene, Camera* camera);

protected:
  void renderObject(Object3D* object);
  void renderMesh(Mesh* mesh);
};

} /* namespace three */

#endif /* SRC_RENDERERS_OPENGLRENDERER_H_ */
