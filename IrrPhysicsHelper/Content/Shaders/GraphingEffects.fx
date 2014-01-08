float4x4 World;
float4x4 ViewProjection;
float3 cameraPos;
bool specular;
bool lighting;

Texture colorTexture;
sampler2D colorTextureSampler = sampler_state { texture = <colorTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};

/////////Colored//////////

struct ColoredVSInput
{
    float4 position : POSITION0;
	float4 Color : COLOR0;
    float3 normal :NORMAL0;
	float2 texCoord : TEXCOORD0;
};

struct VertexColoredVSOutput
{
	float4 Color : COLOR0;
	float4 position : POSITION0;
	float2 texCoord : TEXCOORD0;
};

VertexColoredVSOutput VertexColoredVSFunction(ColoredVSInput input)
{
    VertexColoredVSOutput output;
			
	float3 outPosition = mul(input.position, World);
   	float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	

	if (lighting)
	{
		float3 normal = mul(input.normal, World);
	
		float3 light = normalize(cameraPos - outPosition);
		float diffuse = dot(normal,light);

		if (specular)
		{
			//Specular	
			float3 CameraDir = normalize(cameraPos - outPosition);
			float3 Half = normalize(light + CameraDir);
			float specular = pow(saturate(dot(normal,Half)),100);
			float4 totalSpecular = float4(specular*float3(1,1,1), 1.0);
			output.Color = input.Color*clamp(diffuse+0.4, 0, 1) + totalSpecular;
		}
		else
		{
			output.Color = input.Color*clamp(diffuse+0.4, 0, 1);
		}
	}
	else
	{
		output.Color = input.Color;
	}
	output.texCoord = input.texCoord;

    return output;
}

float4 VertexColoredPSFunction(VertexColoredVSOutput input) : COLOR0
{
		return input.Color*tex2D(colorTextureSampler,input.texCoord);
}

technique GraphingPerVertexColored
{
    pass Pass1
    {
        VertexShader = compile vs_1_0 VertexColoredVSFunction();
        PixelShader = compile ps_2_0 VertexColoredPSFunction();
    }
}



/*Texture colorTexture;
sampler2D colorTextureSampler = sampler_state { texture = <colorTexture> ; magfilter = LINEAR; minfilter = LINEAR; mipfilter=LINEAR;    
	AddressU = Mirror; AddressV = Mirror;};

/////Textured/////

VertexColoredVSOutput VertexTexturedVSFunction(ColoredVSInput input)
{
    VertexColoredVSOutput output;
			
	float3 outPosition = mul(input.position, World);
   	float4 outSVPosition = mul(float4(outPosition, 1.0f), ViewProjection);
	output.position = outSVPosition;	
		
	if (lighting)
	{
		float3 normal = mul(input.normal, World);
	
		//float3 light = normalize(cameraPos - outPosition);
		//float diffuse = dot(normal,light);
		//output.totalDiffuse = float4(clamp(diffuse,ambient,1.0) * diffuseColor * lightCol,1);

		if (specular)
		{
			//Specular	
			float3 CameraDir = normalize(cameraPos - outPosition);
			float3 Half = normalize(light + CameraDir);
			float specular = pow(saturate(dot(normal,Half)),100);
			output.totalSpecular = float4(specular*float3(1,1,1), 1.0);
		}
		else
		{
			output.totalSpecular = float4(0, 0, 0, 0);
		}
    
		output.Color = input.Color;//*clamp(diffuse+0.2, 0, 1);
	}
	else
	{
		output.totalSpecular = float4(0, 0, 0, 0);
		output.Color = input.Color;
	}
    return output;
}

float4 VertexTexturedPSFunction(VertexColoredVSOutput input) : COLOR0
{
		return input.Color + input.totalSpecular;
}

technique GraphingPerVertexTextured
{
    pass Pass1
    {
        VertexShader = compile vs_1_0 VertexTexturedVSFunction();
        PixelShader = compile ps_2_0 VertexTexturedPSFunction();
    }
}*/