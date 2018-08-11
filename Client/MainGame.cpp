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
	CSceneMgr::GetInstance()->LateUpdate();

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
	CDevice::GetInstance()->Render_End();
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
