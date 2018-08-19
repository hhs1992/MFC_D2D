#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

public:
	virtual void CreateBullet() PURE;	// �Ѿ� �߻�
	virtual void WeaponReload() PURE;	// ������
	
	GUN_DATA& GetGunData() { return m_tGunData; }

protected:
	GUN_DATA	m_tGunData;
	float		m_fReloadTime;		// ������ �ð�
	float		m_fWeaponDelay;		// ���� �ӵ�
	float		m_fWeaponDelayTime;
	bool		m_bCanShot;
};


