#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO& GetInfo() { return m_tInfo; }
	void SetPos(D3DXVECTOR3& vPos) { m_tInfo.vPos = vPos; }
	const RECT& GetRect() { return m_tRect; }

	const wstring& GetObjKey() { return m_wstrObjKey; }
	const wstring& GetSateKey() { return m_wstrStateKey; }
	void IsDead() { this->m_bIsDead = true; }
public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	void MoveFrame();
	void UpdateRect();
	void RenderLine();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	float		m_fSpeed;
	bool		m_bIsInit;
	bool		m_bIsDead;

	wstring		m_wstrObjKey;
	wstring		m_wstrStateKey;
};

