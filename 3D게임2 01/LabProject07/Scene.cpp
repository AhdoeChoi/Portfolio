//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
	m_bIsPlayerInTheMirror = false;
	m_bIsMorning = true;
}

CScene::~CScene()
{
}

void CScene::BuildLightsAndMaterials()
{
	m_pLights = new LIGHTS;
	::ZeroMemory(m_pLights, sizeof(LIGHTS));

	m_pLights->m_xmf4GlobalAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

	m_pLights->m_pLights[0].m_bEnable = true;
	m_pLights->m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[0].m_fRange = 100.0f;
	m_pLights->m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Position = XMFLOAT3(0, 0, 0);
	m_pLights->m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);

	m_pLights->m_pLights[1].m_bEnable = false; //손전등
	m_pLights->m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[1].m_fRange = 50.0f;
	m_pLights->m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 1.1f, 1.1f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 1.4f, 1.4f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[1].m_xmf3Position = XMFLOAT3(0, 0, 0);
	m_pLights->m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[1].m_fFalloff = 8.0f;
	m_pLights->m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights->m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));

	m_pLights->m_pLights[2].m_bEnable = false;
	m_pLights->m_pLights[2].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.01f, 0.01f, 0.01f, 0.01f); //태양
	m_pLights->m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.02f, 0000000000000000000.2f, 0.02f, 1.0f);
	m_pLights->m_pLights[2].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);

	

	///////////////////////// 

	//집에있는 조명들
	m_pLights->m_pLights[3].m_bEnable = false;
	m_pLights->m_pLights[3].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[3].m_fRange = 400;
	m_pLights->m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2, 0.0f);
	m_pLights->m_pLights[3].m_xmf3Position = XMFLOAT3(1070, 260, 1805);
	m_pLights->m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[3].m_fFalloff = 8.0f;
	m_pLights->m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(60.0f));

	m_pLights->m_pLights[4].m_bEnable = true; //공전하는 빛
	m_pLights->m_pLights[4].m_nType = DIRECTIONAL_LIGHT;
	//m_pLights->m_pLights[4].m_fRange = 3040.0f;

	m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.2f, 0.6f, 0.6f, 0.01f); //태양
	m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.65f, 0.55f, 0.85f, 1.0f);
	m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.55f, 0.75f, 0.85f, 0.0f);

	//m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.01f, 0.01f, 0.01f, 0.01f); //태양
	//m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.02f, 0000000000000000000.2f, 0.02f, 1.0f);
	//m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);
	/*m_pLights->m_pLights[4].m_xmf3Position = XMFLOAT3(1050, 2000, 1740);
	m_pLights->m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[4].m_fFalloff = 8.0f;
	m_pLights->m_pLights[4].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[4].m_fTheta = (float)cos(XMConvertToRadians(60.0f));*/

	m_pLights->m_pLights[5].m_bEnable = false;
	m_pLights->m_pLights[5].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[5].m_fRange = 60.0f;
	m_pLights->m_pLights[5].m_xmf4Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pLights->m_pLights[5].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pLights->m_pLights[5].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights->m_pLights[5].m_xmf3Position = XMFLOAT3(1020, 260, 1855);
	m_pLights->m_pLights[5].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights->m_pLights[5].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.005f);
	m_pLights->m_pLights[5].m_fFalloff = 8.0f;
	m_pLights->m_pLights[5].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[5].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[6].m_bEnable = false;
	m_pLights->m_pLights[6].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[6].m_fRange = 60.0f;
	m_pLights->m_pLights[6].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[6].m_xmf4Diffuse = XMFLOAT4(0.2, 0.1f, 0.0f, 1.0f);
	m_pLights->m_pLights[6].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.3f, 0.0f);
	m_pLights->m_pLights[6].m_xmf3Position = XMFLOAT3(1070, 260, 1980);
	m_pLights->m_pLights[6].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[6].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[6].m_fFalloff = 8.0f;
	m_pLights->m_pLights[6].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[6].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[7].m_bEnable = false;
	m_pLights->m_pLights[7].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[7].m_fRange = 60.0f;
	m_pLights->m_pLights[7].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[7].m_xmf4Diffuse = XMFLOAT4(0.2, 0.2f, 0.0f, 1.0f);
	m_pLights->m_pLights[7].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.2f, 0.0f);
	m_pLights->m_pLights[7].m_xmf3Position = XMFLOAT3(1070, 260, 1900);
	m_pLights->m_pLights[7].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights->m_pLights[7].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[7].m_fFalloff = 8.0f;
	m_pLights->m_pLights[7].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[7].m_fTheta = (float)cos(XMConvertToRadians(30.0f));


	//여기서부터 안됨
	m_pLights->m_pLights[8].m_bEnable = false;
	m_pLights->m_pLights[8].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[8].m_fRange = 60.0f;
	m_pLights->m_pLights[8].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[8].m_xmf4Diffuse = XMFLOAT4(0.2, 0.2f, 0.0f, 1.0f);
	m_pLights->m_pLights[8].m_xmf4Specular = XMFLOAT4(0.1f, 0.4f, 0.2f, 0.0f);
	m_pLights->m_pLights[8].m_xmf3Position = XMFLOAT3(1070, 260, 1850);
	m_pLights->m_pLights[8].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[8].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[8].m_fFalloff = 8.0f;
	m_pLights->m_pLights[8].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[8].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[9].m_bEnable = false;
	m_pLights->m_pLights[9].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[9].m_fRange = 60.0f;
	m_pLights->m_pLights[9].m_xmf4Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[9].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.2f, 0.5f, 1.0f);
	m_pLights->m_pLights[9].m_xmf4Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	m_pLights->m_pLights[9].m_xmf3Position = XMFLOAT3(1020, 260, 1755);
	m_pLights->m_pLights[9].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[9].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.005f);
	m_pLights->m_pLights[9].m_fFalloff = 8.0f;
	m_pLights->m_pLights[9].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[9].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[10].m_bEnable = false;
	m_pLights->m_pLights[10].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[10].m_fRange = 60.0f;
	m_pLights->m_pLights[10].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.9f, 1.0f);
	m_pLights->m_pLights[10].m_xmf4Diffuse = XMFLOAT4(0.1f, 0.9f, 0.1f, 1.0f);
	m_pLights->m_pLights[10].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights->m_pLights[10].m_xmf3Position = XMFLOAT3(970, 260, 1915);
	m_pLights->m_pLights[10].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[10].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[10].m_fFalloff = 8.0f;
	m_pLights->m_pLights[10].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[10].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[11].m_bEnable = false;
	m_pLights->m_pLights[11].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[11].m_fRange = 60.0f;
	m_pLights->m_pLights[11].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[11].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[11].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[11].m_xmf3Position = XMFLOAT3(930, 260, 1980);
	m_pLights->m_pLights[11].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[11].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[11].m_fFalloff = 8.0f;
	m_pLights->m_pLights[11].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[11].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[12].m_bEnable = false;
	m_pLights->m_pLights[12].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[12].m_fRange = 40.0f;
	m_pLights->m_pLights[12].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[12].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[12].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[12].m_xmf3Position = XMFLOAT3(890, 260, 1900);
	m_pLights->m_pLights[12].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[12].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[12].m_fFalloff = 8.0f;
	m_pLights->m_pLights[12].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[12].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[13].m_bEnable = false;
	m_pLights->m_pLights[13].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[13].m_fRange = 60.0f;
	m_pLights->m_pLights[13].m_xmf4Ambient = XMFLOAT4(1.1f, 0.1f, 1.1f, 1.0f);
	m_pLights->m_pLights[13].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[13].m_xmf4Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	m_pLights->m_pLights[13].m_xmf3Position = XMFLOAT3(840, 260, 2020);
	m_pLights->m_pLights[13].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[13].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[13].m_fFalloff = 8.0f;
	m_pLights->m_pLights[13].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[13].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[14].m_bEnable = false;
	m_pLights->m_pLights[14].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[14].m_fRange = 60.0f;
	m_pLights->m_pLights[14].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[14].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.4f, 0.5f, 1.0f);
	m_pLights->m_pLights[14].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	m_pLights->m_pLights[14].m_xmf3Position = XMFLOAT3(950, 260, 1740);
	m_pLights->m_pLights[14].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[14].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[14].m_fFalloff = 8.0f;
	m_pLights->m_pLights[14].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[14].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[15].m_bEnable = false;
	m_pLights->m_pLights[15].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[15].m_fRange = 400;
	m_pLights->m_pLights[15].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[15].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[15].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2, 0.0f);
	m_pLights->m_pLights[15].m_xmf3Position = XMFLOAT3(900, 260, 1800);
	m_pLights->m_pLights[15].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[15].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[15].m_fFalloff = 8.0f;
	m_pLights->m_pLights[15].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[15].m_fTheta = (float)cos(XMConvertToRadians(60.0f));

	m_pLights->m_pLights[16].m_bEnable = false;
	m_pLights->m_pLights[16].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[16].m_fRange = 400;
	m_pLights->m_pLights[16].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[16].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[16].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2, 0.0f);
	m_pLights->m_pLights[16].m_xmf3Position = XMFLOAT3(810, 260, 1800);
	m_pLights->m_pLights[16].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[16].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[16].m_fFalloff = 8.0f;
	m_pLights->m_pLights[16].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[16].m_fTheta = (float)cos(XMConvertToRadians(60.0f));




	m_pLights->m_pLights[17].m_bEnable = false;
	m_pLights->m_pLights[17].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[17].m_fRange = 400;
	m_pLights->m_pLights[17].m_xmf4Ambient = XMFLOAT4(0.2f, 1.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[17].m_xmf4Diffuse = XMFLOAT4(0.2f, 1.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[17].m_xmf4Specular = XMFLOAT4(0.2f, 1.0f, 1.0, 0.0f);
	m_pLights->m_pLights[17].m_xmf3Position = XMFLOAT3(830, 260, 1745);
	m_pLights->m_pLights[17].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[17].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[17].m_fFalloff = 8.0f;
	m_pLights->m_pLights[17].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[17].m_fTheta = (float)cos(XMConvertToRadians(60.0f));


	m_pLights->m_pLights[18].m_bEnable = false;
	m_pLights->m_pLights[18].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[18].m_fRange = 400;
	m_pLights->m_pLights[18].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 1.2f, 1.0f);
	m_pLights->m_pLights[18].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 1.2f, 1.0f);
	m_pLights->m_pLights[18].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 1.2, 0.0f);
	m_pLights->m_pLights[18].m_xmf3Position = XMFLOAT3(850, 260, 1850);
	m_pLights->m_pLights[18].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[18].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[18].m_fFalloff = 8.0f;
	m_pLights->m_pLights[18].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[18].m_fTheta = (float)cos(XMConvertToRadians(60.0f));


	m_pLights->m_pLights[19].m_bEnable = false;
	m_pLights->m_pLights[19].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[19].m_fRange = 400;
	m_pLights->m_pLights[19].m_xmf4Ambient = XMFLOAT4(1.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[19].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 1.2f, 1.0f);
	m_pLights->m_pLights[19].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f,1.2, 0.0f);
	m_pLights->m_pLights[19].m_xmf3Position = XMFLOAT3(990, 260, 1945);
	m_pLights->m_pLights[19].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights->m_pLights[19].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[19].m_fFalloff = 8.0f;
	m_pLights->m_pLights[19].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[19].m_fTheta = (float)cos(XMConvertToRadians(60.0f));

	m_pLights->m_pLights[20].m_bEnable = false;
	m_pLights->m_pLights[20].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[20].m_fRange = 1200;
	m_pLights->m_pLights[20].m_xmf4Ambient = XMFLOAT4(0.4f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[20].m_xmf4Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[20].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2, 0.0f);
	m_pLights->m_pLights[20].m_xmf3Position = XMFLOAT3(500, 1000, 500);
	m_pLights->m_pLights[20].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[20].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[20].m_fFalloff = 8.0f;
	m_pLights->m_pLights[20].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights->m_pLights[20].m_fTheta = (float)cos(XMConvertToRadians(60.0f));


	/////////////////////////
	m_pMaterials = new MATERIALS;
	::ZeroMemory(m_pMaterials, sizeof(MATERIALS));

	m_pMaterials->m_pReflections[0] = { XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[1] = { XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[2] = { XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 15.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[3] = { XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[4] = { XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[5] = { XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[6] = { XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[7] = { XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
}

//void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
//{
//	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
//
//	m_nShaders = 1;
//	m_pShaders = new CObjectsShader[m_nShaders];
//	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
//	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList);
//
//	BuildLightsAndMaterials();
//
//	CreateShaderVariables(pd3dDevice, pd3dCommandList);
//}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	//지형을 확대할 스케일 벡터이다. x-축과 z-축은 8배, y-축은 2배 확대한다. 
	XMFLOAT3 xmf3Scale(8.0f, 2.0f, 8.0f); XMFLOAT4 xmf4Color(0.0f, 0.2f, 0.0f, 0.0f);
	//지형을 높이 맵 이미지 파일(HeightMap.raw)을 사용하여 생성한다. 높이 맵의 크기는 가로x세로(257x257)이다.
#ifdef _WITH_TERRAIN_PARTITION 
	/*하나의 격자 메쉬의 크기는 가로x세로(17x17)이다. 지형 전체는 가로 방향으로 16개, 세로 방향으로 16의 격자 메 쉬를 가진다.
	지형을 구성하는 격자 메쉬의 개수는 총 256(16x16)개가 된다.*/
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("../Assets/Image/Terrain/HeightMap.raw"), 257, 257, 17, 17, xmf3Scale, xmf4Color);
#else
	//지형을 하나의 격자 메쉬(257x257)로 생성한다.  
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("../Assets/Image/Terrain/HeightMap.raw"), 257, 257, 257, 257, xmf3Scale, xmf4Color);
#endif
	m_nShaders = 1;
	m_pShaders = new CObjectsShader[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList, m_pTerrain);
	BuildLightsAndMaterials();


	m_pMoon = m_pShaders->GetMoonObject();
	m_pMoon_1 = m_pShaders->GetMoonObject_1();
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_pShaders)
	{
		for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseShaderVariables();
		for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseObjects();
		delete[] m_pShaders;
	}

	ReleaseShaderVariables();

	if (m_pLights) delete m_pLights;
	if (m_pMaterials) delete m_pMaterials;
	if (m_pTerrain) delete m_pTerrain;

}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[5];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 0; //Player
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[1].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[1].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 2; //GameObject
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[3].Descriptor.ShaderRegister = 3; //Materials
	pd3dRootParameters[3].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[4].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[4].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) 
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);

	UINT ncbMaterialBytes = ((sizeof(MATERIALS) + 255) & ~255); //256의 배수
	m_pd3dcbMaterials = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbMaterialBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbMaterials->Map(0, NULL, (void **)&m_pcbMappedMaterials);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList) 
{
	::memcpy(m_pcbMappedLights, m_pLights, sizeof(LIGHTS));
	::memcpy(m_pcbMappedMaterials, m_pMaterials, sizeof(MATERIALS));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
	if (m_pd3dcbMaterials)
	{
		m_pd3dcbMaterials->Unmap(0, NULL);
		m_pd3dcbMaterials->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++)
		m_pShaders[i].ReleaseUploadBuffers();
	if (m_pTerrain) m_pTerrain->ReleaseUploadBuffers();

}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}

	if (m_pLights)
	{
		m_pLights->m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition(); 
		m_pLights->m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
	}
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		if(m_pLights)

		if (sqrt(((m_pLights->m_pLights[i].m_xmf3Position.x - m_pPlayer->GetPosition().x) * (m_pLights->m_pLights[i].m_xmf3Position.x - m_pPlayer->GetPosition().x) 
			+ (m_pLights->m_pLights[i].m_xmf3Position.y - m_pPlayer->GetPosition().y) * (m_pLights->m_pLights[i].m_xmf3Position.y - m_pPlayer->GetPosition().y) 
			+ (m_pLights->m_pLights[i].m_xmf3Position.z - m_pPlayer->GetPosition().z) * (m_pLights->m_pLights[i].m_xmf3Position.z - m_pPlayer->GetPosition().z) < 800)))
		{

			//m_ppSphere[i]->MoveForward();
			//m_ppSphere[i]->SetPosition(XMFLOAT3(m_pPlayer->GetPosition()));
		
			
			if (m_pLights->m_pLights[i].m_bEnable == false && i != 1)
			{
				m_pLights->m_pLights[i].m_bEnable = true;
				//cout << i << "번째 조명 ON" << endl;
			}
			
			//cout << "따라와" << endl;
		}
	}

	if (m_pMoon)
	{
		m_pLights->m_pLights[4].m_xmf3Position.x = m_pMoon->GetPosition().x;
		m_pLights->m_pLights[4].m_xmf3Position.y = m_pMoon->GetPosition().y;
		m_pLights->m_pLights[4].m_xmf3Position.z = m_pMoon->GetPosition().z;

		//cout << m_pMoon->GetPosition().x << "\t" << m_pMoon->GetPosition().y << "\t" << m_pMoon->GetPosition().z<< endl;

	}
	if (m_pPlayer->GetPosition().x > 800 && m_pPlayer->GetPosition().x < 1100 && m_pPlayer->GetPosition().z > 1720 && m_pPlayer->GetPosition().z < 2020)
	{
		//cout << "플레이어는 안에있다. " << endl;
		
		/*while (m_pLights->m_pLights[4].m_xmf4Ambient.x < 0.01 && m_pLights->m_pLights[4].m_xmf4Ambient.y < 0.01 && m_pLights->m_pLights[4].m_xmf4Ambient.z < 0.01)
		{
			m_pLights->m_pLights[4].m_xmf4Ambient.x -= 0.1f;
			m_pLights->m_pLights[4].m_xmf4Ambient.y -= 0.1f;
			m_pLights->m_pLights[4].m_xmf4Ambient.z -= 0.1f;
		}*/

		m_bIsPlayerInTheMirror = true;
		
	}
	else
	{
		m_bIsPlayerInTheMirror = false;
	}
	if (m_pLights->m_pLights[4].m_xmf3Position.y < 0) //밤
	{
		m_bIsMorning = false;
	}
	else if (m_pLights->m_pLights[4].m_xmf3Position.y > 0) //아침
	{
		
		m_bIsMorning = true;

	
	}
	/*밤 미로밖 -> 어두움
	밤 미로안 -> 어두움
	낮 미로안 -> 어두움
	낮 미로밖 -> 밝음*/
	if (!m_bIsMorning && !m_bIsPlayerInTheMirror) // 밤 미로밖
	{
		SetDark();
	}
	else if (!m_bIsMorning && m_bIsPlayerInTheMirror) // 밤 미로안
	{
		SetLightInTheMirror();
	}
	else if (m_bIsMorning && m_bIsPlayerInTheMirror) // 낮 미로안
	{
		SetLightInTheMirror();
	}
	else if (m_bIsMorning && !m_bIsPlayerInTheMirror) // 낮 미로밖
	{
		SetBright();
	}

	//cout << m_pLights->m_pLights[1].m_bEnable << endl;
	//cout << m_pLights->m_pLights[4].m_xmf3Position.x << "\t" << m_pLights->m_pLights[4].m_xmf3Position.y << "\t" << m_pLights->m_pLights[4].m_xmf3Position.z << endl;

}
void CScene::SetDark()
{
	
	//m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.02f, 0.02f, 0.02f, 0.01f); //태양
	//m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.02f, 0.2f, 0.02f, 1.0f);
	//m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);

	if(m_pLights->m_pLights[4].m_xmf4Ambient.x > 0.02f)
	m_pLights->m_pLights[4].m_xmf4Ambient.x -= 0.004f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.y > 0.02f)
	m_pLights->m_pLights[4].m_xmf4Ambient.y -= 0.004f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.z > 0.02f)
	m_pLights->m_pLights[4].m_xmf4Ambient.z -= 0.004f;


}
void CScene::SetBright()
{

	if (m_pLights->m_pLights[4].m_xmf4Ambient.x < 0.2f)
		m_pLights->m_pLights[4].m_xmf4Ambient.x += 0.002f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.y < 0.6f)
		m_pLights->m_pLights[4].m_xmf4Ambient.y += 0.004f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.z < 0.6f)
		m_pLights->m_pLights[4].m_xmf4Ambient.z += 0.004f;

	//m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.01f); //태양
	//m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.02f, 0.2f, 0.02f, 1.0f);
	//m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);
}
void CScene::SetLightInTheMirror()
{
	//m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.01f, 0.01f, 0.01f, 0.01f); //태양
	//m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.02f, 0.2f, 0.02f, 1.0f);
	//m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);
	if (m_pLights->m_pLights[4].m_xmf4Ambient.x > 0.02f)
		m_pLights->m_pLights[4].m_xmf4Ambient.x -= 0.02f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.y > 0.02f)
		m_pLights->m_pLights[4].m_xmf4Ambient.y -= 0.02f;
	if (m_pLights->m_pLights[4].m_xmf4Ambient.z > 0.02f)
		m_pLights->m_pLights[4].m_xmf4Ambient.z -= 0.02f;
}
void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(4, d3dcbLightsGpuVirtualAddress); //Lights

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbMaterialsGpuVirtualAddress = m_pd3dcbMaterials->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(3, d3dcbMaterialsGpuVirtualAddress);

	//if (m_pTerrain) m_pTerrain->Render(pd3dCommandList, pCamera);

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, pCamera);
	}
}

