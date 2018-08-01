#pragma once

typedef struct tagTexture
{
	// LPDIRECT3DTEXTURE9: �̹��� ������ ������ Com��ü
	LPDIRECT3DTEXTURE9	pTexture;

	// �̹��� ������ �����ϱ� ���� ����ü.
	D3DXIMAGE_INFO		tImgInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;	// Ÿ���� ����.
	D3DXVECTOR3	vSize;	// Ÿ���� ũ��.
	BYTE byOption;		// Ÿ���� �ɼ�.
	BYTE byDrawID;		// ������ �ɼ�.
	BYTE byRoomNum;		// 
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX  matWorld;

	BYTE byOption;		// Ÿ���� �ɼ�.
	BYTE byDrawID;		// ������ �ɼ�.
}INFO;

typedef struct tagTexturePath
{
	wstring wstrObjKey = L"";
	wstring wstrStateKey = L"";
	wstring wstrPath = L"";
	int iCount = 0;
}IMGPATH;