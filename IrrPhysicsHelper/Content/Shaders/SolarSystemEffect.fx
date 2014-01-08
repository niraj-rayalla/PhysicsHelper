float4x4 World;
float4x4 ViewProjection;
float3 cameraPos;
float3 lightPos;
float3 lightCol;
bool specular;

Texture colorTexture;
sampler2D colorTextureSampler = sampler_state { texture = <colorTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};

Texture bumpTexture;
sampler2D bumpTextureSampler = sampler_state { texture = <bumpTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};

Texture specularTexture;
sampler2D specularTextureSampler = sampler_state { texture = <specularTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};

struct TexturedNormalVSInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal :NORMAL0;
	float3 tangent : TANGENT0;
};

struct TexturedNormalVSOutput
{
	float4 position : POSITION0;
	float2 texCoords : TEXCOORD0;
	float3 outPosition : TEXCOORD1;
	float3x3 toTangentSpace : TEXCOORD2;
};

TexturedNormalVSOutput TexturedNormalVSFunction(TexturedNormalVSInput input)
{
    TexturedNormalVSOutput output;
			
	float3 outPosition = mul(input.position, World);
	output.outPosition = outPosition;
   	 float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
	
	float3 tangent = mul(input.tangent,World);
	float3 normal = mul(input.normal,World);
	float3 binormal = cross(normal.xyz,tangent.xyz);

	output.toTangentSpace = float3x3(tangent, binormal, normal);

    output.texCoords=input.texCoord;
    
    return output;
}

float4 TexturedNormalPSFunction(TexturedNormalVSOutput input) : COLOR0
{
    float4 coltexture = tex2D(colorTextureSampler,input.texCoords);
    
    float3 normal = tex2D(bumpTextureSampler,input.texCoords);
	normal = normal * 2.0 - 1.2;
	normal = mul(normal, input.toTangentSpace);
	normal = normalize(normal);

 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = dot(normal,light);
	float3 totaldiffuse = clamp(diffuse,0.1,1.0) * coltexture * lightCol;

	if (specular)
	{
		//Specular
		float3 specTexture = tex2D(specularTextureSampler,input.texCoords);

		float3 CameraDir = normalize(cameraPos - input.outPosition);
		float3 Half = normalize(light + CameraDir);
		float specular = pow(saturate(dot(normal,Half)),25);
		float4 totalSpecular = float4(lightCol * specular * specTexture, 1.0);
	
		return float4(totaldiffuse,1) + totalSpecular;
	}
	else
	{
		return float4(totaldiffuse,1);
	}
}

technique TexturedNormal
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 TexturedNormalVSFunction();
        PixelShader = compile ps_2_0 TexturedNormalPSFunction();
    }
}



//////////////Earth/////////////


Texture nightLightsTexture;
sampler2D nightLightsSampler = sampler_state { texture = <nightLightsTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};


TexturedNormalVSOutput EarthVSFunction(TexturedNormalVSInput input)
{
    TexturedNormalVSOutput output;
			
	float3 outPosition = mul(input.position, World);
	output.outPosition = outPosition;
   	 float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
	
	float3 tangent = mul(input.tangent,World);
	float3 normal = mul(input.normal,World);
	float3 binormal = cross(normal.xyz,tangent.xyz);

	output.toTangentSpace = float3x3(tangent, binormal, normal);

    output.texCoords=input.texCoord;
    
    return output;
}

float4 EarthPSFunction(TexturedNormalVSOutput input) : COLOR0
{
    float4 coltexture = tex2D(colorTextureSampler,input.texCoords);
    
    float3 normal = tex2D(bumpTextureSampler,input.texCoords);
	normal = normal * 2.0 - 1.2;
	normal = mul(normal, input.toTangentSpace);
	normal = normalize(normal);

 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = dot(normal,light);
	float3 totaldiffuse = clamp(diffuse,0.1,1.0) * coltexture * lightCol;

	float4 nightLightsTex = tex2D(nightLightsSampler,input.texCoords);
	nightLightsTex = saturate(1-diffuse) * nightLightsTex;

	if (specular)
	{
		//Specular
		float3 specTexture = tex2D(specularTextureSampler,input.texCoords);

		float3 CameraDir = normalize(cameraPos - input.outPosition);
		float3 Half = normalize(light + CameraDir);
		float specular = pow(saturate(dot(normal,Half)),25);
		float4 totalSpecular = float4(lightCol * specular * specTexture, 1.0);
	
		return float4(totaldiffuse,1) + totalSpecular + nightLightsTex;
	}
	else
	{
		return float4(totaldiffuse,1) + nightLightsTex;
	}
}

technique Earth
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 EarthVSFunction();
        PixelShader = compile ps_2_0 EarthPSFunction();
    }
}