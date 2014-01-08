/*	
Copyright (C) 2013  Niraj Rayalla

This file is part of 3-DPhysicsSim.    

3-DPhysicsSim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

3-DPhysicsSim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "GraphingShader.h"

s32 graphingShader;

///HLSL///

const char* hlslVertexShader = "\
float4x4 ViewProjection;\
float4x4 World;\
float3 cameraPos;\
bool hasLighting;\
bool hasSpecular;\
\
struct VertexColoredVSOutput\
{\
	float4 Color : COLOR;\
	float4 position : POSITION;\
	float2 texCoord : TEXCOORD0;\
};\
\
VertexColoredVSOutput VertexColoredVSFunction(float4 positionIn : POSITION, float4 ColorIn : COLOR0, float3 normalIn : NORMAL0, float2 texCoordIn : TEXCOORD0)\
{\
    VertexColoredVSOutput output;\
	\
	float3 outPosition = mul(positionIn, World);\
   	float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);\
	output.position = outSVPosition;\
	\
	if (hasLighting)\
	{\
		float3 normal = mul(normalIn, World);\
		\
		float3 light = normalize(cameraPos - outPosition);\
		float diffuse = dot(normal,light);\
		\
		if (hasSpecular)\
		{\
			float3 CameraDir = normalize(cameraPos - outPosition);\
			float3 Half = normalize(light + CameraDir);\
			float specular = pow(saturate(dot(normal,Half)),100);\
			float4 totalSpecular = float4(specular*float3(1,1,1), 1.0);\
			output.Color = ColorIn*clamp(diffuse+0.4, 0, 1) + totalSpecular;\
		}\
		else\
		{\
			output.Color = ColorIn*clamp(diffuse+0.4, 0, 1);\
		}\
	}\
	else\
	{\
		output.Color = ColorIn;\
	}\
	output.texCoord = texCoordIn;\
	\
    return output;\
}";

const char* hlslPixelShader = "\
bool showGrid;\
sampler2D gridTextureSampler : register(s0);\
\
float4 VertexColoredPSFunction(float4 Color : COLOR, float4 position : POSITION0, float2 texCoord : TEXCOORD0) : COLOR0\
{\
	if (showGrid)\
	{\
		return Color*tex2D(gridTextureSampler,texCoord);\
	}\
	else\
	{\
		return Color;\
	}\
}";

//GLSL

const char* glslVertexShader = "\
float xlat_lib_saturate( float x) {\
  return clamp( x, 0.0, 1.0);\
}\
\
vec2 xlat_lib_saturate( vec2 x) {\
  return clamp( x, 0.0, 1.0);\
}\
\
vec3 xlat_lib_saturate( vec3 x) {\
  return clamp( x, 0.0, 1.0);\
}\
\
vec4 xlat_lib_saturate( vec4 x) {\
  return clamp( x, 0.0, 1.0);\
}\
\
mat2 xlat_lib_saturate(mat2 m) {\
  return mat2( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0));\
}\
\
mat3 xlat_lib_saturate(mat3 m) {\
  return mat3( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0));\
}\
\
mat4 xlat_lib_saturate(mat4 m) {\
  return mat4( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0), clamp(m[3], 0.0, 1.0));\
}\
\
\
mat3 xlat_lib_constructMat3( mat4 m) {\
  return mat3( vec3( m[0]), vec3( m[1]), vec3( m[2]));\
}\
\
\
struct VertexColoredVSOutput {\
    vec4 Color;\
    vec4 position;\
    vec2 texCoord;\
};\
\
\
//\
// Global variable definitions\
//\
\
uniform mat4 ViewProjection;\
uniform mat4 World;\
uniform vec3 cameraPos;\
uniform bool hasLighting;\
uniform bool hasSpecular;\
\
//\
// Function declarations\
//\
\
VertexColoredVSOutput VertexColoredVSFunction( in vec4 positionIn, in vec4 ColorIn, in vec3 normalIn, in vec2 texCoordIn );\
\
//\
// Function definitions\
//\
\
VertexColoredVSOutput VertexColoredVSFunction( in vec4 positionIn, in vec4 ColorIn, in vec3 normalIn, in vec2 texCoordIn ) {\
    vec3 outPosition;\
    vec4 outSVPosition;\
    VertexColoredVSOutput xlat_var_output;\
    vec3 normal;\
    vec3 light;\
    float diffuse;\
    vec3 CameraDir;\
    vec3 Half;\
    float specular;\
    vec4 totalSpecular;\
\
    outPosition = vec3( ( positionIn * World ));\
    outSVPosition = ( vec4( outPosition, 1.00000) * ViewProjection );\
    xlat_var_output.position = outSVPosition;\
    if ( hasLighting ){\
        normal = ( normalIn * xlat_lib_constructMat3( World) );\
        light = normalize( (cameraPos - outPosition) );\
        diffuse = dot( normal, light);\
        if ( hasSpecular ){\
            CameraDir = normalize( (cameraPos - outPosition) );\
            Half = normalize( (light + CameraDir) );\
            specular = pow( xlat_lib_saturate( dot( normal, Half) ), 100.000);\
            totalSpecular = vec4( (specular * vec3( 1.00000, 1.00000, 1.00000)), 1.00000);\
            xlat_var_output.Color = ((ColorIn * clamp( (diffuse + 0.400000), 0.000000, 1.00000)) + totalSpecular);\
        }\
        else{\
            xlat_var_output.Color = (ColorIn * clamp( (diffuse + 0.400000), 0.000000, 1.00000));\
        }\
    }\
    else{\
        xlat_var_output.Color = ColorIn;\
    }\
    xlat_var_output.texCoord = texCoordIn;\
    return xlat_var_output;\
}\
\
\
//\
// Translator's entry point\
//\
void main() {\
    VertexColoredVSOutput xlat_retVal;\
\
    xlat_retVal = VertexColoredVSFunction( vec4(gl_Vertex), vec4(gl_Color), vec3(gl_Normal), vec2(gl_MultiTexCoord0));\
\
    gl_FrontColor = vec4( xlat_retVal.Color);\
    gl_Position = vec4( xlat_retVal.position);\
    gl_TexCoord[0] = vec4( xlat_retVal.texCoord, 0.0, 0.0);\
}";

const char* glslPixelShader = "\
//\
// Global variable definitions\
//\
\
uniform sampler2D gridTextureSampler;\
uniform bool showGrid;\
\
//\
// Function declarations\
//\
\
vec4 VertexColoredPSFunction( in vec4 Color, in vec4 position, in vec2 texCoord );\
\
//\
// Function definitions\
//\
\
vec4 VertexColoredPSFunction( in vec4 Color, in vec4 position, in vec2 texCoord ) {\
\
    if ( showGrid ){\
        return (Color * texture2D( gridTextureSampler, texCoord));\
    }\
    else{\
        return Color;\
    }\
}\
\
\
//\
// Translator's entry point\
//\
void main() {\
    vec4 xlat_retVal;\
\
    xlat_retVal = VertexColoredPSFunction( vec4(gl_Color), vec4(gl_FragCoord), vec2(gl_TexCoord[0]));\
\
    gl_FragData[0] = vec4( xlat_retVal);\
}";


GraphingShaderCallBack* SetupGraphingShader(IrrlichtDevice* device)
{
	IGPUProgrammingServices* gpu = device->getVideoDriver()->getGPUProgrammingServices();

	GraphingShaderCallBack* mc = new GraphingShaderCallBack(device);

	const char* vShader = 0;
	const char* pShader = 0;

	#if defined _WX_IRR_WINDOWS

		graphingShader = gpu->addHighLevelShaderMaterial(hlslVertexShader, "VertexColoredVSFunction", EVST_VS_1_1, hlslPixelShader, "VertexColoredPSFunction", EPST_PS_1_1, mc);

	#elif defined _WX_IRR_LINUX

		graphingShader = gpu->addHighLevelShaderMaterial(glslVertexShader, "main", EVST_VS_1_1, glslPixelShader, "main", EPST_PS_1_1, mc);

	#elif defined _WX_IRR_MACOS

		//

	#endif

	mc->drop();

	return mc;
}

s32 GetGraphingShader()
{
	return graphingShader;
}


void GraphingShaderCallBack::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	video::IVideoDriver* driver = services->getVideoDriver();

	core::matrix4 World = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	services->setVertexShaderConstant("World", World.pointer(), 16);

	core::matrix4 ViewProj;
    ViewProj *= services->getVideoDriver()->getTransform(video::ETS_PROJECTION);
	ViewProj *= services->getVideoDriver()->getTransform(video::ETS_VIEW);
	services->setVertexShaderConstant("ViewProjection", ViewProj.pointer(), 16);

	core::vector3df pos = device->getSceneManager()->getActiveCamera()->getPosition();
	services->setVertexShaderConstant("cameraPos", reinterpret_cast<f32*>(&pos), 3);


	services->setVertexShaderConstant("hasSpecular", reinterpret_cast<f32*>(&hasSpecular), 1);

	services->setVertexShaderConstant("hasLighting", reinterpret_cast<f32*>(&hasLighting), 1);

	services->setPixelShaderConstant("showGrid", reinterpret_cast<f32*>(&showGrid), 1);
}