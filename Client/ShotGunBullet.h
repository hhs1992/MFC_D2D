#pragma once
#include "Bullet.h"
class CShotGunBullet :
	public CBullet
{
public:
	CShotGunBullet();
	virtual ~CShotGunBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float	m_fVanishTime;
};

