///-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"
#include "DDSTextureLoader12.h"



XMFLOAT3 CShader::m_f3CrushPosition[PARTICLESIZE] = {};
float CShader::m_fParticleDeleteTimer[BULLETSIZE] = {};
bool CShader::m_bParticleDeleteTimerOn[BULLETSIZE] = {};
bool CShader::m_bCrushState = false;


CShader::CShader()
{
	m_d3dSrvCPUDescriptorStartHandle.ptr = NULL;
	m_d3dSrvGPUDescriptorStartHandle.ptr = NULL;
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

	ID3DBlob *errorBlob = NULL;
	HRESULT hresult = ::D3DCompileFromFile(pszFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

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

void CShader::CreateCbvAndSrvDescriptorHeaps(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
}

void CShader::CreateConstantBufferViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		D3D12_CPU_DESCRIPTOR_HANDLE d3dCbvCPUDescriptorHandle;
		d3dCbvCPUDescriptorHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * j);
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, d3dCbvCPUDescriptorHandle);
	}
}

D3D12_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc(D3D12_RESOURCE_DESC d3dResourceDesc, UINT nTextureType)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc;
	d3dShaderResourceViewDesc.Format = d3dResourceDesc.Format;
	d3dShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	switch (nTextureType)
	{
	case RESOURCE_TEXTURE2D: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 1)
	case RESOURCE_TEXTURE2D_ARRAY:
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		d3dShaderResourceViewDesc.Texture2D.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2D.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_TEXTURE2DARRAY: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize != 1)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
		d3dShaderResourceViewDesc.Texture2DArray.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2DArray.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2DArray.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ResourceMinLODClamp = 0.0f;
		d3dShaderResourceViewDesc.Texture2DArray.FirstArraySlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ArraySize = d3dResourceDesc.DepthOrArraySize;
		break;
	case RESOURCE_TEXTURE_CUBE: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 6)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		d3dShaderResourceViewDesc.TextureCube.MipLevels = -1;
		d3dShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.TextureCube.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_BUFFER: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		d3dShaderResourceViewDesc.Buffer.FirstElement = 0;
		d3dShaderResourceViewDesc.Buffer.NumElements = 0;
		d3dShaderResourceViewDesc.Buffer.StructureByteStride = 0;
		d3dShaderResourceViewDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		break;
	}
	return(d3dShaderResourceViewDesc);
}

void CShader::CreateShaderResourceViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CTexture *pTexture, UINT nRootParameterStartIndex, bool bAutoIncrement)
{
	D3D12_CPU_DESCRIPTOR_HANDLE d3dSrvCPUDescriptorHandle = m_d3dSrvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE d3dSrvGPUDescriptorHandle = m_d3dSrvGPUDescriptorStartHandle;
	int nTextures = pTexture->GetTextureCount();
	int nTextureType = pTexture->GetTextureType();
	for (int i = 0; i < nTextures; i++)
	{
		ID3D12Resource *pShaderResource = pTexture->GetTexture(i);
		D3D12_RESOURCE_DESC d3dResourceDesc = pShaderResource->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = GetShaderResourceViewDesc(d3dResourceDesc, nTextureType);
		pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, d3dSrvCPUDescriptorHandle);
		d3dSrvCPUDescriptorHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;

		pTexture->SetRootArgument(i, (bAutoIncrement) ? (nRootParameterStartIndex + i) : nRootParameterStartIndex, d3dSrvGPUDescriptorHandle);
		d3dSrvGPUDescriptorHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
	}
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

void CShader::ReleaseShaderVariables()
{
	//if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}

void CShader::ReleaseUploadBuffers()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_ppd3dPipelineStates) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
	pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	UpdateShaderVariables(pd3dCommandList);
}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTexturedShader::CTexturedShader()
{
}

CTexturedShader::~CTexturedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTexturedShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTexturedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTexturedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextured", "ps_5_1", ppd3dShaderBlob));
}

void CTexturedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CIlluminatedTexturedShader::CIlluminatedTexturedShader()
{
}

CIlluminatedTexturedShader::~CIlluminatedTexturedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CIlluminatedTexturedShader::CreateInputLayout()
{
	UINT nInputElementDescs = 3;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[2] ={ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CIlluminatedTexturedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTexturedLighting", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CIlluminatedTexturedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTexturedLighting", "ps_5_1", ppd3dShaderBlob));
}

void CIlluminatedTexturedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CIlluminatedShader::CIlluminatedShader()
{
}

CIlluminatedShader::~CIlluminatedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CIlluminatedShader::CreateInputLayout()
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

D3D12_SHADER_BYTECODE CIlluminatedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSLighting", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CIlluminatedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSLighting", "ps_5_1", ppd3dShaderBlob));
}

void CIlluminatedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CObjectsShader::CObjectsShader()
{
}

CObjectsShader::~CObjectsShader()
{
}

void CObjectsShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbGameObjects->Map(0, NULL, (void **)&m_pcbMappedGameObjects);
}

void CObjectsShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nObjects; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedGameObjects + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World)));
#ifdef _WITH_BATCH_MATERIAL
		if (m_pMaterial) pbMappedcbGameObject->m_nMaterial = m_pMaterial->m_nReflection;
#endif
	}
}

void CObjectsShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects)
	{
		m_pd3dcbGameObjects->Unmap(0, NULL);
		m_pd3dcbGameObjects->Release();
	}

	CIlluminatedTexturedShader::ReleaseShaderVariables();
}

D3D12_BLEND_DESC CObjectsShader::CreateBlendState()
{
	//¿©±â
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_COLOR;;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);

}

