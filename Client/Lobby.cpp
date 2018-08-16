#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"
#include "NormalMonster.h"
#include "Trigger.h"
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
	// ���� Ÿ�� �˻�(Astar)
	CTileMgr::GetInstance()->ReadyAdjacency();
	// SubTileMgr Load

	if (FAILED(CSubTileMgr::GetInstance()->LoadSubTile())) {
		ERR_MSG(L"SubTile Load Fail");
		return E_FAIL;
	}
	// Player ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(D3DXVECTOR3{ 445.f, 360.f, 0.f }),
		OBJ_PLAYER);
	//	WeaponMgr Init
	if (FAILED(CWeaponMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"WeaponMgr Init Fail");
		return E_FAIL;
	}
	// 
	CTrigger temp;
	if (FAILED(temp.LoadTrigger())) {
		E_FAIL;
	}

	// �ӽ� Monster ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 300.f, WINCY * 0.5, 0.f }),
		OBJ_MONSTER);
	// �ӽ� Monster ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 100.f, WINCY * 0.5 + 100.f, 0.f }),
		OBJ_MONSTER);
	// �ӽ� Monster ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 200.f, WINCY * 0.5, 0.f }),
		OBJ_MONSTER);

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
	CWeaponMgr::GetInstance()->Update();
}


void CLobby::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
	CMouse::GetInstance()->LateUpdate();
	CWeaponMgr::GetInstance()->LateUpdate();
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
	CSubTileMgr::GetInstance()->Render();
	CWeaponMgr::GetInstance()->Render();
	CObjMgr::GetInstance()->Render();
	CMouse::GetInstance()->Render();

	// �̴ϸ�
	CTileMgr::GetInstance()->MiniMapRender(0.05f);
}

void CLobby::Release()
{
}
