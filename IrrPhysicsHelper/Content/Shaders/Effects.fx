float4x4 World;
float4x4 ViewProjection;
float3 cameraPos;
float3 lightPos;
float3 lightCol;
bool specular;

float3 diffuseColor;
float ambient;

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
	normal = normal * 2.0 - 1.0;
	normal = mul(normal, input.toTangentSpace);
	normal = normalize(normal);

 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = dot(normal,light);
	float3 totaldiffuse = clamp(diffuse,ambient,1.0) * coltexture * lightCol;

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
	normal = normal * 2.0 - 1.0;
	normal = mul(normal, input.toTangentSpace);
	normal = normalize(normal);

 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = clamp(dot(normal,light),0.001,1.0);
	float3 totaldiffuse = diffuse * coltexture * lightCol;

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


/////////Colored//////////

struct ColoredVSInput
{
    float4 position : POSITION0;
    float3 normal :NORMAL0;
};

struct ColoredVSOutput
{
	float4 position : POSITION0;
	float3 normal :TEXCOORD0;
	float3 outPosition : TEXCOORD1;
};

ColoredVSOutput ColoredVSFunction(ColoredVSInput input)
{
    ColoredVSOutput output;
			
	float3 outPosition = mul(input.position, World);
	output.outPosition = outPosition;
   	float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
		
	output.normal = mul(input.normal, World);
    
    return output;
}

float4 ColoredPSFunction(ColoredVSOutput input) : COLOR0
{
    float3 normal = normalize(input.normal);
    
 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = dot(normal,light);
	float3 totaldiffuse = clamp(diffuse+ambient,0,1.0) * diffuseColor;

	if (specular)
	{
		//Specular	
		float3 CameraDir = normalize(cameraPos - input.outPosition);
		float3 Half = normalize(light + CameraDir);
		float specular = pow(saturate(dot(normal,Half)),25);
		float4 totalSpecular = float4(lightCol * specular, 1.0);
	
		return float4(totaldiffuse,1) + totalSpecular;
	}
	else
	{
		return float4(totaldiffuse,1);
	}
}

technique PerPixelColored
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 ColoredVSFunction();
        PixelShader = compile ps_2_0 ColoredPSFunction();
    }
}

struct VertexColoredVSOutput
{
	float4 position : POSITION0;
	float4 totalDiffuse : TEXCOORD0;
	float4 totalSpecular : TEXCOORD1;
};

VertexColoredVSOutput VertexColoredVSFunction(ColoredVSInput input)
{
    VertexColoredVSOutput output;
			
	float3 outPosition = mul(input.position, World);
   	float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
		
	float3 normal = mul(input.normal, World);
	
	float3 light = normalize(lightPos - outPosition);
	float diffuse = dot(normal,light);
	output.totalDiffuse = float4(clamp(diffuse,ambient,1.0) * diffuseColor * lightCol,1);

	if (specular)
	{
		//Specular	
		float3 CameraDir = normalize(cameraPos - outPosition);
		float3 Half = normalize(light + CameraDir);
		float specular = pow(saturate(dot(normal,Half)),25);
		output.totalSpecular = float4(lightCol * specular, 1.0);
	}
	else
	{
		output.totalSpecular = float4(0, 0, 0, 0);
	}
    
    return output;
}

float4 VertexColoredPSFunction(VertexColoredVSOutput input) : COLOR0
{    
	if (specular)
	{
		return input.totalDiffuse + input.totalSpecular;
    }
	else
	{
		return input.totalDiffuse;
	}
}

technique PerVertexColored
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexColoredVSFunction();
        PixelShader = compile ps_2_0 VertexColoredPSFunction();
    }
}


/////////Textured/////////

struct TexturedNoLightVSInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
};

struct TexturedNoLightVSOutput
{
	float4 position : POSITION0;
	float2 texCoords : TEXCOORD0;
};

TexturedNoLightVSOutput TexturedNoLightVSFunction(TexturedNoLightVSInput input)
{
    TexturedNoLightVSOutput output;
			
	float3 outPosition = mul(input.position, World);
   	 float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
		
    output.texCoords=input.texCoord;
    
    return output;
}

float4 TexturedNoLightPSFunction(TexturedNoLightVSOutput input) : COLOR0
{
    float4 coltexture = tex2D(colorTextureSampler,input.texCoords);
 		
    return coltexture;
}

technique TexturedNoLight
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 TexturedNoLightVSFunction();
        PixelShader = compile ps_2_0 TexturedNoLightPSFunction();
    }
}

struct TexturedVSInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal :NORMAL0;
};

struct TexturedVSOutput
{
	float4 position : POSITION0;
	float2 texCoords : TEXCOORD0;
	float3 normal :TEXCOORD1;
	float3 outPosition : TEXCOORD2;
};

TexturedVSOutput TexturedVSFunction(TexturedVSInput input)
{
    TexturedVSOutput output;
			
	float3 outPosition = mul(input.position, World);
	output.outPosition = outPosition;
   	 float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
		
	output.normal = mul(input.normal, World);
    output.texCoords=input.texCoord;
    
    return output;
}

float4 TexturedPSFunction(TexturedVSOutput input) : COLOR0
{
    float4 coltexture = tex2D(colorTextureSampler,input.texCoords);
    
    float3 normal =normalize(input.normal);
    
 	float diffuse = 0;
 	
	float3 light = normalize(lightPos - input.outPosition);
	diffuse = dot(normal,light);
	float3 totaldiffuse = clamp(diffuse,ambient,1.0) * coltexture * lightCol;
	
    return float4(totaldiffuse,1);
}

technique PerPixelTextured
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 TexturedVSFunction();
        PixelShader = compile ps_2_0 TexturedPSFunction();
    }
}

struct VertexTexturedVSOutput
{
	float4 position : POSITION0;
	float2 texCoords : TEXCOORD0;
	float diffuse : TEXCOORD1;
};

VertexTexturedVSOutput VertexTexturedVSFunction(TexturedVSInput input)
{
    VertexTexturedVSOutput output;
			
	float3 worldPosition = mul(input.position, World);
   	float4 outSVPosition = mul(float4(worldPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;
		
	float3 normal = mul(input.normal, World);
	float3 light = normalize(lightPos - worldPosition);
	output.diffuse = dot(normal,light);

    output.texCoords=input.texCoord;
    
    return output;
}

float4 VertexTexturedPSFunction(VertexTexturedVSOutput input) : COLOR0
{
    float4 coltexture = tex2D(colorTextureSampler,input.texCoords);
      
	float3 totaldiffuse = clamp(input.diffuse,ambient,1.0) * coltexture * lightCol;
	
    return float4(totaldiffuse,1);
}

technique PerVertexTextured
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexTexturedVSFunction();
        PixelShader = compile ps_2_0 VertexTexturedPSFunction();
    }
}

