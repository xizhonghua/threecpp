/*
 * cameras.cc
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include "three.h"
using namespace three;

#include <ctime>

#include <GLFW/glfw3.h>

namespace {
class CameraExample: public WindowApp {
private:
  double aspect { width_ * 1.0 / height_ };
  double frustumSize = 500;
  Scene scene;
  PerspectiveCamera cameraP { 60, aspect, 1, 10000 };
  OrthographicCamera cameraO { 0.5 * frustumSize * aspect / -2, 0.5
      * frustumSize * aspect / 2, frustumSize / 2, frustumSize / -2, 0.1, 10000 };

  BoxGeometry geometry1 { 50, 50, 50 };
  BoxGeometry geometry2 { 200, 200, 200 };

  MeshBasicMaterial material1, material2;
  Mesh mesh1 { &geometry1, &material1 };
  Mesh mesh2 { &geometry2, &material2 };
  OpenGLRenderer renderer;

  bool perspectiveCamera { true };
  int frames { 0 };

public:
  CameraExample() :
      WindowApp(800, 450, "examples/cameras") {
  }

  void initScene() override {
    renderer.setPixelRatio(this->getPixelRatio());
    renderer.setSize(width_, height_);

    cameraP.position.z = cameraO.position.z = 1000;

    material1.color(Color(0x0000ff)).wireframe(true);
    material2.color(Color(0xff0000)).wireframe(true);

    scene.add(&mesh1);
    scene.add(&mesh2);
  }

  void animate() override {

    ++frames;

    cameraP.rotation.y += 0.2;
    cameraO.rotation = cameraP.rotation;

    double r = frames * 0.01;

    mesh1.position.x = 300 * cos(r);
    mesh1.position.y = 300 * sin(r);
    mesh1.position.z = 300 * sin(r);

    Camera* camera = nullptr;
    if (perspectiveCamera)
      camera = &cameraP;
    else
      camera = &cameraO;

    renderer.render(&scene, camera);
  }

  void onKeyPress(int key, bool shift, bool ctrl, bool alt, bool super)
      override {
    switch (key) {
    case GLFW_KEY_O:
      perspectiveCamera = false;
      break;
    case GLFW_KEY_P:
      perspectiveCamera = true;
      break;

    default:
      WindowApp::onKeyPress(key, shift, ctrl, alt, super);
    }

  }
};
} // namespace

int main(void) {
  return CameraExample().init().run();
}

