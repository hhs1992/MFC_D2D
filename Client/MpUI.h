#pragma once
#include "UserInterface.h"
class CMpUI :
	public CUserInterface
{
public:
	CMpUI();
	virtual ~CMpUI();

	// CUserInterface��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int		m_iMp;
};

