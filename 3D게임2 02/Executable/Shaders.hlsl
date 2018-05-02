
struct CB_PLAYER_INFO
{
	matrix		mtxWorld;
}; 

struct CB_GAMEOBJECT_INFO
{
	matrix		mtxWorld;
};

struct CB_CAMERA_INFO
{
	matrix		mtxView;
	matrix		mtxProjection;
};

struct GAMEOBJECTINFO
{
	matrix		m_mtxGameObject;

};

ConstantBuffer<CB_PLAYER_INFO> gcbPlayerObjectInfo : register(b0);
ConstantBuffer<CB_CAMERA_INFO> gcbCameraInfo : register(b1);
ConstantBuffer<CB_GAMEOBJECT_INFO> gcbGameObjectInfo : register(b2);
StructuredBuffer<GAMEOBJECTINFO> gGameObjectInfos : register(t0); //gGameObjectInfos 변수는 배열이야 이런뜻임, gGameObjectInfos 를 배열처럼써도됨, 근데 사이즈가없는데? -> 버퍼만들고 최대사이즈 정해놓으면 max사이즈까지면 접근하ㅕㄴ됨,

cbuffer cbPlayerInfo : register(b0)
{
	matrix		gmtxPlayerWorld : packoffset(c0);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
};

cbuffer cbGameObjectInfo : register(b2)
{
	matrix		gmtxWorld : packoffset(c0);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
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

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif
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

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbPlayerObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxPlayerWorld), gmtxView), gmtxProjection);
#endif
	output.color = input.color;

	return(output);
}

float4 PSPlayer(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtTextures[6] : register(t1); //육면체 면마다 배열이 다르니까 텍스쳐를 배열로 만듬 , 이렇게하면 t1부터 6개까지 (SRV 6개를씀), 

//샘플러 2개를쓸꺼야
SamplerState gWrapSamplerState : register(s0);  //육면체를 위한 샘플러 0번
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

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif
	output.uv = input.uv;

	return(output);
}
///////////////////////////////////////////////////////////////////
//인스턴싱을 위한 VSTexturedInstancing
VS_TEXTURED_OUTPUT VSTexturedInstancing(VS_TEXTURED_INPUT input, uint nInstanceID : SV_InstanceID)
{
	//esc 누르면 오류뜸
	VS_TEXTURED_OUTPUT output;
#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gGameObjectInfos[nInstanceID].m_mtxGameObject)), gmtxView), gmtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gGameObjectInfos[nInstanceID].m_mtxGameObject), gmtxView), gmtxProjection);
#endif
	output.uv = input.uv;

	return(output);
}
float4 PSTextured(VS_TEXTURED_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET //픽셀쉐이더 
{
	

	float4 cColor;
	//쉐이더에선 변수 못쓰니까 이렇게 

	/*if (nPrimitiveID < 2)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 4)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

	else if (nPrimitiveID < 6)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

	else if (nPrimitiveID < 8)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

	else if (nPrimitiveID < 10)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

	else
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);*/

	if (nPrimitiveID < 2)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 4)
		cColor = gtxtTextures[1].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 6)
		cColor = gtxtTextures[2].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 8)
		cColor = gtxtTextures[3].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 10)
		cColor = gtxtTextures[4].Sample(gWrapSamplerState, input.uv);
	else
		cColor = gtxtTextures[5].Sample(gWrapSamplerState, input.uv);

	//float4 cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID/2)].Sample(gWrapSamplerState, input.uv); //쉐이더에서 변수를 쓰고싶으면NonUniformResourceIndex를 써야하나봐)

	return(cColor);
}
float4 PSTexturedInstancing(VS_TEXTURED_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET //픽셀쉐이더 
{


	float4 cColor;
//쉐이더에선 변수 못쓰니까 이렇게 

if (nPrimitiveID < 2)
	cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);
else if (nPrimitiveID < 4)
	cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

else if (nPrimitiveID < 6)
	cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

else if (nPrimitiveID < 8)
	cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

else if (nPrimitiveID < 10)
	cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

else
cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);

/*if (nPrimitiveID < 2)
cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);
else if (nPrimitiveID < 4)
cColor = gtxtTextures[1].Sample(gWrapSamplerState, input.uv);
else if (nPrimitiveID < 6)
cColor = gtxtTextures[2].Sample(gWrapSamplerState, input.uv);
else if (nPrimitiveID < 8)
cColor = gtxtTextures[3].Sample(gWrapSamplerState, input.uv);
else if (nPrimitiveID < 10)
cColor = gtxtTextures[4].Sample(gWrapSamplerState, input.uv);
else
cColor = gtxtTextures[5].Sample(gWrapSamplerState, input.uv);*/

//float4 cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID/2)].Sample(gWrapSamplerState, input.uv); //쉐이더에서 변수를 쓰고싶으면NonUniformResourceIndex를 써야하나봐)
//discard;

if (cColor.a < 0.1) discard;
return(cColor);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//지형을 그리기 위해선 base texture, detail texture 2개를 사용할거야
Texture2D gtxtTerrainBaseTexture : register(t7);
Texture2D gtxtTerrainDetailTexture : register(t8);

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

VS_TERRAIN_OUTPUT VSTerrain(VS_TERRAIN_INPUT input)
{
	VS_TERRAIN_OUTPUT output;

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif
	output.color = input.color;
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;

	return(output);
}

float4 PSTerrain(VS_TERRAIN_OUTPUT input) : SV_TARGET
{
	float4 cBaseTexColor = gtxtTerrainBaseTexture.Sample(gWrapSamplerState, input.uv0);
	float4 cDetailTexColor = gtxtTerrainDetailTexture.Sample(gWrapSamplerState, input.uv1);
	float4 cColor = input.color * saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f)); // 베이스텍스쳐랑 디테일텍스쳐 섞어서 사용해버리기

	return(cColor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtSkyBox : register(t9); //스카이박스를 위한 쉐이더 , 레지스터 8번에 텍스쳐가 하나 연결되 이 텍스쳐는 그냥 2d텍스쳐가 아니라 텍스쳐 큐브형태로 연결을 하는거야

float4 PSSkyBox(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtSkyBox.Sample(gClampSamplerState, input.uv);

	return(cColor);
}

