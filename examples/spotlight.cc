/*
 * spotlight.cc
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include "three.h"
using namespace three;

namespace {
class SpotlightExample: public WindowApp {
private:
  Scene scene;
  PerspectiveCamera camera { 35, width_ * 1.0 / height_, 1, 10000 };

  BoxGeometry geoFloor { 2000, 1, 2000 };
  BoxGeometry geoBox { 3, 1, 2 };

  MeshBasicMaterial matFloor, matBox;
  Mesh mshFloor { &geoFloor, &matFloor }, mshBox { &geoBox, &matBox };
  OpenGLRenderer renderer;

public:
  SpotlightExample() :
      WindowApp(800, 450, "examples/Basic") {
  }

  void initScene() override {
    renderer.setPixelRatio(getPixelRatio()).setSize(width_, height_);

    camera.position.set(65, 8, -10);

    matFloor.color(Color(0x808080));
    matBox.color(Color(0x4080ff));

    mshFloor.position.set( 0, - 0.05, 0 );
    mshBox.position.set( 40, 1.8, 0 );

    scene.add(&mshFloor);
    scene.add(&mshBox);
  }

  void animate() override {
    renderer.render(&scene, &camera);
  }
};
}

int main(void) {
  return SpotlightExample().init().run();
}