D3D12_DEPTH_STENCIL_DESC CObjectsShader::CreateDepthStencilState()
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

	/*d3dDepthStencilDesc.DepthEnable = FALSE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	return(d3dDepthStencilDesc);
}

//#define _WITH_TERRAIN_PARTITION

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	int xObjects = 1, yObjects = 1, zObjects = 1, i = 0;

	m_nObjects = 1;//(xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	CTexture *pTexture = new CTexture(6, RESOURCE_TEXTURE2D_ARRAY, 0); //6°³ÀÇ ÅØ½ºÃÄ¸¦ ¾µ²¨¾ß
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 4);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Terrain/Water_Base_Texture_0.dds", 5);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 6);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 5, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
	m_pMaterial->SetReflection(1);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
	pCubeMaterial->SetReflection(1);
#endif

	CCubeMeshIlluminatedTextured *pCubeMesh = new CCubeMeshIlluminatedTextured(pd3dDevice, pd3dCommandList, 500.0f, 1.0f, 3500.0f);

	m_ppObjects = new CGameObject*[m_nObjects];

	float fxPitch = 12.0f * 2.5f, fyPitch = 12.0f * 2.5f, fzPitch = 12.0f * 2.5f;

	CRotatingObject *pRotatingObject = NULL;
//	for (int x = -xObjects; x <= xObjects; x++)
//	{
//		for (int y = -yObjects; y <= yObjects; y++)
//		{
//			for (int z = -zObjects; z <= zObjects; z++)
//			{
//				pRotatingObject = new CRotatingObject(1);
//				pRotatingObject->SetMesh(0, pCubeMesh);
//#ifndef _WITH_BATCH_MATERIAL
//				pRotatingObject->SetMaterial(pCubeMaterial);
//#endif
//				pRotatingObject->SetPosition(3500, 100, 5870,true);
//				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
//				pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
//				m_ppObjects[i++] = pRotatingObject;
//			}
//		}
//	}
	pRotatingObject = new CRotatingObject(1);
	pRotatingObject->SetMesh(0, pCubeMesh);
#ifndef _WITH_BATCH_MATERIAL
	pRotatingObject->SetMaterial(pCubeMaterial);
#endif
	pRotatingObject->SetPosition(1408, 270, 1323, true);
	pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
	pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	m_ppObjects[i++] = pRotatingObject;
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

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) delete m_pMaterial;
#endif
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
	for (int i = 0; i < 5; ++i)
	{
		//cout << (*m_ppEnemyObject[i]).m_xmf4x4ToParentTransform._43 << endl;
		//cout << m_ppEnemyObject[i]->GetPositionParent().x << "\t" << m_ppEnemyObject[i]->GetPositionParent().y << "\t" << m_ppEnemyObject[i]->GetPositionParent().z << endl;

	}
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) m_ppObjects[j]->ReleaseUploadBuffers();
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->ReleaseUploadBuffers();
#endif
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CIlluminatedTexturedShader::Render(pd3dCommandList, pCamera);

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->UpdateShaderVariables(pd3dCommandList);
#endif

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->Render(pd3dCommandList, pCamera);
	}
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextured", "ps_5_1", ppd3dShaderBlob));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CBulletShader::CBulletShader()
{
}

CBulletShader::~CBulletShader()
{
}

void CBulletShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbBullet= ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nBullet, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbBullet->Map(0, NULL, (void **)&m_pcbMappedBullet);
}

void CBulletShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nBullet; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedBullet + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppBullet[j]->m_xmf4x4World)));
#ifdef _WITH_BATCH_MATERIAL
		if (m_pMaterial) pbMappedcbGameObject->m_nMaterial = m_pMaterial->m_nReflection;
#endif
	}
}
D3D12_SHADER_BYTECODE CBulletShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CBulletShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextured", "ps_5_1", ppd3dShaderBlob));
}

void CBulletShader::ReleaseShaderVariables()
{
	if (m_pd3dcbBullet)
	{
		m_pd3dcbBullet->Unmap(0, NULL);
		m_pd3dcbBullet->Release();
	}

	CIlluminatedTexturedShader::ReleaseShaderVariables();
}

D3D12_BLEND_DESC CBulletShader::CreateBlendState()
{
	//¿©±â
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

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);

}

D3D12_DEPTH_STENCIL_DESC CBulletShader::CreateDepthStencilState()
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

	/*d3dDepthStencilDesc.DepthEnable = FALSE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	return(d3dDepthStencilDesc);
}

//#define _WITH_TERRAIN_PARTITION

void CBulletShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	int xObjects = 1, yObjects = 1, zObjects = 1, i = 0;

	m_nBullet = BULLETSIZE;//(xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2DARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/StonesArray.dds", 0);


	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nBullet, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nBullet, m_pd3dcbBullet, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 5, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
	m_pMaterial->SetReflection(1);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
	pCubeMaterial->SetReflection(1);
#endif

	CCubeMeshIlluminatedTextured *pCubeMesh = new CCubeMeshIlluminatedTextured(pd3dDevice, pd3dCommandList, 15, 15, 15);

	m_ppBullet = new CGameObject*[m_nBullet];

	float fxPitch = 12.0f * 2.5f, fyPitch = 12.0f * 2.5f, fzPitch = 12.0f * 2.5f;

	CRotatingObject *pRotatingObject = NULL;

	for (int j = 0; j < m_nBullet; ++j)
	{
		pRotatingObject = new CRotatingObject(1);
		pRotatingObject->SetMesh(0, pCubeMesh);
#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif
		pRotatingObject->SetPosition(1708, 8830, 1323, true);
		pRotatingObject->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
		pRotatingObject->SetMovingSpeed(2.0);
		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppBullet[i++] = pRotatingObject;

	}
	//	for (int x = -xObjects; x <= xObjects; x++)
	//	{
	//		for (int y = -yObjects; y <= yObjects; y++)
	//		{
	//			for (int z = -zObjects; z <= zObjects; z++)
	//			{
	//				pRotatingObject = new CRotatingObject(1);
	//				pRotatingObject->SetMesh(0, pCubeMesh);
	//#ifndef _WITH_BATCH_MATERIAL
	//				pRotatingObject->SetMaterial(pCubeMaterial);
	//#endif
	//				pRotatingObject->SetPosition(3500, 100, 5870,true);
	//				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//				pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
	//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	//				m_ppObjects[i++] = pRotatingObject;
	//			}
	//		}
	//	}
	
	//m_pPlayer->m_pChild = *m_ppBullet;
}

void CBulletShader::ReleaseObjects()
{
	if (m_ppBullet)
	{
		for (int j = 0; j < m_nBullet; j++)
			if (m_ppBullet[j])
				delete m_ppBullet[j];
		delete[] m_ppBullet;
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) delete m_pMaterial;
#endif
}

void CBulletShader::AnimateObjects(float fTimeElapsed)
{

	//ÀÏÁ¤°Å¸® µÇ¸é µû¶ó¿À°Ô ÇÏ±â Àû

	//ÇÃ·¹ÀÌ¾î¿Í Àå¾Ö¹° ÀÏÁ¤°Å¸® µÇ¾úÀ»¶§
	for (int i = 0; i < OBJECTSIZE; ++i)
	{
		if (sqrt(((m_pPlayer->m_xmOOBB.Center.x - m_ppEnemyObject[i]->m_xmOOBB.Center.x) * (m_pPlayer->m_xmOOBB.Center.x - m_ppEnemyObject[i]->m_xmOOBB.Center.x) + (m_pPlayer->m_xmOOBB.Center.y - m_ppEnemyObject[i]->m_xmOOBB.Center.y) * (m_pPlayer->m_xmOOBB.Center.y - m_ppEnemyObject[i]->m_xmOOBB.Center.y) + (m_pPlayer->m_xmOOBB.Center.z - m_ppEnemyObject[i]->m_xmOOBB.Center.z) * (m_pPlayer->m_xmOOBB.Center.z - m_ppEnemyObject[i]->m_xmOOBB.Center.z) < 2050)))
		{

		
		//	cout << "À¯ÈÄ" << endl;


			m_ppEnemyObject[i]->MoveToPlayer(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppEnemyObject[i]->GetPosition()),0.001f);
			//m_ppObjects[i]->SetPosition(a++, (m_ppObjects[i]->GetPosition().y), (m_ppObjects[i]->GetPosition().z));

			XMFLOAT3 pos;

			float playerx = m_pPlayer->GetPosition().x;
			float playery = m_pPlayer->GetPosition().y;
			float playerz = m_pPlayer->GetPosition().z;


			//m_ppEnemyObject[i]->SetPosition(m_ppEnemyObject[i]->GetPosition().x, m_ppEnemyObject[i]->GetPosition().y, m_ppEnemyObject[i]->GetPosition().z, true);
			m_ppEnemyObject[i]->SetOOBB(m_ppEnemyObject[i]->GetPosition(), XMFLOAT3(12, 10, 10), XMFLOAT4(0, 0, 0, 1));
			//cout << "µû¶ó¿Í" << endl;
		}
	}


	//cout << "------------------------------------" << endl;
	//cout << m_pPlayer->GetPosition().x <<"\t"<< m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z<<endl;
	//cout << m_pTerrain->GetHeight(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().z) << endl;
	//cout << "------------------------------------" << endl;
	
	

	//if (m_ppEnemyObject)
	//cout << m_ppEnemyObject[1]->GetPosition().x << "\t" << m_ppEnemyObject[1]->GetPosition().y << "\t" << m_ppEnemyObject[1]->GetPosition().z << endl;

		//cout << m_ppEnemyObject[0]->m_xmOOBB.Center.x << "\t" << m_ppEnemyObject[0]->m_xmOOBB.Center.y << "\t" << m_ppEnemyObject[0]->m_xmOOBB.Center.z << endl;
	//ÃÑ¾Ë°ú Àû Ãæµ¹
	for (int i = 0; i < m_nBullet; ++i)
	{
		for (int j = 0; j < OBJECTSIZE; ++j)
		{
			
			if ((*m_ppEnemyObject[j]).m_xmOOBB.Intersects((*m_ppBullet[i]).m_xmOOBB))
			{
				if (((*m_ppBullet[i]).ItisShooting == true))
				{
					//(*m_ppEnemyObject[j]).m_bLifeState = DEATH;
					cout << "¹Ì»çÀÏ°ú Àå¾Ö¹° Ãæµ¹ " << endl;
				
					for (int j = 0; j < PARTICLESIZE; ++j)
					{
						if (m_f3CrushPosition[j].x == 0)
						{

							m_bCrushState = true;
							m_f3CrushPosition[j].x = (*m_ppBullet[i]).GetPosition().x;
							m_f3CrushPosition[j].y = (*m_ppBullet[i]).GetPosition().y;
							m_f3CrushPosition[j].z = (*m_ppBullet[i]).GetPosition().z;
							m_ppBullet[i]->SetPosition(0, 9999, 0, true);
							
							break;
						}


					}
				}
				//m_listBullet.erase(iter);
			}
		}
	}


	//ÃÑ¾Ë°ú ÁöÇüÀÇ Ãæµ¹ ®c!
	for (int i = 0; i < m_nBullet; ++i)
	{
		if ((*m_ppBullet[i]).GetPosition().y < m_pTerrain->GetHeight((*m_ppBullet[i]).GetPosition().x, (*m_ppBullet[i]).GetPosition().z) && (*m_ppBullet[i]).GetPosition().y < 8000)
		{
			//cout << " Ãæµ¹" << endl;
			for (int j = 0; j < PARTICLESIZE; ++j)
			{
				if (m_f3CrushPosition[j].x == 0 && ((*m_ppBullet[i]).ItisShooting == true))
				{
					m_bCrushState = true;
					m_f3CrushPosition[j].x = (*m_ppBullet[i]).GetPosition().x;
					m_f3CrushPosition[j].y = (*m_ppBullet[i]).GetPosition().y;
					m_f3CrushPosition[j].z = (*m_ppBullet[i]).GetPosition().z;
					m_ppBullet[i]->m_bParticleActive = true;
					m_ppBullet[i]->SetPosition(0, 9999, 0, true);
					break;
				}
			}
		}
	}
	if (m_bCrushState) //Å¸ÀÌ¸Ó ¼¼¾ßÇÔ
	{
		for (int i = 0; i < BULLETSIZE; ++i)
		{
			if (m_bParticleDeleteTimerOn[i] == false)
			{
				m_bParticleDeleteTimerOn[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < BULLETSIZE; ++i)
	{
		if (m_bParticleDeleteTimerOn[i] == true)
		{
			m_fParticleDeleteTimer[i] += fTimeElapsed;
		}
	}
	

	//cout << m_fParticleDeleteTimer[0] << endl;
	m_bCrushState = false;


	for (int i = 0; i < m_nBullet; ++i)
	{
	
		//cout << (*m_ppBullet[i]).ItisShooting << endl;
		if ((*m_ppBullet[i]).ItisShooting == false)
		{
			//oobb ¿Å°Ü¹ö¸®±â
			(*m_ppBullet[i]).SetPosition(m_pPlayer->m_xmOOBB.Center.x, m_pPlayer->m_xmOOBB.Center.y, m_pPlayer->m_xmOOBB.Center.z,true);
			(*m_ppBullet[i]).SetMovingDirection(XMFLOAT3(m_pPlayer->GetCamera()->GetLookVector().x, m_pPlayer->GetCamera()->GetLookVector().y, m_pPlayer->GetCamera()->GetLookVector().z));
		}

	}

	if (m_bShootState == true)
	{
		cout << "ÃÑ¾Ë ¹ß»ç" << endl;
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


	for (int j = 0; j < m_nBullet; j++)
	{
		m_ppBullet[j]->Animate(fTimeElapsed);
	}
	for (int i = 0; i < 5; ++i)
	{
		//cout << (*m_ppEnemyObject[i]).m_xmf4x4ToParentTransform._43 << endl;
		//cout << m_ppEnemyObject[i]->GetPositionParent().x << "\t" << m_ppEnemyObject[i]->GetPositionParent().y << "\t" << m_ppEnemyObject[i]->GetPositionParent().z << endl;

	}
}

void CBulletShader::ReleaseUploadBuffers()
{
	if (m_ppBullet)
	{
		for (int j = 0; j < m_nBullet; j++) if (m_ppBullet[j]) m_ppBullet[j]->ReleaseUploadBuffers();
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->ReleaseUploadBuffers();
#endif
}

void CBulletShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CIlluminatedTexturedShader::Render(pd3dCommandList, pCamera);

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->UpdateShaderVariables(pd3dCommandList);
#endif

	for (int j = 0; j < m_nBullet; j++)
	{
		
		if (m_ppBullet[j])
		{
			if(m_ppBullet[j]->ItisShooting == true)
			m_ppBullet[j]->Render(pd3dCommandList, pCamera);


		}

	}
}
void CParticleShader::SetParticlePosition(XMFLOAT3 particlepos)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CParticleShader::CParticleShader()
{
}

CParticleShader::~CParticleShader()
{
}

D3D12_INPUT_LAYOUT_DESC CParticleShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//Á¤Á¡ Á¤º¸¸¦ À§ÇÑ ÀÔ·Â ¿ø¼ÒÀÌ´Ù. 
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CParticleShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CParticleShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSParticle", "ps_5_1", ppd3dShaderBlob));
}


void CParticleShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbParticle = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nParticle, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbParticle->Map(0, NULL, (void **)&m_pcbMappedParticle);
}

void CParticleShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nParticle; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedParticle + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppParticle[j]->m_xmf4x4World)));
#ifdef _WITH_BATCH_MATERIAL
		if (m_pMaterial) pbMappedcbGameObject->m_nMaterial = m_pMaterial->m_nReflection;
		pbMappedcbGameObject->m_iFrameTime = m_fFrameTime;

		
#endif
	}
}

void CParticleShader::ReleaseShaderVariables()
{
	if (m_pd3dcbParticle)
	{
		m_pd3dcbParticle->Unmap(0, NULL);
		m_pd3dcbParticle->Release();
	}

	CIlluminatedTexturedShader::ReleaseShaderVariables();
}

D3D12_BLEND_DESC CParticleShader::CreateBlendState()
{
	//¿©±â
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	//d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	//d3dBlendDesc.IndependentBlendEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	//d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	//d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	//d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	//d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	//d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	//d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	//d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);

}

D3D12_DEPTH_STENCIL_DESC CParticleShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	//d3dDepthStencilDesc.DepthEnable = TRUE;
	//d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	//d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	//d3dDepthStencilDesc.StencilEnable = FALSE;
	//d3dDepthStencilDesc.StencilReadMask = 0x00;
	//d3dDepthStencilDesc.StencilWriteMask = 0x00;
	//d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	//d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	//d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	d3dDepthStencilDesc.DepthEnable = FALSE;
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

//#define _WITH_TERRAIN_PARTITION

void CParticleShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	int xObjects = 1, yObjects = 1, zObjects = 1, i = 0;

	m_nParticle = PARTICLESIZE;//(xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Particle/Explosion.dds", 0);


	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nParticle, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nParticle, m_pd3dcbParticle, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 11, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
	m_pMaterial->SetReflection(1);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
	pCubeMaterial->SetReflection(1);
#endif

	CTexturedRectMesh *pCubeMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 120, 80, 0);

	m_ppParticle= new CGameObject*[m_nParticle];

	float fxPitch = 12.0f * 2.5f, fyPitch = 12.0f * 2.5f, fzPitch = 12.0f * 2.5f;

	CBillboardObject *pRotatingObject = NULL;
	//	for (int x = -xObjects; x <= xObjects; x++)
	//	{
	//		for (int y = -yObjects; y <= yObjects; y++)
	//		{
	//			for (int z = -zObjects; z <= zObjects; z++)
	//			{
	//				pRotatingObject = new CRotatingObject(1);
	//				pRotatingObject->SetMesh(0, pCubeMesh);
	//#ifndef _WITH_BATCH_MATERIAL
	//				pRotatingObject->SetMaterial(pCubeMaterial);
	//#endif
	//				pRotatingObject->SetPosition(3500, 100, 5870,true);
	//				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//				pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
	//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	//				m_ppObjects[i++] = pRotatingObject;
	//			}
	//		}
	//	}

	for (int j = 0; j < m_nParticle; ++j)
	{
		pRotatingObject = new CBillboardObject(1);
		pRotatingObject->SetMesh(0, pCubeMesh);
#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif
		pRotatingObject->SetPosition(3500, 400, 5870, true);

		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppParticle[i++] = pRotatingObject;

	}

	//m_pPlayer->m_pChild = *m_ppBullet;
}

void CParticleShader::ReleaseObjects()
{
	if (m_ppParticle)
	{
		for (int j = 0; j < m_nParticle; j++)
			if (m_ppParticle[j])
				delete m_ppParticle[j];
		delete[] m_ppParticle;
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) delete m_pMaterial;
#endif
}

void CParticleShader::AnimateObjects(float fTimeElapsed)
{
	m_fFrameTime += 5 * fTimeElapsed;


	for (int i = 0; i < m_nParticle; ++i)
	{

		m_ppParticle[i]->Animate(fTimeElapsed, m_pPlayer->GetCamera());

	}


	for (int i = 0; i < m_nParticle; ++i)
	{
		
		m_ppParticle[i]->SetPosition(m_f3CrushPosition[i].x, m_f3CrushPosition[i].y, m_f3CrushPosition[i].z, true);
	
	}
//	m_ppParticle[0]->SetPosition(m_f3CrushPosition.x, m_f3CrushPosition.y, m_f3CrushPosition.z, true);
	
}

void CParticleShader::ReleaseUploadBuffers()
{
	if (m_ppParticle)
	{
		for (int j = 0; j < m_nParticle; j++) if (m_ppParticle[j]) m_ppParticle[j]->ReleaseUploadBuffers();
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->ReleaseUploadBuffers();
#endif
}

void CParticleShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CIlluminatedTexturedShader::Render(pd3dCommandList, pCamera);

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->UpdateShaderVariables(pd3dCommandList);
#endif

	for (int j = 0; j < m_nParticle; j++)
	{
		if (m_fParticleDeleteTimer[j] < 3)
		{
			if (m_ppParticle[j]->GetPosition().x != 0)
			if (m_ppParticle[j]) m_ppParticle[j]->Render(pd3dCommandList, pCamera);

		}
		
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTerrainShader::CTerrainShader()
{
}

CTerrainShader::~CTerrainShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	UINT nInputElementDescs = 4;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	//pd3dInputElementDescs[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	pd3dInputElementDescs[2] ={ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[3] ={ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTerrain", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTerrain", "ps_5_1", ppd3dShaderBlob));
}

D3D12_BLEND_DESC CTerrainShader::CreateBlendState()
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

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);
}


void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CSkyBoxShader::CSkyBoxShader()
{
}

CSkyBoxShader::~CSkyBoxShader()
{
}



D3D12_DEPTH_STENCIL_DESC CSkyBoxShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	d3dDepthStencilDesc.DepthEnable = FALSE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0xff;
	d3dDepthStencilDesc.StencilWriteMask = 0xff;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_DECR;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	return(d3dDepthStencilDesc);
}


D3D12_SHADER_BYTECODE CSkyBoxShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSSkyBox", "ps_5_1", ppd3dShaderBlob));
}

void CSkyBoxShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


///////////////////////////////////////////////////////////////////////////////////
CInstancingShader::CInstancingShader() { }
CInstancingShader::~CInstancingShader() { }

D3D12_DEPTH_STENCIL_DESC CInstancingShader::CreateDepthStencilState()
{
	//¿©±â
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

	/*d3dDepthStencilDesc.DepthEnable = FALSE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CInstancingShader::CreateBlendState()
{
	//¿©±â
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

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);
}


D3D12_INPUT_LAYOUT_DESC CInstancingShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//Á¤Á¡ Á¤º¸¸¦ À§ÇÑ ÀÔ·Â ¿ø¼ÒÀÌ´Ù. 
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CInstancingShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTexturedInstancing", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CInstancingShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTexturedInstancing", "ps_5_1", ppd3dShaderBlob));
}
void CInstancingShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CInstancingShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	//ÀÎ½ºÅÏ½º Á¤º¸¸¦ ÀúÀåÇÒ Á¤Á¡ ¹öÆÛ¸¦ ¾÷·Îµå Èü À¯ÇüÀ¸·Î »ý¼ºÇÑ´Ù. 
	m_pd3dcbGrass = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, sizeof(VS_VB_INSTANCE) * m_nGrass, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//Á¤Á¡ ¹öÆÛ(¾÷·Îµå Èü)¿¡ ´ëÇÑ Æ÷ÀÎÅÍ¸¦ ÀúÀåÇÑ´Ù.
	m_pd3dcbGrass->Map(0, NULL, (void **)&m_pcbMappedGrass);
}
void CInstancingShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGrass) m_pd3dcbGrass->Unmap(0, NULL);
	if (m_pd3dcbGrass) m_pd3dcbGrass->Release();
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}
//ÀÎ½ºÅÏ½Ì Á¤º¸(°´Ã¼ÀÇ ¿ùµå º¯È¯ Çà·Ä°ú »ö»ó)¸¦ Á¤Á¡ ¹öÆÛ¿¡ º¹»çÇÑ´Ù.
void CInstancingShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	for (int j = 0; j < m_nGrass; j++)
	{
		XMStoreFloat4x4(&m_pcbMappedGrass[j].m_xmf4x4Transform, XMMatrixTranspose(XMLoadFloat4x4(&m_ppGrass[j]->m_xmf4x4World)));
	}
	pd3dCommandList->SetGraphicsRootShaderResourceView(9, m_pd3dcbGrass->GetGPUVirtualAddress());

}


void CInstancingShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList*pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;

	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = 45;
	int yObjects = 1;
	int zObjects = 45;
	m_nGrass = (xObjects * yObjects * zObjects);

	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 0);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 1);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 2);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 3);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 4);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Grasses/Grass08.dds", 5);



	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, 0, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 10, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

	CTexturedRectMesh *pCubeMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 30.0f, 20, 0);


	m_ppGrass = new CGameObject*[m_nGrass];

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	CBillboardObject *pRotatingObject = NULL;

	// ÀÎ½ºÅÏ½Å¿ë ¸Þ½¬ ÇÏ³ª¸¸ Ã³¸®

	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{

			pRotatingObject = new CBillboardObject(1);
#ifndef _WITH_BATCH_MATERIAL
			pRotatingObject->SetMaterial(pCubeMaterial);
#endif
			float xPosition = 105 * x + 1050;
			float zPosition = 100 * z + 1050;
			pRotatingObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 10, zPosition,true);

			//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
			//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
			pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppGrass[i++] = pRotatingObject;

		}
	}
	m_ppGrass[0]->SetMesh(0, pCubeMesh);


}

void CInstancingShader::AnimateObjects(float fTimeElapsed)
{
	//cout << "----------------------------------------------------------------------------" << endl;
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	//cout << m_pPlayer->GetCamera()->GetPosition().x << "\t" << m_pPlayer->GetCamera()->GetPosition().y << "\t" << m_pPlayer->GetCamera()->GetPosition().z << endl;
	//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" << m_pPlayer->m_xmOOBB.Center.z << endl;
	//cout << "----------------------------------------------------------------------------" << endl;

	for (int i = 0; i < m_nGrass; ++i)
	{

		m_ppGrass[i]->Animate(fTimeElapsed, m_pPlayer->GetCamera());

	}
}


void CInstancingShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CObjectsShader::Render(pd3dCommandList, pCamera);
	//¸ðµç °ÔÀÓ °´Ã¼ÀÇ ÀÎ½ºÅÏ½Ì µ¥ÀÌÅÍ¸¦ ¹öÆÛ¿¡ ÀúÀåÇÑ´Ù.
	UpdateShaderVariables(pd3dCommandList);
	//ÇÏ³ªÀÇ Á¤Á¡ µ¥ÀÌÅÍ¸¦ »ç¿ëÇÏ¿© ¸ðµç °ÔÀÓ °´Ã¼(ÀÎ½ºÅÏ½º)µéÀ» ·»´õ¸µÇÑ´Ù.
	m_ppGrass[0]->Render(pd3dCommandList, pCamera, m_nGrass);
}
void CInstancingShader::ReleaseObjects()
{
	if (m_ppGrass)
	{
		for (int j = 0; j < m_nGrass; j++)
			if (m_ppGrass[j])
			{
				delete m_ppGrass[j];
				//cout << j <<"Ç®»èÁ¦" << endl;


			}
		cout << "delete[]Àü " << endl;
		delete[] m_ppGrass;
		cout << "delete[]ÈÄ " << endl;

	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Tree




CInstancingShader_Tree::CInstancingShader_Tree() { }
CInstancingShader_Tree::~CInstancingShader_Tree() { }

D3D12_INPUT_LAYOUT_DESC CInstancingShader_Tree::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//Á¤Á¡ Á¤º¸¸¦ À§ÇÑ ÀÔ·Â ¿ø¼ÒÀÌ´Ù. 
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CInstancingShader_Tree::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTexturedInstancing", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CInstancingShader_Tree::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTexturedInstancing", "ps_5_1", ppd3dShaderBlob));
}
void CInstancingShader_Tree::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CInstancingShader_Tree::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	//ÀÎ½ºÅÏ½º Á¤º¸¸¦ ÀúÀåÇÒ Á¤Á¡ ¹öÆÛ¸¦ ¾÷·Îµå Èü À¯ÇüÀ¸·Î »ý¼ºÇÑ´Ù. 
	m_pd3dcbTree = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, sizeof(VS_VB_INSTANCE) * m_nTree, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//Á¤Á¡ ¹öÆÛ(¾÷·Îµå Èü)¿¡ ´ëÇÑ Æ÷ÀÎÅÍ¸¦ ÀúÀåÇÑ´Ù.
	m_pd3dcbTree->Map(0, NULL, (void **)&m_pcbMappedTree);
}
void CInstancingShader_Tree::ReleaseShaderVariables()
{
	if (m_pd3dcbTree) m_pd3dcbTree->Unmap(0, NULL);
	if (m_pd3dcbTree) m_pd3dcbTree->Release();
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}
//ÀÎ½ºÅÏ½Ì Á¤º¸(°´Ã¼ÀÇ ¿ùµå º¯È¯ Çà·Ä°ú »ö»ó)¸¦ Á¤Á¡ ¹öÆÛ¿¡ º¹»çÇÑ´Ù.
void CInstancingShader_Tree::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	for (int j = 0; j < m_nTree; j++)
	{
		XMStoreFloat4x4(&m_pcbMappedTree[j].m_xmf4x4Transform, XMMatrixTranspose(XMLoadFloat4x4(&m_ppTree[j]->m_xmf4x4World)));
	}
	pd3dCommandList->SetGraphicsRootShaderResourceView(9, m_pd3dcbTree->GetGPUVirtualAddress());

}


void CInstancingShader_Tree::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList*pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;

	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = 45;
	int yObjects = 1;
	int zObjects = 45;
	m_nTree = (xObjects * yObjects * zObjects);

	/*CTexture *pTexture = new CTexture(6, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/rocks2.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 4);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 5);*/

	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/TreeArray/Tree02.dds", 0);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/TreeArray/Tree02.dds", 1);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 2);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 3);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 4);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 5);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, 0, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 10, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

	CTexturedRectMesh *pCubeMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 20.0f, 60, 0);


	m_ppTree = new CGameObject*[m_nTree];

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	CBillboardObject *pRotatingObject = NULL;
	//	for (int i = 0, x = 0; x < xObjects; x++)
	//	{
	//		for (int z = 0; z < zObjects; z++)
	//		{
	//			for (int y = 0; y < yObjects; y++)
	//			{
	//				pRotatingObject = new CBillboardObject(1);
	//#ifndef _WITH_BATCH_MATERIAL
	//				pRotatingObject->SetMaterial(pCubeMaterial);
	//#endif
	//				float xPosition = x * fxPitch;
	//				float zPosition = z * fzPitch;
	//				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
	//				pRotatingObject->SetPosition(xPosition, fHeight + (y * 3.0f * fyPitch) + 6.0f+50, zPosition);
	//				if (y == 0)
	//				{
	//					xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
	//					xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
	//					if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//					float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
	//					pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
	//				}
	//				//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//				//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
	//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	//				m_ppTree[i++] = pRotatingObject;
	//			}
	//		}
	//	}

	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{

			pRotatingObject = new CBillboardObject(1);
#ifndef _WITH_BATCH_MATERIAL
			pRotatingObject->SetMaterial(pCubeMaterial);
#endif
			float xPosition = 200 * x + 500;
			float zPosition = 150 * z + 1000;
			pRotatingObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 30, zPosition,true);
			//cout << pTerrain->GetHeight(xPosition, zPosition) + 30 << endl;
			//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
			//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
			pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppTree[i++] = pRotatingObject;

		}
	}
	// ÀÎ½ºÅÏ½Å¿ë ¸Þ½¬ ÇÏ³ª¸¸ Ã³¸®
	m_ppTree[0]->SetMesh(0, pCubeMesh);
}
D3D12_DEPTH_STENCIL_DESC CInstancingShader_Tree::CreateDepthStencilState()
{
	//¿©±â
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

	/*d3dDepthStencilDesc.DepthEnable = FALSE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CInstancingShader_Tree::CreateBlendState()
{
	//¿©±â
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

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);
}
void CInstancingShader_Tree::AnimateObjects(float fTimeElapsed)
{
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	for (int i = 0; i < m_nTree; ++i)
	{
		m_ppTree[i]->Animate(fTimeElapsed, m_pPlayer->GetCamera());

	}
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;

}

void CInstancingShader_Tree::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CObjectsShader::Render(pd3dCommandList, pCamera);
	//¸ðµç °ÔÀÓ °´Ã¼ÀÇ ÀÎ½ºÅÏ½Ì µ¥ÀÌÅÍ¸¦ ¹öÆÛ¿¡ ÀúÀåÇÑ´Ù.
	UpdateShaderVariables(pd3dCommandList);
	//ÇÏ³ªÀÇ Á¤Á¡ µ¥ÀÌÅÍ¸¦ »ç¿ëÇÏ¿© ¸ðµç °ÔÀÓ °´Ã¼(ÀÎ½ºÅÏ½º)µéÀ» ·»´õ¸µÇÑ´Ù.
	m_ppTree[0]->Render(pd3dCommandList, pCamera, m_nTree);

}

void CInstancingShader_Tree::ReleaseObjects()
{
	if (m_ppTree)
	{
		for (int j = 0; j < m_nTree; j++)
			if (m_ppTree[j])
			{
				delete m_ppTree[j];
				//cout << j <<"Æ®¸®" << endl;


			}
		//cout << "delete[]Àü Tree " << endl;
		delete[] m_ppTree;
		//cout << "delete[]ÈÄ  Tree" << endl;

	}


}


/////////////////////////////////Flower



CInstancingShader_Flower::CInstancingShader_Flower() { }
CInstancingShader_Flower::~CInstancingShader_Flower() { }

D3D12_INPUT_LAYOUT_DESC CInstancingShader_Flower::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//Á¤Á¡ Á¤º¸¸¦ À§ÇÑ ÀÔ·Â ¿ø¼ÒÀÌ´Ù. 
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CInstancingShader_Flower::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTexturedInstancing", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CInstancingShader_Flower::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTexturedInstancing", "ps_5_1", ppd3dShaderBlob));
}
void CInstancingShader_Flower::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CInstancingShader_Flower::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	//ÀÎ½ºÅÏ½º Á¤º¸¸¦ ÀúÀåÇÒ Á¤Á¡ ¹öÆÛ¸¦ ¾÷·Îµå Èü À¯ÇüÀ¸·Î »ý¼ºÇÑ´Ù. 
	m_pd3dcbFlower = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, sizeof(VS_VB_INSTANCE) * m_nFlower, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//Á¤Á¡ ¹öÆÛ(¾÷·Îµå Èü)¿¡ ´ëÇÑ Æ÷ÀÎÅÍ¸¦ ÀúÀåÇÑ´Ù.
	m_pd3dcbFlower->Map(0, NULL, (void **)&m_pcbMappedFlower);
}
void CInstancingShader_Flower::ReleaseShaderVariables()
{
	if (m_pd3dcbFlower) m_pd3dcbFlower->Unmap(0, NULL);
	if (m_pd3dcbFlower) m_pd3dcbFlower->Release();
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}
//ÀÎ½ºÅÏ½Ì Á¤º¸(°´Ã¼ÀÇ ¿ùµå º¯È¯ Çà·Ä°ú »ö»ó)¸¦ Á¤Á¡ ¹öÆÛ¿¡ º¹»çÇÑ´Ù.
void CInstancingShader_Flower::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	for (int j = 0; j < m_nFlower; j++)
	{
		XMStoreFloat4x4(&m_pcbMappedFlower[j].m_xmf4x4Transform, XMMatrixTranspose(XMLoadFloat4x4(&m_ppFlower[j]->m_xmf4x4World)));
	}
	pd3dCommandList->SetGraphicsRootShaderResourceView(9, m_pd3dcbFlower->GetGPUVirtualAddress());

}


void CInstancingShader_Flower::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList*pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;

	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = 45;
	int yObjects = 1;
	int zObjects = 45;
	m_nFlower = (xObjects * yObjects * zObjects);

	/*CTexture *pTexture = new CTexture(6, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/rocks2.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 4);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 5);*/

	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Flowers/Flower.dds", 0);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Flowers/Flower.dds", 1);

	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 2);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 3);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 4);
	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Trees/Tree02.dds", 5);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, 0, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 10, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

	CTexturedRectMesh *pCubeMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 10.0f, 8, 0);


	m_ppFlower = new CGameObject*[m_nFlower];

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	CBillboardObject *pRotatingObject = NULL;
	//	for (int i = 0, x = 0; x < xObjects; x++)
	//	{
	//		for (int z = 0; z < zObjects; z++)
	//		{
	//			for (int y = 0; y < yObjects; y++)
	//			{
	//				pRotatingObject = new CBillboardObject(1);
	//#ifndef _WITH_BATCH_MATERIAL
	//				pRotatingObject->SetMaterial(pCubeMaterial);
	//#endif
	//				float xPosition = x * fxPitch;
	//				float zPosition = z * fzPitch;
	//				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
	//				pRotatingObject->SetPosition(xPosition, fHeight + (y * 3.0f * fyPitch) + 6.0f+50, zPosition);
	//				if (y == 0)
	//				{
	//					xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
	//					xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
	//					if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//					float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
	//					pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
	//				}
	//				//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//				//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
	//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	//				m_ppTree[i++] = pRotatingObject;
	//			}
	//		}
	//	}

	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{

			pRotatingObject = new CBillboardObject(1);
#ifndef _WITH_BATCH_MATERIAL
			pRotatingObject->SetMaterial(pCubeMaterial);
#endif
			float xPosition = 45 * x + 1050;
			float zPosition = 40 * z + 1050;
			pRotatingObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 4, zPosition,true);

			//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
			//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
			pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppFlower[i++] = pRotatingObject;

		}
	}
	// ÀÎ½ºÅÏ½Å¿ë ¸Þ½¬ ÇÏ³ª¸¸ Ã³¸®
	m_ppFlower[0]->SetMesh(0, pCubeMesh);
}
D3D12_DEPTH_STENCIL_DESC CInstancingShader_Flower::CreateDepthStencilState()
{
	//¿©±â
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

	/*d3dDepthStencilDesc.DepthEnable = FALSE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CInstancingShader_Flower::CreateBlendState()
{
	//¿©±â
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

	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	return(d3dBlendDesc);
}
void CInstancingShader_Flower::AnimateObjects(float fTimeElapsed)
{
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	for (int i = 0; i < m_nFlower; ++i)
	{
		m_ppFlower[i]->Animate(fTimeElapsed, m_pPlayer->GetCamera());

	}
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;

}

void CInstancingShader_Flower::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CObjectsShader::Render(pd3dCommandList, pCamera);
	//¸ðµç °ÔÀÓ °´Ã¼ÀÇ ÀÎ½ºÅÏ½Ì µ¥ÀÌÅÍ¸¦ ¹öÆÛ¿¡ ÀúÀåÇÑ´Ù.
	UpdateShaderVariables(pd3dCommandList);
	//ÇÏ³ªÀÇ Á¤Á¡ µ¥ÀÌÅÍ¸¦ »ç¿ëÇÏ¿© ¸ðµç °ÔÀÓ °´Ã¼(ÀÎ½ºÅÏ½º)µéÀ» ·»´õ¸µÇÑ´Ù.
	m_ppFlower[0]->Render(pd3dCommandList, pCamera, m_nFlower);

}

void CInstancingShader_Flower::ReleaseObjects()
{
	if (m_ppFlower)
	{
		for (int j = 0; j < m_nFlower; j++)
			if (m_ppFlower[j])
			{
				delete m_ppFlower[j];
				//cout << j <<"Æ®¸®" << endl;


			}
		//cout << "delete[]Àü Tree " << endl;
		delete[] m_ppFlower;
		//cout << "delete[]ÈÄ  Tree" << endl;

	}


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CSmokeShader::SetParticlePosition(XMFLOAT3 particlepos)
{
	m_ppSmoke[0]->SetPosition(particlepos.x, particlepos.y, particlepos.z, true);
}

CSmokeShader::CSmokeShader()
{
}

CSmokeShader::~CSmokeShader()
{
}

D3D12_INPUT_LAYOUT_DESC CSmokeShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//Á¤Á¡ Á¤º¸¸¦ À§ÇÑ ÀÔ·Â ¿ø¼ÒÀÌ´Ù. 
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CSmokeShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CSmokeShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSSmoke", "ps_5_1", ppd3dShaderBlob));
}




void CSmokeShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbSmoke = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nSmoke, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbSmoke->Map(0, NULL, (void **)&m_pcbMappedSmoke);
}

void CSmokeShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nSmoke; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedSmoke + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppSmoke[j]->m_xmf4x4World)));
#ifdef _WITH_BATCH_MATERIAL
		if (m_pMaterial) pbMappedcbGameObject->m_nMaterial = m_pMaterial->m_nReflection;
		pbMappedcbGameObject->m_iFrameTime = m_fFrameTime;
#endif
	}
}

void CSmokeShader::ReleaseShaderVariables()
{
	if (m_pd3dcbSmoke)
	{
		m_pd3dcbSmoke->Unmap(0, NULL);
		m_pd3dcbSmoke->Release();
	}

	CIlluminatedTexturedShader::ReleaseShaderVariables();
}

D3D12_BLEND_DESC CSmokeShader::CreateBlendState()
{
	//¿©±â
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	/*d3dBlendDesc.AlphaToCoverageEnable = FALSE;
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
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;*/

	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_COLOR;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);

}

