/*
 * basic.cc
 *
 *  Created on: Feb 11, 2017
 *      Author: zxi
 */

#include <three/three.h>
using namespace three;

namespace {
class BasicWindowApp: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 60, aspect_, 1, 10000 };
  AmbientLight ambientLight { Color(0xffffff), 0.5 };
  PointLight pointLight { Color(0xffffff), 1.0 };
  BoxGeometry geometry { 200, 200, 200 };
  SphereGeometry sphereGeometry { 100 };
  MeshBasicMaterial material1, material2;
  Mesh mesh1 { &geometry, &material1 }, mesh2 { &sphereGeometry, &material2 };
  GLRenderer renderer;

public:
  BasicWindowApp() :
      WindowApp(800, 600, "examples/Basic") {
  }

  void initScene() override {
    renderer.setPixelRatio(getPixelRatio()).setSize(width_, height_);

    camera.position.z = 800;

    material1.color(0x0000ff).wireframe(false);
    material2.color(0xff0000).wireframe(true);

    mesh1.position.x -= 300;
    mesh2.position.x += 300;

    pointLight.position.set(0, 200, 200);

    scene.add({&mesh1, &mesh2, &ambientLight, &pointLight});
  }

  void animate() override {

    scene.rotation.z += 0.005;

    mesh1.rotation.x += 0.01;
    mesh1.rotation.y += 0.02;

    mesh2.rotation.x += 0.02;
    mesh2.rotation.y += 0.01;

    renderer.render(&scene, &camera);
  }

  void onResize(int width, int height) override {
    camera.aspect = aspect_;
    camera.updateProjectionMatrix();
  }
};
}

int main(void) {
  return BasicWindowApp().init().run();
}
