#pragma once
#include "Obj.h"
class CRoomTrigger :
	public CObj
{
public:
	CRoomTrigger();
	virtual ~CRoomTrigger();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

