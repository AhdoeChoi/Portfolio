#include "stdafx.h"
#include "Shader.h"
#include "Player.h"

CShader::CShader()
{
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
	//d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;

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
{ return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob)); }
D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}
void CPlayerShader	::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}
CObjectsShader::CObjectsShader() 
{
	m_bDoParticle = false;
	m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, 50.0f);
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
void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) 
{ 
	////가로x세로x높이가 12x12x12인 정육면체 메쉬를 생성한다. 
	//CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
	///*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/ 
	//int xObjects = 10, yObjects = 10, zObjects = 10, i = 0;
	////x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	//m_nObjects = (xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	//m_ppObjects = new CGameObject*[m_nObjects];
	//float fxPitch = 12.0f * 2.5f;
	//float fyPitch = 12.0f * 2.5f;
	//float fzPitch = 12.0f * 2.5f;
	//CRotatingObject *pRotatingObject = NULL;
	//for (int x = -xObjects; x <= xObjects; x++)
	//{
	//	for (int y = -yObjects; y <= yObjects; y++)
	//	{
	//		for (int z = -zObjects; z <= zObjects; z++) 
	//		{
	//			pRotatingObject = new CRotatingObject(); pRotatingObject->SetMesh(pCubeMesh); //각 정육면체 객체의 위치를 설정한다. 
	//			pRotatingObject->SetPosition(fxPitch*x, fyPitch*y, fzPitch*z);
	//			pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//			pRotatingObject->SetRotationSpeed(10.0f*(i % 10) + 3.0f); 
	//			m_ppObjects[i++] = pRotatingObject;
	//		}
	//	}
	//}
	//CreateShaderVariables(pd3dDevice, pd3dCommandList);


	//벽 생성
	//가로x세로x높이가 12x12x12인 정육면체 메쉬를 생성한다. 
	CWallMeshDiffused *pWallMesh = new CWallMeshDiffused(pd3dDevice, pd3dCommandList, 110.0f, 110.0f, 40.0f);
	/*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/ 
	//int xObjects = 10, yObjects = 10, zObjects = 10, i = 0;
	//x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	m_nWall = 6;
	m_ppWall = new CGameObject*[m_nWall];

	CRotatingObject *pWallObject = NULL;

	int i = 0;
	for (int j = 0; j < m_nWall; ++j)
	{
		pWallObject = new CRotatingObject();
		pWallObject->SetMesh(pWallMesh); //각 정육면체 객체의 위치를 설정한다. 
		pWallObject->SetPosition(0, 0, j*40);
		//pRotatingObject->SetPosition(0, 0, 0);
		//pWallObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		//pWallObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
		m_ppWall[i++] = pWallObject;

	}



	//장애물 생성 
	CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 4.0f);
	/*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/
	//int xObjects = 3, yObjects = 3, zObjects = 10, i = 0;
	i = 0;
	//x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	m_nObjects = OBJECTSIZE;
	m_ppObjects = new CGameObject*[m_nObjects];
	//float fxPitch = 12.0f * 2.5f;
	//float fyPitch = 12.0f * 2.5f;
	//float fzPitch = 12.0f * 2.5f;

	
	default_random_engine dre;
	uniform_int<> uiColor(0, 120);
	uniform_real_distribution<> urPosition(-35.f, 35.f);
	uniform_real_distribution<> urSpeed(0.03f, 0.08f);
	uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌
	CRotatingObject *pRotatingObject = NULL;

	for (int j = 0; j < m_nObjects; ++j)
	{
		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh(pCubeMesh); //각 정육면체 객체의 위치를 설정한다. 
		pRotatingObject->SetPosition(urPosition(dre), urPosition(dre), urPosition(dre));
		//pRotatingObject->SetPosition(0, 0, 0);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(urSpeed(dre) );
		pRotatingObject->SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
		//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
		pRotatingObject->SetMovingSpeed(urSpeed(dre));
		pRotatingObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		m_ppObjects[i++] = pRotatingObject;
	}


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
		pBulletObject->SetMesh(pBulletMesh); //각 정육면체 객체의 위치를 설정한다. 
		pBulletObject->SetPosition(0,0,-9999);
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

	CRotatingObject *pParticleObject = NULL;

	

	for (int j = 0; j < m_nParticle; ++j)
	{
		pParticleObject = new CRotatingObject();
		pParticleObject->SetMesh(pParticleMesh); //각 정육면체 객체의 위치를 설정한다. 
		pParticleObject->SetPosition(0, 0, -9999);
		//pRotatingObject->SetPosition(0, 0, 0);
		pParticleObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pParticleObject->SetRotationSpeed(0.5);
		pParticleObject->SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
		//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
		pParticleObject->SetMovingSpeed(4.5);
		pParticleObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		m_ppParticle[i++] = pParticleObject;
	}


	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	
	//if (m_bShootState == false)
	//{
	//	CRotatingObject *bullet = new CRotatingObject;

	//	CCubeMeshDiffused *pBulletCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 4.0f);

	//	bullet->SetMesh(pBulletCubeMesh);
	//	//bullet->SetPosition(m_pPlayer->GetPosition());
	//	bullet->SetPosition(0, 0, 0);

	//	//bullet->SetRotationAxis(m_pPlayer->GetLook());
	//	bullet->SetRotationAxis(XMFLOAT3(0, 1, 0));

	//	bullet->SetRotationSpeed(1.9f);
	//	//bullet->SetMovingDirection(m_pPlayer->GetLook());
	//	bullet->SetMovingDirection(XMFLOAT3(0, 0, 1));

	//	bullet->SetMovingSpeed(0.3f);
	//	bullet->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	//	m_listBullet.push_back(bullet);
	//	cout << bullet->GetPosition().x << endl;
	//	//for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)//총알 순회하며 삭제
	//	//{
	//	//	cout << (*iter)->GetPosition().z << endl;
	//	//}
	//	m_bShootState = true;
	//}
		

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
		delete[] m_ppWall;
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
	//총알처리


	//for (int i = 0; i < m_nBullet; ++i)
	//{
	//	//cout << (*m_ppBullet[i]).ItisShooting << endl;
	//	
	//	cout << (*m_ppBullet[i]).m_xmOOBB.Center.x << "\t" <<  (*m_ppBullet[i]).m_xmOOBB.Center.y << "\t" <<  (*m_ppBullet[i]).m_xmOOBB.Center.z << endl;
	//

	//}


	for (int i = 0; i < m_nBullet; ++i)
	{
		//cout << (*m_ppBullet[i]).ItisShooting << endl;
		if ((*m_ppBullet[i]).ItisShooting == false)
		{
			(*m_ppBullet[i]).SetPosition(m_pPlayer->m_xmOOBB.Center.x, m_pPlayer->m_xmOOBB.Center.y, m_pPlayer->m_xmOOBB.Center.z);
			(*m_ppBullet[i]).SetMovingDirection(XMFLOAT3(m_pPlayer->GetCamera()->GetLookVector().x, m_pPlayer->GetCamera()->GetLookVector().y, m_pPlayer->GetCamera()->GetLookVector().z));
		}
	
	}
	//cout << m_bShootState << endl;
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



	//cout << m_pPlayer->GetPosition().z << endl;
	//무한한 공간

	if (m_pPlayer->GetPosition().z >  (*m_ppWall[0]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));

		(*m_ppWall[0]).SetPosition((*m_ppWall[5]).GetPosition().x, (*m_ppWall[5]).GetPosition().y, (*m_ppWall[5]).GetPosition().z + 40);

	}
	if (m_pPlayer->GetPosition().z > (*m_ppWall[1]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[1]).SetPosition((*m_ppWall[1]).GetPosition().x, (*m_ppWall[1]).GetPosition().y, (*m_ppWall[0]).GetPosition().z + 40);

	}
	if (m_pPlayer->GetPosition().z > (*m_ppWall[2]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[2]).SetPosition((*m_ppWall[1]).GetPosition().x, (*m_ppWall[1]).GetPosition().y, (*m_ppWall[1]).GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > (*m_ppWall[3]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[3]).SetPosition((*m_ppWall[2]).GetPosition().x, (*m_ppWall[2]).GetPosition().y, (*m_ppWall[2]).GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > (*m_ppWall[4]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[4]).SetPosition((*m_ppWall[3]).GetPosition().x, (*m_ppWall[3]).GetPosition().y, (*m_ppWall[3]).GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > (*m_ppWall[5]).GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[5]).SetPosition((*m_ppWall[4]).GetPosition().x, (*m_ppWall[4]).GetPosition().y, (*m_ppWall[4]).GetPosition().z + 40);
	}
	

	////뒤로

	if (m_pPlayer->GetPosition().z < (*m_ppWall[0]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[5]).SetPosition((*m_ppWall[0]).GetPosition().x, (*m_ppWall[0]).GetPosition().y, (*m_ppWall[0]).GetPosition().z - 40);

	}
	if (m_pPlayer->GetPosition().z < (*m_ppWall[5]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[4]).SetPosition((*m_ppWall[5]).GetPosition().x, (*m_ppWall[5]).GetPosition().y, (*m_ppWall[5]).GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < (*m_ppWall[4]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[3]).SetPosition((*m_ppWall[4]).GetPosition().x, (*m_ppWall[4]).GetPosition().y, (*m_ppWall[4]).GetPosition().z - 40);
	}

	if (m_pPlayer->GetPosition().z < (*m_ppWall[3]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[2]).SetPosition((*m_ppWall[3]).GetPosition().x, (*m_ppWall[3]).GetPosition().y, (*m_ppWall[3]).GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < (*m_ppWall[2]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[1]).SetPosition((*m_ppWall[2]).GetPosition().x, (*m_ppWall[2]).GetPosition().y, (*m_ppWall[2]).GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < (*m_ppWall[1]).GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		(*m_ppWall[0]).SetPosition((*m_ppWall[1]).GetPosition().x, (*m_ppWall[1]).GetPosition().y, (*m_ppWall[1]).GetPosition().z - 40);
	}


	//내 뒤에있는 객체 처리
	for (int i = 0; i < m_nObjects; ++i)
	{
		if (m_pPlayer->GetPosition().z - 10 > (*m_ppObjects[i]).GetPosition().z)
		{
			(*m_ppObjects[i]).SetPosition(XMFLOAT3((*m_ppObjects[i]).GetPosition().x, (*m_ppObjects[i]).GetPosition().y, (*m_ppObjects[i]).GetPosition().z + 80));
		}
	}


	if (m_bShootState)
	{
		//cout << " 발사를 해븐것이여" << endl;

	}
	else
	{
		//cout << "발사 안한것이여" << endl;
	}
	//for (auto iter = CObjectsShader::m_listBullet.begin(); iter != CObjectsShader::m_listBullet.end(); ++iter)//총알 순회하며 삭제
	//{
	//	cout << (*iter)->GetPosition().x << "\t" <<  (*iter)->GetPosition().y << "\t" << (*iter)->GetPosition().z << endl;
	//}
	for (int j = 0; j < m_nObjects; j++) 
	{ 
		m_ppObjects[j]->Animate(fTimeElapsed); 
	} 

	for (int j = 0; j < m_nBullet; j++)
	{
		m_ppBullet[j]->Animate(fTimeElapsed);
	}
	for (int j = 0; j < m_nParticle; j++)
	{
		if(m_bDoParticle == true)
		m_ppParticle[j]->Animate(fTimeElapsed);
	}

	//장애물이 벽에 부딪혔는가
	for (int i = 0; i < m_nObjects; i++) //각 객체들에 대해서 충돌체크를 함
	{
	
		ContainmentType containType = (*m_ppWall)->m_xmOOBB.Contains((*m_ppObjects[i]).m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
		switch (containType)
		{
		case DISJOINT: //벽을 뚫고 지나간경우
		{

			int nPlaneIndex = -1;
			for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
			{
				PlaneIntersectionType intersectType = (*m_ppObjects[i]).m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
				if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
				{
					nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
					break;
				}
			}
			if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
			{
				// 반사시키는 행위임 이게
				XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&(*m_ppObjects[i]).m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&(*m_ppObjects[i]).m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 4; j++)
			{
				PlaneIntersectionType intersectType = (*m_ppObjects[i]).m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&(*m_ppObjects[i]).m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&(*m_ppObjects[i]).m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
	//여기서부턴 객체들끼리 충돌체크
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
	
		//cout << (*m_ppObjects[i]).m_pCollider->m_fMovingSpeed <<"\t" << (*m_ppObjects[i]).m_pCollider->m_pCollider->m_fMovingSpeed << endl;
		if ((*m_ppObjects[i]).m_pCollider && (*m_ppObjects[i]).m_pCollider->m_pCollider) //충돌한 정보가 있으면
		{
	
			//서로의 무빙디렉션을 바꿔주겠다.
		
			XMFLOAT3 xmf3MovingDirection = (*m_ppObjects[i]).m_xmf3MovingDirection;
			float fMovingSpeed = (*m_ppObjects[i]).m_fMovingSpeed;
			(*m_ppObjects[i]).m_xmf3MovingDirection = (*m_ppObjects[i]).m_pCollider->m_xmf3MovingDirection;
			(*m_ppObjects[i]).m_fMovingSpeed = (*m_ppObjects[i]).m_pCollider->m_fMovingSpeed;
			(*m_ppObjects[i]).m_pCollider->m_xmf3MovingDirection = xmf3MovingDirection;
			(*m_ppObjects[i]).m_pCollider->m_fMovingSpeed = fMovingSpeed;
			(*m_ppObjects[i]).m_pCollider->m_pCollider = NULL;
			(*m_ppObjects[i]).m_pCollider = NULL;
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
	
		//cout << (*m_ppObjects[i]).m_pCollider->m_fMovingSpeed <<"\t" << (*m_ppObjects[i]).m_pCollider->m_pCollider->m_fMovingSpeed << endl;
		if ((*m_ppObjects[i]).m_pCollider && (*m_ppObjects[i]).m_pCollider->m_pCollider) //충돌한 정보가 있으면
		{
	
			//서로의 무빙디렉션을 바꿔주겠다.
		
			XMFLOAT3 xmf3MovingDirection = (*m_ppObjects[i]).m_xmf3MovingDirection;
			float fMovingSpeed = (*m_ppObjects[i]).m_fMovingSpeed;
			(*m_ppObjects[i]).m_xmf3MovingDirection = (*m_ppObjects[i]).m_pCollider->m_xmf3MovingDirection;
			(*m_ppObjects[i]).m_fMovingSpeed = (*m_ppObjects[i]).m_pCollider->m_fMovingSpeed;
			(*m_ppObjects[i]).m_pCollider->m_xmf3MovingDirection = xmf3MovingDirection;
			(*m_ppObjects[i]).m_pCollider->m_fMovingSpeed = fMovingSpeed;
			(*m_ppObjects[i]).m_pCollider->m_pCollider = NULL;
			(*m_ppObjects[i]).m_pCollider = NULL;
		}
	}
	
	////벽과 비행기 충돌 -3인칭
	//ContainmentType containType = (*m_ppWall)->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
	//switch (containType)
	//{
	//case DISJOINT: //벽을 뚫고 지나간경우
	//{
	//	int nPlaneIndex = -1;
	//	for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
	//	{
	//		PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//		if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
	//		{
	//			nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
	//			break;
	//		}
	//	}
	//	if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
	//	{


	//		XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
	//		XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection), xmvNormal);
	//		XMStoreFloat3(&(m_pPlayer->m_xmf3MovingDirection), xmvReflect);
	//		cout << " 충돌" << endl;

	//		//m_pPlayer->SetPosition(XMFLOAT3(m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f, m_pxmf4WallPlanes[nPlaneIndex].y* 0.2f, m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f));
	//		m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
	//		//m_pCamera->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));



	//	}
	//	break;
	//}
	//case INTERSECTS:
	//{
	//	int nPlaneIndex = -1;
	//	for (int j = 0; j < 4; j++)
	//	{
	//		PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//		if (intersectType == INTERSECTING)
	//		{
	//			nPlaneIndex = j;
	//			break;
	//		}
	//	}

	//	break;
	//}
	//case CONTAINS:

	//	break;
	//}

	

	////벽과 비행기 충돌 -1 카메라
	//ContainmentType containType = (*m_ppWall)->m_xmOOBB.Contains(m_pPlayer->GetCamera()->m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
	//switch (containType)
	//{
	//case DISJOINT: //벽을 뚫고 지나간경우
	//{
	//	int nPlaneIndex = -1;
	//	for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
	//	{
	//		PlaneIntersectionType intersectType = m_pPlayer->GetCamera()->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//		if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
	//		{
	//			nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
	//			break;
	//		}
	//	}
	//	if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
	//	{


	//		XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
	//		XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection), xmvNormal);
	//		XMStoreFloat3(&(m_pPlayer->m_xmf3MovingDirection), xmvReflect);
	//		cout << " 충돌" << endl;

	//		
	//		//m_pPlayer->Setxmf3Position(XMFLOAT3(m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f, m_pxmf4WallPlanes[nPlaneIndex].y* 0.2f, m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f));
	//		//m_pPlayer->SetCamera(m_pPlayer->GetCamera());
	//		//m_pPlayer->SetPosition(XMFLOAT3(m_m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f;pPlayer->GetPosition().x + m_pPlayer->GetPosition().x * m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f, m_pPlayer->GetPosition().y + m_pPlayer->GetPosition().y * m_pxmf4WallPlanes[nPlaneIndex].y * 0.2f, m_pPlayer->GetPosition().z + m_pPlayer->GetPosition().z * m_pxmf4WallPlanes[nPlaneIndex].z * 0.2f));

	//		//m_pPlayer->SetPosition(XMFLOAT3(rand() % 3, rand() % 3, rand() % 3));

	//		//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->m_xmOOBB.Center.x, m_pPlayer->GetCamera()->m_xmOOBB.Center.y, m_pPlayer->GetCamera()->m_xmOOBB.Center.z));
	//		//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetCamera()->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetCamera()->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
	//		//m_pPlayer->GetCamera()->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetCamera()->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetCamera()->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
	//		//m_pPlayer->SetPosition()
	//		//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x +m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
	//		//cout << m_pPlayer->GetPosition().x << "\t " << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	//		//m_pPlayer->GetCamera()->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
	//		//m_pPlayer->Setxmf3Position(XMFLOAT3(0, 0,0));
	//		//cout << m_pPlayer->m_xmOOBB.Center.x << " \t " << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
	//		//cout << m_pxmf4WallPlanes[nPlaneIndex].x << "\t" << m_pxmf4WallPlanes[nPlaneIndex].y << "\t" << m_pxmf4WallPlanes[nPlaneIndex].z << endl;
	//		//cout << m_pPlayer->GetCamera()->m_xmOOBB.Center.x << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.y << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.z << endl;
	//		//m_pPlayer->Setxmf3Position(XMFLOAT3((m_pPlayer->GetCamera()->m_xmOOBB.Center.x) *(m_pxmf4WallPlanes[nPlaneIndex].x)*0.5, m_pPlayer->GetCamera()->m_xmOOBB.Center.y *m_pxmf4WallPlanes[nPlaneIndex].y*0.5, m_pPlayer->GetCamera()->m_xmOOBB.Center.z *m_pxmf4WallPlanes[nPlaneIndex].z*0.5));
	//		//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
	//		//cout << (m_pPlayer->GetCamera()->m_xmOOBB.Center.x) *(m_pxmf4WallPlanes[nPlaneIndex].x)*0.5 << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.y *m_pxmf4WallPlanes[nPlaneIndex].y*0.5 << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.z *m_pxmf4WallPlanes[nPlaneIndex].z*0.5 << endl;
	//		/*cout << m_pPlayer->GetPosition().x << "\t " << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << " !!!" << endl;
	//		cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;*/

	//	}
	//	break;
	//}
	//case INTERSECTS:
	//{
	//	int nPlaneIndex = -1;
	//	for (int j = 0; j < 4; j++)
	//	{
	//		PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//		if (intersectType == INTERSECTING)
	//		{
	//			nPlaneIndex = j;
	//			break;
	//		}
	//	}

	//	break;
	//}
	//case CONTAINS:

	//	break;
	//}

	//벽과 비행기충돌 - 플레이어
	//벽과 비행기 충돌 -1
	ContainmentType containType = (*m_ppWall)->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
	switch (containType)
	{
	case DISJOINT: //벽을 뚫고 지나간경우
	{
		int nPlaneIndex = -1;
		for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
			if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
			{
				nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
				break;
			}
		}
		if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
		{


			XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
			XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection), xmvNormal);
			XMStoreFloat3(&(m_pPlayer->m_xmf3MovingDirection), xmvReflect);
			//cout << " 충돌" << endl;

			m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x * 2.2f, m_pPlayer->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y * 2.2f, m_pPlayer->GetPosition().z +  m_pxmf4WallPlanes[nPlaneIndex].z * 2.2f));

			//cout << m_pPlayer->GetPosition().x +  m_pxmf4WallPlanes[nPlaneIndex].x * 1.2f << "\t" << m_pPlayer->GetPosition().y +  m_pxmf4WallPlanes[nPlaneIndex].y * 1.2f << "\t" << m_pPlayer->GetPosition().z * m_pxmf4WallPlanes[nPlaneIndex].z * 1.2f << endl;
			//cout << m_pxmf4WallPlanes[nPlaneIndex].x << "\t " << m_pxmf4WallPlanes[nPlaneIndex].y << "\t" << m_pxmf4WallPlanes[nPlaneIndex].z << "\t " << endl;
			//m_pPlayer->Setxmf3Position(XMFLOAT3(m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f, m_pxmf4WallPlanes[nPlaneIndex].y* 0.2f, m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f));
			//m_pPlayer->SetPosition(XMFLOAT3(m_m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f;pPlayer->GetPosition().x + m_pPlayer->GetPosition().x * m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f, m_pPlayer->GetPosition().y + m_pPlayer->GetPosition().y * m_pxmf4WallPlanes[nPlaneIndex].y * 0.2f, m_pPlayer->GetPosition().z + m_pPlayer->GetPosition().z * m_pxmf4WallPlanes[nPlaneIndex].z * 0.2f));

			//m_pPlayer->SetPosition(XMFLOAT3(rand() % 3, rand() % 3, rand() % 3));

			//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->m_xmOOBB.Center.x, m_pPlayer->GetCamera()->m_xmOOBB.Center.y, m_pPlayer->GetCamera()->m_xmOOBB.Center.z));
			//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetCamera()->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetCamera()->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
			//m_pPlayer->GetCamera()->SetPosition(XMFLOAT3(m_pPlayer->GetCamera()->GetPosition().x + m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetCamera()->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetCamera()->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
			//m_pPlayer->SetPosition()
			//m_pPlayer->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x +m_pxmf4WallPlanes[nPlaneIndex].x, m_pPlayer->GetPosition().y + m_pxmf4WallPlanes[nPlaneIndex].y, m_pPlayer->GetPosition().z + m_pxmf4WallPlanes[nPlaneIndex].z));
			//cout << m_pPlayer->GetPosition().x << "\t " << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
			//m_pPlayer->GetCamera()->SetPosition(XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z));
			//m_pPlayer->Setxmf3Position(XMFLOAT3(0, 0,0));
			//cout << m_pPlayer->m_xmOOBB.Center.x << " \t " << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
			//cout << m_pxmf4WallPlanes[nPlaneIndex].x << "\t" << m_pxmf4WallPlanes[nPlaneIndex].y << "\t" << m_pxmf4WallPlanes[nPlaneIndex].z << endl;
			//cout << m_pPlayer->GetCamera()->m_xmOOBB.Center.x << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.y << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.z << endl;
			//m_pPlayer->Setxmf3Position(XMFLOAT3((m_pPlayer->GetCamera()->m_xmOOBB.Center.x) *(m_pxmf4WallPlanes[nPlaneIndex].x)*0.5, m_pPlayer->GetCamera()->m_xmOOBB.Center.y *m_pxmf4WallPlanes[nPlaneIndex].y*0.5, m_pPlayer->GetCamera()->m_xmOOBB.Center.z *m_pxmf4WallPlanes[nPlaneIndex].z*0.5));
			//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
			//cout << (m_pPlayer->GetCamera()->m_xmOOBB.Center.x) *(m_pxmf4WallPlanes[nPlaneIndex].x)*0.5 << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.y *m_pxmf4WallPlanes[nPlaneIndex].y*0.5 << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.z *m_pxmf4WallPlanes[nPlaneIndex].z*0.5 << endl;
			/*cout << m_pPlayer->GetPosition().x << "\t " << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << " !!!" << endl;
			cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;*/

		}
		break;
	}
	case INTERSECTS:
	{
		int nPlaneIndex = -1;
		for (int j = 0; j < 4; j++)
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
			if (intersectType == INTERSECTING)
			{
				nPlaneIndex = j;
				break;
			}
		}

		break;
	}
	case CONTAINS:

		break;
	}



	//cout << m_pPlayer->m_xmOOBB.Center.x << "\t " << m_pPlayer->m_xmOOBB.Center.y << "\t " << m_pPlayer->m_xmOOBB.Center.z << endl;


	//cout << m_pPlayer->GetPosition().x << "\t " << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << " !!!" << endl;
	//cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;

	//cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;
	//cout << m_pPlayer->GetCamera()->m_xmOOBB.Center.x << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.y << "\t" << m_pPlayer->GetCamera()->m_xmOOBB.Center.z << endl;



	//장애물과 플레이어 충돌
	//비행기와 장애물 충돌
	
	for (int i = 0; i < m_nObjects; ++i)
	{
		/*if (m_pPlayer->m_xmOOBB.Intersects(m_pObjects[i].m_xmOOBB))*/
		if ((*m_ppObjects[i]).m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//m_pPlayer->m_bCrushState = true;
			m_bCrushListObject[i] = true;
			//(*m_ppObjects[i]).SetPosition(-44444, -4444, -444);
		}
		else
			m_bCrushListObject[i] = false;

	}
	bool bDoseItCrush = false;

	for (int i = 0; i < OBJECTSIZE; ++i)
	{
		if (m_bCrushListObject[i] == true)
			bDoseItCrush = true;

	}
	//cout << m_pPlayer->m_bCrushState << endl;
	//cout << bDoseItCrush << endl;
	if (bDoseItCrush == true)
	{
	/*	default_random_engine dre;
		uniform_int<> uiColor(55, 255);
		uniform_real_distribution<> urPosition(-35.f, 35.f);
		uniform_real_distribution<> urSpeed(0.02f, 0.05f);
		uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);*/
		m_pPlayer->SetPosition(XMFLOAT3(0, 0, 0));
		for (int i = 0; i < m_nObjects; ++i)
		{

			//exit(-1);
			cout << "충돌 " << endl;
		}
			

	}
	//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;


	//총알과 장애물 충돌
	/*for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)
	{
		for (int i = 0; i < OBJECTSIZE; ++i)
		{
			if ((*m_ppObjects[i]).m_xmOOBB.Intersects((*iter)->m_xmOOBB))
			{
				(*m_ppObjects[i]).m_bLifeState = DEATH;
				cout << "미사일 장애물 충돌" << endl;
			}
		}
	}*/
	for (int i = 0; i < m_nBullet; ++i)
	{
		for (int j = 0; j < OBJECTSIZE; ++j)
		{
			
			if ((*m_ppObjects[j]).m_xmOOBB.Intersects((*m_ppBullet[i]).m_xmOOBB))
			{
				if (((*m_ppBullet[i]).ItisShooting == true))
				{
					(*m_ppObjects[j]).m_bLifeState = DEATH;
					cout << "미사일과 장애물 충돌 " << endl;
				}
				//m_listBullet.erase(iter);
			}
		}
	}


	 //총알 맞은 객체는 다시 뒤로 보내자
	for (int i = 0; i < OBJECTSIZE; ++i)
	{
		if ((*m_ppObjects[i]).m_bLifeState == DEATH)
		{
			
			////파티클을 생성하고

			////CWallMeshDiffused *pParticleCubeMesh = new CWallMeshDiffused(pd3dDevice, pd3dCommandList, 1.0f, 1.0f, 1.0f);

			//default_random_engine dre;
			//uniform_real_distribution<> urSpeed(0.6f, 1.0f);
			//uniform_real_distribution<> urMovingDirect(-10.0, 10.0f);
			//uniform_int<> uiColor(55, 255);

			//m_nParticle = 64;
			//m_ppParticle = new CGameObject*[m_nParticle];
			//for (int j = 0; j < m_nParticle; ++j)
			//{

			//	//(*m_ppParticle[j]).SetMesh(pParticleCubeMesh);
			//	(*m_ppParticle[j]).SetPosition((*m_ppObjects[i]).GetPosition());
			//
			//	//m_pParticle[j].SetRotationSpeed(0.5);
			//	(*m_ppParticle[j]).SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
			//	(*m_ppParticle[j]).SetMovingSpeed(urSpeed(dre));
			//	//m_pParticle[i].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			//}
			for (int j = 0; j < m_nParticle; ++j)
			{
				
				(*m_ppParticle[j]).SetPosition((*m_ppObjects[i]).GetPosition());
				
				
			}
			m_bDoParticle = true;
			//뒤로 보내자
			(*m_ppObjects[i]).SetPosition(XMFLOAT3((*m_ppObjects[i]).GetPosition().x, (*m_ppObjects[i]).GetPosition().y, (*m_ppObjects[i]).GetPosition().z + 80));
			(*m_ppObjects[i]).m_bLifeState = LIVE;
		}
	}

	////장애물 생성 
	//CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 4.0f);
	///*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/
	////int xObjects = 3, yObjects = 3, zObjects = 10, i = 0;
	//i = 0;
	////x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	//m_nObjects = OBJECTSIZE;
	//m_ppObjects = new CGameObject*[m_nObjects];
	////float fxPitch = 12.0f * 2.5f;
	////float fyPitch = 12.0f * 2.5f;
	////float fzPitch = 12.0f * 2.5f;


	//default_random_engine dre;
	//uniform_int<> uiColor(0, 120);
	//uniform_real_distribution<> urPosition(-35.f, 35.f);
	//uniform_real_distribution<> urSpeed(0.05f, 0.25f);
	//uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	//dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌
	//CRotatingObject *pRotatingObject = NULL;

	//for (int j = 0; j < m_nObjects; ++j)
	//{
	//	pRotatingObject = new CRotatingObject();
	//	pRotatingObject->SetMesh(pCubeMesh); //각 정육면체 객체의 위치를 설정한다. 
	//	pRotatingObject->SetPosition(urPosition(dre), urPosition(dre), urPosition(dre));
	//	//pRotatingObject->SetPosition(0, 0, 0);
	//	pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//	pRotatingObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	//	pRotatingObject->SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
	//	//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
	//	pRotatingObject->SetMovingSpeed(urSpeed(dre));
	//	pRotatingObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	m_ppObjects[i++] = pRotatingObject;
	//}



}
void CObjectsShader::AnimateObjects(float fTimeElapsed, ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	//if (m_bShootState)
	//{
	//	//cout << "쓔쓨ㄸ띠띠띠씨뜌" << endl;
	//	//장애물 생성 
	//	CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 4.0f);
	//	/*x-축, y-축, z-축 양의 방향의 객체 개수이다. 각 값을 1씩 늘리거나 줄이면서 실행할 때 프레임 레이트가 어떻게 변하는 가를 살펴보기 바란다.*/
	//	//int xObjects = 3, yObjects = 3, zObjects = 10, i = 0;
	//	int i = 0;
	//	//x-축, y-축, z-축으로 21개씩 총 21 x 21 x 21 = 9261개의 정육면체를 생성하고 배치한다.
	//	m_nBullet= OBJECTSIZE;
	//	m_ppBullet = new CGameObject*[m_nBullet];
	//	//float fxPitch = 12.0f * 2.5f;
	//	//float fyPitch = 12.0f * 2.5f;
	//	//float fzPitch = 12.0f * 2.5f;


	//
	//	CRotatingObject *pBulletObject = NULL;

	//	for (int j = 0; j < m_nObjects; ++j)
	//	{
	//		pBulletObject = new CRotatingObject();
	//		pBulletObject->SetMesh(pCubeMesh); //각 정육면체 객체의 위치를 설정한다. 
	//		pBulletObject->SetPosition(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
	//		//pRotatingObject->SetPosition(0, 0, 0);
	//		pBulletObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//		pBulletObject->SetRotationSpeed(10.0f*(i % 10) + 20.0f);
	//		pBulletObject->SetMovingDirection(XMFLOAT3(0, 0, 1));
	//		//pRotatingObject->SetMovingDirection(XMFLOAT3(1.0, 1.0, urMovingDirect(dre)));
	//		pBulletObject->SetMovingSpeed(0.2);
	//		pBulletObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//		m_ppBullet[i++] = pBulletObject;
	//		//CreateShaderVariables(pd3dDevice, pd3dCommandList);

	//	}
	//}

	
}


