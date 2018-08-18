#pragma once
#include "Monster.h"
class CBoss2 :
	public CMonster
{
public:
	CBoss2();
	virtual ~CBoss2();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void AstarMove();
	void BossAttack();
};

