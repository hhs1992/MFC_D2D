#pragma once
#include "Weapon.h"
class CAK :
	public CWeapon
{
public:
	CAK();
	virtual ~CAK();

	// CWeapon을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

