cbuffer cbPlayerInfo : register(b0)
{
	matrix		gmtxPlayerWorld : packoffset(c0);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
	float3		gvCameraPosition : packoffset(c8);
};

cbuffer cbGameObjectInfo : register(b2)
{
	matrix		gmtxGameObject;
	uint		gnMaterial;
		int		frame_time;
};
struct GAMEOBJECTINFO
{
	matrix		m_mtxGameObject;

};
#include "Light.hlsl"

struct VS_DIFFUSED_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_DIFFUSED_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_DIFFUSED_OUTPUT VSDiffused(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.color = input.color;

	return(output);
}

float4 PSDiffused(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
VS_DIFFUSED_OUTPUT VSPlayer(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxPlayerWorld), gmtxView), gmtxProjection);
	output.color = input.color;

	return(output);
}

float4 PSPlayer(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtTexture : register(t0);
Texture2D gtxtTextures : register(t5);
Texture2D gtxtTexture_Particle : register(t9);
Texture2D gtxtTexture_Smoke: register(t10);

SamplerState gSamplerState : register(s0);
SamplerState gClampSamplerState : register(s1); //지형을 위한 샘플러 1번

struct VS_TEXTURED_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_TEXTURED_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_TEXTURED_OUTPUT VSTextured(VS_TEXTURED_INPUT input)
{
	VS_TEXTURED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.uv = input.uv;

	return(output);
}



float4 PSTextured(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);

	return(cColor);
}

#define _WITH_VERTEX_LIGHTING

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_LIGHTING_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct VS_LIGHTING_OUTPUT
{
	float4 position : SV_POSITION;
	float3 positionW : POSITION;
	float3 normalW : NORMAL;
#ifdef _WITH_VERTEX_LIGHTING
	float4 color : COLOR;
#endif
};

VS_LIGHTING_OUTPUT VSLighting(VS_LIGHTING_INPUT input)
{
	VS_LIGHTING_OUTPUT output;

	output.normalW = mul(input.normal, (float3x3)gmtxGameObject);
	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxGameObject);
	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
#ifdef _WITH_VERTEX_LIGHTING
	output.normalW = normalize(output.normalW);
	output.color = Lighting(output.positionW, output.normalW);
#endif
	return(output);
}

float4 PSLighting(VS_LIGHTING_OUTPUT input) : SV_TARGET
{
#ifdef _WITH_VERTEX_LIGHTING
	float4 cIllumination = input.color;
#else
	input.normalW = normalize(input.normalW);
	float4 cIllumination = Lighting(input.positionW, input.normalW);
#endif
	return(cIllumination);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_TEXTURED_LIGHTING_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct VS_TEXTURED_LIGHTING_OUTPUT
{
	float4 position : SV_POSITION;
	float3 positionW : POSITION;
	float3 normalW : NORMAL;
	//	nointerpolation float3dormalW : NORMAL;
	float2 uv : TEXCOORD;
#ifdef _WITH_VERTEX_LIGHTING
	float4 color : COLOR;
#endif
};

VS_TEXTURED_LIGHTING_OUTPUT VSTexturedLighting(VS_TEXTURED_LIGHTING_INPUT input)
{
	VS_TEXTURED_LIGHTING_OUTPUT output;

	output.normalW = mul(input.normal, (float3x3)gmtxGameObject);
	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxGameObject);
	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
	output.uv = input.uv;
#ifdef _WITH_VERTEX_LIGHTING
	output.normalW = normalize(output.normalW);
	output.color = Lighting(output.positionW, output.normalW);
#endif
	return(output);
}

float4 PSTexturedLighting(VS_TEXTURED_LIGHTING_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);
#ifdef _WITH_VERTEX_LIGHTING
	float4 cIllumination = input.color;
#else
	input.normalW = normalize(input.normalW);
	float4 cIllumination = Lighting(input.positionW, input.normalW);
