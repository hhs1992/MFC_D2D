#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	ShowCursor(false);

	// TImeMgr �ʱ�ȭ
	CTimeMgr::GetInstance()->InitTime();
	// Device �ʱ�ȭ
	if (FAILED(CDevice::GetInstance()->InitDevice())) {
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}
	// Texture �ҷ�����
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt"))) {
		ERR_MSG(L"ImgPath Load Fail");
		return E_FAIL;
	}
	// TileMgr Init
	if (FAILED(CTileMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"TileMgr Init Fail");
		return E_FAIL;
	}
	// SubTile Init
	if (FAILED(CSubTileMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"SubTileMgr Init Fail");
		return E_FAIL;
	}
	// SceneMgr Init
	if (FAILED(CSceneMgr::GetInstance()->SceneChange(CSceneMgr::LOBBY))) {
		ERR_MSG(L"Scene Change Failed");
		return E_FAIL;
	}
	return S_OK;
}

void CMainGame::Update()
{
	// �ð� ������ Update �ֻ�ܿ��� ȣ��.
	CTimeMgr::GetInstance()->UpdateTime();
	CKeyMgr::GetInstance()->KeyCheck();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CScrollMgr::ScrollLock2();
	CSceneMgr::GetInstance()->LateUpdate();

	// �浹 ��Ʈ
	if (CKeyMgr::GetInstance()->KeyDown(KEY_F1)) {
		if (g_bOnRect)
			g_bOnRect = false;
		else
			g_bOnRect = true;
	}


}

void CMainGame::Render()
{
	CDevice::GetInstance()->Render_Begin();
	CSceneMgr::GetInstance()->Render();
	/* �÷��̾� ��ǥ */
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	RECT rc = { 0, 0, 100,100 };
	TCHAR szPos[MIN_STR] = L"";
	swprintf_s(szPos, L"ScrollX: %d\nScrollY: %d\nCameraX: %d\nCameraY: %d", 
		(int)CScrollMgr::GetScroll().x, 
		(int)CScrollMgr::GetScroll().y,
		(int)CScrollMgr::GetCamera().x,
		(int)CScrollMgr::GetCamera().y);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szPos, lstrlen(szPos), &rc, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	CDevice::GetInstance()->Render_End();

	/* �̴ϸ� ���� ������ */
	
}

void CMainGame::Release()
{
	/* Devcie Destroy */
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();

	/* Manager Destroy */
	CTileMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CMouse::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CWeaponMgr::GetInstance()->DestroyInstance();
	CAstarMgr::GetInstance()->DestroyInstance();
}
