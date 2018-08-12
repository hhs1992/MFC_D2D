#pragma once
#include "Monster.h"
class CNormalMonster :
	public CMonster
{
public:
	CNormalMonster();
	virtual ~CNormalMonster();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void AStarMove();
};

