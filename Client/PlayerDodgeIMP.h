#pragma once
#include "PlayerIMP.h"
class CPlayerDodgeIMP :
	public CPlayerIMP
{
public:
	CPlayerDodgeIMP();
	virtual ~CPlayerDodgeIMP();

	// CPlayerIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

