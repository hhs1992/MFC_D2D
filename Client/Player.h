#pragma once
#include "Obj.h"

/* Player �߻��� */
class CPlayerIMP;
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBridge(CPlayerIMP* pBridge) { m_pBridge = pBridge; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void PlayerMove();
	
private:
	CPlayerIMP* m_pBridge;
	PLAYER_DIR	m_ePlayerDir = DOWN;
};