#endif
	return(lerp(cColor, cIllumination, 0.5f));
}
/////////////////////////////////////////////////////////////////////////////////
// 지형
//지형을 그리기 위해선 base texture, detail texture 2개를 사용할거야
Texture2D gtxtTerrainBaseTexture : register(t2);
Texture2D gtxtTerrainDetailTexture : register(t3);



/////////////////////////////////////////////////////////////////////////////////

//여기
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//struct VS_TEXTURED_LIGHTING_INPUT
//{
//	float3 position : POSITION;
//	float3 normal : NORMAL;
//	float2 uv : TEXCOORD;
//};
//
//struct VS_TEXTURED_LIGHTING_OUTPUT
//{
//	float4 position : SV_POSITION;
//	float3 positionW : POSITION;
//	float3 normalW : NORMAL;
//	//	nointerpolation float3 normalW : NORMAL;
//	float2 uv : TEXCOORD;
//#ifdef _WITH_VERTEX_LIGHTING
//	float4 color : COLOR;
//#endif
//};
//
//VS_TEXTURED_LIGHTING_OUTPUT VSTexturedLighting(VS_TEXTURED_LIGHTING_INPUT input)
//{
//	VS_TEXTURED_LIGHTING_OUTPUT output;
//
//	output.normalW = mul(input.normal, (float3x3)gmtxGameObject);
//	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxGameObject);
//	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
//	output.uv = input.uv;
//#ifdef _WITH_VERTEX_LIGHTING
//	output.normalW = normalize(output.normalW);
//	output.color = Lighting(output.positionW, output.normalW);
//#endif
//	return(output);
//}
//
//float4 PSTexturedLighting(VS_TEXTURED_LIGHTING_OUTPUT input) : SV_TARGET
//{
//	float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);
//#ifdef _WITH_VERTEX_LIGHTING
//	float4 cIllumination = input.color;
//#else
//	input.normalW = normalize(input.normalW);
//	float4 cIllumination = Lighting(input.positionW, input.normalW);
//#endif
//	return(lerp(cColor, cIllumination, 0.5f));
//}



//struct VS_TERRAIN_INPUT
//{
//	float3 position : POSITION;
//	float3 normal : NORMAL;
//	float2 uv0 : TEXCOORD0;
//	float2 uv1 : TEXCOORD1;
//};
//
//struct VS_TERRAIN_OUTPUT
//{
//	float4 position : SV_POSITION;
//	float3 positionW : POSITION;
//	float3 normalW : NORMAL;
//	//	nointerpolation float3 normalW : NORMAL;
//	float2 uv0 : TEXCOORD;
//	float2 uv1 : TEXCOORD1;
//#ifdef _WITH_VERTEX_LIGHTING
//	float4 color : COLOR;
//#endif
//};
struct VS_TERRAIN_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0; //베이스 텍스쳐 샘플링하기위한 uv좌표
	float2 uv1 : TEXCOORD1; //디테을 텍스쳐 샘플링하기위한 uv좌표
};

struct VS_TERRAIN_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0;
	float2 uv1 : TEXCOORD1;
};

//VS_TERRAIN_OUTPUT VSTerrain(VS_TERRAIN_INPUT input)
//{
//	VS_TERRAIN_OUTPUT output;
//
//	output.normalW = mul(input.normal, (float3x3)gmtxGameObject);
//	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxGameObject);
//	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
//	output.uv0 = input.uv0;
//	output.uv1 = input.uv1;
//#ifdef _WITH_VERTEX_LIGHTING
//	output.normalW = normalize(output.normalW);
//	output.color = Lighting(output.positionW, output.normalW);
//#endif
//	return(output);
//}


VS_TERRAIN_OUTPUT VSTerrain(VS_TERRAIN_INPUT input)
{
	VS_TERRAIN_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	output.color = input.color;
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;

	return(output);
}

