#include "stdafx.h"
#include "Shader.h"
#include "Player.h"

CShader::CShader()
{
	bFollowMe = false;
}


CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++)
			if (m_ppd3dPipelineStates[i]) m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc; ::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	//d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;

	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	//d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;
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
//블렌딩 상태를 설정하기 위한 구조체를 반환한다.
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

//입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체를 반환한다.
D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);

}
//정점 셰이더 바이트 코드를 생성(컴파일)한다.
D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}
//픽셀 셰이더 바이트 코드를 생성(컴파일)한다.
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);

}
//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다.
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}
//그래픽스 파이프라인 상태 객체를 생성한다.
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
	d3dPipelineStateDesc.SampleMask = UINT_MAX; d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs)
		delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}
//셰이더 객체가 포함하는 게임 객체들을 생성한다.

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다. 
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}
void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);

}
void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) { }
void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList) { }
void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World; XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}
void CShader::ReleaseShaderVariables() { }



CPlayerShader::CPlayerShader() { }
CPlayerShader::~CPlayerShader() { }
D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}
void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}
CObjectsShader::CObjectsShader() 
{ 
	m_bDoParticle = false;
}

CObjectsShader::~CObjectsShader() { }
D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}
void CObjectsShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}
void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	//cout << m_pPlayer->GetPosition().z << endl;
	//CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	//float fTerrainWidth = pTerrain->GetWidth(), fTerrainLength = pTerrain->GetLength();
	//float fxPitch = 12.0f * 3.5f;
	//float fyPitch = 12.0f * 3.5f;
	//float fzPitch = 12.0f * 3.5f;
	////직육면체를 지형 표면에 그리고 지형보다 높은 위치에 일정한 간격으로 배치한다.
	//int xObjects = int(fTerrainWidth / fxPitch), yObjects = 2, zObjects = int(fTerrainLength / fzPitch);
	//m_nObjects = xObjects * yObjects * zObjects; m_ppObjects = new CGameObject*[m_nObjects];
	//CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
	//XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	//CRotatingObject *pRotatingObject = NULL; for (int i = 0, x = 0; x < xObjects; x++)
	//{
	//	for (int z = 0; z < zObjects; z++)
	//	{
	//		for (int y = 0; y < yObjects; y++)
	//		{
	//			pRotatingObject = new CRotatingObject(1);
	//			pRotatingObject->SetMesh(0, pCubeMesh);
	//			float xPosition = x * fxPitch;
	//			float zPosition = z * fzPitch; float fHeight = pTerrain->GetHeight(xPosition, zPosition);
	//			pRotatingObject->SetPosition(xPosition, fHeight + (y * 10.0f * fyPitch) + 6.0f, zPosition);
	//			if (y == 0)
	//			{
	//				/*지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선 벡터 방향과 직육면체의 y-축이 일치하도록 한다.*/
	//				xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
	//				xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
	//				if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//				float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
	//				pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
	//			} 
	//			pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//			pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
	//			m_ppObjects[i++] = pRotatingObject;
	//		}
	//	}
	//}

	//집 만들기


	
	CCubeMeshDiffused *pHouseMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1.0f, 300.0f, 300.0f);

	CCubeMeshDiffused *pHouseMesh2 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 200.0f, 300.0f, 1.0f);





	




	//미로 그리기
	m_nMirror = 25;
	m_ppMirror = new CGameObject*[m_nMirror];

	CCubeMeshDiffused *pMiroMeshHeight60 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1.0f, 60.0f, 60.0f);
	CCubeMeshDiffused *pMiroMeshWidth60 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 60.0f, 60.0f, 1.0f);

	CCubeMeshDiffused *pMiroMeshHeight100 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1.0f, 60.0f, 100.0f);
	CCubeMeshDiffused *pMiroMeshWidth100 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 100.0f, 60.0f, 1.0f);

	CCubeMeshDiffused *pDoarMesh1 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 10.0f, 500.0f, 10.0f);
	CCubeMeshDiffused *pDoarMesh2 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 150.0f, 10.0f, 10.0f);

	CRotatingObject *pMirrorObject = NULL;

	int i = 0;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(980, 250, 1775);
	pMirrorObject->MinX = 980 - 30.0f;
	pMirrorObject->MaxX = 980 + 30.0f;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(980, 250, 1775), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1070, 250, 1835);
	pMirrorObject->MinX = 1070 - 30;
	pMirrorObject->MaxX = 1070 + 30;
	pMirrorObject->MinZ = 1835 - 0.5;
	pMirrorObject->MaxZ = 1835 + 0.5;
	pMirrorObject->SetOOBB(XMFLOAT3(1070, 250, 1835), XMFLOAT3(30.f, 30.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1010, 250, 1745);
	pMirrorObject->MinX = 1010 - 0.5f;
	pMirrorObject->MaxX = 1010 + 0.5f;
	pMirrorObject->MinZ = 1745 - 30.0f;
	pMirrorObject->MaxZ = 1745 + 30.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(1010, 250, 1745), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1805);
	pMirrorObject->MinX = 950 - 0.5f;
	pMirrorObject->MaxX = 950 + 0.5f;
	pMirrorObject->MinZ = 1805 - 30.0f;
	pMirrorObject->MaxZ = 1805 + 30.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(950, 250, 1805), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1930);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1930 - 30.0f;
	pMirrorObject->MaxZ = 1930 + 30.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1930), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(900, 250, 1835);
	pMirrorObject->MinX = 900 - 50.0f;
	pMirrorObject->MaxX = 900 + 50.0f;
	pMirrorObject->MinZ = 1835 - 0.5f;
	pMirrorObject->MaxZ = 1835 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1835), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(900, 250, 1775);
	pMirrorObject->MinX = 900 - 50.0f;
	pMirrorObject->MaxX = 900 + 50.0f;
	pMirrorObject->MinZ = 1775 - 0.5f;
	pMirrorObject->MaxZ = 1775 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(900, 250, 1775), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(825, 250, 1770);
	pMirrorObject->MinX = 825 - 0.5f;
	pMirrorObject->MaxX = 825 + 0.5f;
	pMirrorObject->MinZ = 1770 - 50.0f;
	pMirrorObject->MaxZ = 1770 + 50.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(825, 250, 1770), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(830, 250, 1895);
	pMirrorObject->MinX = 830 - 30.0f;
	pMirrorObject->MaxX = 830 + 30.0f;
	pMirrorObject->MinZ = 1895 - 0.5f;
	pMirrorObject->MaxZ = 1895 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(830, 250, 1895), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(990, 250, 1900);
	pMirrorObject->MinX = 990 - 50.0f;
	pMirrorObject->MaxX = 990 + 50.0f;
	pMirrorObject->MinZ = 1900 - 0.5f;
	pMirrorObject->MaxZ = 1900 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(990, 250, 1900), XMFLOAT3(50.0f, 50.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1990);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1990 - 30.0f;
	pMirrorObject->MaxZ = 1990 + 30.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1990), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(890, 250, 1970);
	pMirrorObject->MinX = 890 - 0.5f;
	pMirrorObject->MaxX = 890 + 0.5f;
	pMirrorObject->MinZ = 1970 - 50.0f;
	pMirrorObject->MaxZ = 1970 + 50.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(890, 250, 1970), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1040, 250, 1805);
	pMirrorObject->MinX = 1040 - 0.5f;
	pMirrorObject->MaxX = 1040 + 0.5f;
	pMirrorObject->MinZ = 1805 - 30.0f;
	pMirrorObject->MaxZ = 1805 + 30.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(1040, 250, 1805), XMFLOAT3(0.5f, 30.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshHeight100); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(920, 250, 1885);
	pMirrorObject->MinX = 920 - 0.5f;
	pMirrorObject->MaxX = 920 + 0.5f;
	pMirrorObject->MinZ = 1885 - 50.0f;
	pMirrorObject->MaxZ = 1885 + 50.0f;
	pMirrorObject->SetOOBB(XMFLOAT3(920, 250, 1885), XMFLOAT3(0.5, 50.0f, 50), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pMiroMeshWidth60); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(950, 250, 1935);
	pMirrorObject->MinX = 950 - 30.0f;
	pMirrorObject->MaxX = 950 + 30.0f;
	pMirrorObject->MinZ = 1935 - 0.5f;
	pMirrorObject->MaxZ = 1935 + 0.5f;
	pMirrorObject->SetOOBB(XMFLOAT3(950, 250, 1935), XMFLOAT3(30.0f, 30.f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	///

	//오른쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pHouseMesh); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1100, 350, 1870);

	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->MinX = 1100 - 0.5;
	pMirrorObject->MaxX = 1100 + 0.5;

	pMirrorObject->MinZ = 1870 - 150;
	pMirrorObject->MaxZ = 1870 + 150;
	pMirrorObject->SetOOBB(XMFLOAT3(1100.0f, 350, 1870.0f), XMFLOAT3(0.5f, 150.f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//왼쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pHouseMesh); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(800, 350, 1870);
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->MinX = 800 - 0.5;
	pMirrorObject->MaxX = 800 + 0.5;

	pMirrorObject->MinZ = 1870 - 150;
	pMirrorObject->MaxZ = 1870 + 150;
	pMirrorObject->SetOOBB(XMFLOAT3(800.0f, 350, 1870.0f), XMFLOAT3(0.5f, 150.0f, 150.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//앞쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pHouseMesh2); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(900, 350, 1720);
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->MinX = 900 - 100;
	pMirrorObject->MaxX = 900 + 150;

	pMirrorObject->MinZ = 1720 - 0.5;
	pMirrorObject->MaxZ = 1720 + 0.5;
	pMirrorObject->SetOOBB(XMFLOAT3(900.0f, 350, 1720.0f), XMFLOAT3(100.0f, 150.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//뒤쪽 벽면
	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pHouseMesh2); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1000, 350, 2020);
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->MinX = 1000 - 100;
	pMirrorObject->MaxX = 1000 + 150;

	pMirrorObject->MinZ = 2020 - 0.5;
	pMirrorObject->MaxZ = 2020 + 0.5;
	pMirrorObject->SetOOBB(XMFLOAT3(1000, 350, 2020.0f), XMFLOAT3(150.0f, 150.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();

	pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1005, 350, 1720);
	pMirrorObject->MinX = 1005 - 5;
	pMirrorObject->MaxX = 1005 + 5;
	pMirrorObject->MinZ = 1720 - 5;
	pMirrorObject->MaxZ = 1720 + 5;
	//pDoarObject->dTop = 1005.f
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(1005, 350, 1720), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//pDoarObject->SetNormalV(XMFLOAT3())
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1095, 350, 1720);
	pMirrorObject->MinX = 1095 - 5;
	pMirrorObject->MaxX = 1095 + 5;
	pMirrorObject->MinZ = 1720 - 5;
	pMirrorObject->MaxZ = 1720 + 5;
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(1095, 350, 1720), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pDoarMesh2); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(1055, 600, 1720);
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(1055, 600, 1720), XMFLOAT3(75, 5, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;

	//

	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(805, 350, 2020);
	pMirrorObject->MinX = 805 - 5;
	pMirrorObject->MaxX = 805 + 5;
	pMirrorObject->MinZ = 2020 - 5;
	pMirrorObject->MaxZ = 2020 + 5;
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(805, 350, 2020), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;



	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pDoarMesh1); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(895, 350, 2020);
	pMirrorObject->MinX = 895 - 5;
	pMirrorObject->MaxX = 895 + 5;
	pMirrorObject->MinZ = 2020 - 5;
	pMirrorObject->MaxZ = 2020 + 5;

	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(895, 350, 2020), XMFLOAT3(5, 250, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	pMirrorObject = new CRotatingObject();
	pMirrorObject->SetMesh(0, pDoarMesh2); //각 정육면체 객체의 위치를 설정한다. 
	pMirrorObject->SetPosition(855, 600, 2020);
	//pRotatingObject->SetPosition(0, 0, 0);
	//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	pMirrorObject->SetOOBB(XMFLOAT3(855, 600, 2020), XMFLOAT3(75, 5, 5), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppMirror[i++] = pMirrorObject;


	// 구 객체 그리기
	//
	m_nSphere = SPHERESIZE;
	i = 0;
	m_ppSphere = new CGameObject*[m_nSphere];
	CSphereMeshDiffused * pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 10, 50, 50);
	CRotatingObject *pSphereObjecct = NULL;

	

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(920, 249, 1800));
	pSphereObjecct->MinX = 920 - 5.0f;
	pSphereObjecct->MaxX = 920 + 5.0f;
	pSphereObjecct->MinZ = 1800 - 5.0f;
	pSphereObjecct->MaxZ = 1800 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(920, 249, 1800), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(950, 249, 1740));
	pSphereObjecct->MinX = 950 - 5.0f;
	pSphereObjecct->MaxX = 950 + 5.0f;
	pSphereObjecct->MinZ = 1740 - 5.0f;
	pSphereObjecct->MaxZ = 1740 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(950, 249, 1740), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(1070, 249, 1805));
	pSphereObjecct->MinX = 1070 - 5.0f;
	pSphereObjecct->MaxX = 1070 + 5.0f;
	pSphereObjecct->MinZ = 1805 - 5.0f;
	pSphereObjecct->MaxZ = 1805 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(1070, 249, 1805), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(1070, 249, 1980));
	pSphereObjecct->MinX = 1070 - 5.0f;
	pSphereObjecct->MaxX = 1070 + 5.0f;
	pSphereObjecct->MinZ = 1980 - 5.0f;
	pSphereObjecct->MaxZ = 1980 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(1070, 249, 1980), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(1050, 249, 1745));
	pSphereObjecct->MinX = 1050 - 5.0f;
	pSphereObjecct->MaxX = 1050 + 5.0f;
	pSphereObjecct->MinZ = 1745 - 5.0f;
	pSphereObjecct->MaxZ = 1745 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(1050, 249, 1745), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(930, 249, 1980));
	pSphereObjecct->MinX = 930 - 5.0f;
	pSphereObjecct->MaxX = 930 + 5.0f;
	pSphereObjecct->MinZ = 1980 - 5.0f;
	pSphereObjecct->MaxZ = 1980 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(930, 249, 1980), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(840, 249, 1940));
	pSphereObjecct->MinX = 840 - 5.0f;
	pSphereObjecct->MaxX = 840 + 5.0f;
	pSphereObjecct->MinZ = 1940 - 5.0f;
	pSphereObjecct->MaxZ = 1940 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(840, 249, 1940), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(1000, 249, 1855));
	pSphereObjecct->MinX = 1000 - 5.0f;
	pSphereObjecct->MaxX = 1000 + 5.0f;
	pSphereObjecct->MinZ = 1855 - 5.0f;
	pSphereObjecct->MaxZ = 1855 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(1000, 249, 1855), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(835, 249, 1850));
	pSphereObjecct->MinX = 835 - 5.0f;
	pSphereObjecct->MaxX = 835 + 5.0f;
	pSphereObjecct->MinZ = 1850 - 5.0f;
	pSphereObjecct->MaxZ = 1850 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(835, 249, 1850), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;

	pSphereObjecct = new CRotatingObject();
	pSphereObjecct->SetMesh(0, pSphereMesh);
	pSphereObjecct->SetPosition(XMFLOAT3(890, 249, 1900));
	pSphereObjecct->MinX = 890 - 5.0f;
	pSphereObjecct->MaxX = 890 + 5.0f;
	pSphereObjecct->MinZ = 1900 - 5.0f;
	pSphereObjecct->MaxZ = 1900 + 5.0f;
	pSphereObjecct->SetOOBB(XMFLOAT3(890, 249, 1900), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppSphere[i++] = pSphereObjecct;
	//

	//총알


	//총알 생성 
	CCubeMeshDiffused *pBulletMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 2.0f, 2.0f, 2.0f);
	/*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/
	//int xObjects = 3, yObjects = 3, zObjects = 10, i = 0;

	//x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	m_nBullet = BULLETSIZE;
	m_ppBullet = new CGameObject*[m_nBullet];
	//float fxPitch = 12.0f * 2.5f;
	//float fyPitch = 12.0f * 2.5f;
	//float fzPitch = 12.0f * 2.5f;

	i = 0;

	CRotatingObject *pBulletObject = NULL;

	for (int j = 0; j < m_nBullet; ++j)
	{
		pBulletObject = new CRotatingObject();
		pBulletObject->SetMesh(0,pBulletMesh); //각 정육면체 객체의 위치를 설정한다. 
		pBulletObject->SetPosition(0, 0, -9999);
		//pRotatingObject->SetPosition(0, 0, 0);
		pBulletObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pBulletObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
		pBulletObject->SetMovingDirection(XMFLOAT3(0, 0, 1));
		//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
		pBulletObject->SetMovingSpeed(2.0);
		pBulletObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		m_ppBullet[i++] = pBulletObject;
	}

	//파티클 생성 
	CCubeMeshDiffused *pParticleMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 2.0f, 2.0f, 2.0f);
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
		pParticleObject->SetMesh(0,pParticleMesh); //각 정육면체 객체의 위치를 설정한다. 
		pParticleObject->SetPosition(0, 0, -9999);
		//pRotatingObject->SetPosition(0, 0, 0);
		pParticleObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pParticleObject->SetRotationSpeed(0.05);
		pParticleObject->SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
		//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
		pParticleObject->SetMovingSpeed(1.0);
		pParticleObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		m_ppParticle[i++] = pParticleObject;
	}



	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

CTerrainShader::CTerrainShader() { }
CTerrainShader::~CTerrainShader() { }


CGameObject *CObjectsShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float *pfNearHitDistance)
{
	int nIntersected = 0; *pfNearHitDistance = FLT_MAX;
	int nIntersectedMirror = 0;
	bool bforBreak = false;
	float fHitDistance = FLT_MAX;
	CGameObject *pSelectedObject = NULL;
	CGameObject *pSelectedMirror = NULL;
	
	CGameObject * pSaveObject = NULL;
	CGameObject * pSaveMirror = NULL;

	for (int k = 0; k < m_nMirror; k++)
	{
		nIntersectedMirror = m_ppMirror[k]->PickObjectByRayIntersection(xmf3PickPosition, xmf4x4View, &fHitDistance);
		if ((nIntersectedMirror > 0) && (fHitDistance < *pfNearHitDistance))
		{
			*pfNearHitDistance = fHitDistance;
			cout << "찾아버리기" << endl;
			pSelectedMirror = m_ppMirror[k];
			pSaveMirror = pSelectedMirror;
			//m_ppMirror[k]->SetPosition(XMFLOAT3(-999, 999, 99999));

		}
	}

	for (int j = 0; j < m_nSphere; j++)
	{
		nIntersected = m_ppSphere[j]->PickObjectByRayIntersection(xmf3PickPosition, xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			*pfNearHitDistance = fHitDistance;
			cout << "찾아버리기" << endl;
			pSelectedObject = m_ppSphere[j];

			if (pSaveMirror != NULL) //평면에 가려질 경우를 생각해줘야함
			{
				cout << " 유후" << endl;
				if (sqrt((pSaveMirror->GetPosition().x - m_pPlayer->GetCamera()->GetPosition().x) * (pSaveMirror->GetPosition().x - m_pPlayer->GetCamera()->GetPosition().x)
					+ (pSaveMirror->GetPosition().y - m_pPlayer->GetCamera()->GetPosition().y) * (pSaveMirror->GetPosition().y - m_pPlayer->GetCamera()->GetPosition().y)
					+ (pSaveMirror->GetPosition().z - m_pPlayer->GetCamera()->GetPosition().z) * (pSaveMirror->GetPosition().z - m_pPlayer->GetCamera()->GetPosition().z)
		> (pSelectedObject->GetPosition().x - m_pPlayer->GetCamera()->GetPosition().x) * (pSelectedObject->GetPosition().x - m_pPlayer->GetCamera()->GetPosition().x)
					+ (pSelectedObject->GetPosition().y - m_pPlayer->GetCamera()->GetPosition().y) * (pSelectedObject->GetPosition().y - m_pPlayer->GetCamera()->GetPosition().y)
					+ (pSelectedObject->GetPosition().z - m_pPlayer->GetCamera()->GetPosition().z) * (pSelectedObject->GetPosition().z - m_pPlayer->GetCamera()->GetPosition().z)))
				{
					for (int k = 0; k < m_nParticle; ++k)
					{

						(*m_ppParticle[k]).SetPosition((*m_ppSphere[j]).GetPosition());
					}

					m_bDoParticle = true;
					m_ppSphere[j]->SetPosition(XMFLOAT3(-999, 999, 99999));
				}
				
			}
			else
			{
				m_bDoParticle = true;
				m_ppSphere[j]->SetPosition(XMFLOAT3(-999, 999, 99999));
			}

		}
	}
	return(pSelectedObject);
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}
void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1; m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
	if (m_ppWall)
	{
		for (int j = 0; j < m_nWall; j++)
		{
			if (m_ppWall[j]) delete m_ppWall[j];
		}
	}
	if (m_ppDoar)
	{
		for (int j = 0; j < m_nDoar; j++)
		{
			if (m_ppDoar[j]) delete m_ppDoar[j];
		}
	}
	if (m_ppSphere)
	{
		for (int j = 0; j < m_nSphere; j++)
		{
			if (m_ppSphere[j]) delete m_ppSphere[j];
		}
	}
	if (m_ppMirror)
	{
		for (int j = 0; j < m_nMirror; j++)
		{
			if (m_ppMirror[j]) delete m_ppMirror[j];
		}
	}
	if (m_ppBullet)
	{
		for (int j = 0; j < m_nBullet; j++)
		{
			if (m_ppBullet[j]) delete m_ppBullet[j];
		}
	}
	if (m_ppParticle)
	{
		for (int j = 0; j < m_nParticle; j++)
		{
			if (m_ppParticle[j]) delete m_ppParticle[j];
		}
	}
}
void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	//cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;

	for (int i = 0; i < m_nBullet; ++i)
	{
		//cout << (*m_ppBullet[i]).ItisShooting << endl;
		if ((*m_ppBullet[i]).ItisShooting == false)
		{
			//m_ppBullet[i]->m_xmOOBB.Center.x << endl;
			(*m_ppBullet[i]).SetPosition(m_pPlayer->m_xmOOBB.Center.x, m_pPlayer->m_xmOOBB.Center.y, m_pPlayer->m_xmOOBB.Center.z);
			(*m_ppBullet[i]).SetMovingDirection(XMFLOAT3(m_pPlayer->GetCamera()->GetLookVector().x, m_pPlayer->GetCamera()->GetLookVector().y, m_pPlayer->GetCamera()->GetLookVector().z));
		}

	}
	////cout << m_bShootState << endl;
	//if (m_bShootState == true)
	//{
	//	for (int i = 0; i < m_nBullet; ++i)
	//	{
	//		if ((*m_ppBullet[i]).ItisShooting == false)
	//		{
	//			(*m_ppBullet[i]).ItisShooting = true;
	//			break;
	//		}
	//	}
	//}
	//m_bShootState = false;

	if (m_bShootState == true)
	{
		for (int i = 0; i < m_nBullet; ++i)
		{
			if ((*m_ppBullet[i]).ItisShooting == false)
			{
				(*m_ppBullet[i]).ItisShooting = true;
				break;
			}
		}
	}
	m_bShootState = false;

	
	//cout << m_pPlayer->GetPosition().x << "\t" << endl;
	//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	//cout << (*m_ppWall)[1].GetRight().x << "\t" << (*m_ppWall)[1].GetRight().y << "\t" << (*m_ppWall)[1].GetRight().z << endl;
	//cout << (*m_ppWall[0]).m_xmOOBB.Center.x << "\t" << (*m_ppWall[0]).m_xmOOBB.Center.y << "\t" << (*m_ppWall[0]).m_xmOOBB.Center.z << endl;
	//벽과 플레이어  부딪혔는가
	//cout << m_pPlayer->Myxmf3Shift.x << "\t" << m_pPlayer->Myxmf3Shift.y << "\t" << m_pPlayer->Myxmf3Shift.z << endl;

	//cout << Myxmf3Shift.x << "\t"  << Myxmf3Shift.y <<"\t" << Myxmf3Shift.z << endl;
	for (int i = 0; i < m_nWall; ++i)
	{

		if ((*m_ppWall[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//cout << i << endl;
			/*cout << "------------------------" << endl;
			cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
			cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
			cout << "------------------------" << endl;*/
			////cout << "벽과 플레이어 충돌 " << endl;
			if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppWall[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}

			//cout << "벽과 플레이어 충돌 " << endl;
			/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
			{
				cout << "오른쪽 면과 충돌" << endl;
			}*/

			if (m_pPlayer->GetPosition().x < m_ppWall[i]->MinX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppWall[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x - 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}


			if (m_pPlayer->GetPosition().z < m_ppWall[i]->MinZ && m_pPlayer->GetPosition().x > m_ppWall[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppWall[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z - 1));
				//cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
			}

			if (m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ && m_pPlayer->GetPosition().x > m_ppWall[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppWall[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z + 1));
				//cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
			}
			//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
			//{
			//	//cout << "앞면과 충돌" << endl;
			//}

		}
		//m_listBullet.erase(iter);
	}

	//for (int i = 0; i < m_nDoar; ++i)
	//{
	//	if ((*m_ppDoar[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
	//	{

	//		cout << "벽과 문 충돌 " << endl;
	//	}
	//	//m_listBullet.erase(iter);
	//}

	//미로 충돌

	for (int i = 0; i < m_nMirror; ++i)
	{

		if ((*m_ppMirror[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//cout << "충돌" << endl;
			//cout << i << endl;
			/*cout << "------------------------" << endl;
			cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
			cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
			cout << "------------------------" << endl;*/
			////cout << "벽과 플레이어 충돌 " << endl;
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
			//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
			//{
			//	//cout << "앞면과 충돌" << endl;
			//}

		}
		//m_listBullet.erase(iter);
	}

	//문 충돌
	for (int i = 0; i < m_nDoar; ++i)
	{

		if ((*m_ppDoar[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//cout << "문 충돌" << endl;
			//cout << i << endl;
			/*cout << "------------------------" << endl;
			cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
			cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
			cout << "------------------------" << endl;*/
			////cout << "벽과 플레이어 충돌 " << endl;
			if (m_pPlayer->GetPosition().x > m_ppDoar[i]->MaxX && m_pPlayer->GetPosition().z > m_ppDoar[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppDoar[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}

			//cout << "벽과 플레이어 충돌 " << endl;
			/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
			{
			cout << "오른쪽 면과 충돌" << endl;
			}*/

			if (m_pPlayer->GetPosition().x < m_ppDoar[i]->MinX && m_pPlayer->GetPosition().z > m_ppDoar[i]->MinZ &&  m_pPlayer->GetPosition().z < m_ppDoar[i]->MaxZ)
			{
				//cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x - 1, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			}


			if (m_pPlayer->GetPosition().z < m_ppDoar[i]->MinZ && m_pPlayer->GetPosition().x > m_ppDoar[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppDoar[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z - 1));
				//cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
			}

			if (m_pPlayer->GetPosition().z > m_ppDoar[i]->MinZ && m_pPlayer->GetPosition().x > m_ppDoar[i]->MinX &&  m_pPlayer->GetPosition().x < m_ppDoar[i]->MaxX)
			{
				m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z + 1));
				//cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
			}
			//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
			//{
			//	//cout << "앞면과 충돌" << endl;
			//}

		}
		//m_listBullet.erase(iter);
	}


	//장애물 과 벽충돌
	//cout << m_ppSphere[0]->m_xmOOBB.Center.x << "\t" << m_ppSphere[0]->m_xmOOBB.Center.y << "\t" << m_ppSphere[0]->m_xmOOBB.Center.z << endl;

	for (int i = 0; i < m_nWall; ++i)
	{
		for (int j = 0; j < m_nSphere; ++j)
		{
			if ((*m_ppWall[i]).m_xmOOBB.Intersects(m_ppSphere[j]->m_xmOOBB))
			{
				cout << "장애물 충돌" << endl;
				//cout << i << endl;
				/*cout << "------------------------" << endl;
				cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
				cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
				cout << "------------------------" << endl;*/
				////cout << "벽과 플레이어 충돌 " << endl;
				if (m_ppSphere[j]->GetPosition().x > m_ppWall[i]->MaxX && m_ppSphere[j]->GetPosition().z > m_ppWall[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppWall[i]->MaxZ)
				{
					
					cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x + 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));
				}

				//cout << "벽과 플레이어 충돌 " << endl;
				/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
				{
				cout << "오른쪽 면과 충돌" << endl;
				}*/

				if (m_ppSphere[j]->GetPosition().x < m_ppWall[i]->MinX && m_ppSphere[j]->GetPosition().z > m_ppWall[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppWall[i]->MaxZ)
				{
					cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x - 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));

				}


				if (m_ppSphere[j]->GetPosition().z < m_ppWall[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppWall[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppWall[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z - 1));
					cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
				}

				if (m_ppSphere[j]->GetPosition().z > m_ppWall[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppWall[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppWall[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z + 1));
					cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
				}
				//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
				//{
				//	//cout << "앞면과 충돌" << endl;
				//}

			}
		}
		//m_listBullet.erase(iter);
	}

	//for (int i = 0; i < m_nDoar; ++i)
	//{
	//	if ((*m_ppDoar[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
	//	{

	//		cout << "벽과 문 충돌 " << endl;
	//	}
	//	//m_listBullet.erase(iter);
	//}

	//장애물과 미로 충돌

	for (int i = 0; i < m_nMirror; ++i)
	{
		for (int j = 0; j < m_nSphere; ++j)
		{
			if ((*m_ppMirror[i]).m_xmOOBB.Intersects(m_ppSphere[j]->m_xmOOBB))
			{
				cout << "충돌" << endl;
				//cout << i << endl;
				/*cout << "------------------------" << endl;
				cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
				cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
				cout << "------------------------" << endl;*/
				////cout << "벽과 플레이어 충돌 " << endl;
				if (m_ppSphere[j]->GetPosition().x > m_ppMirror[i]->MaxX && m_ppSphere[j]->GetPosition().z > m_ppMirror[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppMirror[i]->MaxZ)
				{
					cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x + 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));
				}

				//cout << "벽과 플레이어 충돌 " << endl;
				/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
				{
				cout << "오른쪽 면과 충돌" << endl;
				}*/

				if (m_ppSphere[j]->GetPosition().x < m_ppMirror[i]->MinX && m_ppSphere[j]->GetPosition().z > m_ppMirror[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppMirror[i]->MaxZ)
				{
					cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x - 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));
				}


				if (m_ppSphere[j]->GetPosition().z < m_ppMirror[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppMirror[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppMirror[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z - 1));
					cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
				}

				if (m_ppSphere[j]->GetPosition().z > m_ppMirror[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppMirror[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppMirror[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z + 1));
					cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
				}
				//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
				//{
				//	//cout << "앞면과 충돌" << endl;
				//}

			}
		}
		//m_listBullet.erase(iter);
	}

	//장애물과 문 충돌
	for (int i = 0; i < m_nDoar; ++i)
	{

		for (int j = 0; j < m_nSphere; ++j)
		{


			if ((*m_ppDoar[i]).m_xmOOBB.Intersects(m_ppSphere[j]->m_xmOOBB))
			{
				cout << "문 충돌" << endl;
				//cout << i << endl;
				/*cout << "------------------------" << endl;
				cout << "[" << m_ppWall[i]->MaxX << "]" << "\t " << "[" << m_ppWall[i]->MinX << "]" << endl;
				cout << "[" << m_ppWall[i]->MaxZ << "]" << "\t " << "[" << m_ppWall[i]->MinZ << "]" << endl;
				cout << "------------------------" << endl;*/
				////cout << "벽과 플레이어 충돌 " << endl;
				if (m_ppSphere[j]->GetPosition().x > m_ppDoar[i]->MaxX && m_ppSphere[j]->GetPosition().z > m_ppDoar[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppDoar[i]->MaxZ)
				{
					cout << i << "번쨰 면과 " << "오른쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x + 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));
				}

				//cout << "벽과 플레이어 충돌 " << endl;
				/*if (m_pPlayer->GetPosition().x > m_ppWall[i]->MaxX && m_pPlayer->GetPosition().z > m_ppWall[i]->MinZ)
				{
				cout << "오른쪽 면과 충돌" << endl;
				}*/

				if (m_ppSphere[j]->GetPosition().x < m_ppDoar[i]->MinX && m_ppSphere[j]->GetPosition().z > m_ppDoar[i]->MinZ &&  m_ppSphere[j]->GetPosition().z < m_ppDoar[i]->MaxZ)
				{
					cout << i << "번쨰 면과 " << "왼쪽 면과 충돌" << endl;
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x - 1, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z));
				}


				if (m_ppSphere[j]->GetPosition().z < m_ppDoar[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppDoar[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppDoar[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z - 1));
					cout << i << "번쨰 면과 " << "아래 면과 충돌" << endl;
				}

				if (m_ppSphere[j]->GetPosition().z > m_ppDoar[i]->MinZ && m_ppSphere[j]->GetPosition().x > m_ppDoar[i]->MinX &&  m_ppSphere[j]->GetPosition().x < m_ppDoar[i]->MaxX)
				{
					m_ppSphere[j]->SetPosition(XMFLOAT3(m_ppSphere[j]->GetPosition().x, m_ppSphere[j]->GetPosition().y, m_ppSphere[j]->GetPosition().z + 1));
					cout << i << "번쨰 면과 " << "윗 면과 충돌" << endl;
				}
				//if (m_pPlayer->GetPosition().z < m_ppWall[i]->GetPosition().z)
				//{
				//	//cout << "앞면과 충돌" << endl;
				//}

			}
		}
		//m_listBullet.erase(iter);
	}











	//플레이어와 적이 일정거리 이하가 됬을때
	
	for (int i = 0; i < SPHERESIZE; ++i)
	{
		if (sqrt(((m_pPlayer->m_xmOOBB.Center.x - m_ppSphere[i]->m_xmOOBB.Center.x) * (m_pPlayer->m_xmOOBB.Center.x - m_ppSphere[i]->m_xmOOBB.Center.x) + (m_pPlayer->m_xmOOBB.Center.y - m_ppSphere[i]->m_xmOOBB.Center.y) * (m_pPlayer->m_xmOOBB.Center.y - m_ppSphere[i]->m_xmOOBB.Center.y) + (m_pPlayer->m_xmOOBB.Center.z - m_ppSphere[i]->m_xmOOBB.Center.z) * (m_pPlayer->m_xmOOBB.Center.z - m_ppSphere[i]->m_xmOOBB.Center.z) < 5000)))
		{
			
			//m_ppSphere[i]->MoveForward();
			//m_ppSphere[i]->SetPosition(XMFLOAT3(m_pPlayer->GetPosition()));
			m_ppSphere[i]->MoveToPlayer(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppSphere[i]->GetPosition()), 0.0019f);

			m_ppSphere[i]->MinX = m_ppSphere[i]->GetPosition().x - 5.0f;
			m_ppSphere[i]->MaxX = m_ppSphere[i]->GetPosition().x + 5.0f;
			m_ppSphere[i]->MinZ = m_ppSphere[i]->GetPosition().z - 5.0f;
			m_ppSphere[i]->MaxZ = m_ppSphere[i]->GetPosition().z + 5.0f;
			m_ppSphere[i]->SetOOBB(m_ppSphere[i]->GetPosition(), XMFLOAT3(10, 10, 10), XMFLOAT4(0, 0, 0, 1));
			//cout << "따라와" << endl;
		}
	}



	//여기서부턴 객체들끼리 충돌체크
	for (int i = 0; i < m_nSphere; i++) (*m_ppSphere[i]).m_pCollider = NULL;
	for (int i = 0; i < m_nSphere; i++)
	{
		for (int j = (i + 1); j < m_nSphere; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if ((*m_ppSphere[i]).m_xmOOBB.Intersects((*m_ppSphere[j]).m_xmOOBB))
			{
				
				(*m_ppSphere[i]).m_pCollider = &(*m_ppSphere[j]);
				(*m_ppSphere[j]).m_pCollider = &(*m_ppSphere[i]);
			}
		}
	}
	for (int i = 0; i < m_nSphere; i++)
	{
		if ((*m_ppSphere[i]).m_pCollider && (*m_ppSphere[i]).m_pCollider->m_pCollider) //충돌한 정보가 있으면
		{
			//서로의 무빙디렉션을 바꿔주겠다.
			cout << "서로충돌" << endl;
			/*XMFLOAT3 xmf3MovingDirection = (*m_ppSphere[i]).m_xmf3MovingDirection;
			float fMovingSpeed = (*m_ppSphere[i]).m_fMovingSpeed;
			(*m_ppSphere[i]).m_xmf3MovingDirection = (*m_ppSphere[i]).m_pCollider->m_xmf3MovingDirection;
			(*m_ppSphere[i]).m_fMovingSpeed = (*m_ppSphere[i]).m_pCollider->m_fMovingSpeed;
			(*m_ppSphere[i]).m_pCollider->m_xmf3MovingDirection = xmf3MovingDirection;
			(*m_ppSphere[i]).m_pCollider->m_fMovingSpeed = fMovingSpeed;
			(*m_ppSphere[i]).m_pCollider->m_pCollider = NULL;
			(*m_ppSphere[i]).m_pCollider = NULL;*/
			//(*m_ppSphere[i]).SetPosition((*m_ppSphere[i]).GetPosition().x+0.4, (*m_ppSphere[i]).GetPosition().y, (*m_ppSphere[i]).GetPosition().z + 0.4);
			m_ppSphere[i]->Move(Vector3::Normalize(Vector3::Subtract(m_ppSphere[i]->m_pCollider->m_pCollider->GetPosition(),m_ppSphere[i]->m_pCollider->GetPosition() )), true);
				//m_pPlayer->Move(Vector3::Normalize(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppSphere[j]->GetPosition())), true);
			break;
		}
	}

	//장애물과 플레이어 충돌
	for (int j = 0; j < m_nSphere; ++j)
	{


		if (m_pPlayer->m_xmOOBB.Intersects(m_ppSphere[j]->m_xmOOBB))
		{
			for (int k = 0; k < m_nParticle; ++k)
			{

				(*m_ppParticle[k]).SetPosition(m_pPlayer->GetPosition());
			}
		
		/*	
			cout << "-----------------" << endl;
			cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
			cout << m_ppSphere[j]->GetPosition().x << "\t" << m_ppSphere[j]->GetPosition().y << "\t" << m_ppSphere[j]->GetPosition().z << endl;
			cout << "-----------------" << endl;*/
			
			
			m_pPlayer->Move(Vector3::Normalize(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppSphere[j]->GetPosition())),true);
			//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x	+ (m_pPlayer->GetPosition().x - (m_ppSphere[j]->GetPosition().x))		, m_pPlayer->GetPosition().y + (m_pPlayer->GetPosition().y - (m_ppSphere[j]->GetPosition().y)), m_pPlayer->GetPosition().z + (m_pPlayer->GetPosition().z - (m_ppSphere[j]->GetPosition().z))));
			//m_pPlayer->MoveToPlayer(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppSphere[j]->GetPosition()), 100.05f);
			//cout << "충돌" << endl;
			m_bDoParticle = true;
			break;
		}
	}



	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
	for (int j = 0; j < m_nParticle; j++)
	{
		if (m_bDoParticle == true)
			m_ppParticle[j]->Animate(fTimeElapsed);
	}
}
void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
			m_ppObjects[j]->ReleaseUploadBuffers();
	}
}
void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
	for (int j = 0; j < m_nWall; j++)
	{
		if (m_ppWall[j])
		{
			m_ppWall[j]->Render(pd3dCommandList, pCamera);
		}
	}
	for (int j = 0; j < m_nDoar; j++)
	{
		if (m_ppDoar[j])
		{
			m_ppDoar[j]->Render(pd3dCommandList, pCamera);
		}
	}

	for (int j = 0; j < m_nSphere; j++)
	{
		if (m_ppSphere)
		{
			m_ppSphere[j]->Render(pd3dCommandList, pCamera);
		}
	}

	for (int j = 0; j < m_nMirror; j++)
	{
		if (m_ppMirror)
		{
			m_ppMirror[j]->Render(pd3dCommandList, pCamera);
		}
	}
	for (int j = 0; j < m_nBullet; j++)
	{
		if (m_ppBullet[j])
		{
			if ((*m_ppBullet[j]).ItisShooting == true)
				m_ppBullet[j]->Render(pd3dCommandList, pCamera);
		}
	}

	for (int j = 0; j < m_nParticle; j++)
	{
		if (m_ppParticle[j])
		{
			m_ppParticle[j]->Render(pd3dCommandList, pCamera);
		}
	}
}
