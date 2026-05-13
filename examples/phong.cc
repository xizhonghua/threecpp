/*
 * phong.cc
 */

#include <three/three.h>
using namespace three;

namespace {
class PhongExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 60, aspect_, 1, 10000 };
  AmbientLight ambientLight { Color(0x404040), 1.0 };
  PointLight pointLight { Color(0xffffff), 1.0 };
  BoxGeometry geometry { 200, 200, 200 };
  MeshPhongMaterial material { Color(0x49ef4), Color(0x303030), Color(0x808080), 100 };
  Mesh mesh { &geometry, &material };
  GLRenderer renderer;

public:
  PhongExample() :
      WindowApp(800, 600, "examples/Phong", {&camera}) {
  }

  void initScene() override {
    renderer.setPixelRatio(getPixelRatio()).setSize(width_, height_);

    camera.position.z = 600;
    pointLight.position.set(200, 200, 200);

    scene.add({&mesh, &ambientLight, &pointLight});
  }

  void animate(int64_t time_us) override {
    mesh.rotation.x += 0.005;
    mesh.rotation.y += 0.01;

    renderer.render(&scene, &camera);
  }
};
}

int main(void) {
  return PhongExample().init().run();
}