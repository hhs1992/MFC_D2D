#pragma once
#include "BossIMP.h"
class CBossHalfIMP :
	public CBossIMP
{
public:
	CBossHalfIMP();
	virtual ~CBossHalfIMP();

	// CBossIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

