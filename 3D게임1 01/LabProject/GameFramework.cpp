//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

CGameFramework::CGameFramework()
{
	_tcscpy_s(m_pszFrameRate, _T("LapProject ("));

	m_hInstance = NULL;
	m_hWnd = NULL;

	m_hDCFrameBuffer = NULL;
	m_hBitmapFrameBuffer = NULL;

	m_bActive = true;

	m_nObjects = 0;

	m_fRotateX = 0;
	m_fRotateY = 0;
	
	m_bShootState = false;
	memset(&m_bCrushListObject, 0, 0);
	memset(&m_bCrushListWall, 0, 0);
}

CGameFramework::~CGameFramework()
{
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);

	m_pPlayer = new CPlayer();
	m_pPlayer->m_pCamera->SetViewport(rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

	BuildFrameBuffer();

	BuildObjects();

	SetupGameState();

	return(true);
}

void CGameFramework::BuildFrameBuffer()
{
	HDC hDC = ::GetDC(m_hWnd);

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);

	m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, (rcClient.right - rcClient.left) + 1, (rcClient.bottom - rcClient.top) + 1);
	::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, m_pPlayer->m_pCamera->m_Viewport.m_nWidth, m_pPlayer->m_pCamera->m_Viewport.m_nHeight);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{
	HDC hDC = ::GetDC(m_hWnd);
	::BitBlt(hDC, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, m_pPlayer->m_pCamera->m_Viewport.m_nWidth, m_pPlayer->m_pCamera->m_Viewport.m_nHeight, m_hDCFrameBuffer, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::SetupGameState()
{
}

void CGameFramework::SetupRenderStates()
{
}

void CGameFramework::BuildObjects()
{
	/*비행기*/
	CAirplaneMesh *pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);
	m_pPlayer = new CPlayer();
	m_pPlayer->SetPosition(0.0f, 0.0f, 0);
	m_pPlayer->SetMesh(pAirplaneMesh);
	m_pPlayer->SetColor(RGB(0, 0, 255));

	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -25.0f));
	m_pPlayer->SetOOBB(XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f),XMFLOAT4(0,0,0,1));


	/*벽*/
	CWallMesh *pWallCubeMesh = new CWallMesh(110.0f, 110.0f, 40.0f); //이거 해제 안해줘도 되나? (80.0f, 40.0f, 40.0f);
	m_pWall = new CGameObject[6];
	
	//for (int i = 0; i < 6; ++i)
	//{
	//	m_pWall[i].SetPosition(0.0, 0.0f, (float)i * (float)40.f);
	//	m_pWall[i].SetMesh(pWallCubeMesh);
	//	m_pWall[i].SetColor(RGB(0, 0, 0));
	//	m_pWall[i].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 20.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//}

	m_pWall[0].SetPosition(0.0f, 0.0f, 0.0f);
	m_pWall[0].SetMesh(pWallCubeMesh);
	m_pWall[0].SetColor(RGB(0, 0, 0));
	//m_pWall[0].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 20.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	
	m_pWall[1].SetPosition(0.0f, 0.0f, 40.0f);
	m_pWall[1].SetMesh(pWallCubeMesh);
	m_pWall[1].SetColor(RGB(0, 0, 0));
	//m_pWall[1].SetOOBB(XMFLOAT3(0.0f, 0.0f, 40.0f), XMFLOAT3(20.0f, 20.0f, 60.0f), XMFLOAT4(0.0f, 0.0f, 0, 1.0f));

	m_pWall[2].SetPosition(0.0f, 0.0f, 80.0f);
	m_pWall[2].SetMesh(pWallCubeMesh);
	m_pWall[2].SetColor(RGB(0, 0, 0));
	//m_pWall[2].SetOOBB(XMFLOAT3(0.0f, 0.0f, 80.0f), XMFLOAT3(20.0f, 20.0f, 100.0f), XMFLOAT4(0.0f, 0.0f, 0, 1.0f));

	m_pWall[3].SetPosition(0.0f, 0.0f, 120.0f);
	m_pWall[3].SetMesh(pWallCubeMesh);
	m_pWall[3].SetColor(RGB(0, 0, 0));
	//m_pWall[3].SetOOBB(XMFLOAT3(0.0f, 0.0f, 120.0f), XMFLOAT3(20.0f, 20.0f, 140.0f), XMFLOAT4(0.0f, 0.0f, 0, 1.0f));

	m_pWall[4].SetPosition(0.0f, 0.0f, 160.0f);
	m_pWall[4].SetMesh(pWallCubeMesh);
	m_pWall[4].SetColor(RGB(0, 0, 0));
	//m_pWall[4].SetOOBB(XMFLOAT3(0.0f, 0.0f, 160.0f), XMFLOAT3(20.0f, 20.0f, 180.0f), XMFLOAT4(0.0f, 0.0f, 0, 1.0f));

	m_pWall[5].SetPosition(0.0f, 0.0f, 200.0f);
	m_pWall[5].SetMesh(pWallCubeMesh);
	m_pWall[5].SetColor(RGB(0, 0, 0));
	//m_pWall[5].SetOOBB(XMFLOAT3(0.0f, 0.0f, 160.0f), XMFLOAT3(20.0f, 20.0f, 180.0f), XMFLOAT4(0.0f, 0.0f, 0, 1.0f));


	//cout << m_pWall[4].m_xmOOBB.Center.x << "\t " << m_pWall[0].m_xmOOBB.Center.y << "\t" << m_pWall[0].m_xmOOBB.Center.z << endl;
	//cout << m_pWall[4].GetPosition().x << "\t" << m_pWall[4].GetPosition().y << "\t" << m_pWall[4].GetPosition().z << endl;
	//평면 4개만 있게 기획을 합시당 (무한한 공간이니까)

	m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, 50.0f);
	m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, 50.0f);
	//m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, 50.0f);
	//m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, 50.0f);


	/*장애물*/
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	default_random_engine dre;
	uniform_int<> uiColor(0, 120);
	uniform_real_distribution<> urPosition(-35.f, 35.f);
	uniform_real_distribution<> urSpeed(0.02f, 0.05f);
	uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌


	m_nObjects = 8;
	m_pObjects = new CGameObject[m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		m_pObjects[i].SetMesh(pObjectCubeMesh);
		m_pObjects[i].SetColor(RGB(uiColor(dre), uiColor(dre), uiColor(dre)));
		m_pObjects[i].SetPosition(urPosition(dre), urPosition(dre), urPosition(dre));
		m_pObjects[i].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
		m_pObjects[i].SetRotationSpeed(0.05f);
		m_pObjects[i].SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
		m_pObjects[i].SetMovingSpeed(urSpeed(dre));
		m_pObjects[i].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	/*m_pObjects[0].SetMesh(pObjectCubeMesh);
	m_pObjects[0].SetColor(RGB(255, 0, 0));
	m_pObjects[0].SetPosition(-13.5f, 0.0f, 24.0f);
	m_pObjects[0].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_pObjects[0].SetRotationSpeed(0.05f);
	m_pObjects[0].SetMovingDirection(XMFLOAT3(1.0f, 0.3f, 0.1f));
	m_pObjects[0].SetMovingSpeed(0.02f);
	m_pObjects[0].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[1].SetMesh(pObjectCubeMesh);
	m_pObjects[1].SetColor(RGB(0, 0, 255));
	m_pObjects[1].SetPosition(+13.5f, -16.0f, 14.0f);
	m_pObjects[1].SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_pObjects[1].SetRotationSpeed(0.1f);
	m_pObjects[1].SetMovingDirection(XMFLOAT3(-1.0f, 0.2f, 0.2f));
	m_pObjects[1].SetMovingSpeed(0.02f);
	m_pObjects[1].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[2].SetMesh(pObjectCubeMesh);
	m_pObjects[2].SetColor(RGB(0, 255, 0));
	m_pObjects[2].SetPosition(9.0f, 7.0f, 18.0f);
	m_pObjects[2].SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_pObjects[2].SetRotationSpeed(0.15f);
	m_pObjects[2].SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_pObjects[2].SetMovingSpeed(0.04f);
	m_pObjects[2].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[3].SetMesh(pObjectCubeMesh);
	m_pObjects[3].SetColor(RGB(0, 255, 255));
	m_pObjects[3].SetPosition(0.0f, -5.0f, 16.0f);
	m_pObjects[3].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_pObjects[3].SetRotationSpeed(0.06f);
	m_pObjects[3].SetMovingDirection(XMFLOAT3(0.2f, 0.3f, 0.0f));
	m_pObjects[3].SetMovingSpeed(0.01f);
	m_pObjects[3].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[4].SetMesh(pObjectCubeMesh);
	m_pObjects[4].SetColor(RGB(128, 0, 255));
	m_pObjects[4].SetPosition(10.0f, 13.0f, 36.0f);
	m_pObjects[4].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pObjects[4].SetRotationSpeed(0.06f);
	m_pObjects[4].SetMovingDirection(XMFLOAT3(0.0f, 1.0f, -1.0f));
	m_pObjects[4].SetMovingSpeed(0.02f);
	m_pObjects[4].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[5].SetMesh(pObjectCubeMesh);
	m_pObjects[5].SetColor(RGB(255, 0, 255));
	m_pObjects[5].SetPosition(-10.0f, 0.0f, 10.0f);
	m_pObjects[5].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pObjects[5].SetRotationSpeed(0.06f);
	m_pObjects[5].SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_pObjects[5].SetMovingSpeed(0.02f);
	m_pObjects[5].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[6].SetMesh(pObjectCubeMesh);
	m_pObjects[6].SetColor(RGB(255, 0, 255));
	m_pObjects[6].SetPosition(-10.0f, 10.0f, 21.0f);
	m_pObjects[6].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pObjects[6].SetRotationSpeed(0.06f);
	m_pObjects[6].SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_pObjects[6].SetMovingSpeed(0.02f);
	m_pObjects[6].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pObjects[7].SetMesh(pObjectCubeMesh);
	m_pObjects[7].SetColor(RGB(255, 0, 128));
	m_pObjects[7].SetPosition(-15.0f, 10.0f, 20.0f);
	m_pObjects[7].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pObjects[7].SetRotationSpeed(0.06f);
	m_pObjects[7].SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	m_pObjects[7].SetMovingSpeed(0.01f);
	m_pObjects[7].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	cout << m_pObjects[4].m_xmOOBB.Center.x << "\t " << m_pObjects[4].m_xmOOBB.Center.y << "\t" << m_pObjects[4].m_xmOOBB.Center.z << endl;
	cout << m_pObjects[4].GetPosition().x << "\t" << m_pObjects[4].GetPosition().y << "\t" << m_pObjects[4].GetPosition().z << endl;*/
	//총알 
	
}