D3D12_DEPTH_STENCIL_DESC CSmokeShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	/*d3dDepthStencilDesc.DepthEnable = TRUE;
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
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;*/

	d3dDepthStencilDesc.DepthEnable = FALSE;
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

//#define _WITH_TERRAIN_PARTITION

void CSmokeShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	int xObjects = 1, yObjects = 1, zObjects = 1, i = 0;

	m_nSmoke = PARTICLESIZE;//(xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Particle/Smoke.dds", 0);


	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nSmoke, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nSmoke, m_pd3dcbSmoke, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 12, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
	m_pMaterial->SetReflection(1);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
	pCubeMaterial->SetReflection(1);
#endif

	CTexturedRectMesh *pCubeMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 100, 100, 0);

	m_ppSmoke = new CGameObject*[m_nSmoke];

	float fxPitch = 12.0f * 2.5f, fyPitch = 12.0f * 2.5f, fzPitch = 12.0f * 2.5f;

	CBillboardObject *pRotatingObject = NULL;
	//	for (int x = -xObjects; x <= xObjects; x++)
	//	{
	//		for (int y = -yObjects; y <= yObjects; y++)
	//		{
	//			for (int z = -zObjects; z <= zObjects; z++)
	//			{
	//				pRotatingObject = new CRotatingObject(1);
	//				pRotatingObject->SetMesh(0, pCubeMesh);
	//#ifndef _WITH_BATCH_MATERIAL
	//				pRotatingObject->SetMaterial(pCubeMaterial);
	//#endif
	//				pRotatingObject->SetPosition(3500, 100, 5870,true);
	//				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//				pRotatingObject->SetRotationSpeed(10.0f * (i % 10));
	//				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
	//				m_ppObjects[i++] = pRotatingObject;
	//			}
	//		}
	//	}
	for (int j = 0; j < m_nSmoke; ++j)
	{
		pRotatingObject = new CBillboardObject(1);
		pRotatingObject->SetMesh(0, pCubeMesh);
#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif
		pRotatingObject->SetPosition(3500, 500, 5870, true);

		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppSmoke[i++] = pRotatingObject;

	}
	
	//m_pPlayer->m_pChild = *m_ppBullet;
}

