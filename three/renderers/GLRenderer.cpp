/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <three/renderers/GLRenderer.h>

#include <cmath>
#include <iostream>

#include <GLFW/glfw3.h>


#include <OpenGL/glu.h>
#include <three/renderers/GLExtension.h>
#include <three/lights/Light.h>

#include <three/three.h>
#include <three/renderers/shaders/ShaderLib.h>


using namespace std;

namespace three {

GLRenderer::GLRenderer() {
}

GLRenderer::~GLRenderer() {
}

GLRenderer& GLRenderer::setSize(int width, int height) {
  width_ = width;
  height_ = height;

  glViewport(0, 0, width_ * pixel_ratio_, height_ * pixel_ratio_);

  return *this;
}

GLRenderer& GLRenderer::setPixelRatio(double pixel_ratio) {
  this->pixel_ratio_ = pixel_ratio;

  return *this;
}

void GLRenderer::render(Scene* scene, Camera* camera) {

  // Update scene and children's matrix
  if (scene->autoUpdate)
    scene->updateMatrixWorld();

  // Update camera matrix
  if (camera->parent == nullptr)
    camera->updateMatrixWorld();

  // Pre-compute the inverse of the camara's world matrix
  camera->matrixWorldInverse.getInverse(camera->matrixWorld);

  this->projScreenMatrix_ = camera->projectionMatrix()
      * camera->matrixWorldInverse;

// update projection
  updateProjectionMatrix(camera);

  glMatrixMode(GL_MODELVIEW);

//TODO(zxi) pre-render
  glClear(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

// Reset count
  this->opaqueObjectsLastIndex_ = -1;
  this->transparentObjectsLastIndex_ = -1;

  // Reset object list
  this->opaqueObjects_.clear();
  this->transparentObjects_.clear();
  this->lights_.clear();

  //TODO(zxi) clipping...

  // Project objects
  projectObject(scene, camera);

  //TODO(zxi) sorting
  
  // Setup lights
  if (!lights_.empty()) {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE); // Normalizes our on-the-fly cross products and scales

    int lightIndex = 0;
    double ambientR = 0, ambientG = 0, ambientB = 0;

    for (Light* light : lights_) {
      if (light->type() == "AmbientLight") {
        ambientR += light->color.r * light->intensity;
        ambientG += light->color.g * light->intensity;
        ambientB += light->color.b * light->intensity;
      } else if (lightIndex < 8) { // Up to GL_LIGHT7
        int glLightId = GL_LIGHT0 + lightIndex;
        glEnable(glLightId);

        GLfloat color[] = { (GLfloat)(light->color.r * light->intensity),
                            (GLfloat)(light->color.g * light->intensity),
                            (GLfloat)(light->color.b * light->intensity), 1.0f };
        glLightfv(glLightId, GL_DIFFUSE, color);
        glLightfv(glLightId, GL_SPECULAR, color);

        Vector3 worldPos { light->matrixWorld.elements[12], 
                           light->matrixWorld.elements[13], 
                           light->matrixWorld.elements[14] };
        GLfloat position[] = { (GLfloat)worldPos.x, (GLfloat)worldPos.y, (GLfloat)worldPos.z, 1.0f };
        glLightfv(glLightId, GL_POSITION, position);

        lightIndex++;
      }
    }

    GLfloat ambient[] = { (GLfloat)ambientR, (GLfloat)ambientG, (GLfloat)ambientB, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    for (int i = lightIndex; i < 8; ++i) {
      glDisable(GL_LIGHT0 + i);
    }
  } else {
    glDisable(GL_LIGHTING);
  }

  //TODO(zxi) background

  //TOOD(zxi) set blend mode

  // opaque pass (front-to-back order)
  this->renderObjects(opaqueObjects_, scene, camera);

  // transparent pass (back-to-front order)
  this->renderObjects(transparentObjects_, scene, camera);

  // set test bits
//  state.setDepthTest(true);
//  state.setDepthWrite(true);
//  state.setColorWrite(true);

}

void GLRenderer::setMaterial(Material* material) {
  //TODO(zxi)


  auto& shader = ShaderLib::basic();

  material->uniforms = shader.uniforms;
  material->vertexGLSL = shader.vertexGLSL;
  material->fragmentGLSL = shader.fragmentGLSL;

  // ...
}

void GLRenderer::renderBufferDirect(Camera* camera, void* fog,
    Geometry* geometry, Material* material, RenderableObject* object,
    void* group) {
  this->setMaterial(material);
}

void GLRenderer::renderObjects(const std::vector<RenderItem>& items,
    Scene* scene, Camera* camera) {

  for (const RenderItem& item : items) {

    auto object = item.object;
    auto geometry = item.geometry;
    auto material = item.material;

    object->modelViewMatrix = camera->matrixWorldInverse * object->matrixWorld;

//    cerr << "id = " << object->id()<<" modelViewMatrix = " << object->modelViewMatrix << endl;

    //TODO(zxi) normalMartix
//    object->normalMatrix

    //TODO(zxi) onBefore render

    //TODO(zxi) pass sepaerate parameters
    this->renderObject(object);

    //TODO(zxi) onAfter render
  }

}

void GLRenderer::updateProjectionMatrix(Camera* camera) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glLoadMatrixd(camera->projectionMatrix().elements);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glLoadMatrixd(camera->matrixWorldInverse.elements);

  glMatrixMode(GL_MODELVIEW);
}

void GLRenderer::renderObject(RenderableObject* object) {

//  glPushMatrix();
//
//  glTranslated(object->position);
//
//  glRotated(object->rotation);

  prepareMaterial(object->getMaterial());

  bool isMeshNormalMaterial = dynamic_cast<MeshNormalMaterial*>(object->getMaterial()) != nullptr;
  bool isMeshDepthMaterial = dynamic_cast<MeshDepthMaterial*>(object->getMaterial()) != nullptr;
  if (isMeshNormalMaterial || isMeshDepthMaterial) {
    glDisable(GL_LIGHTING);
  }

  glPushMatrix();

  glLoadMatrixd(object->modelViewMatrix.elements);

  Geometry* const geom = object->getGeomtry();

  if (geom->normalsArray.empty() && !geom->vertices.empty()) {
    geom->computeVertexNormals();
  }
  if (geom->verticesArray.empty() && !geom->vertices.empty()) {
    geom->computeVerticesArray();
  }
  if (geom->facesArray.empty() && !geom->faces.empty()) {
    geom->computeFacesArray();
  }
  if (isMeshNormalMaterial && geom->colorsArray.empty() && !geom->normalsArray.empty()) {
    geom->computeColorsArray();
  }

  std::vector<float> depthColors;
  if (isMeshDepthMaterial) {
    depthColors.reserve(geom->vertices.size() * 3);
    for (const Vector3& v : geom->vertices) {
      Vector3 eyePos(v);
      eyePos *= object->modelViewMatrix;
      double z = -eyePos.z;
      double depthColor = z / 1200.0;
      if (depthColor < 0.0) depthColor = 0.0;
      if (depthColor > 1.0) depthColor = 1.0;
      depthColor = 1.0 - depthColor;
      depthColors.push_back(static_cast<float>(depthColor));
      depthColors.push_back(static_cast<float>(depthColor));
      depthColors.push_back(static_cast<float>(depthColor));
    }
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, geom->verticesArray.data());

  if (!geom->normalsArray.empty()) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, geom->normalsArray.data());
  }

  if (isMeshNormalMaterial) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, geom->colorsArray.data());
  } else if (isMeshDepthMaterial) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, depthColors.data());
  }

  if (object->getMaterial()->wireframe()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(geom->facesArray.size()), GL_UNSIGNED_INT, geom->facesArray.data());

  if (object->getMaterial()->wireframe()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (isMeshNormalMaterial || isMeshDepthMaterial) {
    glDisableClientState(GL_COLOR_ARRAY);
  }

  if (!geom->normalsArray.empty()) {
    glDisableClientState(GL_NORMAL_ARRAY);
  }

  glDisableClientState(GL_VERTEX_ARRAY);

  glPopMatrix();

  if ((isMeshNormalMaterial || isMeshDepthMaterial) && !lights_.empty()) {
    glEnable(GL_LIGHTING);
  }
}