void CGameFramework::ReleaseObjects()
{
	if (m_pObjects) delete[] m_pObjects;
	m_pObjects = NULL;

	
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);

	if (m_hWnd) DestroyWindow(m_hWnd);
}

void CGameFramework::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	DWORD dwDirection = 0;
	if (GetKeyboardState(pKeyBuffer))
	{
		if (pKeyBuffer[0x57] & 0xF0)
		{
			dwDirection |= DIR_FORWARD; //w
		}
		if (pKeyBuffer[0x53] & 0xF0)
		{
			dwDirection |= DIR_BACKWARD; //s
		}
		if (pKeyBuffer[0x41] & 0xF0)
		{
			dwDirection |= DIR_LEFT; // a
		}
		if (pKeyBuffer[0x44] & 0xF0)
		{
			dwDirection |= DIR_RIGHT; // d
		}
		if (pKeyBuffer[0x51] & 0xF0)
		{
			dwDirection |= DIR_UP; // q
		}
		if (pKeyBuffer[0x5A] & 0xF0)
		{
			dwDirection |= DIR_DOWN; //Z
		
		}
		if (pKeyBuffer[VK_UP] & 0xF0)
		{
			m_fRotateX = -0.03f;
			m_pPlayer->Rotate(m_fRotateX, 0, 0);
		
		}
		if (pKeyBuffer[VK_DOWN] & 0xF0)
		{
			m_fRotateX = 0.03f;
			m_pPlayer->Rotate(m_fRotateX, 0, 0);
		}
		if (pKeyBuffer[VK_LEFT] & 0xF0)
		{
			m_fRotateY = -0.03f;
			m_pPlayer->Rotate(0, m_fRotateY, 0);
		}
		if (pKeyBuffer[VK_RIGHT] & 0xF0)
		{
			m_fRotateY = 0.03f;
			m_pPlayer->Rotate(0, m_fRotateY, 0);
		}
		if (pKeyBuffer[VK_SPACE] & 0x80) //총알 발사 0x80으로 바꾸면 한번만
		{
			//총알
			if (m_bShootState == false)
			{
			
				CGameObject *bullet = new CGameObject;
				CCubeMesh *pBulletCubeMesh = new CCubeMesh(1.0f, 1.0f, 1.0f);

				bullet->SetMesh(pBulletCubeMesh);
				bullet->SetColor(RGB(255, 0, 0));
				bullet->SetPosition(m_pPlayer->GetPosition());
				bullet->SetRotationAxis(m_pPlayer->m_xmf3Look);
				bullet->SetRotationSpeed(1.9f);
				bullet->SetMovingDirection(m_pPlayer->GetUp());
				bullet->SetMovingSpeed(0.3f);
				bullet->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
				m_listBullet.push_back(bullet);
				m_bShootState = true;
			}

		}
		else
		{
			m_bShootState = false;
		}
	}
	//float cxDelta = 0.0f, cyDelta = 0.0f;
	//POINT ptCursorPos; //이게 마우스인거 같음
	//if (GetCapture() == m_hWnd)
	//{
	//	SetCursor(NULL);
	//	GetCursorPos(&ptCursorPos);
	//	//cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
	//	//cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
	//	cxDelta = m_fRotateX;
	//	cyDelta = m_fRotateY;
	//	SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	//}
	
		
		if (dwDirection)
		{
			m_pPlayer->Move(dwDirection, 0.04f);
			
			//m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
			//XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));


			m_pPlayer->m_xmOOBBTransformed.Transform(m_pPlayer->m_xmOOBB, XMLoadFloat4x4(&(m_pPlayer->m_xmf4x4World)));
			XMStoreFloat4(&(m_pPlayer->m_xmOOBBTransformed.Orientation),XMQuaternionNormalize(XMLoadFloat4(&(m_pPlayer->m_xmOOBBTransformed.Orientation))));
			
			//m_pPlayer->SetOOBB(m_pPlayer->GetPosition(), XMFLOAT3(5, 5, 5), XMFLOAT4(0, 0, 0, 1));

			//cout << m_pPlayer->m_xmOOBB.Center.x << "\t" << m_pPlayer->m_xmOOBB.Center.y << "\t" <<m_pPlayer->m_xmOOBB.Center.z << endl;
		}
	
	m_pPlayer->Update(0.00516f);
}