void CSmokeShader::ReleaseObjects()
{
	if (m_ppSmoke)
	{
		for (int j = 0; j < m_nSmoke; j++)
			if (m_ppSmoke[j])
				delete m_ppSmoke[j];
		delete[] m_ppSmoke;
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) delete m_pMaterial;
#endif
}

void CSmokeShader::AnimateObjects(float fTimeElapsed)
{
	m_fFrameTime += 4* fTimeElapsed;

	for (int i = 0; i < m_nSmoke; ++i)
	{
		
		m_ppSmoke[i]->Animate(fTimeElapsed, m_pPlayer->GetCamera());
		
	}
//	cout << m_f3CrushPosition.x << endl;
	for (int i = 0; i < m_nSmoke; ++i)
	{

		m_ppSmoke[i]->SetPosition(m_f3CrushPosition[i].x, m_f3CrushPosition[i].y, m_f3CrushPosition[i].z, true);
		//m_ppSmoke[i]->m_bParticleActive = true;
	}
	//m_ppSmoke[0]->SetPosition(m_f3CrushPosition.x, m_f3CrushPosition.y, m_f3CrushPosition.z, true);
	/*for (int i = 0; i < m_nSmoke; ++i)
	{

		cout << m_ppSmoke[i]->m_fParticleDeleteTimer << endl;
	}*/

}

void CSmokeShader::ReleaseUploadBuffers()
{
	if (m_ppSmoke)
	{
		for (int j = 0; j < m_nSmoke; j++) if (m_ppSmoke[j]) m_ppSmoke[j]->ReleaseUploadBuffers();
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->ReleaseUploadBuffers();
#endif
}

void CSmokeShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CIlluminatedTexturedShader::Render(pd3dCommandList, pCamera);

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->UpdateShaderVariables(pd3dCommandList);
#endif

	for (int j = 0; j < m_nSmoke; j++)
	{
		
		if (m_ppSmoke[j])
		{
			if (m_fParticleDeleteTimer[j] <3)
			{
				if(m_ppSmoke[j]->GetPosition().x != 0)
				m_ppSmoke[j]->Render(pd3dCommandList, pCamera);

			}

		}
	}
}
