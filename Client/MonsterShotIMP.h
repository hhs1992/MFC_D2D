#pragma once
#include "MonsterIMP.h"
class MonsterShotIMP :
	public MonsterIMP
{
public:
	MonsterShotIMP();
	virtual ~MonsterShotIMP();

	// MonsterIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

