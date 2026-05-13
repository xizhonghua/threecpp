#include <three/three.h>
using namespace three;

namespace {
class NormalExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 60, aspect_, 1, 10000 };
  SphereGeometry geometry { 200, 32, 32 };
  MeshNormalMaterial material;
  Mesh mesh { &geometry, &material };
  GLRenderer renderer;

public:
  NormalExample() :
      WindowApp(800, 600, "examples/normal") {
  }

  void initScene() override {
    renderer.setPixelRatio(getPixelRatio()).setSize(width_, height_);

    camera.position.z = 600;

    // MeshNormalMaterial does not require lights to be visible
    scene.add(&mesh);
  }

  void animate(int64_t time_us) override {
    mesh.rotation.x += 0.005;
    mesh.rotation.y += 0.01;

    renderer.render(&scene, &camera);
  }

  void onResize(int width, int height) override {
    camera.onResize(width, height);
  }
};
}

int main(void) {
  return NormalExample().init().run();
}