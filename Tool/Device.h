#pragma once
class CDevice
{
	DECLARE_SINGLETON(CDevice)
private:
	CDevice();
	~CDevice();

public:
	HRESULT InitDevice();
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr);
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPD3DXFONT GetFont() { return m_pFont; }

private:
	void SetParemeters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	// IDirect3D9: ���� ��ġ�� �����ϱ� ���� ��ɵ��� �����Ǿ��ִ� ��ü������(LPDIRECT3D9).
	// I (Interface)
	LPDIRECT3D9			m_p3D;

	// IDirect3DDevice9: �׷��� ��ġ�� ���� �������� �����ϴ� ��ü������(LPDIRECT3DDEVICE9)
	// I (Interface)
	LPDIRECT3DDEVICE9	m_pDevice;

	// LPD3DXSPRITE: DirectX���� 2D �̹����� �������ϰ� �����ϴ� Com��ü.
	LPD3DXSPRITE		m_pSprite;

	// LPD3DXFONT: ��Ʈ�� ����ϴ� Com��ü
	LPD3DXFONT			m_pFont;
	LPD3DXFONT			m_pMyFont;

	// I�� �����ϴ� �������̽����� COM��ü�� �θ���.
	// COM(Component Object Model)
	// ���� ȯ�濡 ������� ȣȯ�� ������ ������Ʈ(��ǰ)�� ����� ���� 
	// ����ũ�� ����Ʈ�� ������ ǥ��ȭ�� ����� �ٷ� COM�̴�.
};

