#pragma once
#include "PlayerIMP.h"
class CPlayerIdleIMP :
	public CPlayerIMP
{
public:
	CPlayerIdleIMP();
	virtual ~CPlayerIdleIMP();

	// CPlayerIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

