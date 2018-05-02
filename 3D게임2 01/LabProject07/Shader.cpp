//-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"

CShader::CShader()
{
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i]) m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob *pd3dErrorBlob = NULL;
	HRESULT hResult = ::D3DCompileFromFile(pszFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, &pd3dErrorBlob);
//	char *pErrorString = (char *)pd3dErrorBlob->GetBufferPointer();

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
}

#define _WITH_WFOPEN
//#define _WITH_STD_STREAM

#ifdef _WITH_STD_STREAM
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#endif

D3D12_SHADER_BYTECODE CShader::ReadCompiledShaderFromFile(WCHAR *pszFileName, ID3DBlob **ppd3dShaderBlob)
{
	UINT nReadBytes = 0;
#ifdef _WITH_WFOPEN
	FILE *pFile = NULL;
	::_wfopen_s(&pFile, pszFileName, L"rb");
	::fseek(pFile, 0, SEEK_END);
	int nFileSize = ::ftell(pFile);
	BYTE *pByteCode = new BYTE[nFileSize];
	::rewind(pFile);
	nReadBytes = (UINT)::fread(pByteCode, sizeof(BYTE), nFileSize, pFile);
	::fclose(pFile);
#endif
#ifdef _WITH_STD_STREAM
	std::ifstream ifsFile;
	ifsFile.open(pszFileName, std::ios::in | std::ios::ate | std::ios::binary);
	nReadBytes = (int)ifsFile.tellg();
	BYTE *pByteCode = new BYTE[*pnReadBytes];
	ifsFile.seekg(0);
	ifsFile.read((char *)pByteCode, nReadBytes);
	ifsFile.close();
#endif

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	if (ppd3dShaderBlob)
	{
		*ppd3dShaderBlob = NULL;
		HRESULT hResult = D3DCreateBlob(nReadBytes, ppd3dShaderBlob);
		memcpy((*ppd3dShaderBlob)->GetBufferPointer(), pByteCode, nReadBytes);
		d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
		d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	}
	else
	{
		d3dShaderByteCode.BytecodeLength = nReadBytes;
		d3dShaderByteCode.pShaderBytecode = pByteCode;
	}

	return(d3dShaderByteCode);
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, MATERIAL *pMaterial)
{
}

void CShader::ReleaseShaderVariables()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_ppd3dPipelineStates) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}
void CShader::SetPlayer(CPlayer* Pplayer)
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSPlayer", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSPlayer", "ps_5_1", ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CPlayerShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_PLAYER_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbPlayer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbPlayer->Map(0, NULL, (void **)&m_pcbMappedPlayer);
}

void CPlayerShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CPlayerShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	::memcpy(&m_pcbMappedPlayer->m_xmf4x4World, &xmf4x4World, sizeof(XMFLOAT4X4));
}

void CPlayerShader::ReleaseShaderVariables()
{
	if (m_pd3dcbPlayer)
	{
		m_pd3dcbPlayer->Unmap(0, NULL);
		m_pd3dcbPlayer->Release();
	}
}

void CPlayerShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = m_pd3dcbPlayer->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(0, d3dGpuVirtualAddress);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CObjectsShader::CObjectsShader()
{
	m_bDoParticle = false;

}

CObjectsShader::~CObjectsShader()
{
}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSLighting", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSLighting", "ps_5_1", ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CObjectsShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) /*쉐이더가 가지고있는 오브젝트 갯수만큼 상수버퍼를 만듬*/
{
	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbGameObjectBytes * m_nObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	m_pd3dcbGameObjects->Map(0, NULL, (void **)&m_pcbMappedGameObjects);

	UINT ncbMirrorBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbMirror = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbMirrorBytes * m_nMirror, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	m_pd3dcbMirror->Map(0, NULL, (void **)&m_pcbMappedMirror);



	UINT ncbTerrainBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbTerrain = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbTerrainBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	m_pd3dcbTerrain->Map(0, NULL, (void **)&m_pcbMappedTerrain);


	UINT ncbParticleBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbParticle = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbParticleBytes * m_nParticle, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	m_pd3dcbParticle->Map(0, NULL, (void **)&m_pcbMappedParticle);

}

void CObjectsShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	XMFLOAT4X4 xmf4x4World;
	for (int j = 0; j < m_nObjects; j++)
	{
		XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World)));
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)(m_pcbMappedGameObjects + (j * ncbGameObjectBytes));
		::memcpy(&pbMappedcbGameObject->m_xmf4x4World, &xmf4x4World, sizeof(XMFLOAT4X4));
		pbMappedcbGameObject->m_nMaterial = m_ppObjects[j]->m_pMaterial->m_nReflection;
	}
	///////


	UINT ncbMirrorBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	XMFLOAT4X4 xmf4x4WorldMirror;
	for (int j = 0; j < m_nMirror; j++)
	{
		XMStoreFloat4x4(&xmf4x4WorldMirror, XMMatrixTranspose(XMLoadFloat4x4(&m_ppMirror[j]->m_xmf4x4World)));
		CB_GAMEOBJECT_INFO *pbMappedcbMirror = (CB_GAMEOBJECT_INFO *)(m_pcbMappedMirror + (j * ncbMirrorBytes));
		::memcpy(&pbMappedcbMirror->m_xmf4x4World, &xmf4x4WorldMirror, sizeof(XMFLOAT4X4));
		pbMappedcbMirror->m_nMaterial = m_ppMirror[j]->m_pMaterial->m_nReflection;
	}
	//

	UINT ncbParticleBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	XMFLOAT4X4 xmf4x4WorldParticle;
	for (int j = 0; j < m_nParticle; j++)
	{
		XMStoreFloat4x4(&xmf4x4WorldParticle, XMMatrixTranspose(XMLoadFloat4x4(&m_ppParticle[j]->m_xmf4x4World)));
		CB_GAMEOBJECT_INFO *pbMappedcbParticle = (CB_GAMEOBJECT_INFO *)(m_pcbMappedParticle + (j * ncbParticleBytes));
		::memcpy(&pbMappedcbParticle->m_xmf4x4World, &xmf4x4WorldParticle, sizeof(XMFLOAT4X4));
		pbMappedcbParticle->m_nMaterial = m_ppParticle[j]->m_pMaterial->m_nReflection;
	}


	/////

	UINT ncbGameTerrain = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	XMFLOAT4X4 xmf4x4WorldTerrain;
	XMStoreFloat4x4(&xmf4x4WorldTerrain, XMMatrixTranspose(XMLoadFloat4x4(&m_pTerrain->m_xmf4x4World)));
	CB_GAMEOBJECT_INFO *pbMappedcbTerrain = (CB_GAMEOBJECT_INFO *)(m_pcbMappedTerrain);
	::memcpy(&pbMappedcbTerrain->m_xmf4x4World, &xmf4x4WorldTerrain, sizeof(XMFLOAT4X4));
	pbMappedcbTerrain->m_nMaterial = m_pTerrain->m_pMaterial->m_nReflection;
	
}

void CObjectsShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects)
	{
		m_pd3dcbGameObjects->Unmap(0, NULL);
		m_pd3dcbGameObjects->Release();
	}


	if (m_pd3dcbMirror)
	{
		m_pd3dcbMirror->Unmap(0, NULL);
		m_pd3dcbMirror->Release();
	}

	if (m_pd3dcbTerrain)
	{
		m_pd3dcbTerrain->Unmap(0, NULL);
		m_pd3dcbTerrain->Release();
	}

	if (m_pd3dcbParticle)
	{
		m_pd3dcbParticle->Unmap(0, NULL);
		m_pd3dcbParticle->Release();
	}
}

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	m_pTerrain = (CHeightMapTerrain *)pContext;



	//집만들기

	CCubeMeshIlluminated *pHouseMesh = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 300.0f, 300.0f);

	CCubeMeshIlluminated *pHouseMesh2 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 200.0f, 300.0f, 1.0f);

	//

	CCubeMeshIlluminated *pDoarMesh1 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 10.0f, 500.0f, 10.0f);
	CCubeMeshIlluminated *pDoarMesh2 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 150.0f, 10.0f, 10.0f);

	CCubeMeshIlluminated *pRoofMesh30 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 30, 1, 30);

	//

	//CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	CCubeMeshIlluminated *pMiroMeshWidth60 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 60, 30, 1.0f);
	CCubeMeshIlluminated *pMiroMeshHeight60 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 30, 60.0f);

	CCubeMeshIlluminated *pMiroMeshWidth30 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 30, 30, 1.0f);
	CCubeMeshIlluminated *pMiroMeshHeight30 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 30, 30.0f);

	CCubeMeshIlluminated *pMiroMeshHeight100 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 30, 100.0f);
	CCubeMeshIlluminated *pMiroMeshWidth100 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 100.0f, 30, 1.0f);

	CCubeMeshIlluminated *pMiroMeshWidth20 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 20, 30, 1.0f);
	CCubeMeshIlluminated *pMiroMeshHeight20 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 30, 20.0f);

	CCubeMeshIlluminated *pMiroMeshWidth10 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 5, 30, 1.0f);
	CCubeMeshIlluminated *pMiroMeshHeight10 = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 30, 5);
	CRotatingObject *pMirrorObject = NULL;

	//미로그리기
	int i = 0;

	m_nMirror = 167;
	m_ppMirror = new CGameObject*[m_nMirror];

	int k = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			pMirrorObject = new CRotatingObject();
			pMirrorObject->SetMesh(0, pRoofMesh30); //각 정육면체 객체의 위치를 설정한다. 
			pMirrorObject->SetPosition(815+30*i, 265, 1735 + 30*j);
			/*pMirrorObject->MinX = 980 - 30.0f;
			pMirrorObject->MaxX = 980 + 30.0f;
			pMirrorObject->MinZ = 1775 - 0.5f;
			pMirrorObject->MaxZ = 1775 + 0.5f;*/
			pMirrorObject->SetMaterial(3);
			pMirrorObject->SetOOBB(XMFLOAT3(980, 250, 1775), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			m_ppMirror[k++] = pMirrorObject;
			
		}
	}
	i = k;
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(980, 250, 1775);
	pMirrorObject->MinX = 980 - 30.0f;
	pMirrorObject->MaxX = 980 + 30.0f;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(980, 250, 1775), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1070, 250, 1835);
	pMirrorObject->MinX = 1070 - 30;
	pMirrorObject->MaxX = 1070 + 30;
	pMirrorObject->MinZ = 1835 - 0.5;
	pMirrorObject->MaxZ = 1835 + 0.5;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1070, 250, 1835), XMFLOAT3(30.f, 30.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1010, 250, 1735);
	pMirrorObject->MinX = 1010 - 0.5f;
	pMirrorObject->MaxX = 1010 + 0.5f;
	pMirrorObject->MinZ = 1735 - 15.0f;
	pMirrorObject->MaxZ = 1735 + 15.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1010, 250, 1735), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1010, 250, 1760);
	pMirrorObject->MinX = 1010 - 0.5f;
	pMirrorObject->MaxX = 1010 + 0.5f;
	pMirrorObject->MinZ = 1760 - 10.0f;
	pMirrorObject->MaxZ = 1760 + 10.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1010, 250, 1760), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight10); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1010, 250, 1772.5);
	pMirrorObject->MinX = 1010 - 0.5f;
	pMirrorObject->MaxX = 1010 + 0.5f;
	pMirrorObject->MinZ = 1772.5 - 5;
	pMirrorObject->MaxZ = 1772.5 + 5;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1010, 250, 1772.5), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1805);
	pMirrorObject->MinX = 950 - 0.5f;
	pMirrorObject->MaxX = 950 + 0.5f;
	pMirrorObject->MinZ = 1805 - 30.0f;
	pMirrorObject->MaxZ = 1805 + 30.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(950, 250, 1805), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1930);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1930 - 30.0f;
	pMirrorObject->MaxZ = 1930 + 30.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1930), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(860, 250, 1835);
	pMirrorObject->MinX = 860 - 10;
	pMirrorObject->MaxX = 860 + 10;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(880, 250, 1835);
	pMirrorObject->MinX = 880 - 10;
	pMirrorObject->MaxX = 880 + 10;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(900, 250, 1835);
	pMirrorObject->MinX = 900 - 10;
	pMirrorObject->MaxX = 900 + 10;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1835);
	pMirrorObject->MinX = 920 - 10;
	pMirrorObject->MaxX = 920 + 10;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(940, 250, 1835);
	pMirrorObject->MinX = 940 - 10;
	pMirrorObject->MaxX = 940 + 10;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//빵상
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(860, 250, 1775);
	pMirrorObject->MinX = 860 - 10;
	pMirrorObject->MaxX = 860 + 10;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(880, 250, 1775);
	pMirrorObject->MinX = 880 - 10;
	pMirrorObject->MaxX = 880 + 10;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(900, 250, 1775);
	pMirrorObject->MinX = 900 - 10;
	pMirrorObject->MaxX = 900 + 10;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1775);
	pMirrorObject->MinX = 920 - 10;
	pMirrorObject->MaxX = 920 + 10;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(940, 250, 1775);
	pMirrorObject->MinX = 940 - 10;
	pMirrorObject->MaxX = 940 + 10;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;
	//빵상
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(825, 250, 1735);
	pMirrorObject->MinX = 825 - 0.5f;
	pMirrorObject->MaxX = 825 + 0.5f;
	pMirrorObject->MinZ = 1735 - 15.0f;
	pMirrorObject->MaxZ = 1735 + 15.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(825, 250, 1735), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(825, 250, 1765);
	pMirrorObject->MinX = 825 - 0.5f;
	pMirrorObject->MaxX = 825 + 0.5f;
	pMirrorObject->MinZ = 1765 - 15.0f;
	pMirrorObject->MaxZ = 1765 + 15.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(825, 250, 1765), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(825, 250, 1795);
	pMirrorObject->MinX = 825 - 0.5f;
	pMirrorObject->MaxX = 825 + 0.5f;
	pMirrorObject->MinZ = 1795 - 15.0f;
	pMirrorObject->MaxZ = 1795 + 15.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(825, 250, 1795), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(830, 250, 1895);
	pMirrorObject->MinX = 830 - 30.0f;
	pMirrorObject->MaxX = 830 + 30.0f;
	pMirrorObject->MinZ = 1895 - 0.5f;
	pMirrorObject->MaxZ = 1895 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(830, 250, 1895), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1900);
	pMirrorObject->MinX = 950 - 10;
	pMirrorObject->MaxX = 950 + 10;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(970, 250, 1900);
	pMirrorObject->MinX = 970 - 10;
	pMirrorObject->MaxX = 970 + 10;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(990, 250, 1900);
	pMirrorObject->MinX = 990 - 10;
	pMirrorObject->MaxX = 990 + 10;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1010, 250, 1900);
	pMirrorObject->MinX = 1010 - 10.0f;
	pMirrorObject->MaxX = 1010 + 10.0f;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1030, 250, 1900);
	pMirrorObject->MinX = 1030 - 10;
	pMirrorObject->MaxX = 1030 + 10;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1990);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1990 - 30.0f;
	pMirrorObject->MaxZ = 1990 + 30.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1990), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1930);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 1930 - 10;
	pMirrorObject->MaxZ = 1930 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1930), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1950);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 1950 - 10;
	pMirrorObject->MaxZ = 1950 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1950), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1970);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 1970 - 10;
	pMirrorObject->MaxZ = 1970 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1970), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1990);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 1990 - 10;
	pMirrorObject->MaxZ = 1990 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1990), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 2010);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 2010 - 10;
	pMirrorObject->MaxZ = 2010 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1970), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1805);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1805 - 30.0f;
	pMirrorObject->MaxZ = 1805 + 30.0f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1805), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1845);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1845 - 10;
	pMirrorObject->MaxZ = 1845 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1845), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1865);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1865 - 10;
	pMirrorObject->MaxZ = 1865 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1865), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1885);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1885 - 10;
	pMirrorObject->MaxZ = 1885 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1865), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1905);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1905 - 10;
	pMirrorObject->MaxZ = 1905 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1905), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight20); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1925);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1925 - 10;
	pMirrorObject->MaxZ = 1925 + 10;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1925), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1935);
	pMirrorObject->MinX = 950 - 30.0f;
	pMirrorObject->MaxX = 950 + 30.0f;
	pMirrorObject->MinZ = 1935 - 0.5f;
	pMirrorObject->MaxZ = 1935 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(950, 250, 1935), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	///

	//오른쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1735);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1735 - 15;
	pMirrorObject->MaxZ = 1735 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1765);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1765 - 15;
	pMirrorObject->MaxZ = 1765 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1795);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1795 - 15;
	pMirrorObject->MaxZ = 1795 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1825);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1825 - 15;
	pMirrorObject->MaxZ = 1825 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1855);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1855 - 15;
	pMirrorObject->MaxZ = 1855 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1885);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1885 - 15;
	pMirrorObject->MaxZ = 1885 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1915);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1915 - 15;
	pMirrorObject->MaxZ = 1915 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1915), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1945);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1945 - 15;
	pMirrorObject->MaxZ = 1945 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1945), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 1975);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 1975 - 15;
	pMirrorObject->MaxZ = 1975 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 1975), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 250, 2005);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;
	pMirrorObject->MinZ = 2005 - 15;
	pMirrorObject->MaxZ = 2005 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 250, 2005), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//왼쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1735);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1735 - 15;
	pMirrorObject->MaxZ = 1735 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1735), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1765);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1765 - 15;
	pMirrorObject->MaxZ = 1765 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1765), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1795);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1795 - 15;
	pMirrorObject->MaxZ = 1795 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1795), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1825);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1825 - 15;
	pMirrorObject->MaxZ = 1825 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1825), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1855);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1855 - 15;
	pMirrorObject->MaxZ = 1855 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1855), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1885);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1885 - 15;
	pMirrorObject->MaxZ = 1885 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1885), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1915);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1915 - 15;
	pMirrorObject->MaxZ = 1915 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1915), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1945);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1945 - 15;
	pMirrorObject->MaxZ = 1945 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1945), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 1975);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 1975 - 15;
	pMirrorObject->MaxZ = 1975 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 1975), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 250, 2005);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;
	pMirrorObject->MinZ = 2005 - 15;
	pMirrorObject->MaxZ = 2005 + 15;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 250, 2005), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	////앞쪽 벽면
	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pHouseMesh2); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(90044, 350, 1720);
	//pMirrorObject->MinX = 900 - 100;
	//pMirrorObject->MaxX = 900 + 150;
	//pMirrorObject->MinZ = 1720 - 0.5;
	//pMirrorObject->MaxZ = 1720 + 0.5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(900.0f, 350, 1720.0f), XMFLOAT3(100.0f, 150.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;

	////뒤쪽 벽면
	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pHouseMesh2); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(101100, 350, 2020);
	//pMirrorObject->MinX = 1000 - 100;
	//pMirrorObject->MaxX = 1000 + 150;
	//pMirrorObject->MinZ = 2020 - 0.5;
	//pMirrorObject->MaxZ = 2020 + 0.5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(1000, 350, 2020.0f), XMFLOAT3(150.0f, 150.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;


	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(1111005, 350, 1720);
	//pMirrorObject->MinX = 1005 - 5;
	//pMirrorObject->MaxX = 1005 + 5;
	//pMirrorObject->MinZ = 1720 - 5;
	//pMirrorObject->MaxZ = 1720 + 5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(1005, 350, 1720), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	////pDoarObject->SetNormalV(XMFLOAT3())
	//m_ppMirror[i++] = pMirrorObject;

	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(1095, 350, 1720);
	//pMirrorObject->MinX = 1095 - 5;
	//pMirrorObject->MaxX = 1095 + 5;
	//pMirrorObject->MinZ = 1720 - 5;
	//pMirrorObject->MaxZ = 1720 + 5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(1095, 350, 1720), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;

	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh2); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(1055, 600, 1720);
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(1055, 600, 1720), XMFLOAT3(75, 5, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;

	////

	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(11805, 350, 2020);
	//pMirrorObject->MinX = 805 - 5;
	//pMirrorObject->MaxX = 805 + 5;
	//pMirrorObject->MinZ = 2020 - 5;
	//pMirrorObject->MaxZ = 2020 + 5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(805, 350, 2020), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;



	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(11895, 350, 2020);
	//pMirrorObject->MinX = 895 - 5;
	//pMirrorObject->MaxX = 895 + 5;
	//pMirrorObject->MinZ = 2020 - 5;
	//pMirrorObject->MaxZ = 2020 + 5;
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(895, 350, 2020), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;


	//pMirrorObject = new CRotatingObject();
	//pMirrorObject->SetMesh(0, pDoarMesh2); //각 정육면체 객체의 위치를 설정한다. 
	//pMirrorObject->SetPosition(855, 600, 2020);
	//pMirrorObject->SetMaterial(3);
	//pMirrorObject->SetOOBB(XMFLOAT3(855, 600, 2020), XMFLOAT3(75, 5, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//m_ppMirror[i++] = pMirrorObject;







	////////////

	//앞면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(830, 250, 1720);
	pMirrorObject->MinX = 830 - 30.0f;
	pMirrorObject->MaxX = 830 + 30.0f;
	pMirrorObject->MinZ = 1720 - 0.5f;
	pMirrorObject->MaxZ = 1720 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(830, 250, 1720), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1720);
	pMirrorObject->MinX = 890 - 30.0f;
	pMirrorObject->MaxX = 890 + 30.0f;
	pMirrorObject->MinZ = 1720 - 0.5f;
	pMirrorObject->MaxZ = 1720 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1720), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1720);
	pMirrorObject->MinX = 950 - 30.0f;
	pMirrorObject->MaxX = 950 + 30.0f;
	pMirrorObject->MinZ = 1720 - 0.5f;
	pMirrorObject->MaxZ = 1720 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(950, 250, 1720), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(995, 250, 1720);
	pMirrorObject->MinX = 995 - 15.0f;
	pMirrorObject->MaxX = 995 + 15.0f;
	pMirrorObject->MinZ = 1720 - 0.5f;
	pMirrorObject->MaxZ = 1720 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(995, 250, 1720), XMFLOAT3(15.0f, 15.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	// 뒷면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 2020);
	pMirrorObject->MinX = 920 - 30.0f;
	pMirrorObject->MaxX = 920 + 30.0f;
	pMirrorObject->MinZ = 2020 - 0.5f;
	pMirrorObject->MaxZ = 2020 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 2020), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(980, 250, 2020);
	pMirrorObject->MinX = 980 - 30.0f;
	pMirrorObject->MaxX = 980 + 30.0f;
	pMirrorObject->MinZ = 2020 - 0.5f;
	pMirrorObject->MaxZ = 2020 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(980, 250, 2020), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 2020);
	pMirrorObject->MinX = 1040 - 30.0f;
	pMirrorObject->MaxX = 1040 + 30.0f;
	pMirrorObject->MinZ = 2020 - 0.5f;
	pMirrorObject->MaxZ = 2020 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 2020), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth30); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1085, 250, 2020);
	pMirrorObject->MinX = 1085 - 15.0f;
	pMirrorObject->MaxX = 1085 + 15.0f;
	pMirrorObject->MinZ = 2020 - 0.5f;
	pMirrorObject->MaxZ = 2020 + 0.5f;
	pMirrorObject->SetMaterial(3);
	pMirrorObject->SetOOBB(XMFLOAT3(1085, 250, 2020), XMFLOAT3(15.0f, 15.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	///////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	i = 0;

	float fTerrainWidth = m_pTerrain->GetWidth(), fTerrainLength = m_pTerrain->GetLength();
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
	//직육면체를 지형 표면에 그리고 지형보다 높은 위치에 일정한 간격으로 배치한다.
	int xObjects = 8, yObjects = 1, zObjects =8;
	m_nObjects = xObjects * yObjects * zObjects + 2;
	m_ppObjects = new CGameObject*[m_nObjects];
	CRotatingObject *pRotatingObject = NULL;

	CSphereMeshIlluminated *pMoonMesh = new CSphereMeshIlluminated(pd3dDevice, pd3dCommandList, 120.0f, 120.0f, 120.0f);
	CSphereMeshIlluminated *pSphereMesh = new CSphereMeshIlluminated(pd3dDevice, pd3dCommandList, 12, 12, 12);

	pRotatingObject = new CRotatingObject();
	pRotatingObject->SetMesh(0, pMoonMesh);
	pRotatingObject->SetPosition(XMFLOAT3(1070, 249, 18005));
	pRotatingObject->SetOOBB(XMFLOAT3(1070, 249, 1805), XMFLOAT3(12.0f, 10.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pRotatingObject->SetMaterial(7);
	m_ppObjects[i++] = pRotatingObject;

	pRotatingObject = new CRotatingObject();
	pRotatingObject->SetMesh(0, pMoonMesh);
	pRotatingObject->SetPosition(XMFLOAT3(1070, -2249, 1800));
	pRotatingObject->SetOOBB(XMFLOAT3(920, 249, 1800), XMFLOAT3(12.0f, 10.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pRotatingObject->SetMaterial(5);
	m_ppObjects[i++] = pRotatingObject;

	for (int x = 0;  x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{
			for (int y = 0; y < yObjects; y++)
			{
				pRotatingObject = new CRotatingObject(1);
				pRotatingObject->SetMesh(0, pSphereMesh);
				pRotatingObject->SetMaterial(1);
				float xPosition = x * fxPitch + 800;
				float zPosition = z * fzPitch + 1200; 
				float fHeight = m_pTerrain->GetHeight(xPosition, zPosition) ;
				pRotatingObject->SetPosition(xPosition, fHeight + (y * 10.0f * fyPitch) + 6.0f, zPosition);
				//if (y == 0)
				//{
				//	/*지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선 벡터 방향과 직육면체의 y-축이 일치하도록 한다.*/
				//	xmf3SurfaceNormal = m_pTerrain->GetNormal(xPosition, zPosition);
				//	xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
				//	if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
				//	float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
				//	pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
				//}
				pRotatingObject->SetOOBB(pRotatingObject->GetPosition(), XMFLOAT3(12, 10, 10), XMFLOAT4(0, 0, 0, 1));
				m_ppObjects[i++] = pRotatingObject;
			}
		}
	}
	
	//pRotatingObject = new CRotatingObject();
	//pRotatingObject->SetMesh(0, pSphereMesh);
	//pRotatingObject->SetPosition(XMFLOAT3(950, -2429, 1800));
	//pRotatingObject->SetOOBB(XMFLOAT3(950, 249, 1800), XMFLOAT3(12.0f, 10.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//pRotatingObject->SetMaterial(3);
	//m_ppObjects[i++] = pRotatingObject;



	//////////////////////////////////////////////////
	//파티클 생성
	CCubeMeshIlluminated *pParticleMesh = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 1.0f, 1.0f, 1.0f);
	/*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/
	//int xObjects = 3, yObjects = 3, zObjects = 10, i = 0;

	//x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	m_nParticle = 64;
	m_ppParticle = new CGameObject*[m_nParticle];
	//float fxPitch = 12.0f * 2.5f;
	//float fyPitch = 12.0f * 2.5f;
	//float fzPitch = 12.0f * 2.5f;

	i = 0;

	default_random_engine dre;
	uniform_int<> uiColor(0, 120);
	uniform_real_distribution<> urPosition(-35.f, 35.f);
	uniform_real_distribution<> urSpeed(0.03f, 0.08f);
	uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌

	CRotatingObject *pParticleObject = NULL;


	for (int j = 0; j < m_nParticle; ++j)
	{
		pParticleObject = new CRotatingObject();
		pParticleObject->SetMesh(0, pParticleMesh); //각 정육면체 객체의 위치를 설정한다. 
		pParticleObject->SetPosition(9999, 249, 1645);
		pParticleObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pParticleObject->SetRotationSpeed(0.5);
		pParticleObject->SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
		pParticleObject->SetMaterial(3);
		pParticleObject->SetMovingSpeed(1.0);
		m_ppParticle[i++] = pParticleObject;
	}
	
	


	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) 
			if (m_ppObjects[j]) 
				delete m_ppObjects[j];
		delete[] m_ppObjects;
	}

	if (m_ppMirror)
	{
		for (int j = 0; j < m_nMirror; j++) 
			if (m_ppMirror[j]) 
				delete m_ppMirror[j];
		delete[] m_ppMirror;
	}

	if (m_ppParticle)
	{
		for (int j = 0; j < m_nParticle; j++)
			if (m_ppParticle[j])
				delete m_ppParticle[j];
		delete[] m_ppParticle;
	}
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	//미로 충돌

	for (int i = 0; i < m_nMirror; ++i)
	{

		if ((*m_ppMirror[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//cout << "충돌" << endl;
			
			if (m_pPlayer->GetPosition().x > m_ppMirror[i]->MaxX && m_pPlayer->GetPosition().z > m_ppMirror[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppMirror[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}

			//cout << "벽과 플레이어 충돌 " << endl;
			/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
			{
			cout << "오른쪽 면과 충돌" << endl;
			}*/

			if (m_pPlayer->GetPosition().x < m_ppMirror[i]->MinX && m_pPlayer->GetPosition().z > m_ppMirror[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppMirror[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x - 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}


			if (m_pPlayer->GetPosition().z < m_ppMirror[i]->MinZ && m_pPlayer->GetPosition().x > m_ppMirror[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppMirror[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z - 1));
				//cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
			}

			if (m_pPlayer->GetPosition().z > m_ppMirror[i]->MinZ && m_pPlayer->GetPosition().x > m_ppMirror[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppMirror[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z + 1));
				//cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
			}
			

		}
	}
	//플레이어와 장애물 일정거리 되었을때
	for (int i = 0; i < m_nObjects; ++i)
	{
		if (sqrt(((m_pPlayer->m_xmOOBB.Center.x - m_ppObjects[i]->m_xmOOBB.Center.x) * (m_pPlayer->m_xmOOBB.Center.x - m_ppObjects[i]->m_xmOOBB.Center.x) + (m_pPlayer->m_xmOOBB.Center.y - m_ppObjects[i]->m_xmOOBB.Center.y) * (m_pPlayer->m_xmOOBB.Center.y - m_ppObjects[i]->m_xmOOBB.Center.y) + (m_pPlayer->m_xmOOBB.Center.z - m_ppObjects[i]->m_xmOOBB.Center.z) * (m_pPlayer->m_xmOOBB.Center.z - m_ppObjects[i]->m_xmOOBB.Center.z) < 2250)))
		{

			//m_ppSphere[i]->MoveForward();
			//m_ppSphere[i]->SetPosition(XMFLOAT3(m_pPlayer->GetPosition()));
			m_ppObjects[i]->MoveToPlayer(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppObjects[i]->GetPosition()), 0.0004f);

		
			m_ppObjects[i]->SetOOBB(m_ppObjects[i]->GetPosition(), XMFLOAT3(12, 10, 10), XMFLOAT4(0, 0, 0, 1));
			//cout << "따라와" << endl;
		}
	}

	cout << "------------------------------" << endl;
	cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
	cout << m_ppObjects[2]->m_xmOOBB.Center.x << "\t" << m_ppObjects[2]->m_xmOOBB.Center.y << "\t" << m_ppObjects[2]->m_xmOOBB.Center.z << endl;
	cout << "------------------------------" << endl;



	//장애물과 플레이어 충돌
	for (int j = 0; j < m_nObjects; ++j)
	{
		if (m_pPlayer->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
		{
			for (int k = 0; k < m_nParticle; ++k)
			{

				(*m_ppParticle[k]).SetPosition(m_pPlayer->GetPosition());
			}
			//m_ppObjects[j]->SetPosition(XMFLOAT3(-99999, 999, 999));
			m_pPlayer->Move(Vector3::Normalize(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppObjects[j]->GetPosition())), true);
			m_bDoParticle = true;
			break;
		}
	}
	if (m_bDoParticle == true)
	{
		for (int j = 0; j < m_nParticle; j++)
		{

			m_ppParticle[j]->Animate(fTimeElapsed);
		}
	}
	


	for (int i = 0; i < m_nObjects; i++) (*m_ppObjects[i]).m_pCollider = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if ((*m_ppObjects[i]).m_xmOOBB.Intersects((*m_ppObjects[j]).m_xmOOBB))
			{

				(*m_ppObjects[i]).m_pCollider = &(*m_ppObjects[j]);
				(*m_ppObjects[j]).m_pCollider = &(*m_ppObjects[i]);
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if ((*m_ppObjects[i]).m_pCollider && (*m_ppObjects[i]).m_pCollider->m_pCollider) //충돌한 정보가 있으면
		{
			//서로의 무빙디렉션을 바꿔주겠다.
			//cout << "서로충돌" << endl;
			
			XMFLOAT3 moveVector = Vector3::Normalize(Vector3::Subtract(m_ppObjects[i]->m_pCollider->m_pCollider->GetPosition(), m_ppObjects[i]->m_pCollider->GetPosition()));

			m_ppObjects[i]->Move(XMFLOAT3(moveVector.x, moveVector.y, moveVector.z), true);
			m_ppObjects[i]->SetOOBB(m_ppObjects[i]->GetPosition(), XMFLOAT3(12, 10, 10), XMFLOAT4(0, 0, 0, 1));
			break;
		}
	}


	//////// 장애물과 미로 충돌
	//for (int i = 0; i < m_nMirror; ++i)
	//{
	//	for (int j = 0; j < m_nObjects; ++j)
	//	{
	//		if ((*m_ppMirror[i]).m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
	//		{
	//			//cout << i << endl;
	//			/*cout << "------------------------" << endl;
	//			cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
	//			cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
	//			cout << "------------------------" << endl;*/
	//			////cout << "벽과 플레이어 충돌 " << endl;
	//			if (m_ppObjects[j]->GetPosition().x > m_ppMirror[i]->MaxX && m_ppObjects[j]->GetPosition().z > m_ppMirror[i]->MinZ &&  m_ppObjects[j]->GetPosition().z < m_ppMirror[i]->MaxZ)
	//			{
	//				//cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
	//				m_ppObjects[j]->SetPosition(XMFLOAT3(m_ppObjects[j]->GetPosition().x + 1, m_ppObjects[j]->GetPosition().y, m_ppObjects[j]->GetPosition().z));
	//			}

	//			//cout << "벽과 플레이어 충돌 " << endl;
	//			/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
	//			{
	//			cout << "오른쪽 면과 충돌" << endl;
	//			}*/

	//			if (m_ppObjects[j]->GetPosition().x < m_ppMirror[i]->MinX && m_ppObjects[j]->GetPosition().z > m_ppMirror[i]->MinZ &&  m_ppObjects[j]->GetPosition().z < m_ppMirror[i]->MaxZ)
	//			{
	//				//cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
	//				m_ppObjects[j]->SetPosition(XMFLOAT3(m_ppObjects[j]->GetPosition().x - 1, m_ppObjects[j]->GetPosition().y, m_ppObjects[j]->GetPosition().z));
	//			}


	//			if (m_ppObjects[j]->GetPosition().z < m_ppMirror[i]->MinZ && m_ppObjects[j]->GetPosition().x > m_ppMirror[i]->MinX &&  m_ppObjects[j]->GetPosition().x < m_ppMirror[i]->MaxX)
	//			{
	//				//m_ppObjects[j]->SetPosition(XMFLOAT3(m_ppObjects[j]->GetPosition().x, m_ppObjects[j]->GetPosition().y, m_ppObjects[j]->GetPosition().z - 1));
	//				//cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
	//			}

	//			if (m_ppObjects[j]->GetPosition().z > m_ppMirror[i]->MaxZ && m_ppObjects[j]->GetPosition().x > m_ppMirror[i]->MinX &&  m_ppObjects[j]->GetPosition().x < m_ppMirror[i]->MaxX)
	//			{
	//				//m_ppObjects[j]->SetPosition(XMFLOAT3(m_ppObjects[j]->GetPosition().x, m_ppObjects[j]->GetPosition().y, m_ppObjects[j]->GetPosition().z + 1));
	//			//	cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
	//			}
	//			//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
	//			//{
	//			//	//cout << "앞면과 충돌" << endl;
	//			//}

	//		}
	//	}
	//	//m_listBullet.erase(iter);
	//}
	//m_ppObjects[0]->MoveForward(1);
	m_ppObjects[0]->Revolution(1,2500,XMFLOAT3(1000, 245, 1000),0);
	m_ppObjects[1]->Revolution(1, 2500, XMFLOAT3(1000, 245, 1000),1);

	
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << "\t" << endl;
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) m_ppObjects[j]->ReleaseUploadBuffers();
	}
	if (m_ppMirror)
	{
		for (int j = 0; j < m_nMirror; j++) if (m_ppMirror[j]) m_ppMirror[j]->ReleaseUploadBuffers();

	}
	if (m_ppParticle)
	{
		for (int j = 0; j < m_nParticle; j++) if (m_ppParticle[j]) m_ppParticle[j]->ReleaseUploadBuffers();

	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	UpdateShaderVariables(pd3dCommandList);

	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbGameObjectGpuVirtualAddress = m_pd3dcbGameObjects->GetGPUVirtualAddress();

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbGameObjectGpuVirtualAddress + (ncbGameObjectBytes * j));
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
	////////
	UINT ncbMirrorBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbMirrorGpuVirtualAddress = m_pd3dcbMirror->GetGPUVirtualAddress();

	for (int j = 0; j < m_nMirror; j++)
	{
		if (m_ppMirror[j])
		{
			pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbMirrorGpuVirtualAddress + (ncbMirrorBytes * j));
			//메쉬를 랜더하기전에 실제로 오브젝트 정보가 어느 주소에있는지, 그건 루트디스크립터로 알려주기로했으니까 필요한정보가(상수버퍼가) 어디에있어 이걸 루프돌면서
				// 오브젝트크기 * 인덱스 j , 를 하는건 걍 배열 인덱스 접근하는 것처럼 하는거니까. 
			m_ppMirror[j]->Render(pd3dCommandList, pCamera);
		}
	}


	///////////
	UINT ncbTerrainBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbTerrainGpuVirtualAddress = m_pd3dcbTerrain->GetGPUVirtualAddress();

	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbTerrainGpuVirtualAddress);


	m_pTerrain->Render(pd3dCommandList, pCamera);

	/////////
	UINT ncbParticleBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbParticleGpuVirtualAddress = m_pd3dcbParticle->GetGPUVirtualAddress();

	for (int j = 0; j < m_nParticle; j++)
	{
		if (m_ppParticle[j])
		{
			pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbParticleGpuVirtualAddress + (ncbParticleBytes * j));
			m_ppParticle[j]->Render(pd3dCommandList, pCamera);
		}
		//터짐
	}


	/*UINT ncbParticleBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbParticleGpuVirtualAddress = m_pd3dcbParticle->GetGPUVirtualAddress();

	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbParticleGpuVirtualAddress);*/


	//m_ppParticle[0]->Render(pd3dCommandList, pCamera);



}

CTerrainShader::CTerrainShader() { }
CTerrainShader::~CTerrainShader() { }

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSLighting", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSLighting", "ps_5_1", ppd3dShaderBlob));
}
void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}