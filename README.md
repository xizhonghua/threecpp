## threecpp

A C++ version of [three.js](https://threejs.org/)


### Example
```c++
#include "three.h"
using namespace three;

class BasicWindowApp: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 75, width_ * 1.0 / height_, 0, 1e5 };
  BoxGeometry geometry { 200, 200, 200 };
  MeshBasicMaterial material;
  Mesh mesh { &geometry, &material };
  OpenGLRenderer renderer;

public:
  BasicWindowApp() :
      WindowApp(500, 500) {
  }
  virtual ~BasicWindowApp() {
  }

  void initScene() override {
    renderer.setSize(width_, height_);
    camera.position.z = 800;
    material.color(Color(0x0000ff))->wireframe(true);
    scene.add(&mesh);
  }

  void animate() override {
    mesh.rotation.x += 0.5;
    mesh.rotation.y += 1.0;
    renderer.render(&scene, &camera);
  }
};

int main(void) {
  BasicWindowApp app;
  app.init();
  app.run();
  return 0;
}
```

### Current Status
