#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice()
	: m_p3D(nullptr), m_pDevice(nullptr), m_pSprite(nullptr), m_pFont(nullptr)
{
}


CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::InitDevice()
{
	// ��ġ �ʱ�ȭ ����
	// 1.	LPDIRECT3D9 ��ü ����
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (nullptr == m_p3D)
		return E_FAIL;

	// 2. ��ġ ����(����, ���ؽ� ���μ��� ����)
	// ���ؽ�(����) ���μ���: ���� ó�� + ���� ó��. ex) ������ �������� ���� �� �ǻ翡 ������ �繰�� ����.
	// ���ؽ� ���μ����� �ϵ����� �����ϴ����� �����ؾ��Ѵ�.

	// HAL(Hardware Abstraction Layer, �ϵ���� �߻� ����)
	// �����簡 �ٸ����� Ư�� �÷����� ���� �����ϰ� �����ϱ� ���ؼ���
	// �� �����縶�� �ϵ����鿡 �ʿ��� ������ �������� �߻�ȭ�� �ʿ䰡 �ִ�.

	// 2-1.HAL�� ���Ͽ� ���� ��ġ�� ���� ������ ���� �� D3DCAPS9 ����ü�� ����ؾ���.
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps: ��ġ�� ���� ����(HAL)�� ������ �Լ�.
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed!!!");
		return E_FAIL;
	}

	// 2-2. ���ؽ� ���μ��� ���� ����
	DWORD vp;

	// HAL�� ���� ������ ��ġ�� �ϵ���� ���ؽ� ���μ����� �����ϴ��� ����.
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// �ϵ���� ���ؽ� ���μ����� ���.
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	// 3. LPDIRECT3DDEVICE9 ��ü ����

	// 3-1. 
	// D3DPRESENT_PARAMETERS: �츮�� �����ϰ��� �ϴ� LPDIRECT3DDEVICE9�� ������ ���� ���� ����ü.
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));	

	SetParemeters(d3dpp);

	// 3-2. LPDIRECT3DDEVICE9 ��ü ����
	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"Device Create Failed!!");
		return E_FAIL;
	}

	// ��������Ʈ Com��ü ����
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Sprite Create Failed!!");
		return E_FAIL;
	}

	// ��Ʈ Com��ü ����
	// D3DXFONT_DESCW: ����� ��Ʈ�� �Ӽ��� ����.
	D3DXFONT_DESCW	tFontInfo;
	
	tFontInfo.Height = 15;	// ����
	tFontInfo.Width = 5;	// �ʺ�
	tFontInfo.Weight = FW_HEAVY; // �β�
	tFontInfo.CharSet = HANGEUL_CHARSET; // �ѱ�
	lstrcpy(tFontInfo.FaceName, L"Consolas"); // �۾�ü

	// D3DXFONT_DESCW �Ӽ��� �������� ��Ʈ Com��ü�� �����ϰ� �ִ�.
	// LPD3DXFONT�� ��Ʈ �ؽ���(�̹���)�� ������ �����Ͽ� ����ϹǷ� �����ٴ� ������ �����Ѵ�.
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"Font Create Failed!!");
		return E_FAIL;
	}

	AddFontResourceEx(L"../Font/digital-7.ttf", FR_PRIVATE, 0);
	tFontInfo.Height = 16;	// ����
	tFontInfo.Width = 8;	// �ʺ�
	tFontInfo.Weight = FW_HEAVY; // �β�
	tFontInfo.Italic = FALSE;
	tFontInfo.CharSet = DEFAULT_CHARSET; // �ѱ�
	lstrcpy(tFontInfo.FaceName, L"Digital-7"); // �۾�ü

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pMyFont)))
	{
		ERR_MSG(L"Font Create Failed!!");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(L"Line Create Failed!!");
		return E_FAIL;
	}

	return S_OK; // �������� ��	
	// ���������� E_FAIL�� ����.
}

void CDevice::Render_Begin()
{
	// ������ ����: �ĸ���۸� ����. -> �ĸ���ۿ� �׸���. -> �ĸ���۸� ������۷� ��ü�� �� ȭ�鿡 ����Ѵ�.

	// 1. �ĸ� ���۸� ����.
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	// 2. �ĸ���ۿ� �׸���
	// ���⼭���� ����� ��(���)�� ���� ���̴�.
	m_pDevice->BeginScene();

	// 2D �̹����� ������ �� �� �ֵ��� ��ġ�� �غ�.
	// D3DXSPRITE_ALPHABLEND: ���� �׽�Ʈ�� ��ȿ�� ���¿��� ���� ������ ����Ѵ�.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(HWND hWnd/* = nullptr*/)
{
	// 2D �̹����� �׸����� ��ġ�� ����.
	m_pSprite->End();

	// ��������� ����� ���� �����̴�.
	m_pDevice->EndScene();

	// 3.�ĸ���۸� ������۷� ��ü�� �� ȭ�鿡 ����Ѵ�.
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}

void CDevice::Release()
{
	// ���� ����. m_p3D�� ���� ������ ��� m_pDevice�� �ҽǵȴ�.
	if (m_pLine)
		m_pLine->Release();

	if (m_pMyFont)
		m_pMyFont->Release();

	if (m_pFont)
		m_pFont->Release();

	if (m_pSprite)
		m_pSprite->Release();

	if (m_pDevice)
		m_pDevice->Release();

	if (m_p3D)
		m_p3D->Release();
}


void CDevice::SetParemeters(D3DPRESENT_PARAMETERS & d3dpp)
{
	// �ĸ� ������ ����, ���� ũ�� ����.
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;

	// �ĸ���� �ȼ� ���� ����. 32��Ʈ ����.
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// �ĸ���� ����.
	d3dpp.BackBufferCount = 1;

	// �ĸ���ۿ��� ����� ��Ƽ ���ø� Ÿ��.
	// ����� ������� �ʴ´�. ����ϰԵǸ� �����ս� ����.
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	
	// ��Ƽ ���ø� ǰ��
	d3dpp.MultiSampleQuality = 0;

	// ����ü�� ��� ����.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// ��ġ�� ����� ������ ����.
	d3dpp.hDeviceWindow = g_hWnd;

	d3dpp.Windowed = TRUE; // â���

	// Direct�� ����/���ٽ� ���۸� ����� �ڵ����� �����ϱ� ���ϴٸ� TRUE
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.Flags = 0;

	// ��üȭ�� �� ����� �ֻ���(�����) ����.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// ����� �ֻ����� FPS�� ����.
	// D3DPRESENT_INTERVAL_IMMEDIATE: ���� ���α׷� FPS�� ���� ��� �ÿ�.
	// D3DPRESENT_INTERVAL_DEFAULT: ������ ������ Directx�� �˾Ƽ� ����. ���� ������� ����.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
