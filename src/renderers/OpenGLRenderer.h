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
class Material;
class Mesh;
class Object3D;
class Scene;
}

namespace three {

class OpenGLRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  void setSize(int width, int height);

  void render(Scene* scene, Camera* camera);

protected:
  void prepareMaterial(Material* material);
  void renderObject(Object3D* object);
  void renderMesh(Mesh* mesh);
  void updateProjectionMatrix(Camera* camera);

  int width_ {0};
  int height_ {0};

  bool first_ {true};
};

} /* namespace three */

#endif /* SRC_RENDERERS_OPENGLRENDERER_H_ */
