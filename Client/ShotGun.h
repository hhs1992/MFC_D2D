#pragma once
#include "Weapon.h"
class CShotGun :
	public CWeapon
{
public:
	CShotGun();
	virtual ~CShotGun();

	// CWeapon��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

