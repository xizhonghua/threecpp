/*
 * ShaderLib.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: zxi
 */

#include <three/renderers/shaders/ShaderLib.h>

#include <sstream>

#include <three/renderers/shaders/ShaderChunk.h>

namespace {
using namespace three;

static Shader createBasicShader() {
  //TODO(zxi)
  GLUniforms uniforms;

  std::stringstream vss;

  vss << ShaderChunk::map_pars_vertex() << std::endl <<
      ShaderChunk::lightmap_pars_vertex() << std::endl <<
      ShaderChunk::envmap_pars_vertex() << std::endl <<
      ShaderChunk::color_pars_vertex() << std::endl <<
      ShaderChunk::skinning_pars_vertex() << std::endl <<
      ShaderChunk::morphtarget_pars_vertex() << std::endl <<

      "void main() {"  << std::endl <<

      "vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );" << std::endl <<

      ShaderChunk::map_vertex() << std::endl <<
      ShaderChunk::lightmap_vertex() << std::endl <<
      ShaderChunk::envmap_vertex() << std::endl <<
      ShaderChunk::color_vertex() << std::endl <<
      ShaderChunk::skinbase_vertex() << std::endl <<
      ShaderChunk::skinning_vertex() << std::endl <<
      ShaderChunk::morphtarget_vertex() << std::endl <<
      ShaderChunk::default_vertex() << std::endl <<
      ShaderChunk::shadowmap_vertex() << std::endl <<

      "}" << std::endl;


  std::stringstream fss;

  fss <<
      "uniform vec3 diffuse;" << std::endl <<
      "uniform float opacity;" << std::endl <<

      ShaderChunk::color_pars_fragment() << std::endl <<
      ShaderChunk::map_pars_fragment() << std::endl <<
      ShaderChunk::lightmap_pars_fragment() << std::endl <<
      ShaderChunk::envmap_pars_fragment() << std::endl <<
      ShaderChunk::fog_pars_fragment() << std::endl <<
      ShaderChunk::shadowmap_pars_fragment() << std::endl <<
      ShaderChunk::specularmap_pars_fragment() << std::endl <<

      "void main() {"  << std::endl <<

      "gl_FragColor = vec4( diffuse, opacity );" << std::endl <<

      ShaderChunk::map_fragment() << std::endl <<
      ShaderChunk::alphatest_fragment() << std::endl <<
      ShaderChunk::specularmap_fragment() << std::endl <<
      ShaderChunk::lightmap_fragment() << std::endl <<
      ShaderChunk::color_fragment() << std::endl <<
      ShaderChunk::envmap_fragment() << std::endl <<
      ShaderChunk::shadowmap_fragment() << std::endl <<

      ShaderChunk::linear_to_gamma_fragment() << std::endl <<

      ShaderChunk::fog_fragment() << std::endl <<

      "}" << std::endl;



  return Shader(std::move(uniforms), vss.str(), fss.str());
}

} /* namespace */

namespace three {

const Shader& ShaderLib::basic() {
  static Shader shader = createBasicShader();
  return shader;
}

} /* namespace three */
