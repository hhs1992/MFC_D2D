#pragma once
#include "Obj.h"
class CDark2 :
	public CObj
{
public:
	CDark2();
	virtual ~CDark2();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT LoadDark();
	int		m_iAlpha = 0;

};