void CGameFramework::AnimateObjects() //FrameAdvance에서 계속 호출됨 
{

	//m_pPlayer->Animate();

	//cout << m_pObjects[0].GetPosition().x << "\t " << m_pObjects[0].GetPosition().y << "\t " << m_pObjects[0].GetPosition().z << "\t " << endl;
	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)//총알 순회하며 삭제
	{

		/*if ((Vector3::Subtract((*(iter))->GetPosition, m_pPlayer->GetPosition)))
		{

		}*/
		if (sqrt(((*iter)->GetPosition().x - m_pPlayer->GetPosition().x)*((*iter)->GetPosition().x - m_pPlayer->GetPosition().x) +
			((*iter)->GetPosition().y - m_pPlayer->GetPosition().y)*((*iter)->GetPosition().y - m_pPlayer->GetPosition().y) +
			((*iter)->GetPosition().z - m_pPlayer->GetPosition().z)*((*iter)->GetPosition().z - m_pPlayer->GetPosition().z)) > 250.f)
		{
			m_listBullet.erase(iter);
			
		}
	}

	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)//벽에 부딪힌 총알 처리
	{

		ContainmentType containType = m_pWall->m_xmOOBB.Contains((*iter)->m_xmOOBB);
		{
			switch (containType)
			{
			case DISJOINT: //벽을 뚫고 지나간경우
			{
				int nPlaneIndex = -1;
				for (int j = 0; j < 4; j++) //4개의 평면중 어느놈이랑 충돌했니?
				{
					PlaneIntersectionType intersectType = ((*iter)->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j])));
					if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
					{
						nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
						break;
					}
				}
				if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
				{
					
					m_listBullet.erase(iter);
				}
				break;
			}
			case INTERSECTS:
			{
				int nPlaneIndex = -1;
				for (int j = 0; j < 4; j++)
				{
					PlaneIntersectionType intersectType = (*iter)->m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
					if (intersectType == INTERSECTING)
					{
						nPlaneIndex = j;
						break;
					}
				}
				if (nPlaneIndex != -1)
				{
					m_listBullet.erase(iter);
				}
				break;
			}
			case CONTAINS:
				break;
			}

		}
	}

	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)//총알 회전
	{
		(*(iter))->Animate();
	}



	for (int i = 0; i < m_nObjects; i++) m_pObjects[i].Animate();
	for (int i = 0; i < m_nParticle; ++i) m_pParticle[i].Animate();

	for (int i = 0; i < m_nObjects; i++) //각 객체들에 대해서 충돌체크를 함
	{
		
		ContainmentType containType = m_pWall->m_xmOOBB.Contains(m_pObjects[i].m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
		switch (containType)
		{
		case DISJOINT: //벽을 뚫고 지나간경우
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
			{
				PlaneIntersectionType intersectType = m_pObjects[i].m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
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
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pObjects[i].m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_pObjects[i].m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 4; j++)
			{
				PlaneIntersectionType intersectType = m_pObjects[i].m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pObjects[i].m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_pObjects[i].m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}


	//여기서부턴 객체들끼리 충돌체크
	for (int i = 0; i < m_nObjects; i++) m_pObjects[i].m_pCollider = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{ 
			if (m_pObjects[i].m_xmOOBB.Intersects(m_pObjects[j].m_xmOOBB))
			{
				m_pObjects[i].m_pCollider = &m_pObjects[j];
				m_pObjects[j].m_pCollider = &m_pObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_pObjects[i].m_pCollider && m_pObjects[i].m_pCollider->m_pCollider) //충돌한 정보가 있으면
		{
			//서로의 무빙디렉션을 바꿔주겠다.

			XMFLOAT3 xmf3MovingDirection = m_pObjects[i].m_xmf3MovingDirection;
			float fMovingSpeed = m_pObjects[i].m_fMovingSpeed;
			m_pObjects[i].m_xmf3MovingDirection = m_pObjects[i].m_pCollider->m_xmf3MovingDirection;
			m_pObjects[i].m_fMovingSpeed = m_pObjects[i].m_pCollider->m_fMovingSpeed;
			m_pObjects[i].m_pCollider->m_xmf3MovingDirection = xmf3MovingDirection;
			m_pObjects[i].m_pCollider->m_fMovingSpeed = fMovingSpeed;
			m_pObjects[i].m_pCollider->m_pCollider = NULL;
			m_pObjects[i].m_pCollider = NULL;
		}
	}


	//총알과 장애물 충돌
	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)
	{
		for (int i = 0; i < OBJECTSIZE; ++i)
		{
			if (m_pObjects[i].m_xmOOBB.Intersects((*iter)->m_xmOOBB))
			{
				m_pObjects[i].m_bLifeState = DEATH;
				m_listBullet.erase(iter);
			}
		}
	}

	////비행기와 장애물 충돌
	//for (int i = 0; i < m_nObjects; i++) 
	//{

	//	ContainmentType containType = m_pPlayer->m_xmOOBB.Contains(m_pObjects[i].m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
	//	switch (containType)
	//	{
	//	case DISJOINT: //벽을 뚫고 지나간경우
	//	{
	//		//int nPlaneIndex = -1;
	//		//for (int j = 0; j < 4; j++) //6개의 평면중 어느놈이랑 충돌했니?
	//		//{
	//		//	PlaneIntersectionType intersectType = m_pObjects[i].m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//		//	if (intersectType == BACK) // 평면 뒤에있음 (걸쳐져있는게 아니라) 아예 뒤로 뚫고 지나간경우
	//		//	{
	//		//		nPlaneIndex = j; //뚫고 지나간 평면을 찾아서 break;
	//		//		break;
	//		//	}
	//		//}
	//		//if (nPlaneIndex != -1) // 뚫고 지나간평면 못찾음
	//		//{
	//		//	// 반사시키는 행위임 이게
	//		//	XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
	//		//	XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pObjects[i].m_xmf3MovingDirection), xmvNormal);
	//		//	XMStoreFloat3(&m_pObjects[i].m_xmf3MovingDirection, xmvReflect);
	//		//}
	//		//break;

	//
	//		break;
	//	}
	//	case INTERSECTS:
	//	{
	//		/*int nPlaneIndex = -1;
	//		for (int j = 0; j < 4; j++)
	//		{
	//			PlaneIntersectionType intersectType = m_pObjects[i].m_xmOOBB.Intersects(XMLoadFloat4(&m_pxmf4WallPlanes[j]));
	//			if (intersectType == INTERSECTING)
	//			{
	//				nPlaneIndex = j;
	//				break;
	//			}
	//		}
	//		if (nPlaneIndex != -1)
	//		{
	//			XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
	//			XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pObjects[i].m_xmf3MovingDirection), xmvNormal);
	//			XMStoreFloat3(&m_pObjects[i].m_xmf3MovingDirection, xmvReflect);
	//		}
	//		break;*/

	//		m_pPlayer->m_bCrushState = true;
	//		
	//		
	//		break;
	//		
	//	}
	//	case CONTAINS:
	//		break;
	//	}

	//	if (m_pPlayer->m_bCrushState)
	//		m_pPlayer->SetColor(RGB(0, 255, 255));
	//	

	//	cout << containType << endl;
	//}


	//비행기와 장애물 충돌
	for (int i = 0; i < m_nObjects; ++i)
	{
		/*if (m_pPlayer->m_xmOOBB.Intersects(m_pObjects[i].m_xmOOBB))*/
		if (m_pObjects[i].m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//m_pPlayer->m_bCrushState = true;
			m_bCrushListObject[i] = true;
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
		default_random_engine dre;
		uniform_int<> uiColor(55, 255);
		uniform_real_distribution<> urPosition(-35.f, 35.f);
		uniform_real_distribution<> urSpeed(0.02f, 0.05f);
		uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);

		m_pPlayer->SetPosition(0, 0, 0);
		//m_pPlayer->m_xmf3Look.z = 1;
	
		for (int i = 0; i < m_nObjects; ++i)
		{
		
			m_pObjects[i].SetPosition(urPosition(dre), urPosition(dre), urPosition(dre));
			m_pObjects[i].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
			m_pObjects[i].SetRotationSpeed(0.05f);
			m_pObjects[i].SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
			m_pObjects[i].SetMovingSpeed(urSpeed(dre));
	
		}

	}

	
	
	//벽과 비행기의 충돌
	
	//cout << m_pPlayer->m_xmf3Look.x << "\t" << m_pPlayer->m_xmf3Look.y << "\t" << m_pPlayer->m_xmf3Look.z << endl;
	//cout << m_pPlayer->m_xmf3MovingDirection.x << "\t" << m_pPlayer->m_xmf3MovingDirection.y << " \t" << m_pPlayer->m_xmf3MovingDirection.z << endl;
	//cout << m_pPlayer->GetLook().x << "\t " << m_pPlayer->GetLook().y << "\t" << m_pPlayer->GetLook().z << "\t" << "]tsdfsdkf" << endl;
	//m_pPlayer->SetMovingDirection(XMFLOAT3(2.0f, 2.0f, 2.0f));
 	ContainmentType containType = m_pWall->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB); //각 객체마다 벽과의 충돌체크를함
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
				
				if (m_pPlayer->m_xmf3Look.x != m_pPlayer->m_xmf3MovingDirection.x)
				{
					/*m_pPlayer->m_xmf3Look.x += m_pPlayer->m_xmf3MovingDirection.x;
					m_pPlayer->m_xmf3Look.y += m_pPlayer->m_xmf3MovingDirection.y;
					m_pPlayer->m_xmf3Look.z += m_pPlayer->m_xmf3MovingDirection.z;*/
					
				}

				m_pPlayer->m_xmf3Position.x += m_pxmf4WallPlanes[nPlaneIndex].x * 0.2f;
				m_pPlayer->m_xmf3Position.y += m_pxmf4WallPlanes[nPlaneIndex].y* 0.2f;
				m_pPlayer->m_xmf3Position.y += m_pxmf4WallPlanes[nPlaneIndex].z* 0.2f;

			cout << endl;
			
		}
		else
		{
			m_pPlayer->SetColor(RGB(0, 0, 0));
			//cout << " 충돌 안함 " << endl;
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
		if (nPlaneIndex != -1)
		{
			XMVECTOR xmvNormal = XMVectorSet(m_pxmf4WallPlanes[nPlaneIndex].x, m_pxmf4WallPlanes[nPlaneIndex].y, m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
			XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection), xmvNormal);
			XMStoreFloat3(&(m_pPlayer->m_xmf3Look), xmvReflect);
			XMStoreFloat3(&(m_pPlayer->m_xmf3MovingDirection), xmvReflect);
			//cout << " 충돌!" << endl;
		
		}
		else
		{
			//cout << "충돌 안함 " << endl;
		}

		break;
	}
	case CONTAINS:
	
		break;
	}
	//if (m_pPlayer->m_pCollider && m_pObjects[i].m_pCollider->m_pCollider) //충돌한 정보가 있으면
	//{
	//	//서로의 무빙디렉션을 바꿔주겠다.

	//	XMFLOAT3 xmf3MovingDirection = m_pObjects[i].m_xmf3MovingDirection;
	//	float fMovingSpeed = m_pObjects[i].m_fMovingSpeed;
	//	m_pObjects[i].m_xmf3MovingDirection = m_pObjects[i].m_pCollider->m_xmf3MovingDirection;
	//	m_pObjects[i].m_fMovingSpeed = m_pObjects[i].m_pCollider->m_fMovingSpeed;
	//	m_pObjects[i].m_pCollider->m_xmf3MovingDirection = xmf3MovingDirection;
	//	m_pObjects[i].m_pCollider->m_fMovingSpeed = fMovingSpeed;
	//	m_pObjects[i].m_pCollider->m_pCollider = NULL;
	//	m_pObjects[i].m_pCollider = NULL;
	//}
}

