#pragma once
#include "Scene.h"
class CNormal :
	public CScene
{
public:
	CNormal();
	virtual ~CNormal();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

