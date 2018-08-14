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
	BYTE byMiniMap;

	int iIndex = 0;
	int iParentIdx = 0;

	BYTE& GetTileOption() { return byOption; }
	D3DXVECTOR3& GetTileSize() { return vSize; }
	D3DXVECTOR3& GetTilePos() { return vPos; }
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX  matWorld;
	BYTE		byRoomNum;

	BYTE byOption;		// Ÿ���� �ɼ�.
	BYTE byDrawID;		// ������ �ɼ�.
} INFO;

typedef struct tagTexturePath
{
	wstring wstrObjKey = L"";
	wstring wstrStateKey = L"";
	wstring wstrPath = L"";
	int iCount = 0;

} IMGPATH;

typedef struct tagFrame
{
	tagFrame()
		: fFrame(0.f), fMax(0.f)
	{}

	tagFrame(float frame, float max)
		: fFrame(frame), fMax(max)
	{}

	float fFrame; // ���� �ִϸ��̼� ��� ����.
	float fMax;	// �ִ� ��� ����.

} FRAME;