/*
 * depth.cc
 */

#include <three/three.h>
using namespace three;

#include <cmath>

namespace {
class DepthExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 60, aspect_, 1, 10000 };
  BoxGeometry geometry { 200, 200, 200 };
  SphereGeometry sphereGeometry { 100, 32, 32 };
  MeshDepthMaterial material;
  Mesh mesh1 { &geometry, &material };
  Mesh mesh2 { &sphereGeometry, &material };
  GLRenderer renderer;

public:
  DepthExample() :
      WindowApp(800, 600, "examples/depth") {
  }

  void initScene() override {
    renderer.setPixelRatio(getPixelRatio()).setSize(width_, height_);

    camera.position.z = 800;

    mesh1.position.x -= 300;
    mesh2.position.x += 300;

    scene.add({&mesh1, &mesh2});
  }

  void animate(int64_t time_us) override {

    mesh1.rotation.x += 0.01;
    mesh1.rotation.y += 0.02;

    mesh2.rotation.x += 0.02;
    mesh2.rotation.y += 0.01;

    mesh1.position.z = std::sin(time_us * 1e-6) * 400;
    mesh2.position.z = std::cos(time_us * 1e-6) * 400;

    renderer.render(&scene, &camera);
  }

  void onResize(int width, int height) override {
    camera.onResize(width, height);
  }
};
}

int main(void) {
  return DepthExample().init().run();
}