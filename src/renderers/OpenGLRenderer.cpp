/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <renderers/OpenGLRenderer.h>

#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GLKit/GLKMatrix4.h>

#include <cameras/Camera.h>
#include <scenes/Scene.h>
#include <objects/Mesh.h>

using namespace std;

namespace three {

OpenGLRenderer::OpenGLRenderer() {
  // TODO Auto-generated constructor stub

}

OpenGLRenderer::~OpenGLRenderer() {
  // TODO Auto-generated destructor stub
}

void OpenGLRenderer::render(Scene* scene, Camera* camera) {

  //glViewport(0, 0, 640, 640);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1.0, 0, 1e5);

//  glMultMatrix( GLKMatrix4MakePerspective(60, 1.0, -100, 1e5));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(camera->position.x, camera->position.y, camera->position.z, 0, 0, 0,
//      0, 1, 0);

  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  auto f = [=](Object3D* object) {
    this->renderObject(object);
  };

  scene->traverseVisible(f);

  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void OpenGLRenderer::renderObject(Object3D* object) {

//  glPushMatrix();
  glRotated(object->rotation.x, 1, 0, 0);
  glRotated(object->rotation.y, 0, 1, 0);
  glRotated(object->rotation.z, 0, 0, 1);

  Mesh* mesh = dynamic_cast<Mesh*>(object);

  if (mesh != nullptr) {
    this->renderMesh(mesh);
  }

//  glPopMatrix();
}

void OpenGLRenderer::renderMesh(Mesh* mesh) {

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
