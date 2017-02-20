/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <renderers/OpenGLRenderer.h>

#include <cmath>
#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include "three.h"

using namespace std;

namespace three {

OpenGLRenderer::OpenGLRenderer() {
}

OpenGLRenderer::~OpenGLRenderer() {
}

void OpenGLRenderer::setSize(int width, int height) {
  width_ = width;
  height_ = height;
}

void OpenGLRenderer::render(Scene* scene, Camera* camera) {

  updateProjectionMatrix(camera);

  glMatrixMode(GL_MODELVIEW);

  auto f = [=](Object3D* object) {
    this->renderObject(object);
  };

  scene->traverseVisible(f);
}

void OpenGLRenderer::updateProjectionMatrix(Camera* camera) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMultMatrixd(camera->projectionMatrix().elements);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //TODO(zxi) use camera up
  glMultMatrixd(
      Matrix4::makeLookAt(camera->position, Vector3 { 0, 0, 0 }, Vector3 { 0, 1,
          0 }).elements);

//  GLKMatrix4MakeLookAt()
}

void OpenGLRenderer::renderObject(Object3D* object) {

  glPushMatrix();
  glRotated(object->rotation.x, 1, 0, 0);
  glRotated(object->rotation.y, 0, 1, 0);
  glRotated(object->rotation.z, 0, 0, 1);

  Mesh* mesh = dynamic_cast<Mesh*>(object);

  if (mesh != nullptr) {
    this->renderMesh(mesh);
  }

  glPopMatrix();
}

void OpenGLRenderer::prepareMaterial(Material* material) {

  glColor3f(material->color().r, material->color().g, material->color().b);

}

void OpenGLRenderer::renderMesh(Mesh* mesh) {

  prepareMaterial(mesh->getMaterial());

  Geometry* const geom = mesh->getGeomtry();
  glBegin(GL_LINES);

  for (const Face3& f : geom->faces) {
    std::vector<Vector3*> vs = { &(geom->vertices[f.a]), &(geom->vertices[f.b]),
        &(geom->vertices[f.c]) };

    for (int i = 1; i <= 3; ++i) {
      const auto v0 = vs[i - 1];
      const auto v1 = vs[i % 3];
      glVertex3d(v0->x, v0->y, v0->z);
      glVertex3d(v1->x, v1->y, v1->z);
    }
  }

  glEnd();
}

} /* namespace three */