void CGameFramework::FrameAdvance()
{
	if (!m_bActive) return;
	
	m_pPlayer->m_xmf3MovingDirection = m_pPlayer->m_xmf3Look;
	//cout << m_pPlayer->GetPosition().x << "\t" << m_pPlayer->GetPosition().y << "\t" << m_pPlayer->GetPosition().z << endl;
	//cout << m_pObjects[0].GetPosition().x << "\t" <<m_pObjects[0].GetPosition().y << "\t" << m_pObjects[0].GetPosition().z << endl;
	

	//내 뒤에있는 객체 처리
	for (int i = 0; i < 8; ++i)
	{
		if (m_pPlayer->GetPosition().z - 10 > m_pObjects[i].GetPosition().z)
		{
			m_pObjects[i].SetPosition(XMFLOAT3(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z + 80));
		}
	}

	// 총알 맞은 객체는 다시 뒤로 보내자
	for (int i = 0; i < 8; ++i)
	{
		if (m_pObjects[i].m_bLifeState == DEATH)
		{
			//파티클을 생성하고
			
			CCubeMesh *pParticleCubeMesh = new CCubeMesh(1.0f, 1.0f, 1.0f);

			default_random_engine dre;
			uniform_real_distribution<> urSpeed(0.6f, 1.0f);
			uniform_real_distribution<> urMovingDirect(-10.0, 10.0f);
			uniform_int<> uiColor(55, 255);

			m_nParticle = 64;
			m_pParticle = new CGameObject[m_nParticle];
			for (int j = 0; j < m_nParticle; ++j)
			{
				
				m_pParticle[j].SetMesh(pParticleCubeMesh);
				m_pParticle[j].SetColor(RGB(uiColor(dre),uiColor(dre),uiColor(dre)));
				m_pParticle[j].SetPosition(m_pObjects[i].GetPosition());
				m_pParticle[j].SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
				//m_pParticle[j].SetRotationSpeed(0.5);
				m_pParticle[j].SetMovingDirection(XMFLOAT3(urMovingDirect(dre), urMovingDirect(dre), urMovingDirect(dre)));
				m_pParticle[j].SetMovingSpeed(urSpeed(dre));
				//m_pParticle[i].SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			}


			//뒤로 보내자
			m_pObjects[i].SetPosition(XMFLOAT3(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z + 80));
			m_pObjects[i].m_bLifeState = LIVE;
		}
	}

	//무한한 공간
	if (m_pPlayer->GetPosition().z >  m_pWall[0].GetPosition().z + 20)
	{	
//m_pWall[2].SetColor(RGB(255, 0, 0));

		m_pWall[0].SetPosition(m_pWall[5].GetPosition().x, m_pWall[5].GetPosition().y, m_pWall[5].GetPosition().z + 40);
		
	}

	if (m_pPlayer->GetPosition().z > m_pWall[1].GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[1].SetPosition(m_pWall[0].GetPosition().x, m_pWall[0].GetPosition().y, m_pWall[0].GetPosition().z + 40);

	}
	if (m_pPlayer->GetPosition().z > m_pWall[2].GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[2].SetPosition(m_pWall[1].GetPosition().x, m_pWall[1].GetPosition().y, m_pWall[1].GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > m_pWall[3].GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[3].SetPosition(m_pWall[2].GetPosition().x, m_pWall[2].GetPosition().y, m_pWall[2].GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > m_pWall[4].GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[4].SetPosition(m_pWall[3].GetPosition().x, m_pWall[3].GetPosition().y, m_pWall[3].GetPosition().z + 40);
	}
	if (m_pPlayer->GetPosition().z > m_pWall[5].GetPosition().z + 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[5].SetPosition(m_pWall[4].GetPosition().x, m_pWall[4].GetPosition().y, m_pWall[4].GetPosition().z + 40);
	}




	if (m_pPlayer->GetPosition().z < m_pWall[0].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[5].SetPosition(m_pWall[0].GetPosition().x, m_pWall[0].GetPosition().y, m_pWall[0].GetPosition().z - 40);
	
	}
	if (m_pPlayer->GetPosition().z < m_pWall[5].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[4].SetPosition(m_pWall[5].GetPosition().x, m_pWall[5].GetPosition().y, m_pWall[5].GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < m_pWall[4].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[3].SetPosition(m_pWall[4].GetPosition().x, m_pWall[4].GetPosition().y, m_pWall[4].GetPosition().z - 40);
	}

	if (m_pPlayer->GetPosition().z < m_pWall[3].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[2].SetPosition(m_pWall[3].GetPosition().x, m_pWall[3].GetPosition().y, m_pWall[3].GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < m_pWall[2].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[1].SetPosition(m_pWall[2].GetPosition().x, m_pWall[2].GetPosition().y, m_pWall[2].GetPosition().z - 40);
	}
	if (m_pPlayer->GetPosition().z < m_pWall[1].GetPosition().z - 20)
	{
		//m_pWall[2].SetColor(RGB(255, 0, 0));
		m_pWall[0].SetPosition(m_pWall[1].GetPosition().x, m_pWall[1].GetPosition().y, m_pWall[1].GetPosition().z - 40);
	}
	//if ( m_pPlayer->m_xmf3Position.z < m_)


	m_GameTimer.Tick(0.0f);


	ProcessInput();

	AnimateObjects();

	ClearFrameBuffer(RGB(255, 255, 255));

	//벽 출력
	m_pWall[0].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pWall[1].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pWall[2].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pWall[3].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pWall[4].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pWall[5].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);

	//장애물 출력
	for (int i = 0; i < m_nObjects; i++)
		m_pObjects[i].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);

	// 비행기 출력
	m_pPlayer->Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);

	// 총알 출력
	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end(); ++iter)
	{
		(*iter)->Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	}
	// 파티클출력
	for (int j = 0; j < m_nParticle; ++j)
	{
		m_pParticle[j].Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	}
		

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37); ::SetWindowText(m_hWnd, m_pszFrameRate);
	
	PresentFrameBuffer();
}


