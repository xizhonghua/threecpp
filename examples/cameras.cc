/*
 * cameras.cc
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include <three/three.h>
using namespace three;

#include <ctime>

#include <GLFW/glfw3.h>

namespace {
constexpr double kFrustumSize = 1000;

void PrintHelp() {
  std::cout << "Press `?` to print this help message." << std::endl;
  std::cout << "Press `O` to switch to orthographic camera, `P` to switch to perspective camera." << std::endl;
  std::cout << "Press `+/-` to zoom in/out." << std::endl;
  std::cout << "Press `Esc` to quit." << std::endl;
}

class CameraExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera cameraP { 60, aspect_, 1, 10000 };
  OrthographicCamera cameraO { kFrustumSize, aspect_, 0.1, 10000 };
  AmbientLight ambientLight { Color(0xffffff), 0.5 };
  PointLight pointLight { Color(0xffffff), 1.0 };

  BoxGeometry geometry1 { 50, 50, 50 };
  BoxGeometry geometry2 { 200, 200, 200 };
  MeshBasicMaterial material1 { Color(0x0000ff) };
  MeshBasicMaterial material2 { Color(0xff0000) };
  Mesh mesh1 { &geometry1, &material1 };
  Mesh mesh2 { &geometry2, &material2 };

  GLRenderer renderer;
  // Current camera
  Camera* camera { nullptr };

  bool perspectiveCamera { true };

public:
  CameraExample() :
      WindowApp(800, 600, "examples/cameras") {
  }

  void initScene() override {
    renderer.setPixelRatio(this->getPixelRatio());
    renderer.setSize(width_, height_);

    cameraP.position.z = cameraO.position.z = 1000;

    pointLight.position.set(0, 200, 200);

    scene.add({&mesh1, &mesh2, &ambientLight, &pointLight});
  }

  void animate(int64_t time_us) override {

    mesh1.rotation.y += 0.005;
    mesh2.rotation.y += 0.005;

    const double r = time_us * 1e-6;

    mesh1.position.x = 300 * cos(r);
    mesh1.position.y = 300 * sin(r);
    mesh1.position.z = 300 * sin(r);

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
    case GLFW_KEY_EQUAL:
      camera->position.z /= 1.1;
      break;
    case GLFW_KEY_MINUS:
      camera->position.z *= 1.1;
      break;
    case GLFW_KEY_SLASH:
      if (shift) {
        PrintHelp();
      }
      break;

    default:
      WindowApp::onKeyPress(key, shift, ctrl, alt, super);
    }
  }

  void onResize(int width, int height) override {

    cameraP.onResize(width, height);
    cameraO.onResize(width, height);

    this->renderer.setSize(width, height);
  }
};
} // namespace

int main(void) {
  PrintHelp();
  return CameraExample().init().run();
}
