#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::GetTexture(const TCHAR * pStateKey/* = L""*/, const int & iIndex/* = 0*/)
{
	auto iter_find = find_if(m_MapMultiTex.begin(), m_MapMultiTex.end(),
		[&pStateKey](auto& MyPair)
	{
		return pStateKey == MyPair.first;
	});

	if(m_MapMultiTex.end() == iter_find)
		return nullptr;

	if ((size_t)iIndex < 0 || (size_t)iIndex >= iter_find->second.size())
		return nullptr;

	return iter_find->second[iIndex];
}

HRESULT CMultiTexture::InsertTexture(const TCHAR * pFilePath, const TCHAR * pStateKey/* = L""*/, 
	const int & iCount/* = 0*/)
{
	TCHAR szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);

		TEXINFO* m_pTexInfo = new TEXINFO;
		ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

		// D3DXGetImageInfoFromFile: ������ �̹��� ���Ͽ� ���� ������ D3DXIMAGE_INFO���� ������ִ� �Լ�.
		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &m_pTexInfo->tImgInfo)))
		{
			ERR_MSG(szFullPath);
			SafeDelete(m_pTexInfo);
			return E_FAIL;
		}

		// D3DXIMAGE_INFO������ �������� LPDIRECT3DTEXTURE9��ü�� ����.
		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice() /*Texture Com��ü ���� ��ü*/,
			szFullPath /*�̹��� ���*/,
			m_pTexInfo->tImgInfo.Width /*�̹����� ���� ũ��*/,
			m_pTexInfo->tImgInfo.Height /*�̹����� ���� ũ��*/,
			m_pTexInfo->tImgInfo.MipLevels /*mipmap�� ����ϱ� ���� ����ġ*/,
			0, /*������ �ؽ��ĸ� ����ϴ� ���*/
			m_pTexInfo->tImgInfo.Format /*�ؽ��Ŀ� ���� �ȼ� ����*/,
			D3DPOOL_MANAGED /*Direct3D �ڿ��鿡 ���� � �޸𸮿� ������ ���ΰ��� ���� ����*/,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, &m_pTexInfo->tImgInfo, nullptr, &m_pTexInfo->pTexture)))
		{
			ERR_MSG(L"Multi Texture Load Failed!!!");
			SafeDelete(m_pTexInfo);
			return E_FAIL;
		}

		m_MapMultiTex[pStateKey].push_back(m_pTexInfo);
	}

	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& MyPair : m_MapMultiTex)
	{
		for_each(MyPair.second.begin(), MyPair.second.end(),
			[](TEXINFO*& pTexInfo)
		{
			// ���� ����.
			pTexInfo->pTexture->Release(); // Com��ü�� ���� ����.
			SafeDelete(pTexInfo);
		});

		MyPair.second.clear();
		MyPair.second.shrink_to_fit();
	}

	m_MapMultiTex.clear();	
}

int CMultiTexture::GetFrameCount(const TCHAR * pStateKey)
{
	auto& iter_find = m_MapMultiTex.find(pStateKey);

	// ������
	if (iter_find == m_MapMultiTex.end())
		return 0;

	// ������
	return iter_find->second.size();
}

vector<TEXINFO*>& CMultiTexture::GetVecTexInfo(const TCHAR * pStateKey)
{
	auto& iter_find = m_MapMultiTex.find(pStateKey);

	return iter_find->second;
}

