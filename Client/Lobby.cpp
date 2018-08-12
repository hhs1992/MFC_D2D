#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"
#include "NormalMonster.h"

CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

HRESULT CLobby::Initialize()
{
	// Tile �ҷ�����
	if (FAILED(CTileMgr::GetInstance()->LoadTile())) {
		return E_FAIL;
	}
	CTileMgr::GetInstance()->ReadyAdjacency();

	// Player ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5, 0.f }),
		OBJ_PLAYER);
	//	WeaponMgr Init
	if (FAILED(CWeaponMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"WeaponMgr Init Fail");
		return E_FAIL;
	}
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 300.f, WINCY * 0.5, 0.f }),
		OBJ_MONSTER);

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CWeaponMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
}


void CLobby::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
	CMouse::GetInstance()->LateUpdate();
	CWeaponMgr::GetInstance()->LateUpdate();
	//CScrollMgr::ScrollLock();
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
	CMouse::GetInstance()->Render();
	CWeaponMgr::GetInstance()->Render();
	CObjMgr::GetInstance()->Render();
}

void CLobby::Release()
{
}
