#pragma once
#include "BossIMP.h"
class CBossSkillIMP :
	public CBossIMP
{
public:
	CBossSkillIMP();
	virtual ~CBossSkillIMP();

	// CBossIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

