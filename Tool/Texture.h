#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();

public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = L"" /*��Ƽ �ؽ�ó�� ��� ���Ǵ� ����*/,
		const int& iIndex = 0 /*��Ƽ �ؽ�ó�� �̹��� �ε��� ����*/) PURE;

public:
	virtual HRESULT InsertTexture(const TCHAR* pFilePath /*�̹��� ���*/,
		const TCHAR* pStateKey = L"" /*��Ƽ �ؽ�ó�� ��� ���Ǵ� ����*/,
		const int& iCount = 0 /*��Ƽ �ؽ�ó�� �̹��� ����*/) PURE;
	virtual void Release() PURE;
};

