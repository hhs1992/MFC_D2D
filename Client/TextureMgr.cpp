#include "stdafx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO* CTextureMgr::GetTexture(const TCHAR* pObjKey, const TCHAR* pStateKey, 
	const int & iIndex)
{
	// �켱 ObjKey�� CTexture�� Ž��
	auto iter_find = find_if(m_MapTexture.begin(), m_MapTexture.end(),
		[&pObjKey](auto& MyPair)
	{
		return pObjKey == MyPair.first;
	});

	if (m_MapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTexture(pStateKey, iIndex);
}

HRESULT CTextureMgr::InsertTexture(const TCHAR * pFilePath, const TCHAR * pObjKey, TEXTYPE eType,
	const TCHAR * pStateKey, const int & iCount)
{
	// �켱 ObjKey�� CTexture�� Ž��
	auto iter_find = find_if(m_MapTexture.begin(), m_MapTexture.end(),
		[&pObjKey](auto& MyPair)
	{
		return pObjKey == MyPair.first;
	});

	// �ش� ObjKey�� ã�� ���ϸ� ���� �������־�� �Ѵ�.
	if (m_MapTexture.end() == iter_find)
	{
		CTexture* pTexture = nullptr;

		switch (eType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(pFilePath, pStateKey, iCount)))
		{
			ERR_MSG(pFilePath);
			SafeDelete(pTexture);
			return E_FAIL;
		}

		m_MapTexture.insert({ pObjKey, pTexture });
	}	
	else if (TEX_MULTI == eType)
		iter_find->second->InsertTexture(pFilePath, pStateKey, iCount);

	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapTexture.clear();
}
