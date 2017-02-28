// Generated file! Do NOT modify!

#include <three/renderers/shaders/ShaderChunk.h>

namespace three {
// Converted from three/renderers/shaders/ShaderChunk/alphamap_fragment.glsl
const char* ShaderChunk::alphamap_fragment() {
  return
    "#ifdef USE_ALPHAMAP\n"
    "diffuseColor.a *= texture2D( alphaMap, vUv ).g;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/alphamap_pars_fragment.glsl
const char* ShaderChunk::alphamap_pars_fragment() {
  return
    "#ifdef USE_ALPHAMAP\n"
    "uniform sampler2D alphaMap;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/alphatest_fragment.glsl
const char* ShaderChunk::alphatest_fragment() {
  return
    "#ifdef ALPHATEST\n"
    "if ( diffuseColor.a < ALPHATEST ) discard;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/aomap_fragment.glsl
const char* ShaderChunk::aomap_fragment() {
  return
    "#ifdef USE_AOMAP\n"
    "float ambientOcclusion = ( texture2D( aoMap, vUv2 ).r - 1.0 ) * aoMapIntensity + 1.0;\n"
    "reflectedLight.indirectDiffuse *= ambientOcclusion;\n"
    "#if defined( USE_ENVMAP ) && defined( PHYSICAL )\n"
    "float dotNV = saturate( dot( geometry.normal, geometry.viewDir ) );\n"
    "reflectedLight.indirectSpecular *= computeSpecularOcclusion( dotNV, ambientOcclusion, material.specularRoughness );\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/aomap_pars_fragment.glsl
const char* ShaderChunk::aomap_pars_fragment() {
  return
    "#ifdef USE_AOMAP\n"
    "uniform sampler2D aoMap;\n"
    "uniform float aoMapIntensity;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/begin_vertex.glsl
const char* ShaderChunk::begin_vertex() {
  return
    "vec3 transformed = vec3( position );\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/beginnormal_vertex.glsl
const char* ShaderChunk::beginnormal_vertex() {
  return
    "vec3 objectNormal = vec3( normal );\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/bsdfs.glsl
const char* ShaderChunk::bsdfs() {
  return
    "float punctualLightIntensityToIrradianceFactor( const in float lightDistance, const in float cutoffDistance, const in float decayExponent ) {\n"
    "if( decayExponent > 0.0 ) {\n"
    "#if defined ( PHYSICALLY_CORRECT_LIGHTS )\n"
    "float distanceFalloff = 1.0 / max( pow( lightDistance, decayExponent ), 0.01 );\n"
    "float maxDistanceCutoffFactor = pow2( saturate( 1.0 - pow4( lightDistance / cutoffDistance ) ) );\n"
    "return distanceFalloff * maxDistanceCutoffFactor;\n"
    "#else\n"
    "return pow( saturate( -lightDistance / cutoffDistance + 1.0 ), decayExponent );\n"
    "#endif\n"
    "}\n"
    "return 1.0;\n"
    "}\n"
    "vec3 BRDF_Diffuse_Lambert( const in vec3 diffuseColor ) {\n"
    "return RECIPROCAL_PI * diffuseColor;\n"
    "} // validated\n"
    "vec3 F_Schlick( const in vec3 specularColor, const in float dotLH ) {\n"
    "float fresnel = exp2( ( -5.55473 * dotLH - 6.98316 ) * dotLH );\n"
    "return ( 1.0 - specularColor ) * fresnel + specularColor;\n"
    "} // validated\n"
    "float G_GGX_Smith( const in float alpha, const in float dotNL, const in float dotNV ) {\n"
    "float a2 = pow2( alpha );\n"
    "float gl = dotNL + sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNL ) );\n"
    "float gv = dotNV + sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNV ) );\n"
    "return 1.0 / ( gl * gv );\n"
    "} // validated\n"
    "float G_GGX_SmithCorrelated( const in float alpha, const in float dotNL, const in float dotNV ) {\n"
    "float a2 = pow2( alpha );\n"
    "float gv = dotNL * sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNV ) );\n"
    "float gl = dotNV * sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNL ) );\n"
    "return 0.5 / max( gv + gl, EPSILON );\n"
    "}\n"
    "float D_GGX( const in float alpha, const in float dotNH ) {\n"
    "float a2 = pow2( alpha );\n"
    "float denom = pow2( dotNH ) * ( a2 - 1.0 ) + 1.0; // avoid alpha = 0 with dotNH = 1\n"
    "return RECIPROCAL_PI * a2 / pow2( denom );\n"
    "}\n"
    "vec3 BRDF_Specular_GGX( const in IncidentLight incidentLight, const in GeometricContext geometry, const in vec3 specularColor, const in float roughness ) {\n"
    "float alpha = pow2( roughness ); // UE4's roughness\n"
    "vec3 halfDir = normalize( incidentLight.direction + geometry.viewDir );\n"
    "float dotNL = saturate( dot( geometry.normal, incidentLight.direction ) );\n"
    "float dotNV = saturate( dot( geometry.normal, geometry.viewDir ) );\n"
    "float dotNH = saturate( dot( geometry.normal, halfDir ) );\n"
    "float dotLH = saturate( dot( incidentLight.direction, halfDir ) );\n"
    "vec3 F = F_Schlick( specularColor, dotLH );\n"
    "float G = G_GGX_SmithCorrelated( alpha, dotNL, dotNV );\n"
    "float D = D_GGX( alpha, dotNH );\n"
    "return F * ( G * D );\n"
    "} // validated\n"
    "vec2 ltcTextureCoords( const in GeometricContext geometry, const in float roughness ) {\n"
    "const float LUT_SIZE  = 64.0;\n"
    "const float LUT_SCALE = (LUT_SIZE - 1.0)/LUT_SIZE;\n"
    "const float LUT_BIAS  = 0.5/LUT_SIZE;\n"
    "vec3 N = geometry.normal;\n"
    "vec3 V = geometry.viewDir;\n"
    "vec3 P = geometry.position;\n"
    "float theta = acos( dot( N, V ) );\n"
    "vec2 uv = vec2(\n"
    "sqrt( saturate( roughness ) ),\n"
    "saturate( theta / ( 0.5 * PI ) ) );\n"
    "uv = uv * LUT_SCALE + LUT_BIAS;\n"
    "return uv;\n"
    "}\n"
    "void clipQuadToHorizon( inout vec3 L[5], out int n ) {\n"
    "int config = 0;\n"
    "if ( L[0].z > 0.0 ) config += 1;\n"
    "if ( L[1].z > 0.0 ) config += 2;\n"
    "if ( L[2].z > 0.0 ) config += 4;\n"
    "if ( L[3].z > 0.0 ) config += 8;\n"
    "n = 0;\n"
    "if ( config == 0 ) {\n"
    "} else if ( config == 1 ) {\n"
    "n = 3;\n"
    "L[1] = -L[1].z * L[0] + L[0].z * L[1];\n"
    "L[2] = -L[3].z * L[0] + L[0].z * L[3];\n"
    "} else if ( config == 2 ) {\n"
    "n = 3;\n"
    "L[0] = -L[0].z * L[1] + L[1].z * L[0];\n"
    "L[2] = -L[2].z * L[1] + L[1].z * L[2];\n"
    "} else if ( config == 3 ) {\n"
    "n = 4;\n"
    "L[2] = -L[2].z * L[1] + L[1].z * L[2];\n"
    "L[3] = -L[3].z * L[0] + L[0].z * L[3];\n"
    "} else if ( config == 4 ) {\n"
    "n = 3;\n"
    "L[0] = -L[3].z * L[2] + L[2].z * L[3];\n"
    "L[1] = -L[1].z * L[2] + L[2].z * L[1];\n"
    "} else if ( config == 5 ) {\n"
    "n = 0;\n"
    "} else if ( config == 6 ) {\n"
    "n = 4;\n"
    "L[0] = -L[0].z * L[1] + L[1].z * L[0];\n"
    "L[3] = -L[3].z * L[2] + L[2].z * L[3];\n"
    "} else if ( config == 7 ) {\n"
    "n = 5;\n"
    "L[4] = -L[3].z * L[0] + L[0].z * L[3];\n"
    "L[3] = -L[3].z * L[2] + L[2].z * L[3];\n"
    "} else if ( config == 8 ) {\n"
    "n = 3;\n"
    "L[0] = -L[0].z * L[3] + L[3].z * L[0];\n"
    "L[1] = -L[2].z * L[3] + L[3].z * L[2];\n"
    "L[2] =  L[3];\n"
    "} else if ( config == 9 ) {\n"
    "n = 4;\n"
    "L[1] = -L[1].z * L[0] + L[0].z * L[1];\n"
    "L[2] = -L[2].z * L[3] + L[3].z * L[2];\n"
    "} else if ( config == 10 ) {\n"
    "n = 0;\n"
    "} else if ( config == 11 ) {\n"
    "n = 5;\n"
    "L[4] = L[3];\n"
    "L[3] = -L[2].z * L[3] + L[3].z * L[2];\n"
    "L[2] = -L[2].z * L[1] + L[1].z * L[2];\n"
    "} else if ( config == 12 ) {\n"
    "n = 4;\n"
    "L[1] = -L[1].z * L[2] + L[2].z * L[1];\n"
    "L[0] = -L[0].z * L[3] + L[3].z * L[0];\n"
    "} else if ( config == 13 ) {\n"
    "n = 5;\n"
    "L[4] = L[3];\n"
    "L[3] = L[2];\n"
    "L[2] = -L[1].z * L[2] + L[2].z * L[1];\n"
    "L[1] = -L[1].z * L[0] + L[0].z * L[1];\n"
    "} else if ( config == 14 ) {\n"
    "n = 5;\n"
    "L[4] = -L[0].z * L[3] + L[3].z * L[0];\n"
    "L[0] = -L[0].z * L[1] + L[1].z * L[0];\n"
    "} else if ( config == 15 ) {\n"
    "n = 4;\n"
    "}\n"
    "if ( n == 3 )\n"
    "L[3] = L[0];\n"
    "if ( n == 4 )\n"
    "L[4] = L[0];\n"
    "}\n"
    "float integrateLtcBrdfOverRectEdge( vec3 v1, vec3 v2 ) {\n"
    "float cosTheta = dot( v1, v2 );\n"
    "float theta = acos( cosTheta );\n"
    "float res = cross( v1, v2 ).z * ( ( theta > 0.001 ) ? theta / sin( theta ) : 1.0 );\n"
    "return res;\n"
    "}\n"
    "void initRectPoints( const in vec3 pos, const in vec3 halfWidth, const in vec3 halfHeight, out vec3 rectPoints[4] ) {\n"
    "rectPoints[0] = pos - halfWidth - halfHeight;\n"
    "rectPoints[1] = pos + halfWidth - halfHeight;\n"
    "rectPoints[2] = pos + halfWidth + halfHeight;\n"
    "rectPoints[3] = pos - halfWidth + halfHeight;\n"
    "}\n"
    "vec3 integrateLtcBrdfOverRect( const in GeometricContext geometry, const in mat3 brdfMat, const in vec3 rectPoints[4] ) {\n"
    "vec3 N = geometry.normal;\n"
    "vec3 V = geometry.viewDir;\n"
    "vec3 P = geometry.position;\n"
    "vec3 T1, T2;\n"
    "T1 = normalize(V - N * dot( V, N ));\n"
    "T2 = - cross( N, T1 );\n"
    "mat3 brdfWrtSurface = brdfMat * transpose( mat3( T1, T2, N ) );\n"
    "vec3 clippedRect[5];\n"
    "clippedRect[0] = brdfWrtSurface * ( rectPoints[0] - P );\n"
    "clippedRect[1] = brdfWrtSurface * ( rectPoints[1] - P );\n"
    "clippedRect[2] = brdfWrtSurface * ( rectPoints[2] - P );\n"
    "clippedRect[3] = brdfWrtSurface * ( rectPoints[3] - P );\n"
    "int n;\n"
    "clipQuadToHorizon(clippedRect, n);\n"
    "if ( n == 0 )\n"
    "return vec3( 0, 0, 0 );\n"
    "clippedRect[0] = normalize( clippedRect[0] );\n"
    "clippedRect[1] = normalize( clippedRect[1] );\n"
    "clippedRect[2] = normalize( clippedRect[2] );\n"
    "clippedRect[3] = normalize( clippedRect[3] );\n"
    "clippedRect[4] = normalize( clippedRect[4] );\n"
    "float sum = 0.0;\n"
    "sum += integrateLtcBrdfOverRectEdge( clippedRect[0], clippedRect[1] );\n"
    "sum += integrateLtcBrdfOverRectEdge( clippedRect[1], clippedRect[2] );\n"
    "sum += integrateLtcBrdfOverRectEdge( clippedRect[2], clippedRect[3] );\n"
    "if (n >= 4)\n"
    "sum += integrateLtcBrdfOverRectEdge( clippedRect[3], clippedRect[4] );\n"
    "if (n == 5)\n"
    "sum += integrateLtcBrdfOverRectEdge( clippedRect[4], clippedRect[0] );\n"
    "sum = max( 0.0, sum );\n"
    "vec3 Lo_i = vec3( sum, sum, sum );\n"
    "return Lo_i;\n"
    "}\n"
    "vec3 Rect_Area_Light_Specular_Reflectance(\n"
    "const in GeometricContext geometry,\n"
    "const in vec3 lightPos, const in vec3 lightHalfWidth, const in vec3 lightHalfHeight,\n"
    "const in float roughness,\n"
    "const in sampler2D ltcMat, const in sampler2D ltcMag ) {\n"
    "vec3 rectPoints[4];\n"
    "initRectPoints( lightPos, lightHalfWidth, lightHalfHeight, rectPoints );\n"
    "vec2 uv = ltcTextureCoords( geometry, roughness );\n"
    "vec4 brdfLtcApproxParams, t;\n"
    "brdfLtcApproxParams = texture2D( ltcMat, uv );\n"
    "t = texture2D( ltcMat, uv );\n"
    "float brdfLtcScalar = texture2D( ltcMag, uv ).a;\n"
    "mat3 brdfLtcApproxMat = mat3(\n"
    "vec3(   1,   0, t.y ),\n"
    "vec3(   0, t.z,   0 ),\n"
    "vec3( t.w,   0, t.x )\n"
    ");\n"
    "vec3 specularReflectance = integrateLtcBrdfOverRect( geometry, brdfLtcApproxMat, rectPoints );\n"
    "specularReflectance *= brdfLtcScalar;\n"
    "return specularReflectance;\n"
    "}\n"
    "vec3 Rect_Area_Light_Diffuse_Reflectance(\n"
    "const in GeometricContext geometry,\n"
    "const in vec3 lightPos, const in vec3 lightHalfWidth, const in vec3 lightHalfHeight ) {\n"
    "vec3 rectPoints[4];\n"
    "initRectPoints( lightPos, lightHalfWidth, lightHalfHeight, rectPoints );\n"
    "mat3 diffuseBrdfMat = mat3(1);\n"
    "vec3 diffuseReflectance = integrateLtcBrdfOverRect( geometry, diffuseBrdfMat, rectPoints );\n"
    "return diffuseReflectance;\n"
    "}\n"
    "vec3 BRDF_Specular_GGX_Environment( const in GeometricContext geometry, const in vec3 specularColor, const in float roughness ) {\n"
    "float dotNV = saturate( dot( geometry.normal, geometry.viewDir ) );\n"
    "const vec4 c0 = vec4( - 1, - 0.0275, - 0.572, 0.022 );\n"
    "const vec4 c1 = vec4( 1, 0.0425, 1.04, - 0.04 );\n"
    "vec4 r = roughness * c0 + c1;\n"
    "float a004 = min( r.x * r.x, exp2( - 9.28 * dotNV ) ) * r.x + r.y;\n"
    "vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;\n"
    "return specularColor * AB.x + AB.y;\n"
    "} // validated\n"
    "float G_BlinnPhong_Implicit( /* const in float dotNL, const in float dotNV */ ) {\n"
    "return 0.25;\n"
    "}\n"
    "float D_BlinnPhong( const in float shininess, const in float dotNH ) {\n"
    "return RECIPROCAL_PI * ( shininess * 0.5 + 1.0 ) * pow( dotNH, shininess );\n"
    "}\n"
    "vec3 BRDF_Specular_BlinnPhong( const in IncidentLight incidentLight, const in GeometricContext geometry, const in vec3 specularColor, const in float shininess ) {\n"
    "vec3 halfDir = normalize( incidentLight.direction + geometry.viewDir );\n"
    "float dotNH = saturate( dot( geometry.normal, halfDir ) );\n"
    "float dotLH = saturate( dot( incidentLight.direction, halfDir ) );\n"
    "vec3 F = F_Schlick( specularColor, dotLH );\n"
    "float G = G_BlinnPhong_Implicit( /* dotNL, dotNV */ );\n"
    "float D = D_BlinnPhong( shininess, dotNH );\n"
    "return F * ( G * D );\n"
    "} // validated\n"
    "float GGXRoughnessToBlinnExponent( const in float ggxRoughness ) {\n"
    "return ( 2.0 / pow2( ggxRoughness + 0.0001 ) - 2.0 );\n"
    "}\n"
    "float BlinnExponentToGGXRoughness( const in float blinnExponent ) {\n"
    "return sqrt( 2.0 / ( blinnExponent + 2.0 ) );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/bumpmap_pars_fragment.glsl
const char* ShaderChunk::bumpmap_pars_fragment() {
  return
    "#ifdef USE_BUMPMAP\n"
    "uniform sampler2D bumpMap;\n"
    "uniform float bumpScale;\n"
    "vec2 dHdxy_fwd() {\n"
    "vec2 dSTdx = dFdx( vUv );\n"
    "vec2 dSTdy = dFdy( vUv );\n"
    "float Hll = bumpScale * texture2D( bumpMap, vUv ).x;\n"
    "float dBx = bumpScale * texture2D( bumpMap, vUv + dSTdx ).x - Hll;\n"
    "float dBy = bumpScale * texture2D( bumpMap, vUv + dSTdy ).x - Hll;\n"
    "return vec2( dBx, dBy );\n"
    "}\n"
    "vec3 perturbNormalArb( vec3 surf_pos, vec3 surf_norm, vec2 dHdxy ) {\n"
    "vec3 vSigmaX = dFdx( surf_pos );\n"
    "vec3 vSigmaY = dFdy( surf_pos );\n"
    "vec3 vN = surf_norm;		// normalized\n"
    "vec3 R1 = cross( vSigmaY, vN );\n"
    "vec3 R2 = cross( vN, vSigmaX );\n"
    "float fDet = dot( vSigmaX, R1 );\n"
    "vec3 vGrad = sign( fDet ) * ( dHdxy.x * R1 + dHdxy.y * R2 );\n"
    "return normalize( abs( fDet ) * surf_norm - vGrad );\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/clipping_planes_fragment.glsl
const char* ShaderChunk::clipping_planes_fragment() {
  return
    "#if NUM_CLIPPING_PLANES > 0\n"
    "for ( int i = 0; i < UNION_CLIPPING_PLANES; ++ i ) {\n"
    "vec4 plane = clippingPlanes[ i ];\n"
    "if ( dot( vViewPosition, plane.xyz ) > plane.w ) discard;\n"
    "}\n"
    "#if UNION_CLIPPING_PLANES < NUM_CLIPPING_PLANES\n"
    "bool clipped = true;\n"
    "for ( int i = UNION_CLIPPING_PLANES; i < NUM_CLIPPING_PLANES; ++ i ) {\n"
    "vec4 plane = clippingPlanes[ i ];\n"
    "clipped = ( dot( vViewPosition, plane.xyz ) > plane.w ) && clipped;\n"
    "}\n"
    "if ( clipped ) discard;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/clipping_planes_pars_fragment.glsl
const char* ShaderChunk::clipping_planes_pars_fragment() {
  return
    "#if NUM_CLIPPING_PLANES > 0\n"
    "#if ! defined( PHYSICAL ) && ! defined( PHONG )\n"
    "varying vec3 vViewPosition;\n"
    "#endif\n"
    "uniform vec4 clippingPlanes[ NUM_CLIPPING_PLANES ];\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/clipping_planes_pars_vertex.glsl
const char* ShaderChunk::clipping_planes_pars_vertex() {
  return
    "#if NUM_CLIPPING_PLANES > 0 && ! defined( PHYSICAL ) && ! defined( PHONG )\n"
    "varying vec3 vViewPosition;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/clipping_planes_vertex.glsl
const char* ShaderChunk::clipping_planes_vertex() {
  return
    "#if NUM_CLIPPING_PLANES > 0 && ! defined( PHYSICAL ) && ! defined( PHONG )\n"
    "vViewPosition = - mvPosition.xyz;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/color_fragment.glsl
const char* ShaderChunk::color_fragment() {
  return
    "#ifdef USE_COLOR\n"
    "diffuseColor.rgb *= vColor;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/color_pars_fragment.glsl
const char* ShaderChunk::color_pars_fragment() {
  return
    "#ifdef USE_COLOR\n"
    "varying vec3 vColor;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/color_pars_vertex.glsl
const char* ShaderChunk::color_pars_vertex() {
  return
    "#ifdef USE_COLOR\n"
    "varying vec3 vColor;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/color_vertex.glsl
const char* ShaderChunk::color_vertex() {
  return
    "#ifdef USE_COLOR\n"
    "vColor.xyz = color.xyz;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/common.glsl
const char* ShaderChunk::common() {
  return
    "#define PI 3.14159265359\n"
    "#define PI2 6.28318530718\n"
    "#define PI_HALF 1.5707963267949\n"
    "#define RECIPROCAL_PI 0.31830988618\n"
    "#define RECIPROCAL_PI2 0.15915494\n"
    "#define LOG2 1.442695\n"
    "#define EPSILON 1e-6\n"
    "#define saturate(a) clamp( a, 0.0, 1.0 )\n"
    "#define whiteCompliment(a) ( 1.0 - saturate( a ) )\n"
    "float pow2( const in float x ) { return x*x; }\n"
    "float pow3( const in float x ) { return x*x*x; }\n"
    "float pow4( const in float x ) { float x2 = x*x; return x2*x2; }\n"
    "float average( const in vec3 color ) { return dot( color, vec3( 0.3333 ) ); }\n"
    "highp float rand( const in vec2 uv ) {\n"
    "const highp float a = 12.9898, b = 78.233, c = 43758.5453;\n"
    "highp float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );\n"
    "return fract(sin(sn) * c);\n"
    "}\n"
    "struct IncidentLight {\n"
    "vec3 color;\n"
    "vec3 direction;\n"
    "bool visible;\n"
    "};\n"
    "struct ReflectedLight {\n"
    "vec3 directDiffuse;\n"
    "vec3 directSpecular;\n"
    "vec3 indirectDiffuse;\n"
    "vec3 indirectSpecular;\n"
    "};\n"
    "struct GeometricContext {\n"
    "vec3 position;\n"
    "vec3 normal;\n"
    "vec3 viewDir;\n"
    "};\n"
    "vec3 transformDirection( in vec3 dir, in mat4 matrix ) {\n"
    "return normalize( ( matrix * vec4( dir, 0.0 ) ).xyz );\n"
    "}\n"
    "vec3 inverseTransformDirection( in vec3 dir, in mat4 matrix ) {\n"
    "return normalize( ( vec4( dir, 0.0 ) * matrix ).xyz );\n"
    "}\n"
    "vec3 projectOnPlane(in vec3 point, in vec3 pointOnPlane, in vec3 planeNormal ) {\n"
    "float distance = dot( planeNormal, point - pointOnPlane );\n"
    "return - distance * planeNormal + point;\n"
    "}\n"
    "float sideOfPlane( in vec3 point, in vec3 pointOnPlane, in vec3 planeNormal ) {\n"
    "return sign( dot( point - pointOnPlane, planeNormal ) );\n"
    "}\n"
    "vec3 linePlaneIntersect( in vec3 pointOnLine, in vec3 lineDirection, in vec3 pointOnPlane, in vec3 planeNormal ) {\n"
    "return lineDirection * ( dot( planeNormal, pointOnPlane - pointOnLine ) / dot( planeNormal, lineDirection ) ) + pointOnLine;\n"
    "}\n"
    "mat3 transpose( const in mat3 v ) {\n"
    "mat3 tmp;\n"
    "tmp[0] = vec3(v[0].x, v[1].x, v[2].x);\n"
    "tmp[1] = vec3(v[0].y, v[1].y, v[2].y);\n"
    "tmp[2] = vec3(v[0].z, v[1].z, v[2].z);\n"
    "return tmp;\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/cube_uv_reflection_fragment.glsl
const char* ShaderChunk::cube_uv_reflection_fragment() {
  return
    "#ifdef ENVMAP_TYPE_CUBE_UV\n"
    "#define cubeUV_textureSize (1024.0)\n"
    "int getFaceFromDirection(vec3 direction) {\n"
    "vec3 absDirection = abs(direction);\n"
    "int face = -1;\n"
    "if( absDirection.x > absDirection.z ) {\n"
    "if(absDirection.x > absDirection.y )\n"
    "face = direction.x > 0.0 ? 0 : 3;\n"
    "else\n"
    "face = direction.y > 0.0 ? 1 : 4;\n"
    "}\n"
    "else {\n"
    "if(absDirection.z > absDirection.y )\n"
    "face = direction.z > 0.0 ? 2 : 5;\n"
    "else\n"
    "face = direction.y > 0.0 ? 1 : 4;\n"
    "}\n"
    "return face;\n"
    "}\n"
    "#define cubeUV_maxLods1  (log2(cubeUV_textureSize*0.25) - 1.0)\n"
    "#define cubeUV_rangeClamp (exp2((6.0 - 1.0) * 2.0))\n"
    "vec2 MipLevelInfo( vec3 vec, float roughnessLevel, float roughness ) {\n"
    "float scale = exp2(cubeUV_maxLods1 - roughnessLevel);\n"
    "float dxRoughness = dFdx(roughness);\n"
    "float dyRoughness = dFdy(roughness);\n"
    "vec3 dx = dFdx( vec * scale * dxRoughness );\n"
    "vec3 dy = dFdy( vec * scale * dyRoughness );\n"
    "float d = max( dot( dx, dx ), dot( dy, dy ) );\n"
    "d = clamp(d, 1.0, cubeUV_rangeClamp);\n"
    "float mipLevel = 0.5 * log2(d);\n"
    "return vec2(floor(mipLevel), fract(mipLevel));\n"
    "}\n"
    "#define cubeUV_maxLods2 (log2(cubeUV_textureSize*0.25) - 2.0)\n"
    "#define cubeUV_rcpTextureSize (1.0 / cubeUV_textureSize)\n"
    "vec2 getCubeUV(vec3 direction, float roughnessLevel, float mipLevel) {\n"
    "mipLevel = roughnessLevel > cubeUV_maxLods2 - 3.0 ? 0.0 : mipLevel;\n"
    "float a = 16.0 * cubeUV_rcpTextureSize;\n"
    "vec2 exp2_packed = exp2( vec2( roughnessLevel, mipLevel ) );\n"
    "vec2 rcp_exp2_packed = vec2( 1.0 ) / exp2_packed;\n"
    "float powScale = exp2_packed.x * exp2_packed.y;\n"
    "float scale = rcp_exp2_packed.x * rcp_exp2_packed.y * 0.25;\n"
    "float mipOffset = 0.75*(1.0 - rcp_exp2_packed.y) * rcp_exp2_packed.x;\n"
    "bool bRes = mipLevel == 0.0;\n"
    "scale =  bRes && (scale < a) ? a : scale;\n"
    "vec3 r;\n"
    "vec2 offset;\n"
    "int face = getFaceFromDirection(direction);\n"
    "float rcpPowScale = 1.0 / powScale;\n"
    "if( face == 0) {\n"
    "r = vec3(direction.x, -direction.z, direction.y);\n"
    "offset = vec2(0.0+mipOffset,0.75 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? a : offset.y;\n"
    "}\n"
    "else if( face == 1) {\n"
    "r = vec3(direction.y, direction.x, direction.z);\n"
    "offset = vec2(scale+mipOffset, 0.75 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? a : offset.y;\n"
    "}\n"
    "else if( face == 2) {\n"
    "r = vec3(direction.z, direction.x, direction.y);\n"
    "offset = vec2(2.0*scale+mipOffset, 0.75 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? a : offset.y;\n"
    "}\n"
    "else if( face == 3) {\n"
    "r = vec3(direction.x, direction.z, direction.y);\n"
    "offset = vec2(0.0+mipOffset,0.5 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? 0.0 : offset.y;\n"
    "}\n"
    "else if( face == 4) {\n"
    "r = vec3(direction.y, direction.x, -direction.z);\n"
    "offset = vec2(scale+mipOffset, 0.5 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? 0.0 : offset.y;\n"
    "}\n"
    "else {\n"
    "r = vec3(direction.z, -direction.x, direction.y);\n"
    "offset = vec2(2.0*scale+mipOffset, 0.5 * rcpPowScale);\n"
    "offset.y = bRes && (offset.y < 2.0*a) ? 0.0 : offset.y;\n"
    "}\n"
    "r = normalize(r);\n"
    "float texelOffset = 0.5 * cubeUV_rcpTextureSize;\n"
    "vec2 s = ( r.yz / abs( r.x ) + vec2( 1.0 ) ) * 0.5;\n"
    "vec2 base = offset + vec2( texelOffset );\n"
    "return base + s * ( scale - 2.0 * texelOffset );\n"
    "}\n"
    "#define cubeUV_maxLods3 (log2(cubeUV_textureSize*0.25) - 3.0)\n"
    "vec4 textureCubeUV(vec3 reflectedDirection, float roughness ) {\n"
    "float roughnessVal = roughness* cubeUV_maxLods3;\n"
    "float r1 = floor(roughnessVal);\n"
    "float r2 = r1 + 1.0;\n"
    "float t = fract(roughnessVal);\n"
    "vec2 mipInfo = MipLevelInfo(reflectedDirection, r1, roughness);\n"
    "float s = mipInfo.y;\n"
    "float level0 = mipInfo.x;\n"
    "float level1 = level0 + 1.0;\n"
    "level1 = level1 > 5.0 ? 5.0 : level1;\n"
    "level0 += min( floor( s + 0.5 ), 5.0 );\n"
    "vec2 uv_10 = getCubeUV(reflectedDirection, r1, level0);\n"
    "vec4 color10 = envMapTexelToLinear(texture2D(envMap, uv_10));\n"
    "vec2 uv_20 = getCubeUV(reflectedDirection, r2, level0);\n"
    "vec4 color20 = envMapTexelToLinear(texture2D(envMap, uv_20));\n"
    "vec4 result = mix(color10, color20, t);\n"
    "return vec4(result.rgb, 1.0);\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/defaultnormal_vertex.glsl
const char* ShaderChunk::defaultnormal_vertex() {
  return
    "#ifdef FLIP_SIDED\n"
    "objectNormal = -objectNormal;\n"
    "#endif\n"
    "vec3 transformedNormal = normalMatrix * objectNormal;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/displacementmap_pars_vertex.glsl
const char* ShaderChunk::displacementmap_pars_vertex() {
  return
    "#ifdef USE_DISPLACEMENTMAP\n"
    "uniform sampler2D displacementMap;\n"
    "uniform float displacementScale;\n"
    "uniform float displacementBias;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/displacementmap_vertex.glsl
const char* ShaderChunk::displacementmap_vertex() {
  return
    "#ifdef USE_DISPLACEMENTMAP\n"
    "transformed += normal * ( texture2D( displacementMap, uv ).x * displacementScale + displacementBias );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/emissivemap_fragment.glsl
const char* ShaderChunk::emissivemap_fragment() {
  return
    "#ifdef USE_EMISSIVEMAP\n"
    "vec4 emissiveColor = texture2D( emissiveMap, vUv );\n"
    "emissiveColor.rgb = emissiveMapTexelToLinear( emissiveColor ).rgb;\n"
    "totalEmissiveRadiance *= emissiveColor.rgb;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/emissivemap_pars_fragment.glsl
const char* ShaderChunk::emissivemap_pars_fragment() {
  return
    "#ifdef USE_EMISSIVEMAP\n"
    "uniform sampler2D emissiveMap;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/encodings_fragment.glsl
const char* ShaderChunk::encodings_fragment() {
  return
    "gl_FragColor = linearToOutputTexel( gl_FragColor );\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/encodings_pars_fragment.glsl
const char* ShaderChunk::encodings_pars_fragment() {
  return
    "vec4 LinearToLinear( in vec4 value ) {\n"
    "return value;\n"
    "}\n"
    "vec4 GammaToLinear( in vec4 value, in float gammaFactor ) {\n"
    "return vec4( pow( value.xyz, vec3( gammaFactor ) ), value.w );\n"
    "}\n"
    "vec4 LinearToGamma( in vec4 value, in float gammaFactor ) {\n"
    "return vec4( pow( value.xyz, vec3( 1.0 / gammaFactor ) ), value.w );\n"
    "}\n"
    "vec4 sRGBToLinear( in vec4 value ) {\n"
    "return vec4( mix( pow( value.rgb * 0.9478672986 + vec3( 0.0521327014 ), vec3( 2.4 ) ), value.rgb * 0.0773993808, vec3( lessThanEqual( value.rgb, vec3( 0.04045 ) ) ) ), value.w );\n"
    "}\n"
    "vec4 LinearTosRGB( in vec4 value ) {\n"
    "return vec4( mix( pow( value.rgb, vec3( 0.41666 ) ) * 1.055 - vec3( 0.055 ), value.rgb * 12.92, vec3( lessThanEqual( value.rgb, vec3( 0.0031308 ) ) ) ), value.w );\n"
    "}\n"
    "vec4 RGBEToLinear( in vec4 value ) {\n"
    "return vec4( value.rgb * exp2( value.a * 255.0 - 128.0 ), 1.0 );\n"
    "}\n"
    "vec4 LinearToRGBE( in vec4 value ) {\n"
    "float maxComponent = max( max( value.r, value.g ), value.b );\n"
    "float fExp = clamp( ceil( log2( maxComponent ) ), -128.0, 127.0 );\n"
    "return vec4( value.rgb / exp2( fExp ), ( fExp + 128.0 ) / 255.0 );\n"
    "}\n"
    "vec4 RGBMToLinear( in vec4 value, in float maxRange ) {\n"
    "return vec4( value.xyz * value.w * maxRange, 1.0 );\n"
    "}\n"
    "vec4 LinearToRGBM( in vec4 value, in float maxRange ) {\n"
    "float maxRGB = max( value.x, max( value.g, value.b ) );\n"
    "float M      = clamp( maxRGB / maxRange, 0.0, 1.0 );\n"
    "M            = ceil( M * 255.0 ) / 255.0;\n"
    "return vec4( value.rgb / ( M * maxRange ), M );\n"
    "}\n"
    "vec4 RGBDToLinear( in vec4 value, in float maxRange ) {\n"
    "return vec4( value.rgb * ( ( maxRange / 255.0 ) / value.a ), 1.0 );\n"
    "}\n"
    "vec4 LinearToRGBD( in vec4 value, in float maxRange ) {\n"
    "float maxRGB = max( value.x, max( value.g, value.b ) );\n"
    "float D      = max( maxRange / maxRGB, 1.0 );\n"
    "D            = min( floor( D ) / 255.0, 1.0 );\n"
    "return vec4( value.rgb * ( D * ( 255.0 / maxRange ) ), D );\n"
    "}\n"
    "const mat3 cLogLuvM = mat3( 0.2209, 0.3390, 0.4184, 0.1138, 0.6780, 0.7319, 0.0102, 0.1130, 0.2969 );\n"
    "vec4 LinearToLogLuv( in vec4 value )  {\n"
    "vec3 Xp_Y_XYZp = value.rgb * cLogLuvM;\n"
    "Xp_Y_XYZp = max(Xp_Y_XYZp, vec3(1e-6, 1e-6, 1e-6));\n"
    "vec4 vResult;\n"
    "vResult.xy = Xp_Y_XYZp.xy / Xp_Y_XYZp.z;\n"
    "float Le = 2.0 * log2(Xp_Y_XYZp.y) + 127.0;\n"
    "vResult.w = fract(Le);\n"
    "vResult.z = (Le - (floor(vResult.w*255.0))/255.0)/255.0;\n"
    "return vResult;\n"
    "}\n"
    "const mat3 cLogLuvInverseM = mat3( 6.0014, -2.7008, -1.7996, -1.3320, 3.1029, -5.7721, 0.3008, -1.0882, 5.6268 );\n"
    "vec4 LogLuvToLinear( in vec4 value ) {\n"
    "float Le = value.z * 255.0 + value.w;\n"
    "vec3 Xp_Y_XYZp;\n"
    "Xp_Y_XYZp.y = exp2((Le - 127.0) / 2.0);\n"
    "Xp_Y_XYZp.z = Xp_Y_XYZp.y / value.y;\n"
    "Xp_Y_XYZp.x = value.x * Xp_Y_XYZp.z;\n"
    "vec3 vRGB = Xp_Y_XYZp.rgb * cLogLuvInverseM;\n"
    "return vec4( max(vRGB, 0.0), 1.0 );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/envmap_fragment.glsl
const char* ShaderChunk::envmap_fragment() {
  return
    "#ifdef USE_ENVMAP\n"
    "#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG )\n"
    "vec3 cameraToVertex = normalize( vWorldPosition - cameraPosition );\n"
    "vec3 worldNormal = inverseTransformDirection( normal, viewMatrix );\n"
    "#ifdef ENVMAP_MODE_REFLECTION\n"
    "vec3 reflectVec = reflect( cameraToVertex, worldNormal );\n"
    "#else\n"
    "vec3 reflectVec = refract( cameraToVertex, worldNormal, refractionRatio );\n"
    "#endif\n"
    "#else\n"
    "vec3 reflectVec = vReflect;\n"
    "#endif\n"
    "#ifdef ENVMAP_TYPE_CUBE\n"
    "vec4 envColor = textureCube( envMap, flipNormal * vec3( flipEnvMap * reflectVec.x, reflectVec.yz ) );\n"
    "#elif defined( ENVMAP_TYPE_EQUIREC )\n"
    "vec2 sampleUV;\n"
    "sampleUV.y = saturate( flipNormal * reflectVec.y * 0.5 + 0.5 );\n"
    "sampleUV.x = atan( flipNormal * reflectVec.z, flipNormal * reflectVec.x ) * RECIPROCAL_PI2 + 0.5;\n"
    "vec4 envColor = texture2D( envMap, sampleUV );\n"
    "#elif defined( ENVMAP_TYPE_SPHERE )\n"
    "vec3 reflectView = flipNormal * normalize( ( viewMatrix * vec4( reflectVec, 0.0 ) ).xyz + vec3( 0.0, 0.0, 1.0 ) );\n"
    "vec4 envColor = texture2D( envMap, reflectView.xy * 0.5 + 0.5 );\n"
    "#else\n"
    "vec4 envColor = vec4( 0.0 );\n"
    "#endif\n"
    "envColor = envMapTexelToLinear( envColor );\n"
    "#ifdef ENVMAP_BLENDING_MULTIPLY\n"
    "outgoingLight = mix( outgoingLight, outgoingLight * envColor.xyz, specularStrength * reflectivity );\n"
    "#elif defined( ENVMAP_BLENDING_MIX )\n"
    "outgoingLight = mix( outgoingLight, envColor.xyz, specularStrength * reflectivity );\n"
    "#elif defined( ENVMAP_BLENDING_ADD )\n"
    "outgoingLight += envColor.xyz * specularStrength * reflectivity;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/envmap_pars_fragment.glsl
const char* ShaderChunk::envmap_pars_fragment() {
  return
    "#if defined( USE_ENVMAP ) || defined( PHYSICAL )\n"
    "uniform float reflectivity;\n"
    "uniform float envMapIntensity;\n"
    "#endif\n"
    "#ifdef USE_ENVMAP\n"
    "#if ! defined( PHYSICAL ) && ( defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG ) )\n"
    "varying vec3 vWorldPosition;\n"
    "#endif\n"
    "#ifdef ENVMAP_TYPE_CUBE\n"
    "uniform samplerCube envMap;\n"
    "#else\n"
    "uniform sampler2D envMap;\n"
    "#endif\n"
    "uniform float flipEnvMap;\n"
    "#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG ) || defined( PHYSICAL )\n"
    "uniform float refractionRatio;\n"
    "#else\n"
    "varying vec3 vReflect;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/envmap_pars_vertex.glsl
const char* ShaderChunk::envmap_pars_vertex() {
  return
    "#ifdef USE_ENVMAP\n"
    "#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG )\n"
    "varying vec3 vWorldPosition;\n"
    "#else\n"
    "varying vec3 vReflect;\n"
    "uniform float refractionRatio;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/envmap_vertex.glsl
const char* ShaderChunk::envmap_vertex() {
  return
    "#ifdef USE_ENVMAP\n"
    "#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG )\n"
    "vWorldPosition = worldPosition.xyz;\n"
    "#else\n"
    "vec3 cameraToVertex = normalize( worldPosition.xyz - cameraPosition );\n"
    "vec3 worldNormal = inverseTransformDirection( transformedNormal, viewMatrix );\n"
    "#ifdef ENVMAP_MODE_REFLECTION\n"
    "vReflect = reflect( cameraToVertex, worldNormal );\n"
    "#else\n"
    "vReflect = refract( cameraToVertex, worldNormal, refractionRatio );\n"
    "#endif\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/fog_fragment.glsl
const char* ShaderChunk::fog_fragment() {
  return
    "#ifdef USE_FOG\n"
    "#ifdef FOG_EXP2\n"
    "float fogFactor = whiteCompliment( exp2( - fogDensity * fogDensity * fogDepth * fogDepth * LOG2 ) );\n"
    "#else\n"
    "float fogFactor = smoothstep( fogNear, fogFar, fogDepth );\n"
    "#endif\n"
    "gl_FragColor.rgb = mix( gl_FragColor.rgb, fogColor, fogFactor );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/fog_pars_fragment.glsl
const char* ShaderChunk::fog_pars_fragment() {
  return
    "#ifdef USE_FOG\n"
    "uniform vec3 fogColor;\n"
    "varying float fogDepth;\n"
    "#ifdef FOG_EXP2\n"
    "uniform float fogDensity;\n"
    "#else\n"
    "uniform float fogNear;\n"
    "uniform float fogFar;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/fog_pars_vertex.glsl
const char* ShaderChunk::fog_pars_vertex() {
  return
    "#ifdef USE_FOG\n"
    "varying float fogDepth;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/fog_vertex.glsl
const char* ShaderChunk::fog_vertex() {
  return
    "#ifdef USE_FOG\n"
    "fogDepth = -mvPosition.z;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/gradientmap_pars_fragment.glsl
const char* ShaderChunk::gradientmap_pars_fragment() {
  return
    "#ifdef TOON\n"
    "uniform sampler2D gradientMap;\n"
    "vec3 getGradientIrradiance( vec3 normal, vec3 lightDirection ) {\n"
    "float dotNL = dot( normal, lightDirection );\n"
    "vec2 coord = vec2( dotNL * 0.5 + 0.5, 0.0 );\n"
    "#ifdef USE_GRADIENTMAP\n"
    "return texture2D( gradientMap, coord ).rgb;\n"
    "#else\n"
    "return ( coord.x < 0.7 ) ? vec3( 0.7 ) : vec3( 1.0 );\n"
    "#endif\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lightmap_fragment.glsl
const char* ShaderChunk::lightmap_fragment() {
  return
    "#ifdef USE_LIGHTMAP\n"
    "reflectedLight.indirectDiffuse += PI * texture2D( lightMap, vUv2 ).xyz * lightMapIntensity; // factor of PI should not be present; included here to prevent breakage\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lightmap_pars_fragment.glsl
const char* ShaderChunk::lightmap_pars_fragment() {
  return
    "#ifdef USE_LIGHTMAP\n"
    "uniform sampler2D lightMap;\n"
    "uniform float lightMapIntensity;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_lambert_vertex.glsl
const char* ShaderChunk::lights_lambert_vertex() {
  return
    "vec3 diffuse = vec3( 1.0 );\n"
    "GeometricContext geometry;\n"
    "geometry.position = mvPosition.xyz;\n"
    "geometry.normal = normalize( transformedNormal );\n"
    "geometry.viewDir = normalize( -mvPosition.xyz );\n"
    "GeometricContext backGeometry;\n"
    "backGeometry.position = geometry.position;\n"
    "backGeometry.normal = -geometry.normal;\n"
    "backGeometry.viewDir = geometry.viewDir;\n"
    "vLightFront = vec3( 0.0 );\n"
    "#ifdef DOUBLE_SIDED\n"
    "vLightBack = vec3( 0.0 );\n"
    "#endif\n"
    "IncidentLight directLight;\n"
    "float dotNL;\n"
    "vec3 directLightColor_Diffuse;\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "getPointDirectLightIrradiance( pointLights[ i ], geometry, directLight );\n"
    "dotNL = dot( geometry.normal, directLight.direction );\n"
    "directLightColor_Diffuse = PI * directLight.color;\n"
    "vLightFront += saturate( dotNL ) * directLightColor_Diffuse;\n"
    "#ifdef DOUBLE_SIDED\n"
    "vLightBack += saturate( -dotNL ) * directLightColor_Diffuse;\n"
    "#endif\n"
    "}\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {\n"
    "getSpotDirectLightIrradiance( spotLights[ i ], geometry, directLight );\n"
    "dotNL = dot( geometry.normal, directLight.direction );\n"
    "directLightColor_Diffuse = PI * directLight.color;\n"
    "vLightFront += saturate( dotNL ) * directLightColor_Diffuse;\n"
    "#ifdef DOUBLE_SIDED\n"
    "vLightBack += saturate( -dotNL ) * directLightColor_Diffuse;\n"
    "#endif\n"
    "}\n"
    "#endif\n"
    "/*\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_RECT_AREA_LIGHTS; i ++ ) {\n"
    "}\n"
    "#endif\n"
    "*/\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {\n"
    "getDirectionalDirectLightIrradiance( directionalLights[ i ], geometry, directLight );\n"
    "dotNL = dot( geometry.normal, directLight.direction );\n"
    "directLightColor_Diffuse = PI * directLight.color;\n"
    "vLightFront += saturate( dotNL ) * directLightColor_Diffuse;\n"
    "#ifdef DOUBLE_SIDED\n"
    "vLightBack += saturate( -dotNL ) * directLightColor_Diffuse;\n"
    "#endif\n"
    "}\n"
    "#endif\n"
    "#if NUM_HEMI_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_HEMI_LIGHTS; i ++ ) {\n"
    "vLightFront += getHemisphereLightIrradiance( hemisphereLights[ i ], geometry );\n"
    "#ifdef DOUBLE_SIDED\n"
    "vLightBack += getHemisphereLightIrradiance( hemisphereLights[ i ], backGeometry );\n"
    "#endif\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_pars.glsl
const char* ShaderChunk::lights_pars() {
  return
    "uniform vec3 ambientLightColor;\n"
    "vec3 getAmbientLightIrradiance( const in vec3 ambientLightColor ) {\n"
    "vec3 irradiance = ambientLightColor;\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "irradiance *= PI;\n"
    "#endif\n"
    "return irradiance;\n"
    "}\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "struct DirectionalLight {\n"
    "vec3 direction;\n"
    "vec3 color;\n"
    "int shadow;\n"
    "float shadowBias;\n"
    "float shadowRadius;\n"
    "vec2 shadowMapSize;\n"
    "};\n"
    "uniform DirectionalLight directionalLights[ NUM_DIR_LIGHTS ];\n"
    "void getDirectionalDirectLightIrradiance( const in DirectionalLight directionalLight, const in GeometricContext geometry, out IncidentLight directLight ) {\n"
    "directLight.color = directionalLight.color;\n"
    "directLight.direction = directionalLight.direction;\n"
    "directLight.visible = true;\n"
    "}\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "struct PointLight {\n"
    "vec3 position;\n"
    "vec3 color;\n"
    "float distance;\n"
    "float decay;\n"
    "int shadow;\n"
    "float shadowBias;\n"
    "float shadowRadius;\n"
    "vec2 shadowMapSize;\n"
    "};\n"
    "uniform PointLight pointLights[ NUM_POINT_LIGHTS ];\n"
    "void getPointDirectLightIrradiance( const in PointLight pointLight, const in GeometricContext geometry, out IncidentLight directLight ) {\n"
    "vec3 lVector = pointLight.position - geometry.position;\n"
    "directLight.direction = normalize( lVector );\n"
    "float lightDistance = length( lVector );\n"
    "directLight.color = pointLight.color;\n"
    "directLight.color *= punctualLightIntensityToIrradianceFactor( lightDistance, pointLight.distance, pointLight.decay );\n"
    "directLight.visible = ( directLight.color != vec3( 0.0 ) );\n"
    "}\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "struct SpotLight {\n"
    "vec3 position;\n"
    "vec3 direction;\n"
    "vec3 color;\n"
    "float distance;\n"
    "float decay;\n"
    "float coneCos;\n"
    "float penumbraCos;\n"
    "int shadow;\n"
    "float shadowBias;\n"
    "float shadowRadius;\n"
    "vec2 shadowMapSize;\n"
    "};\n"
    "uniform SpotLight spotLights[ NUM_SPOT_LIGHTS ];\n"
    "void getSpotDirectLightIrradiance( const in SpotLight spotLight, const in GeometricContext geometry, out IncidentLight directLight  ) {\n"
    "vec3 lVector = spotLight.position - geometry.position;\n"
    "directLight.direction = normalize( lVector );\n"
    "float lightDistance = length( lVector );\n"
    "float angleCos = dot( directLight.direction, spotLight.direction );\n"
    "if ( angleCos > spotLight.coneCos ) {\n"
    "float spotEffect = smoothstep( spotLight.coneCos, spotLight.penumbraCos, angleCos );\n"
    "directLight.color = spotLight.color;\n"
    "directLight.color *= spotEffect * punctualLightIntensityToIrradianceFactor( lightDistance, spotLight.distance, spotLight.decay );\n"
    "directLight.visible = true;\n"
    "} else {\n"
    "directLight.color = vec3( 0.0 );\n"
    "directLight.visible = false;\n"
    "}\n"
    "}\n"
    "#endif\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "struct RectAreaLight {\n"
    "vec3 color;\n"
    "vec3 position;\n"
    "vec3 halfWidth;\n"
    "vec3 halfHeight;\n"
    "};\n"
    "uniform sampler2D ltcMat; // RGBA Float\n"
    "uniform sampler2D ltcMag; // Alpha Float (only has w component)\n"
    "uniform RectAreaLight rectAreaLights[ NUM_RECT_AREA_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_HEMI_LIGHTS > 0\n"
    "struct HemisphereLight {\n"
    "vec3 direction;\n"
    "vec3 skyColor;\n"
    "vec3 groundColor;\n"
    "};\n"
    "uniform HemisphereLight hemisphereLights[ NUM_HEMI_LIGHTS ];\n"
    "vec3 getHemisphereLightIrradiance( const in HemisphereLight hemiLight, const in GeometricContext geometry ) {\n"
    "float dotNL = dot( geometry.normal, hemiLight.direction );\n"
    "float hemiDiffuseWeight = 0.5 * dotNL + 0.5;\n"
    "vec3 irradiance = mix( hemiLight.groundColor, hemiLight.skyColor, hemiDiffuseWeight );\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "irradiance *= PI;\n"
    "#endif\n"
    "return irradiance;\n"
    "}\n"
    "#endif\n"
    "#if defined( USE_ENVMAP ) && defined( PHYSICAL )\n"
    "vec3 getLightProbeIndirectIrradiance( /*const in SpecularLightProbe specularLightProbe,*/ const in GeometricContext geometry, const in int maxMIPLevel ) {\n"
    "vec3 worldNormal = inverseTransformDirection( geometry.normal, viewMatrix );\n"
    "#ifdef ENVMAP_TYPE_CUBE\n"
    "vec3 queryVec = vec3( flipEnvMap * worldNormal.x, worldNormal.yz );\n"
    "#ifdef TEXTURE_LOD_EXT\n"
    "vec4 envMapColor = textureCubeLodEXT( envMap, queryVec, float( maxMIPLevel ) );\n"
    "#else\n"
    "vec4 envMapColor = textureCube( envMap, queryVec, float( maxMIPLevel ) );\n"
    "#endif\n"
    "envMapColor.rgb = envMapTexelToLinear( envMapColor ).rgb;\n"
    "#elif defined( ENVMAP_TYPE_CUBE_UV )\n"
    "vec3 queryVec = vec3( flipEnvMap * worldNormal.x, worldNormal.yz );\n"
    "vec4 envMapColor = textureCubeUV( queryVec, 1.0 );\n"
    "#else\n"
    "vec4 envMapColor = vec4( 0.0 );\n"
    "#endif\n"
    "return PI * envMapColor.rgb * envMapIntensity;\n"
    "}\n"
    "float getSpecularMIPLevel( const in float blinnShininessExponent, const in int maxMIPLevel ) {\n"
    "float maxMIPLevelScalar = float( maxMIPLevel );\n"
    "float desiredMIPLevel = maxMIPLevelScalar - 0.79248 - 0.5 * log2( pow2( blinnShininessExponent ) + 1.0 );\n"
    "return clamp( desiredMIPLevel, 0.0, maxMIPLevelScalar );\n"
    "}\n"
    "vec3 getLightProbeIndirectRadiance( /*const in SpecularLightProbe specularLightProbe,*/ const in GeometricContext geometry, const in float blinnShininessExponent, const in int maxMIPLevel ) {\n"
    "#ifdef ENVMAP_MODE_REFLECTION\n"
    "vec3 reflectVec = reflect( -geometry.viewDir, geometry.normal );\n"
    "#else\n"
    "vec3 reflectVec = refract( -geometry.viewDir, geometry.normal, refractionRatio );\n"
    "#endif\n"
    "reflectVec = inverseTransformDirection( reflectVec, viewMatrix );\n"
    "float specularMIPLevel = getSpecularMIPLevel( blinnShininessExponent, maxMIPLevel );\n"
    "#ifdef ENVMAP_TYPE_CUBE\n"
    "vec3 queryReflectVec = vec3( flipEnvMap * reflectVec.x, reflectVec.yz );\n"
    "#ifdef TEXTURE_LOD_EXT\n"
    "vec4 envMapColor = textureCubeLodEXT( envMap, queryReflectVec, specularMIPLevel );\n"
    "#else\n"
    "vec4 envMapColor = textureCube( envMap, queryReflectVec, specularMIPLevel );\n"
    "#endif\n"
    "envMapColor.rgb = envMapTexelToLinear( envMapColor ).rgb;\n"
    "#elif defined( ENVMAP_TYPE_CUBE_UV )\n"
    "vec3 queryReflectVec = vec3( flipEnvMap * reflectVec.x, reflectVec.yz );\n"
    "vec4 envMapColor = textureCubeUV(queryReflectVec, BlinnExponentToGGXRoughness(blinnShininessExponent));\n"
    "#elif defined( ENVMAP_TYPE_EQUIREC )\n"
    "vec2 sampleUV;\n"
    "sampleUV.y = saturate( reflectVec.y * 0.5 + 0.5 );\n"
    "sampleUV.x = atan( reflectVec.z, reflectVec.x ) * RECIPROCAL_PI2 + 0.5;\n"
    "#ifdef TEXTURE_LOD_EXT\n"
    "vec4 envMapColor = texture2DLodEXT( envMap, sampleUV, specularMIPLevel );\n"
    "#else\n"
    "vec4 envMapColor = texture2D( envMap, sampleUV, specularMIPLevel );\n"
    "#endif\n"
    "envMapColor.rgb = envMapTexelToLinear( envMapColor ).rgb;\n"
    "#elif defined( ENVMAP_TYPE_SPHERE )\n"
    "vec3 reflectView = normalize( ( viewMatrix * vec4( reflectVec, 0.0 ) ).xyz + vec3( 0.0,0.0,1.0 ) );\n"
    "#ifdef TEXTURE_LOD_EXT\n"
    "vec4 envMapColor = texture2DLodEXT( envMap, reflectView.xy * 0.5 + 0.5, specularMIPLevel );\n"
    "#else\n"
    "vec4 envMapColor = texture2D( envMap, reflectView.xy * 0.5 + 0.5, specularMIPLevel );\n"
    "#endif\n"
    "envMapColor.rgb = envMapTexelToLinear( envMapColor ).rgb;\n"
    "#endif\n"
    "return envMapColor.rgb * envMapIntensity;\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_phong_fragment.glsl
const char* ShaderChunk::lights_phong_fragment() {
  return
    "BlinnPhongMaterial material;\n"
    "material.diffuseColor = diffuseColor.rgb;\n"
    "material.specularColor = specular;\n"
    "material.specularShininess = shininess;\n"
    "material.specularStrength = specularStrength;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_phong_pars_fragment.glsl
const char* ShaderChunk::lights_phong_pars_fragment() {
  return
    "varying vec3 vViewPosition;\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "struct BlinnPhongMaterial {\n"
    "vec3	diffuseColor;\n"
    "vec3	specularColor;\n"
    "float	specularShininess;\n"
    "float	specularStrength;\n"
    "};\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "void RE_Direct_RectArea_BlinnPhong( const in RectAreaLight rectAreaLight, const in GeometricContext geometry, const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "vec3 matDiffColor = material.diffuseColor;\n"
    "vec3 matSpecColor = material.specularColor;\n"
    "vec3 lightColor   = rectAreaLight.color;\n"
    "float roughness = BlinnExponentToGGXRoughness( material.specularShininess );\n"
    "vec3 spec = Rect_Area_Light_Specular_Reflectance(\n"
    "geometry,\n"
    "rectAreaLight.position, rectAreaLight.halfWidth, rectAreaLight.halfHeight,\n"
    "roughness,\n"
    "ltcMat, ltcMag );\n"
    "vec3 diff = Rect_Area_Light_Diffuse_Reflectance(\n"
    "geometry,\n"
    "rectAreaLight.position, rectAreaLight.halfWidth, rectAreaLight.halfHeight );\n"
    "reflectedLight.directSpecular += lightColor * matSpecColor * spec / PI2;\n"
    "reflectedLight.directDiffuse  += lightColor * matDiffColor * diff / PI2;\n"
    "}\n"
    "#endif\n"
    "void RE_Direct_BlinnPhong( const in IncidentLight directLight, const in GeometricContext geometry, const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "#ifdef TOON\n"
    "vec3 irradiance = getGradientIrradiance( geometry.normal, directLight.direction ) * directLight.color;\n"
    "#else\n"
    "float dotNL = saturate( dot( geometry.normal, directLight.direction ) );\n"
    "vec3 irradiance = dotNL * directLight.color;\n"
    "#endif\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "irradiance *= PI; // punctual light\n"
    "#endif\n"
    "reflectedLight.directDiffuse += irradiance * BRDF_Diffuse_Lambert( material.diffuseColor );\n"
    "reflectedLight.directSpecular += irradiance * BRDF_Specular_BlinnPhong( directLight, geometry, material.specularColor, material.specularShininess ) * material.specularStrength;\n"
    "}\n"
    "void RE_IndirectDiffuse_BlinnPhong( const in vec3 irradiance, const in GeometricContext geometry, const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "reflectedLight.indirectDiffuse += irradiance * BRDF_Diffuse_Lambert( material.diffuseColor );\n"
    "}\n"
    "#define RE_Direct				RE_Direct_BlinnPhong\n"
    "#define RE_Direct_RectArea		RE_Direct_RectArea_BlinnPhong\n"
    "#define RE_IndirectDiffuse		RE_IndirectDiffuse_BlinnPhong\n"
    "#define Material_LightProbeLOD( material )	(0)\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_physical_fragment.glsl
const char* ShaderChunk::lights_physical_fragment() {
  return
    "PhysicalMaterial material;\n"
    "material.diffuseColor = diffuseColor.rgb * ( 1.0 - metalnessFactor );\n"
    "material.specularRoughness = clamp( roughnessFactor, 0.04, 1.0 );\n"
    "#ifdef STANDARD\n"
    "material.specularColor = mix( vec3( DEFAULT_SPECULAR_COEFFICIENT ), diffuseColor.rgb, metalnessFactor );\n"
    "#else\n"
    "material.specularColor = mix( vec3( MAXIMUM_SPECULAR_COEFFICIENT * pow2( reflectivity ) ), diffuseColor.rgb, metalnessFactor );\n"
    "material.clearCoat = saturate( clearCoat ); // Burley clearcoat model\n"
    "material.clearCoatRoughness = clamp( clearCoatRoughness, 0.04, 1.0 );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_physical_pars_fragment.glsl
const char* ShaderChunk::lights_physical_pars_fragment() {
  return
    "struct PhysicalMaterial {\n"
    "vec3	diffuseColor;\n"
    "float	specularRoughness;\n"
    "vec3	specularColor;\n"
    "#ifndef STANDARD\n"
    "float clearCoat;\n"
    "float clearCoatRoughness;\n"
    "#endif\n"
    "};\n"
    "#define MAXIMUM_SPECULAR_COEFFICIENT 0.16\n"
    "#define DEFAULT_SPECULAR_COEFFICIENT 0.04\n"
    "float clearCoatDHRApprox( const in float roughness, const in float dotNL ) {\n"
    "return DEFAULT_SPECULAR_COEFFICIENT + ( 1.0 - DEFAULT_SPECULAR_COEFFICIENT ) * ( pow( 1.0 - dotNL, 5.0 ) * pow( 1.0 - roughness, 2.0 ) );\n"
    "}\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "void RE_Direct_RectArea_Physical( const in RectAreaLight rectAreaLight, const in GeometricContext geometry, const in PhysicalMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "vec3 matDiffColor = material.diffuseColor;\n"
    "vec3 matSpecColor = material.specularColor;\n"
    "vec3 lightColor   = rectAreaLight.color;\n"
    "float roughness = material.specularRoughness;\n"
    "vec3 spec = Rect_Area_Light_Specular_Reflectance(\n"
    "geometry,\n"
    "rectAreaLight.position, rectAreaLight.halfWidth, rectAreaLight.halfHeight,\n"
    "roughness,\n"
    "ltcMat, ltcMag );\n"
    "vec3 diff = Rect_Area_Light_Diffuse_Reflectance(\n"
    "geometry,\n"
    "rectAreaLight.position, rectAreaLight.halfWidth, rectAreaLight.halfHeight );\n"
    "reflectedLight.directSpecular += lightColor * matSpecColor * spec;\n"
    "reflectedLight.directDiffuse  += lightColor * matDiffColor * diff;\n"
    "}\n"
    "#endif\n"
    "void RE_Direct_Physical( const in IncidentLight directLight, const in GeometricContext geometry, const in PhysicalMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "float dotNL = saturate( dot( geometry.normal, directLight.direction ) );\n"
    "vec3 irradiance = dotNL * directLight.color;\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "irradiance *= PI; // punctual light\n"
    "#endif\n"
    "#ifndef STANDARD\n"
    "float clearCoatDHR = material.clearCoat * clearCoatDHRApprox( material.clearCoatRoughness, dotNL );\n"
    "#else\n"
    "float clearCoatDHR = 0.0;\n"
    "#endif\n"
    "reflectedLight.directSpecular += ( 1.0 - clearCoatDHR ) * irradiance * BRDF_Specular_GGX( directLight, geometry, material.specularColor, material.specularRoughness );\n"
    "reflectedLight.directDiffuse += ( 1.0 - clearCoatDHR ) * irradiance * BRDF_Diffuse_Lambert( material.diffuseColor );\n"
    "#ifndef STANDARD\n"
    "reflectedLight.directSpecular += irradiance * material.clearCoat * BRDF_Specular_GGX( directLight, geometry, vec3( DEFAULT_SPECULAR_COEFFICIENT ), material.clearCoatRoughness );\n"
    "#endif\n"
    "}\n"
    "void RE_IndirectDiffuse_Physical( const in vec3 irradiance, const in GeometricContext geometry, const in PhysicalMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "reflectedLight.indirectDiffuse += irradiance * BRDF_Diffuse_Lambert( material.diffuseColor );\n"
    "}\n"
    "void RE_IndirectSpecular_Physical( const in vec3 radiance, const in vec3 clearCoatRadiance, const in GeometricContext geometry, const in PhysicalMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "#ifndef STANDARD\n"
    "float dotNV = saturate( dot( geometry.normal, geometry.viewDir ) );\n"
    "float dotNL = dotNV;\n"
    "float clearCoatDHR = material.clearCoat * clearCoatDHRApprox( material.clearCoatRoughness, dotNL );\n"
    "#else\n"
    "float clearCoatDHR = 0.0;\n"
    "#endif\n"
    "reflectedLight.indirectSpecular += ( 1.0 - clearCoatDHR ) * radiance * BRDF_Specular_GGX_Environment( geometry, material.specularColor, material.specularRoughness );\n"
    "#ifndef STANDARD\n"
    "reflectedLight.indirectSpecular += clearCoatRadiance * material.clearCoat * BRDF_Specular_GGX_Environment( geometry, vec3( DEFAULT_SPECULAR_COEFFICIENT ), material.clearCoatRoughness );\n"
    "#endif\n"
    "}\n"
    "#define RE_Direct				RE_Direct_Physical\n"
    "#define RE_Direct_RectArea		RE_Direct_RectArea_Physical\n"
    "#define RE_IndirectDiffuse		RE_IndirectDiffuse_Physical\n"
    "#define RE_IndirectSpecular		RE_IndirectSpecular_Physical\n"
    "#define Material_BlinnShininessExponent( material )   GGXRoughnessToBlinnExponent( material.specularRoughness )\n"
    "#define Material_ClearCoat_BlinnShininessExponent( material )   GGXRoughnessToBlinnExponent( material.clearCoatRoughness )\n"
    "float computeSpecularOcclusion( const in float dotNV, const in float ambientOcclusion, const in float roughness ) {\n"
    "return saturate( pow( dotNV + ambientOcclusion, exp2( - 16.0 * roughness - 1.0 ) ) - 1.0 + ambientOcclusion );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/lights_template.glsl
const char* ShaderChunk::lights_template() {
  return
    "/**\n"
    "* This is a template that can be used to light a material, it uses pluggable\n"
    "* RenderEquations (RE)for specific lighting scenarios.\n"
    "*\n"
    "* Instructions for use:\n"
    "* - Ensure that both RE_Direct, RE_IndirectDiffuse and RE_IndirectSpecular are defined\n"
    "* - If you have defined an RE_IndirectSpecular, you need to also provide a Material_LightProbeLOD. <---- ???\n"
    "* - Create a material parameter that is to be passed as the third parameter to your lighting functions.\n"
    "*\n"
    "* TODO:\n"
    "* - Add area light support.\n"
    "* - Add sphere light support.\n"
    "* - Add diffuse light probe (irradiance cubemap) support.\n"
    "*/\n"
    "GeometricContext geometry;\n"
    "geometry.position = - vViewPosition;\n"
    "geometry.normal = normal;\n"
    "geometry.viewDir = normalize( vViewPosition );\n"
    "IncidentLight directLight;\n"
    "#if ( NUM_POINT_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "PointLight pointLight;\n"
    "for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "pointLight = pointLights[ i ];\n"
    "getPointDirectLightIrradiance( pointLight, geometry, directLight );\n"
    "#ifdef USE_SHADOWMAP\n"
    "directLight.color *= all( bvec2( pointLight.shadow, directLight.visible ) ) ? getPointShadow( pointShadowMap[ i ], pointLight.shadowMapSize, pointLight.shadowBias, pointLight.shadowRadius, vPointShadowCoord[ i ] ) : 1.0;\n"
    "#endif\n"
    "RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "}\n"
    "#endif\n"
    "#if ( NUM_SPOT_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "SpotLight spotLight;\n"
    "for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {\n"
    "spotLight = spotLights[ i ];\n"
    "getSpotDirectLightIrradiance( spotLight, geometry, directLight );\n"
    "#ifdef USE_SHADOWMAP\n"
    "directLight.color *= all( bvec2( spotLight.shadow, directLight.visible ) ) ? getShadow( spotShadowMap[ i ], spotLight.shadowMapSize, spotLight.shadowBias, spotLight.shadowRadius, vSpotShadowCoord[ i ] ) : 1.0;\n"
    "#endif\n"
    "RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "}\n"
    "#endif\n"
    "#if ( NUM_DIR_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "DirectionalLight directionalLight;\n"
    "for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {\n"
    "directionalLight = directionalLights[ i ];\n"
    "getDirectionalDirectLightIrradiance( directionalLight, geometry, directLight );\n"
    "#ifdef USE_SHADOWMAP\n"
    "directLight.color *= all( bvec2( directionalLight.shadow, directLight.visible ) ) ? getShadow( directionalShadowMap[ i ], directionalLight.shadowMapSize, directionalLight.shadowBias, directionalLight.shadowRadius, vDirectionalShadowCoord[ i ] ) : 1.0;\n"
    "#endif\n"
    "RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "}\n"
    "#endif\n"
    "#if ( NUM_RECT_AREA_LIGHTS > 0 ) && defined( RE_Direct_RectArea )\n"
    "RectAreaLight rectAreaLight;\n"
    "for ( int i = 0; i < NUM_RECT_AREA_LIGHTS; i ++ ) {\n"
    "rectAreaLight = rectAreaLights[ i ];\n"
    "RE_Direct_RectArea( rectAreaLight, geometry, material, reflectedLight );\n"
    "}\n"
    "#endif\n"
    "#if defined( RE_IndirectDiffuse )\n"
    "vec3 irradiance = getAmbientLightIrradiance( ambientLightColor );\n"
    "#ifdef USE_LIGHTMAP\n"
    "vec3 lightMapIrradiance = texture2D( lightMap, vUv2 ).xyz * lightMapIntensity;\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "lightMapIrradiance *= PI; // factor of PI should not be present; included here to prevent breakage\n"
    "#endif\n"
    "irradiance += lightMapIrradiance;\n"
    "#endif\n"
    "#if ( NUM_HEMI_LIGHTS > 0 )\n"
    "for ( int i = 0; i < NUM_HEMI_LIGHTS; i ++ ) {\n"
    "irradiance += getHemisphereLightIrradiance( hemisphereLights[ i ], geometry );\n"
    "}\n"
    "#endif\n"
    "#if defined( USE_ENVMAP ) && defined( PHYSICAL ) && defined( ENVMAP_TYPE_CUBE_UV )\n"
    "irradiance += getLightProbeIndirectIrradiance( /*lightProbe,*/ geometry, 8 );\n"
    "#endif\n"
    "RE_IndirectDiffuse( irradiance, geometry, material, reflectedLight );\n"
    "#endif\n"
    "#if defined( USE_ENVMAP ) && defined( RE_IndirectSpecular )\n"
    "vec3 radiance = getLightProbeIndirectRadiance( /*specularLightProbe,*/ geometry, Material_BlinnShininessExponent( material ), 8 );\n"
    "#ifndef STANDARD\n"
    "vec3 clearCoatRadiance = getLightProbeIndirectRadiance( /*specularLightProbe,*/ geometry, Material_ClearCoat_BlinnShininessExponent( material ), 8 );\n"
    "#else\n"
    "vec3 clearCoatRadiance = vec3( 0.0 );\n"
    "#endif\n"
    "RE_IndirectSpecular( radiance, clearCoatRadiance, geometry, material, reflectedLight );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/logdepthbuf_fragment.glsl
const char* ShaderChunk::logdepthbuf_fragment() {
  return
    "#if defined(USE_LOGDEPTHBUF) && defined(USE_LOGDEPTHBUF_EXT)\n"
    "gl_FragDepthEXT = log2(vFragDepth) * logDepthBufFC * 0.5;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/logdepthbuf_pars_fragment.glsl
const char* ShaderChunk::logdepthbuf_pars_fragment() {
  return
    "#ifdef USE_LOGDEPTHBUF\n"
    "uniform float logDepthBufFC;\n"
    "#ifdef USE_LOGDEPTHBUF_EXT\n"
    "varying float vFragDepth;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/logdepthbuf_pars_vertex.glsl
const char* ShaderChunk::logdepthbuf_pars_vertex() {
  return
    "#ifdef USE_LOGDEPTHBUF\n"
    "#ifdef USE_LOGDEPTHBUF_EXT\n"
    "varying float vFragDepth;\n"
    "#endif\n"
    "uniform float logDepthBufFC;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/logdepthbuf_vertex.glsl
const char* ShaderChunk::logdepthbuf_vertex() {
  return
    "#ifdef USE_LOGDEPTHBUF\n"
    "gl_Position.z = log2(max( EPSILON, gl_Position.w + 1.0 )) * logDepthBufFC;\n"
    "#ifdef USE_LOGDEPTHBUF_EXT\n"
    "vFragDepth = 1.0 + gl_Position.w;\n"
    "#else\n"
    "gl_Position.z = (gl_Position.z - 1.0) * gl_Position.w;\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/map_fragment.glsl
const char* ShaderChunk::map_fragment() {
  return
    "#ifdef USE_MAP\n"
    "vec4 texelColor = texture2D( map, vUv );\n"
    "texelColor = mapTexelToLinear( texelColor );\n"
    "diffuseColor *= texelColor;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/map_pars_fragment.glsl
const char* ShaderChunk::map_pars_fragment() {
  return
    "#ifdef USE_MAP\n"
    "uniform sampler2D map;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/map_particle_fragment.glsl
const char* ShaderChunk::map_particle_fragment() {
  return
    "#ifdef USE_MAP\n"
    "vec4 mapTexel = texture2D( map, vec2( gl_PointCoord.x, 1.0 - gl_PointCoord.y ) * offsetRepeat.zw + offsetRepeat.xy );\n"
    "diffuseColor *= mapTexelToLinear( mapTexel );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/map_particle_pars_fragment.glsl
const char* ShaderChunk::map_particle_pars_fragment() {
  return
    "#ifdef USE_MAP\n"
    "uniform vec4 offsetRepeat;\n"
    "uniform sampler2D map;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/metalnessmap_fragment.glsl
const char* ShaderChunk::metalnessmap_fragment() {
  return
    "float metalnessFactor = metalness;\n"
    "#ifdef USE_METALNESSMAP\n"
    "vec4 texelMetalness = texture2D( metalnessMap, vUv );\n"
    "metalnessFactor *= texelMetalness.b;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/metalnessmap_pars_fragment.glsl
const char* ShaderChunk::metalnessmap_pars_fragment() {
  return
    "#ifdef USE_METALNESSMAP\n"
    "uniform sampler2D metalnessMap;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/morphnormal_vertex.glsl
const char* ShaderChunk::morphnormal_vertex() {
  return
    "#ifdef USE_MORPHNORMALS\n"
    "objectNormal += ( morphNormal0 - normal ) * morphTargetInfluences[ 0 ];\n"
    "objectNormal += ( morphNormal1 - normal ) * morphTargetInfluences[ 1 ];\n"
    "objectNormal += ( morphNormal2 - normal ) * morphTargetInfluences[ 2 ];\n"
    "objectNormal += ( morphNormal3 - normal ) * morphTargetInfluences[ 3 ];\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/morphtarget_pars_vertex.glsl
const char* ShaderChunk::morphtarget_pars_vertex() {
  return
    "#ifdef USE_MORPHTARGETS\n"
    "#ifndef USE_MORPHNORMALS\n"
    "uniform float morphTargetInfluences[ 8 ];\n"
    "#else\n"
    "uniform float morphTargetInfluences[ 4 ];\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/morphtarget_vertex.glsl
const char* ShaderChunk::morphtarget_vertex() {
  return
    "#ifdef USE_MORPHTARGETS\n"
    "transformed += ( morphTarget0 - position ) * morphTargetInfluences[ 0 ];\n"
    "transformed += ( morphTarget1 - position ) * morphTargetInfluences[ 1 ];\n"
    "transformed += ( morphTarget2 - position ) * morphTargetInfluences[ 2 ];\n"
    "transformed += ( morphTarget3 - position ) * morphTargetInfluences[ 3 ];\n"
    "#ifndef USE_MORPHNORMALS\n"
    "transformed += ( morphTarget4 - position ) * morphTargetInfluences[ 4 ];\n"
    "transformed += ( morphTarget5 - position ) * morphTargetInfluences[ 5 ];\n"
    "transformed += ( morphTarget6 - position ) * morphTargetInfluences[ 6 ];\n"
    "transformed += ( morphTarget7 - position ) * morphTargetInfluences[ 7 ];\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/normal_flip.glsl
const char* ShaderChunk::normal_flip() {
  return
    "#ifdef DOUBLE_SIDED\n"
    "float flipNormal = ( float( gl_FrontFacing ) * 2.0 - 1.0 );\n"
    "#else\n"
    "float flipNormal = 1.0;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/normal_fragment.glsl
const char* ShaderChunk::normal_fragment() {
  return
    "#ifdef FLAT_SHADED\n"
    "vec3 fdx = vec3( dFdx( vViewPosition.x ), dFdx( vViewPosition.y ), dFdx( vViewPosition.z ) );\n"
    "vec3 fdy = vec3( dFdy( vViewPosition.x ), dFdy( vViewPosition.y ), dFdy( vViewPosition.z ) );\n"
    "vec3 normal = normalize( cross( fdx, fdy ) );\n"
    "#else\n"
    "vec3 normal = normalize( vNormal ) * flipNormal;\n"
    "#endif\n"
    "#ifdef USE_NORMALMAP\n"
    "normal = perturbNormal2Arb( -vViewPosition, normal );\n"
    "#elif defined( USE_BUMPMAP )\n"
    "normal = perturbNormalArb( -vViewPosition, normal, dHdxy_fwd() );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/normalmap_pars_fragment.glsl
const char* ShaderChunk::normalmap_pars_fragment() {
  return
    "#ifdef USE_NORMALMAP\n"
    "uniform sampler2D normalMap;\n"
    "uniform vec2 normalScale;\n"
    "vec3 perturbNormal2Arb( vec3 eye_pos, vec3 surf_norm ) {\n"
    "vec3 q0 = dFdx( eye_pos.xyz );\n"
    "vec3 q1 = dFdy( eye_pos.xyz );\n"
    "vec2 st0 = dFdx( vUv.st );\n"
    "vec2 st1 = dFdy( vUv.st );\n"
    "vec3 S = normalize( q0 * st1.t - q1 * st0.t );\n"
    "vec3 T = normalize( -q0 * st1.s + q1 * st0.s );\n"
    "vec3 N = normalize( surf_norm );\n"
    "vec3 mapN = texture2D( normalMap, vUv ).xyz * 2.0 - 1.0;\n"
    "mapN.xy = normalScale * mapN.xy;\n"
    "mat3 tsn = mat3( S, T, N );\n"
    "return normalize( tsn * mapN );\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/packing.glsl
const char* ShaderChunk::packing() {
  return
    "vec3 packNormalToRGB( const in vec3 normal ) {\n"
    "return normalize( normal ) * 0.5 + 0.5;\n"
    "}\n"
    "vec3 unpackRGBToNormal( const in vec3 rgb ) {\n"
    "return 1.0 - 2.0 * rgb.xyz;\n"
    "}\n"
    "const float PackUpscale = 256. / 255.; // fraction -> 0..1 (including 1)\n"
    "const float UnpackDownscale = 255. / 256.; // 0..1 -> fraction (excluding 1)\n"
    "const vec3 PackFactors = vec3( 256. * 256. * 256., 256. * 256.,  256. );\n"
    "const vec4 UnpackFactors = UnpackDownscale / vec4( PackFactors, 1. );\n"
    "const float ShiftRight8 = 1. / 256.;\n"
    "vec4 packDepthToRGBA( const in float v ) {\n"
    "vec4 r = vec4( fract( v * PackFactors ), v );\n"
    "r.yzw -= r.xyz * ShiftRight8; // tidy overflow\n"
    "return r * PackUpscale;\n"
    "}\n"
    "float unpackRGBAToDepth( const in vec4 v ) {\n"
    "return dot( v, UnpackFactors );\n"
    "}\n"
    "float viewZToOrthographicDepth( const in float viewZ, const in float near, const in float far ) {\n"
    "return ( viewZ + near ) / ( near - far );\n"
    "}\n"
    "float orthographicDepthToViewZ( const in float linearClipZ, const in float near, const in float far ) {\n"
    "return linearClipZ * ( near - far ) - near;\n"
    "}\n"
    "float viewZToPerspectiveDepth( const in float viewZ, const in float near, const in float far ) {\n"
    "return (( near + viewZ ) * far ) / (( far - near ) * viewZ );\n"
    "}\n"
    "float perspectiveDepthToViewZ( const in float invClipZ, const in float near, const in float far ) {\n"
    "return ( near * far ) / ( ( far - near ) * invClipZ - far );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/premultiplied_alpha_fragment.glsl
const char* ShaderChunk::premultiplied_alpha_fragment() {
  return
    "#ifdef PREMULTIPLIED_ALPHA\n"
    "gl_FragColor.rgb *= gl_FragColor.a;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/project_vertex.glsl
const char* ShaderChunk::project_vertex() {
  return
    "#ifdef USE_SKINNING\n"
    "vec4 mvPosition = modelViewMatrix * skinned;\n"
    "#else\n"
    "vec4 mvPosition = modelViewMatrix * vec4( transformed, 1.0 );\n"
    "#endif\n"
    "gl_Position = projectionMatrix * mvPosition;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/roughnessmap_fragment.glsl
const char* ShaderChunk::roughnessmap_fragment() {
  return
    "float roughnessFactor = roughness;\n"
    "#ifdef USE_ROUGHNESSMAP\n"
    "vec4 texelRoughness = texture2D( roughnessMap, vUv );\n"
    "roughnessFactor *= texelRoughness.g;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/roughnessmap_pars_fragment.glsl
const char* ShaderChunk::roughnessmap_pars_fragment() {
  return
    "#ifdef USE_ROUGHNESSMAP\n"
    "uniform sampler2D roughnessMap;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/shadowmap_pars_fragment.glsl
const char* ShaderChunk::shadowmap_pars_fragment() {
  return
    "#ifdef USE_SHADOWMAP\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "uniform sampler2D directionalShadowMap[ NUM_DIR_LIGHTS ];\n"
    "varying vec4 vDirectionalShadowCoord[ NUM_DIR_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "uniform sampler2D spotShadowMap[ NUM_SPOT_LIGHTS ];\n"
    "varying vec4 vSpotShadowCoord[ NUM_SPOT_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "uniform sampler2D pointShadowMap[ NUM_POINT_LIGHTS ];\n"
    "varying vec4 vPointShadowCoord[ NUM_POINT_LIGHTS ];\n"
    "#endif\n"
    "/*\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "#endif\n"
    "*/\n"
    "float texture2DCompare( sampler2D depths, vec2 uv, float compare ) {\n"
    "return step( compare, unpackRGBAToDepth( texture2D( depths, uv ) ) );\n"
    "}\n"
    "float texture2DShadowLerp( sampler2D depths, vec2 size, vec2 uv, float compare ) {\n"
    "const vec2 offset = vec2( 0.0, 1.0 );\n"
    "vec2 texelSize = vec2( 1.0 ) / size;\n"
    "vec2 centroidUV = floor( uv * size + 0.5 ) / size;\n"
    "float lb = texture2DCompare( depths, centroidUV + texelSize * offset.xx, compare );\n"
    "float lt = texture2DCompare( depths, centroidUV + texelSize * offset.xy, compare );\n"
    "float rb = texture2DCompare( depths, centroidUV + texelSize * offset.yx, compare );\n"
    "float rt = texture2DCompare( depths, centroidUV + texelSize * offset.yy, compare );\n"
    "vec2 f = fract( uv * size + 0.5 );\n"
    "float a = mix( lb, lt, f.y );\n"
    "float b = mix( rb, rt, f.y );\n"
    "float c = mix( a, b, f.x );\n"
    "return c;\n"
    "}\n"
    "float getShadow( sampler2D shadowMap, vec2 shadowMapSize, float shadowBias, float shadowRadius, vec4 shadowCoord ) {\n"
    "shadowCoord.xyz /= shadowCoord.w;\n"
    "shadowCoord.z += shadowBias;\n"
    "bvec4 inFrustumVec = bvec4 ( shadowCoord.x >= 0.0, shadowCoord.x <= 1.0, shadowCoord.y >= 0.0, shadowCoord.y <= 1.0 );\n"
    "bool inFrustum = all( inFrustumVec );\n"
    "bvec2 frustumTestVec = bvec2( inFrustum, shadowCoord.z <= 1.0 );\n"
    "bool frustumTest = all( frustumTestVec );\n"
    "if ( frustumTest ) {\n"
    "#if defined( SHADOWMAP_TYPE_PCF )\n"
    "vec2 texelSize = vec2( 1.0 ) / shadowMapSize;\n"
    "float dx0 = - texelSize.x * shadowRadius;\n"
    "float dy0 = - texelSize.y * shadowRadius;\n"
    "float dx1 = + texelSize.x * shadowRadius;\n"
    "float dy1 = + texelSize.y * shadowRadius;\n"
    "return (\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, dy0 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( 0.0, dy0 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, dy0 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, 0.0 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy, shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, 0.0 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, dy1 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( 0.0, dy1 ), shadowCoord.z ) +\n"
    "texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, dy1 ), shadowCoord.z )\n"
    ") * ( 1.0 / 9.0 );\n"
    "#elif defined( SHADOWMAP_TYPE_PCF_SOFT )\n"
    "vec2 texelSize = vec2( 1.0 ) / shadowMapSize;\n"
    "float dx0 = - texelSize.x * shadowRadius;\n"
    "float dy0 = - texelSize.y * shadowRadius;\n"
    "float dx1 = + texelSize.x * shadowRadius;\n"
    "float dy1 = + texelSize.y * shadowRadius;\n"
    "return (\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, dy0 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( 0.0, dy0 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, dy0 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, 0.0 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy, shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, 0.0 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, dy1 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( 0.0, dy1 ), shadowCoord.z ) +\n"
    "texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, dy1 ), shadowCoord.z )\n"
    ") * ( 1.0 / 9.0 );\n"
    "#else // no percentage-closer filtering:\n"
    "return texture2DCompare( shadowMap, shadowCoord.xy, shadowCoord.z );\n"
    "#endif\n"
    "}\n"
    "return 1.0;\n"
    "}\n"
    "vec2 cubeToUV( vec3 v, float texelSizeY ) {\n"
    "vec3 absV = abs( v );\n"
    "float scaleToCube = 1.0 / max( absV.x, max( absV.y, absV.z ) );\n"
    "absV *= scaleToCube;\n"
    "v *= scaleToCube * ( 1.0 - 2.0 * texelSizeY );\n"
    "vec2 planar = v.xy;\n"
    "float almostATexel = 1.5 * texelSizeY;\n"
    "float almostOne = 1.0 - almostATexel;\n"
    "if ( absV.z >= almostOne ) {\n"
    "if ( v.z > 0.0 )\n"
    "planar.x = 4.0 - v.x;\n"
    "} else if ( absV.x >= almostOne ) {\n"
    "float signX = sign( v.x );\n"
    "planar.x = v.z * signX + 2.0 * signX;\n"
    "} else if ( absV.y >= almostOne ) {\n"
    "float signY = sign( v.y );\n"
    "planar.x = v.x + 2.0 * signY + 2.0;\n"
    "planar.y = v.z * signY - 2.0;\n"
    "}\n"
    "return vec2( 0.125, 0.25 ) * planar + vec2( 0.375, 0.75 );\n"
    "}\n"
    "float getPointShadow( sampler2D shadowMap, vec2 shadowMapSize, float shadowBias, float shadowRadius, vec4 shadowCoord ) {\n"
    "vec2 texelSize = vec2( 1.0 ) / ( shadowMapSize * vec2( 4.0, 2.0 ) );\n"
    "vec3 lightToPosition = shadowCoord.xyz;\n"
    "vec3 bd3D = normalize( lightToPosition );\n"
    "float dp = ( length( lightToPosition ) - shadowBias ) / 1000.0;\n"
    "#if defined( SHADOWMAP_TYPE_PCF ) || defined( SHADOWMAP_TYPE_PCF_SOFT )\n"
    "vec2 offset = vec2( - 1, 1 ) * shadowRadius * texelSize.y;\n"
    "return (\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xyy, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yyy, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xyx, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yyx, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xxy, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yxy, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xxx, texelSize.y ), dp ) +\n"
    "texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yxx, texelSize.y ), dp )\n"
    ") * ( 1.0 / 9.0 );\n"
    "#else // no percentage-closer filtering\n"
    "return texture2DCompare( shadowMap, cubeToUV( bd3D, texelSize.y ), dp );\n"
    "#endif\n"
    "}\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/shadowmap_pars_vertex.glsl
const char* ShaderChunk::shadowmap_pars_vertex() {
  return
    "#ifdef USE_SHADOWMAP\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "uniform mat4 directionalShadowMatrix[ NUM_DIR_LIGHTS ];\n"
    "varying vec4 vDirectionalShadowCoord[ NUM_DIR_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "uniform mat4 spotShadowMatrix[ NUM_SPOT_LIGHTS ];\n"
    "varying vec4 vSpotShadowCoord[ NUM_SPOT_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "uniform mat4 pointShadowMatrix[ NUM_POINT_LIGHTS ];\n"
    "varying vec4 vPointShadowCoord[ NUM_POINT_LIGHTS ];\n"
    "#endif\n"
    "/*\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "#endif\n"
    "*/\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/shadowmap_vertex.glsl
const char* ShaderChunk::shadowmap_vertex() {
  return
    "#ifdef USE_SHADOWMAP\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {\n"
    "vDirectionalShadowCoord[ i ] = directionalShadowMatrix[ i ] * worldPosition;\n"
    "}\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {\n"
    "vSpotShadowCoord[ i ] = spotShadowMatrix[ i ] * worldPosition;\n"
    "}\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "vPointShadowCoord[ i ] = pointShadowMatrix[ i ] * worldPosition;\n"
    "}\n"
    "#endif\n"
    "/*\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "#endif\n"
    "*/\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/shadowmask_pars_fragment.glsl
const char* ShaderChunk::shadowmask_pars_fragment() {
  return
    "float getShadowMask() {\n"
    "float shadow = 1.0;\n"
    "#ifdef USE_SHADOWMAP\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "DirectionalLight directionalLight;\n"
    "for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {\n"
    "directionalLight = directionalLights[ i ];\n"
    "shadow *= bool( directionalLight.shadow ) ? getShadow( directionalShadowMap[ i ], directionalLight.shadowMapSize, directionalLight.shadowBias, directionalLight.shadowRadius, vDirectionalShadowCoord[ i ] ) : 1.0;\n"
    "}\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "SpotLight spotLight;\n"
    "for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {\n"
    "spotLight = spotLights[ i ];\n"
    "shadow *= bool( spotLight.shadow ) ? getShadow( spotShadowMap[ i ], spotLight.shadowMapSize, spotLight.shadowBias, spotLight.shadowRadius, vSpotShadowCoord[ i ] ) : 1.0;\n"
    "}\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "PointLight pointLight;\n"
    "for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "pointLight = pointLights[ i ];\n"
    "shadow *= bool( pointLight.shadow ) ? getPointShadow( pointShadowMap[ i ], pointLight.shadowMapSize, pointLight.shadowBias, pointLight.shadowRadius, vPointShadowCoord[ i ] ) : 1.0;\n"
    "}\n"
    "#endif\n"
    "/*\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "#endif\n"
    "*/\n"
    "#endif\n"
    "return shadow;\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/skinbase_vertex.glsl
const char* ShaderChunk::skinbase_vertex() {
  return
    "#ifdef USE_SKINNING\n"
    "mat4 boneMatX = getBoneMatrix( skinIndex.x );\n"
    "mat4 boneMatY = getBoneMatrix( skinIndex.y );\n"
    "mat4 boneMatZ = getBoneMatrix( skinIndex.z );\n"
    "mat4 boneMatW = getBoneMatrix( skinIndex.w );\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/skinning_pars_vertex.glsl
const char* ShaderChunk::skinning_pars_vertex() {
  return
    "#ifdef USE_SKINNING\n"
    "uniform mat4 bindMatrix;\n"
    "uniform mat4 bindMatrixInverse;\n"
    "#ifdef BONE_TEXTURE\n"
    "uniform sampler2D boneTexture;\n"
    "uniform int boneTextureSize;\n"
    "mat4 getBoneMatrix( const in float i ) {\n"
    "float j = i * 4.0;\n"
    "float x = mod( j, float( boneTextureSize ) );\n"
    "float y = floor( j / float( boneTextureSize ) );\n"
    "float dx = 1.0 / float( boneTextureSize );\n"
    "float dy = 1.0 / float( boneTextureSize );\n"
    "y = dy * ( y + 0.5 );\n"
    "vec4 v1 = texture2D( boneTexture, vec2( dx * ( x + 0.5 ), y ) );\n"
    "vec4 v2 = texture2D( boneTexture, vec2( dx * ( x + 1.5 ), y ) );\n"
    "vec4 v3 = texture2D( boneTexture, vec2( dx * ( x + 2.5 ), y ) );\n"
    "vec4 v4 = texture2D( boneTexture, vec2( dx * ( x + 3.5 ), y ) );\n"
    "mat4 bone = mat4( v1, v2, v3, v4 );\n"
    "return bone;\n"
    "}\n"
    "#else\n"
    "uniform mat4 boneMatrices[ MAX_BONES ];\n"
    "mat4 getBoneMatrix( const in float i ) {\n"
    "mat4 bone = boneMatrices[ int(i) ];\n"
    "return bone;\n"
    "}\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/skinning_vertex.glsl
const char* ShaderChunk::skinning_vertex() {
  return
    "#ifdef USE_SKINNING\n"
    "vec4 skinVertex = bindMatrix * vec4( transformed, 1.0 );\n"
    "vec4 skinned = vec4( 0.0 );\n"
    "skinned += boneMatX * skinVertex * skinWeight.x;\n"
    "skinned += boneMatY * skinVertex * skinWeight.y;\n"
    "skinned += boneMatZ * skinVertex * skinWeight.z;\n"
    "skinned += boneMatW * skinVertex * skinWeight.w;\n"
    "skinned  = bindMatrixInverse * skinned;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/skinnormal_vertex.glsl
const char* ShaderChunk::skinnormal_vertex() {
  return
    "#ifdef USE_SKINNING\n"
    "mat4 skinMatrix = mat4( 0.0 );\n"
    "skinMatrix += skinWeight.x * boneMatX;\n"
    "skinMatrix += skinWeight.y * boneMatY;\n"
    "skinMatrix += skinWeight.z * boneMatZ;\n"
    "skinMatrix += skinWeight.w * boneMatW;\n"
    "skinMatrix  = bindMatrixInverse * skinMatrix * bindMatrix;\n"
    "objectNormal = vec4( skinMatrix * vec4( objectNormal, 0.0 ) ).xyz;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/specularmap_fragment.glsl
const char* ShaderChunk::specularmap_fragment() {
  return
    "float specularStrength;\n"
    "#ifdef USE_SPECULARMAP\n"
    "vec4 texelSpecular = texture2D( specularMap, vUv );\n"
    "specularStrength = texelSpecular.r;\n"
    "#else\n"
    "specularStrength = 1.0;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/specularmap_pars_fragment.glsl
const char* ShaderChunk::specularmap_pars_fragment() {
  return
    "#ifdef USE_SPECULARMAP\n"
    "uniform sampler2D specularMap;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/tonemapping_fragment.glsl
const char* ShaderChunk::tonemapping_fragment() {
  return
    "#if defined( TONE_MAPPING )\n"
    "gl_FragColor.rgb = toneMapping( gl_FragColor.rgb );\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/tonemapping_pars_fragment.glsl
const char* ShaderChunk::tonemapping_pars_fragment() {
  return
    "#define saturate(a) clamp( a, 0.0, 1.0 )\n"
    "uniform float toneMappingExposure;\n"
    "uniform float toneMappingWhitePoint;\n"
    "vec3 LinearToneMapping( vec3 color ) {\n"
    "return toneMappingExposure * color;\n"
    "}\n"
    "vec3 ReinhardToneMapping( vec3 color ) {\n"
    "color *= toneMappingExposure;\n"
    "return saturate( color / ( vec3( 1.0 ) + color ) );\n"
    "}\n"
    "#define Uncharted2Helper( x ) max( ( ( x * ( 0.15 * x + 0.10 * 0.50 ) + 0.20 * 0.02 ) / ( x * ( 0.15 * x + 0.50 ) + 0.20 * 0.30 ) ) - 0.02 / 0.30, vec3( 0.0 ) )\n"
    "vec3 Uncharted2ToneMapping( vec3 color ) {\n"
    "color *= toneMappingExposure;\n"
    "return saturate( Uncharted2Helper( color ) / Uncharted2Helper( vec3( toneMappingWhitePoint ) ) );\n"
    "}\n"
    "vec3 OptimizedCineonToneMapping( vec3 color ) {\n"
    "color *= toneMappingExposure;\n"
    "color = max( vec3( 0.0 ), color - 0.004 );\n"
    "return pow( ( color * ( 6.2 * color + 0.5 ) ) / ( color * ( 6.2 * color + 1.7 ) + 0.06 ), vec3( 2.2 ) );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv2_pars_fragment.glsl
const char* ShaderChunk::uv2_pars_fragment() {
  return
    "#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )\n"
    "varying vec2 vUv2;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv2_pars_vertex.glsl
const char* ShaderChunk::uv2_pars_vertex() {
  return
    "#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )\n"
    "attribute vec2 uv2;\n"
    "varying vec2 vUv2;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv2_vertex.glsl
const char* ShaderChunk::uv2_vertex() {
  return
    "#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )\n"
    "vUv2 = uv2;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv_pars_fragment.glsl
const char* ShaderChunk::uv_pars_fragment() {
  return
    "#if defined( USE_MAP ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( USE_SPECULARMAP ) || defined( USE_ALPHAMAP ) || defined( USE_EMISSIVEMAP ) || defined( USE_ROUGHNESSMAP ) || defined( USE_METALNESSMAP )\n"
    "varying vec2 vUv;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv_pars_vertex.glsl
const char* ShaderChunk::uv_pars_vertex() {
  return
    "#if defined( USE_MAP ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( USE_SPECULARMAP ) || defined( USE_ALPHAMAP ) || defined( USE_EMISSIVEMAP ) || defined( USE_ROUGHNESSMAP ) || defined( USE_METALNESSMAP )\n"
    "varying vec2 vUv;\n"
    "uniform vec4 offsetRepeat;\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/uv_vertex.glsl
const char* ShaderChunk::uv_vertex() {
  return
    "#if defined( USE_MAP ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( USE_SPECULARMAP ) || defined( USE_ALPHAMAP ) || defined( USE_EMISSIVEMAP ) || defined( USE_ROUGHNESSMAP ) || defined( USE_METALNESSMAP )\n"
    "vUv = uv * offsetRepeat.zw + offsetRepeat.xy;\n"
;
}

// Converted from three/renderers/shaders/ShaderChunk/worldpos_vertex.glsl
const char* ShaderChunk::worldpos_vertex() {
  return
    "#if defined( USE_ENVMAP ) || defined( PHONG ) || defined( PHYSICAL ) || defined( LAMBERT ) || defined ( USE_SHADOWMAP )\n"
    "#ifdef USE_SKINNING\n"
    "vec4 worldPosition = modelMatrix * skinned;\n"
    "#else\n"
    "vec4 worldPosition = modelMatrix * vec4( transformed, 1.0 );\n"
    "#endif\n"
    "#endif\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/cube_frag.glsl
const char* ShaderChunk::cube_frag() {
  return
    "uniform samplerCube tCube;\n"
    "uniform float tFlip;\n"
    "uniform float opacity;\n"
    "varying vec3 vWorldPosition;\n"
    "#include <common>\n"
    "void main() {\n"
    "gl_FragColor = textureCube( tCube, vec3( tFlip * vWorldPosition.x, vWorldPosition.yz ) );\n"
    "gl_FragColor.a *= opacity;\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/cube_vert.glsl
const char* ShaderChunk::cube_vert() {
  return
    "varying vec3 vWorldPosition;\n"
    "#include <common>\n"
    "void main() {\n"
    "vWorldPosition = transformDirection( position, modelMatrix );\n"
    "#include <begin_vertex>\n"
    "#include <project_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/depth_frag.glsl
const char* ShaderChunk::depth_frag() {
  return
    "#if DEPTH_PACKING == 3200\n"
    "uniform float opacity;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <uv_pars_fragment>\n"
    "#include <map_pars_fragment>\n"
    "#include <alphamap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec4 diffuseColor = vec4( 1.0 );\n"
    "#if DEPTH_PACKING == 3200\n"
    "diffuseColor.a = opacity;\n"
    "#endif\n"
    "#include <map_fragment>\n"
    "#include <alphamap_fragment>\n"
    "#include <alphatest_fragment>\n"
    "#include <logdepthbuf_fragment>\n"
    "#if DEPTH_PACKING == 3200\n"
    "gl_FragColor = vec4( vec3( gl_FragCoord.z ), opacity );\n"
    "#elif DEPTH_PACKING == 3201\n"
    "gl_FragColor = packDepthToRGBA( gl_FragCoord.z );\n"
    "#endif\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/depth_vert.glsl
const char* ShaderChunk::depth_vert() {
  return
    "#include <common>\n"
    "#include <uv_pars_vertex>\n"
    "#include <displacementmap_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#include <begin_vertex>\n"
    "#include <displacementmap_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/distanceRGBA_frag.glsl
const char* ShaderChunk::distanceRGBA_frag() {
  return
    "uniform vec3 lightPos;\n"
    "varying vec4 vWorldPosition;\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main () {\n"
    "#include <clipping_planes_fragment>\n"
    "gl_FragColor = packDepthToRGBA( length( vWorldPosition.xyz - lightPos.xyz ) / 1000.0 );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/distanceRGBA_vert.glsl
const char* ShaderChunk::distanceRGBA_vert() {
  return
    "varying vec4 vWorldPosition;\n"
    "#include <common>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <skinbase_vertex>\n"
    "#include <begin_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <worldpos_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "vWorldPosition = worldPosition;\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/equirect_frag.glsl
const char* ShaderChunk::equirect_frag() {
  return
    "uniform sampler2D tEquirect;\n"
    "uniform float tFlip;\n"
    "varying vec3 vWorldPosition;\n"
    "#include <common>\n"
    "void main() {\n"
    "vec3 direction = normalize( vWorldPosition );\n"
    "vec2 sampleUV;\n"
    "sampleUV.y = saturate( tFlip * direction.y * -0.5 + 0.5 );\n"
    "sampleUV.x = atan( direction.z, direction.x ) * RECIPROCAL_PI2 + 0.5;\n"
    "gl_FragColor = texture2D( tEquirect, sampleUV );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/equirect_vert.glsl
const char* ShaderChunk::equirect_vert() {
  return
    "varying vec3 vWorldPosition;\n"
    "#include <common>\n"
    "void main() {\n"
    "vWorldPosition = transformDirection( position, modelMatrix );\n"
    "#include <begin_vertex>\n"
    "#include <project_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/linedashed_frag.glsl
const char* ShaderChunk::linedashed_frag() {
  return
    "uniform vec3 diffuse;\n"
    "uniform float opacity;\n"
    "uniform float dashSize;\n"
    "uniform float totalSize;\n"
    "varying float vLineDistance;\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "#include <fog_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "if ( mod( vLineDistance, totalSize ) > dashSize ) {\n"
    "discard;\n"
    "}\n"
    "vec3 outgoingLight = vec3( 0.0 );\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <color_fragment>\n"
    "outgoingLight = diffuseColor.rgb; // simple shader\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/linedashed_vert.glsl
const char* ShaderChunk::linedashed_vert() {
  return
    "uniform float scale;\n"
    "attribute float lineDistance;\n"
    "varying float vLineDistance;\n"
    "#include <common>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <color_vertex>\n"
    "vLineDistance = scale * lineDistance;\n"
    "vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );\n"
    "gl_Position = projectionMatrix * mvPosition;\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshbasic_frag.glsl
const char* ShaderChunk::meshbasic_frag() {
  return
    "uniform vec3 diffuse;\n"
    "uniform float opacity;\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "#include <uv_pars_fragment>\n"
    "#include <uv2_pars_fragment>\n"
    "#include <map_pars_fragment>\n"
    "#include <alphamap_pars_fragment>\n"
    "#include <aomap_pars_fragment>\n"
    "#include <lightmap_pars_fragment>\n"
    "#include <envmap_pars_fragment>\n"
    "#include <fog_pars_fragment>\n"
    "#include <specularmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <map_fragment>\n"
    "#include <color_fragment>\n"
    "#include <alphamap_fragment>\n"
    "#include <alphatest_fragment>\n"
    "#include <specularmap_fragment>\n"
    "ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "#ifdef USE_LIGHTMAP\n"
    "reflectedLight.indirectDiffuse += texture2D( lightMap, vUv2 ).xyz * lightMapIntensity;\n"
    "#else\n"
    "reflectedLight.indirectDiffuse += vec3( 1.0 );\n"
    "#endif\n"
    "#include <aomap_fragment>\n"
    "reflectedLight.indirectDiffuse *= diffuseColor.rgb;\n"
    "vec3 outgoingLight = reflectedLight.indirectDiffuse;\n"
    "#include <normal_flip>\n"
    "#include <envmap_fragment>\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshbasic_vert.glsl
const char* ShaderChunk::meshbasic_vert() {
  return
    "#include <common>\n"
    "#include <uv_pars_vertex>\n"
    "#include <uv2_pars_vertex>\n"
    "#include <envmap_pars_vertex>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <uv2_vertex>\n"
    "#include <color_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#ifdef USE_ENVMAP\n"
    "#include <beginnormal_vertex>\n"
    "#include <morphnormal_vertex>\n"
    "#include <skinnormal_vertex>\n"
    "#include <defaultnormal_vertex>\n"
    "#endif\n"
    "#include <begin_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <worldpos_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "#include <envmap_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshlambert_frag.glsl
const char* ShaderChunk::meshlambert_frag() {
  return
    "uniform vec3 diffuse;\n"
    "uniform vec3 emissive;\n"
    "uniform float opacity;\n"
    "varying vec3 vLightFront;\n"
    "#ifdef DOUBLE_SIDED\n"
    "varying vec3 vLightBack;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <color_pars_fragment>\n"
    "#include <uv_pars_fragment>\n"
    "#include <uv2_pars_fragment>\n"
    "#include <map_pars_fragment>\n"
    "#include <alphamap_pars_fragment>\n"
    "#include <aomap_pars_fragment>\n"
    "#include <lightmap_pars_fragment>\n"
    "#include <emissivemap_pars_fragment>\n"
    "#include <envmap_pars_fragment>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars>\n"
    "#include <fog_pars_fragment>\n"
    "#include <shadowmap_pars_fragment>\n"
    "#include <shadowmask_pars_fragment>\n"
    "#include <specularmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "vec3 totalEmissiveRadiance = emissive;\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <map_fragment>\n"
    "#include <color_fragment>\n"
    "#include <alphamap_fragment>\n"
    "#include <alphatest_fragment>\n"
    "#include <specularmap_fragment>\n"
    "#include <emissivemap_fragment>\n"
    "reflectedLight.indirectDiffuse = getAmbientLightIrradiance( ambientLightColor );\n"
    "#include <lightmap_fragment>\n"
    "reflectedLight.indirectDiffuse *= BRDF_Diffuse_Lambert( diffuseColor.rgb );\n"
    "#ifdef DOUBLE_SIDED\n"
    "reflectedLight.directDiffuse = ( gl_FrontFacing ) ? vLightFront : vLightBack;\n"
    "#else\n"
    "reflectedLight.directDiffuse = vLightFront;\n"
    "#endif\n"
    "reflectedLight.directDiffuse *= BRDF_Diffuse_Lambert( diffuseColor.rgb ) * getShadowMask();\n"
    "#include <aomap_fragment>\n"
    "vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + totalEmissiveRadiance;\n"
    "#include <normal_flip>\n"
    "#include <envmap_fragment>\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshlambert_vert.glsl
const char* ShaderChunk::meshlambert_vert() {
  return
    "#define LAMBERT\n"
    "varying vec3 vLightFront;\n"
    "#ifdef DOUBLE_SIDED\n"
    "varying vec3 vLightBack;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <uv_pars_vertex>\n"
    "#include <uv2_pars_vertex>\n"
    "#include <envmap_pars_vertex>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <shadowmap_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <uv2_vertex>\n"
    "#include <color_vertex>\n"
    "#include <beginnormal_vertex>\n"
    "#include <morphnormal_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#include <skinnormal_vertex>\n"
    "#include <defaultnormal_vertex>\n"
    "#include <begin_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "#include <worldpos_vertex>\n"
    "#include <envmap_vertex>\n"
    "#include <lights_lambert_vertex>\n"
    "#include <shadowmap_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshphong_frag.glsl
const char* ShaderChunk::meshphong_frag() {
  return
    "#define PHONG\n"
    "uniform vec3 diffuse;\n"
    "uniform vec3 emissive;\n"
    "uniform vec3 specular;\n"
    "uniform float shininess;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <color_pars_fragment>\n"
    "#include <uv_pars_fragment>\n"
    "#include <uv2_pars_fragment>\n"
    "#include <map_pars_fragment>\n"
    "#include <alphamap_pars_fragment>\n"
    "#include <aomap_pars_fragment>\n"
    "#include <lightmap_pars_fragment>\n"
    "#include <emissivemap_pars_fragment>\n"
    "#include <envmap_pars_fragment>\n"
    "#include <gradientmap_pars_fragment>\n"
    "#include <fog_pars_fragment>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars>\n"
    "#include <lights_phong_pars_fragment>\n"
    "#include <shadowmap_pars_fragment>\n"
    "#include <bumpmap_pars_fragment>\n"
    "#include <normalmap_pars_fragment>\n"
    "#include <specularmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "vec3 totalEmissiveRadiance = emissive;\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <map_fragment>\n"
    "#include <color_fragment>\n"
    "#include <alphamap_fragment>\n"
    "#include <alphatest_fragment>\n"
    "#include <specularmap_fragment>\n"
    "#include <normal_flip>\n"
    "#include <normal_fragment>\n"
    "#include <emissivemap_fragment>\n"
    "#include <lights_phong_fragment>\n"
    "#include <lights_template>\n"
    "#include <aomap_fragment>\n"
    "vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + reflectedLight.directSpecular + reflectedLight.indirectSpecular + totalEmissiveRadiance;\n"
    "#include <envmap_fragment>\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshphong_vert.glsl
const char* ShaderChunk::meshphong_vert() {
  return
    "#define PHONG\n"
    "varying vec3 vViewPosition;\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <uv_pars_vertex>\n"
    "#include <uv2_pars_vertex>\n"
    "#include <displacementmap_pars_vertex>\n"
    "#include <envmap_pars_vertex>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <shadowmap_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <uv2_vertex>\n"
    "#include <color_vertex>\n"
    "#include <beginnormal_vertex>\n"
    "#include <morphnormal_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#include <skinnormal_vertex>\n"
    "#include <defaultnormal_vertex>\n"
    "#ifndef FLAT_SHADED // Normal computed with derivatives when FLAT_SHADED\n"
    "vNormal = normalize( transformedNormal );\n"
    "#endif\n"
    "#include <begin_vertex>\n"
    "#include <displacementmap_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "vViewPosition = - mvPosition.xyz;\n"
    "#include <worldpos_vertex>\n"
    "#include <envmap_vertex>\n"
    "#include <shadowmap_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshphysical_frag.glsl
const char* ShaderChunk::meshphysical_frag() {
  return
    "#define PHYSICAL\n"
    "uniform vec3 diffuse;\n"
    "uniform vec3 emissive;\n"
    "uniform float roughness;\n"
    "uniform float metalness;\n"
    "uniform float opacity;\n"
    "#ifndef STANDARD\n"
    "uniform float clearCoat;\n"
    "uniform float clearCoatRoughness;\n"
    "#endif\n"
    "varying vec3 vViewPosition;\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <color_pars_fragment>\n"
    "#include <uv_pars_fragment>\n"
    "#include <uv2_pars_fragment>\n"
    "#include <map_pars_fragment>\n"
    "#include <alphamap_pars_fragment>\n"
    "#include <aomap_pars_fragment>\n"
    "#include <lightmap_pars_fragment>\n"
    "#include <emissivemap_pars_fragment>\n"
    "#include <envmap_pars_fragment>\n"
    "#include <fog_pars_fragment>\n"
    "#include <bsdfs>\n"
    "#include <cube_uv_reflection_fragment>\n"
    "#include <lights_pars>\n"
    "#include <lights_physical_pars_fragment>\n"
    "#include <shadowmap_pars_fragment>\n"
    "#include <bumpmap_pars_fragment>\n"
    "#include <normalmap_pars_fragment>\n"
    "#include <roughnessmap_pars_fragment>\n"
    "#include <metalnessmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "vec3 totalEmissiveRadiance = emissive;\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <map_fragment>\n"
    "#include <color_fragment>\n"
    "#include <alphamap_fragment>\n"
    "#include <alphatest_fragment>\n"
    "#include <specularmap_fragment>\n"
    "#include <roughnessmap_fragment>\n"
    "#include <metalnessmap_fragment>\n"
    "#include <normal_flip>\n"
    "#include <normal_fragment>\n"
    "#include <emissivemap_fragment>\n"
    "#include <lights_physical_fragment>\n"
    "#include <lights_template>\n"
    "#include <aomap_fragment>\n"
    "vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + reflectedLight.directSpecular + reflectedLight.indirectSpecular + totalEmissiveRadiance;\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/meshphysical_vert.glsl
const char* ShaderChunk::meshphysical_vert() {
  return
    "#define PHYSICAL\n"
    "varying vec3 vViewPosition;\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <common>\n"
    "#include <uv_pars_vertex>\n"
    "#include <uv2_pars_vertex>\n"
    "#include <displacementmap_pars_vertex>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <shadowmap_pars_vertex>\n"
    "#include <specularmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <uv2_vertex>\n"
    "#include <color_vertex>\n"
    "#include <beginnormal_vertex>\n"
    "#include <morphnormal_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#include <skinnormal_vertex>\n"
    "#include <defaultnormal_vertex>\n"
    "#ifndef FLAT_SHADED // Normal computed with derivatives when FLAT_SHADED\n"
    "vNormal = normalize( transformedNormal );\n"
    "#endif\n"
    "#include <begin_vertex>\n"
    "#include <displacementmap_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "vViewPosition = - mvPosition.xyz;\n"
    "#include <worldpos_vertex>\n"
    "#include <shadowmap_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/normal_frag.glsl
const char* ShaderChunk::normal_frag() {
  return
    "#define NORMAL\n"
    "uniform float opacity;\n"
    "#if defined( FLAT_SHADED ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP )\n"
    "varying vec3 vViewPosition;\n"
    "#endif\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <packing>\n"
    "#include <uv_pars_fragment>\n"
    "#include <bumpmap_pars_fragment>\n"
    "#include <normalmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "void main() {\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <normal_flip>\n"
    "#include <normal_fragment>\n"
    "gl_FragColor = vec4( packNormalToRGB( normal ), opacity );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/normal_vert.glsl
const char* ShaderChunk::normal_vert() {
  return
    "#define NORMAL\n"
    "#if defined( FLAT_SHADED ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP )\n"
    "varying vec3 vViewPosition;\n"
    "#endif\n"
    "#ifndef FLAT_SHADED\n"
    "varying vec3 vNormal;\n"
    "#endif\n"
    "#include <uv_pars_vertex>\n"
    "#include <displacementmap_pars_vertex>\n"
    "#include <morphtarget_pars_vertex>\n"
    "#include <skinning_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "void main() {\n"
    "#include <uv_vertex>\n"
    "#include <beginnormal_vertex>\n"
    "#include <morphnormal_vertex>\n"
    "#include <skinbase_vertex>\n"
    "#include <skinnormal_vertex>\n"
    "#include <defaultnormal_vertex>\n"
    "#ifndef FLAT_SHADED // Normal computed with derivatives when FLAT_SHADED\n"
    "vNormal = normalize( transformedNormal );\n"
    "#endif\n"
    "#include <begin_vertex>\n"
    "#include <displacementmap_vertex>\n"
    "#include <morphtarget_vertex>\n"
    "#include <skinning_vertex>\n"
    "#include <project_vertex>\n"
    "#include <logdepthbuf_vertex>\n"
    "#if defined( FLAT_SHADED ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP )\n"
    "vViewPosition = - mvPosition.xyz;\n"
    "#endif\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/points_frag.glsl
const char* ShaderChunk::points_frag() {
  return
    "uniform vec3 diffuse;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <color_pars_fragment>\n"
    "#include <map_particle_pars_fragment>\n"
    "#include <fog_pars_fragment>\n"
    "#include <shadowmap_pars_fragment>\n"
    "#include <logdepthbuf_pars_fragment>\n"
    "#include <clipping_planes_pars_fragment>\n"
    "void main() {\n"
    "#include <clipping_planes_fragment>\n"
    "vec3 outgoingLight = vec3( 0.0 );\n"
    "vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "#include <logdepthbuf_fragment>\n"
    "#include <map_particle_fragment>\n"
    "#include <color_fragment>\n"
    "#include <alphatest_fragment>\n"
    "outgoingLight = diffuseColor.rgb;\n"
    "gl_FragColor = vec4( outgoingLight, diffuseColor.a );\n"
    "#include <premultiplied_alpha_fragment>\n"
    "#include <tonemapping_fragment>\n"
    "#include <encodings_fragment>\n"
    "#include <fog_fragment>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/points_vert.glsl
const char* ShaderChunk::points_vert() {
  return
    "uniform float size;\n"
    "uniform float scale;\n"
    "#include <common>\n"
    "#include <color_pars_vertex>\n"
    "#include <fog_pars_vertex>\n"
    "#include <shadowmap_pars_vertex>\n"
    "#include <logdepthbuf_pars_vertex>\n"
    "#include <clipping_planes_pars_vertex>\n"
    "void main() {\n"
    "#include <color_vertex>\n"
    "#include <begin_vertex>\n"
    "#include <project_vertex>\n"
    "#ifdef USE_SIZEATTENUATION\n"
    "gl_PointSize = size * ( scale / - mvPosition.z );\n"
    "#else\n"
    "gl_PointSize = size;\n"
    "#endif\n"
    "#include <logdepthbuf_vertex>\n"
    "#include <clipping_planes_vertex>\n"
    "#include <worldpos_vertex>\n"
    "#include <shadowmap_vertex>\n"
    "#include <fog_vertex>\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/shadow_frag.glsl
const char* ShaderChunk::shadow_frag() {
  return
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <packing>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars>\n"
    "#include <shadowmap_pars_fragment>\n"
    "#include <shadowmask_pars_fragment>\n"
    "void main() {\n"
    "gl_FragColor = vec4( 0.0, 0.0, 0.0, opacity * ( 1.0 - getShadowMask() ) );\n"
    "}\n"
;
}

// Converted from three/renderers/shaders/ShaderLib/shadow_vert.glsl
const char* ShaderChunk::shadow_vert() {
  return
    "#include <shadowmap_pars_vertex>\n"
    "void main() {\n"
    "#include <begin_vertex>\n"
    "#include <project_vertex>\n"
    "#include <worldpos_vertex>\n"
    "#include <shadowmap_vertex>\n"
    "}\n"
;
}

} /* namespace three */