void GLRenderer::prepareMaterial(Material* material) {

  glColor3f(material->color().r, material->color().g, material->color().b);

  if (auto phong = dynamic_cast<MeshPhongMaterial*>(material)) {
    GLfloat specular[] = { (GLfloat)phong->specular().r, (GLfloat)phong->specular().g, (GLfloat)phong->specular().b, 1.0f };
    GLfloat emissive[] = { (GLfloat)phong->emissive().r, (GLfloat)phong->emissive().g, (GLfloat)phong->emissive().b, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, phong->shininess());
  } else {
    GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
  }
}

void GLRenderer::projectObject(Object3D* object, Camera* camera) {

  if (!object->visible)
    return;

  //TODO(zxi) check object/camera layer id
  bool visible = true;
  if (!visible)
    goto SKIP;

  if (object->isLight()) {
    this->lights_.push_back(static_cast<Light*>(object));
  } else if (object->isMesh() || object->isLine() || object->isPoint()) {

    RenderableObject* renderable = dynamic_cast<RenderableObject*>(object);

    // TODO(zxi) update geometry
    Geometry* geometry = renderable->getGeomtry();
    // TODO(zxi) support material group
    Material* material = renderable->getMaterial();

    // TODO(zxi) compute z
    double z = 0;

    if (material->visiable()) {

      this->pushRenderItem(renderable, geometry, material, z);
    }

  }

  SKIP: for (auto child : object->children) {
    projectObject(child, camera);
  }
}

void GLRenderer::pushRenderItem(RenderableObject* object, Geometry* geometry,
    Material* material, double z) {

  std::vector<RenderItem>* array = nullptr;
  int index = 0;

  if (material->transparent()) {
    array = &transparentObjects_;
    index = ++transparentObjectsLastIndex_;
  } else {
    array = &opaqueObjects_;
    index = ++opaqueObjectsLastIndex_;
  }

  array->push_back( { object->id(), object, geometry, material, z });
}

}
/* namespace three */
