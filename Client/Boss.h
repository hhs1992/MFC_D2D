#pragma once
#include "Scene.h"
class CBoss :
	public CScene
{
public:
	CBoss();
	virtual ~CBoss();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

