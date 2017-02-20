/*
 * cameras.cc
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include "three.h"
using namespace three;

namespace {
class CameraExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 60, width_ * 1.0 / height_, 1, 10000 };
  BoxGeometry geometry { 200, 200, 200 };
  MeshBasicMaterial material1, material2;
  Mesh mesh1 { &geometry, &material1 }, mesh2 { &geometry, &material2 };
  OpenGLRenderer renderer;

public:
  CameraExample() :
      WindowApp(800, 450, "examples/cameras") {
  }

  void initScene() override {
    renderer.setSize(width_, height_);

    camera.position.z = 800;

    material1.color(Color(0x0000ff)).wireframe(true);
    material2.color(Color(0xff0000)).wireframe(false);

    mesh1.position.x -= 300;
    mesh2.position.x += 300;

    scene.add(&mesh1);
    scene.add(&mesh2);
  }

  void animate() override {
//    camera.rotation.x += 0.1;
    camera.rotation.y += 0.2;

    renderer.render(&scene, &camera);
  }
};
}

int main(void) {
  return CameraExample().init().run();
}