//float4 PSTerrain(VS_TERRAIN_OUTPUT input) : SV_TARGET
//{
//	//float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);
//	float4 cBaseTexColor = gtxtTerrainBaseTexture.Sample(gSamplerState, input.uv0);
//	float4 cDetailTexColor = gtxtTerrainDetailTexture.Sample(gSamplerState, input.uv1);
//	float4 cColor = input.color * saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f)); // 베이스텍스쳐랑 디테일텍스쳐 섞어서 사용해버리기
//	//return(cColor);
//#ifdef _WITH_VERTEX_LIGHTING
//	float4 cIllumination = input.color;
//#else
//	input.normalW = normalize(input.normalW);
//	float4 cIllumination = Lighting(input.positionW, input.normalW);
//#endif
//	return(lerp(cColor, cIllumination, 0.5f));
//
//}

float4 PSTerrain(VS_TERRAIN_OUTPUT input) : SV_TARGET
{
	float4 cBaseTexColor = gtxtTerrainBaseTexture.Sample(gSamplerState, input.uv0);
	float4 cDetailTexColor = gtxtTerrainDetailTexture.Sample(gSamplerState, input.uv1);
	float4 cColor = input.color * saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f)); // 베이스텍스쳐랑 디테일텍스쳐 섞어서 사용해버리기

	return(cColor);
}

////////////////////////////////////////////////////////////
//스카이박스
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtSkyBox : register(t1); //스카이박스를 위한 쉐이더 , 레지스터 8번에 텍스쳐가 하나 연결되 이 텍스쳐는 그냥 2d텍스쳐가 아니라 텍스쳐 큐브형태로 연결을 하는거야

float4 PSSkyBox(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtSkyBox.Sample(gClampSamplerState, input.uv);

	return(cColor);
}

/////////////////////////////////////////////////////////
// 인스턴싱
StructuredBuffer<GAMEOBJECTINFO> gGameObjectInfos : register(t4); //gGameObjectInfos 변수는 배열이야 이런뜻임, gGameObjectInfos 를 배열처럼써도됨, 근데 사이즈가없는데? -> 버퍼만들고 최대사이즈 정해놓으면 max사이즈까지면 접근하ㅕㄴ됨,

																  ///////////////////////////////////////////////////////////////////
																  //인스턴싱을 위한 VSTexturedInstancing
VS_TEXTURED_OUTPUT VSTexturedInstancing(VS_TEXTURED_INPUT input, uint nInstanceID : SV_InstanceID)
{
	//esc 누르면 오류뜸
	VS_TEXTURED_OUTPUT output;
#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gGameObjectInfos[nInstanceID].m_mtxGameObject), gmtxView), gmtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gGameObjectInfos[nInstanceID].m_mtxGameObject), gmtxView), gmtxProjection);
#endif
	output.uv = input.uv;

	return(output);
}

float4 PSTexturedInstancing(VS_TEXTURED_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET //픽셀쉐이더 
{


	float4 cColor;
//쉐이더에선 변수 못쓰니까 이렇게 


cColor = gtxtTextures.Sample(gSamplerState, input.uv);


if (cColor.a < 0.1) discard;
return(cColor);
}


///////////////////////////////////////////////////////////////////////
float4 PSParticle(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
		
	float2 Tex = input.uv;
	Tex.x = Tex.x / 8.0f + (1 / 8.0f)*frame_time;


	float4 cColor = gtxtTexture_Particle.Sample(gSamplerState, Tex);
	if (cColor.a < 0.1) discard;
//	if (frame_time < 0.1) discard;

	return(cColor);
}

///////////////////////////////////////////////////////////////////////
float4 PSSmoke(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float2 Tex = input.uv;
	Tex.x = Tex.x / 4.0f + (1 / 4.0f)*(frame_time%4);
	Tex.y = Tex.y / 4.0f + (1 / 4.0f)*(frame_time/4);


	//Tex.x = Tex.x / 16.0f + (1 / 16.0f)*frame_time;
float4 cColor = gtxtTexture_Smoke.Sample(gSamplerState, Tex);

if (cColor.a < 0.1) discard;

return(cColor);
}