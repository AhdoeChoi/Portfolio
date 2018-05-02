#pragma once
#include "GameObject.h"
#include "Camera.h"
//게임 객체의 정보를 셰이더에게 넘겨주기 위한 구조체(상수 버퍼)이다. 
struct CB_GAMEOBJECT_INFO { XMFLOAT4X4 m_xmf4x4World; };

class CShader 
{
public:
	CPlayer *m_pPlayer;
public:
	bool bFollowMe;
public:
	CShader();
	virtual ~CShader();
private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(); 
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
	virtual D3D12_BLEND_DESC CreateBlendState(); 
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob); 
	D3D12_SHADER_BYTECODE CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList); virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World);
	virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
	virtual void SetPlayer(CPlayer * pPlayer) { }
protected: 
	ID3D12PipelineState **m_ppd3dPipelineStates = NULL;
	int m_nPipelineStates = 0;
public:
	//XMFLOAT3 HouseCenter;

};


class CPlayerShader : public CShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
};
class CObjectsShader : public CShader {
public:
	CObjectsShader();
	virtual ~CObjectsShader();
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext);

	virtual void AnimateObjects(float fTimeElapsed); 
	virtual void ReleaseObjects();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(); 
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob); 
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
	virtual void ReleaseUploadBuffers();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
	virtual void SetPlayer(CPlayer * pPlayer) { m_pPlayer = pPlayer; }
public: //셰이더에 포함되어 있는 모든 게임 객체들에 대한 마우스 픽킹을 수행한다. 
	virtual CGameObject *PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float *pfNearHitDistance);


protected: 
	CGameObject **m_ppObjects = NULL;
	int m_nObjects = 0;
	CGameObject **m_ppWall = NULL;
	int m_nWall = 0;
	CGameObject **m_ppDoar = NULL;
	int m_nDoar = 0;
	CGameObject **m_ppMirror = NULL;
	int m_nMirror = 0;
	CGameObject **m_ppSphere = NULL;
	int m_nSphere = 0;

	CGameObject **m_ppBullet = NULL; //총알
	int m_nBullet = 0; // 총알 갯수


	CGameObject **m_ppParticle = NULL; //파티클
	int m_nParticle = 0; // 파티클 갯수

	bool						m_bDoParticle;
	//test
	//CPlayer *m_pPlayer;
public:
	static bool m_bShootState;
	//static XMFLOAT3 Myxmf3Shift;

};

class CTerrainShader : public CShader
{
public: 
	CTerrainShader();
	virtual ~CTerrainShader();
		virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
		virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
		virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
		virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
};
