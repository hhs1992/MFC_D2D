#pragma once
#include "Observer.h"
class CUIObserver :
	public CObserver
{
public:
	CUIObserver();
	virtual ~CUIObserver();

public:
	const DATA& GetData() { return m_tData; }

public: 
	// CObserver��(��) ���� ��ӵ�
	virtual void Update(int iMessage, void * pData) override;

private:
	DATA m_tData;
};

