#pragma once
#include "Obj.h"
class CObstacle :
	public CObj
{
public:
	CObstacle();
	virtual ~CObstacle();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT LoadObstacle();

};

