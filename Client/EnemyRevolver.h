#pragma once
#include "Weapon.h"
class CEnemyRevolver :
	public CWeapon
{
public:
	CEnemyRevolver();
	virtual ~CEnemyRevolver();

	// CWeapon��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void CreateBullet() override;
	virtual void WeaponReload() override;
};

