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

protected:
	int			m_iMaxBullet;		// �ִ� �Ѿ�
	int			m_iMagazine;		// źâ�� �Ѿ� ����

	float		m_fReloadTime;		// ������ �ð�
	float		m_fWeaponDelay;		// ���� �ӵ�
	float		m_fWeaponDelayTime;
	bool		m_bCanShot;
};


