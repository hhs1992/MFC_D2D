#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

	wstring& GetStateKey() { return m_wstrObjKey; }

protected:
	int			m_iMaxBullet;		// �ִ� �Ѿ�
	int			m_iMagazine;		// źâ�� �Ѿ� ����
	float		m_fReloadTime;		// ������ �ð�
	float		m_fWeaponDelay;		// ���� �ӵ�
	bool		m_bIsGet;
};


