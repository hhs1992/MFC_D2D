#pragma once
#include "UserInterface.h"
class CkeyUI :
	public CUserInterface
{
public:
	CkeyUI();
	virtual ~CkeyUI();

	// CUserInterface��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iKey;
};

