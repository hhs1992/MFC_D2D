#pragma once
#include "Scene.h"
class CLobby :
	public CScene
{
public:
	CLobby();
	virtual ~CLobby();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

