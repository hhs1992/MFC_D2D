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
	// TImeMgr �ʱ�ȭ
	CTimeMgr::GetInstance()->InitTime();

	// Device �ʱ�ȭ
	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}


	if (FAILED(CSceneMgr::GetInstance()->SceneChange(CSceneMgr::LOBBY)))
	{
		ERR_MSG(L"Scene Change Failed");
		return E_FAIL;
	}

	// Tile Init
	if (FAILED(CTileMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"Tile Init Failed");
		return E_FAIL;
	}


	return S_OK;
}

void CMainGame::Update()
{
	// �ð� ������ Update �ֻ�ܿ��� ȣ��.
	CTimeMgr::GetInstance()->UpdateTime();

	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	CDevice::GetInstance()->Render_Begin();

	CSceneMgr::GetInstance()->Render();
	
	CDevice::GetInstance()->Render_End();
}

void CMainGame::Release()
{


	///// Manager Destory
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();

	CTileMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
}
