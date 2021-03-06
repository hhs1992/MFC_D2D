#include "stdafx.h"
#include "ShotGunBullet.h"

#include "Effect.h"
#include "AnimEffect.h"
CShotGunBullet::CShotGunBullet() {}

CShotGunBullet::~CShotGunBullet() { Release(); }

HRESULT CShotGunBullet::Initialize()
{
	m_eObjectID = OBJ_BULLET;
	m_wstrObjKey = L"Bullet";
	m_wstrStateKey = L"Normal";
	m_fSpeed = 450.f;
	m_iBulletDamage = 1;
	m_tInfo.vSize = { 10.f, 10.f, 0 };
	m_fVanishTime = 3.f;

	return S_OK;
}

void CShotGunBullet::LateInit()
{
	// �Ѿ� ���� = ���콺 - �÷��̾�
	// ���� ����
	float fRandom = float(rand() % 200) - 100.f;
	m_tInfo.vDir = (CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll() - D3DXVECTOR3(fRandom, fRandom, 0.f)) -
		CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	/* ���� �ӵ� ���� ���� */
	float fRandomSpeed = float((rand() % 20) + 1);
	m_fSpeed -= fRandomSpeed;
}


int CShotGunBullet::Update()
{
	CObj::LateInit();

	/* Bullet �Ҹ� ���� */
	if (m_bIsDead) {
		CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(
			m_tInfo.vPos, L"Step", { 0.f, 7.f });
		CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
		return DEAD_OBJ;
	}
	else if (m_fVanishTimer > m_fVanishTime) {
		return DEAD_OBJ;
	}

	/* �Ѿ� �̵� */
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	/* �Ѿ� ��� ���� */
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CShotGunBullet::LateUpdate()
{
	m_fVanishTimer += CTimeMgr::GetInstance()->GetTime();
}

void CShotGunBullet::Render()
{
	CObj::UpdateRect();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DXCOLOR(255, 255, 255, 255));

	// �浹 ��Ʈ
	if (g_bOnRect)
		CObj::RenderLine();
}

void CShotGunBullet::Release()
{
}
