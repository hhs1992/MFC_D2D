#pragma once
#include "WeaponIMP.h"
class CShootIMP :
	public CWeaponIMP
{
public:
	CShootIMP();
	virtual ~CShootIMP();

	// CWeaponIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