void CObjectsShader::ReleaseUploadBuffers() 
{ 
	if (m_ppObjects)
	{ 
		for (int j = 0; j < m_nObjects; j++)
			m_ppObjects[j]->ReleaseUploadBuffers(); 
	} 
	if (m_ppWall)
	{
		for (int j = 0; j < m_nWall; j++)
			m_ppWall[j]->ReleaseUploadBuffers();
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
	//for (auto iter = CObjectsShader::m_listBullet.begin(); iter != CObjectsShader::m_listBullet.end(); ++iter)//총알 순회하며 삭제
	//{
	//	(*iter)->Render(pd3dCommandList, pCamera);
	//}
	//cout << "------------------------" << endl;
	//for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)//총알 순회하며 삭제
	//{
	//	//cout << (*iter)->m_xmOOBB.Center.x << "\t" << (*iter)->m_xmOOBB.Center.y << "\t" <<(*iter)->m_xmOOBB.Center.z << endl;
	//	(*iter)->Render(pd3dCommandList, pCamera);

	//	/*if ((*iter)->m_pMesh)
	//	{
	//		cout << "널아님" << endl;
	//	}*/
	//}
	//cout << "------------------------" << endl;
	//for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)
	//{

	//	cout << (*iter)->GetPosition().x << "\t" << (*iter)->GetPosition().y << "\t" << (*iter)->GetPosition().z << "\t" << endl;
	//}
	//cout << "------------------------" << endl;

	



	//쉐이더가 객체를 포함하고 있는데
	//그러면 키 누를떄 생기는 총알은 어디서 생성해줘야되는 것인가?
}
