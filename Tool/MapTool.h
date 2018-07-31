#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Release();
	void TileListLoad();

	/////////////////////////////////////
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelectTileBox();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedSaveTile();
	afx_msg void OnBnClickedLoadTile();
	afx_msg void OnBnClickedTileListSave();
	afx_msg void OnBnClickedTileListLoad();
	afx_msg void OnEnChangeFindTileNum();
	afx_msg void OnEnChangeRoomNumber();

	/////////////////////////////////////
	CListBox m_TileBox;
	CStatic m_PictureCtrl;
	CButton m_CheckMove;
	CString m_strTileNum;
	CButton m_CheckTileInfo;

	/////////////////////////////////////
	map<CString, CImage*>	m_MapImg;
	map<CString, CString>	m_mapTilePath;
	CImage*					m_pImage;

	int		m_byCursorIndex;
	int		m_iDrawID;
	BYTE	m_SelectTileDrawID;
	BYTE	m_byCursorDrawID;
	BYTE	m_byTileOption;
	BYTE m_byCursorRoomNum;
	BYTE m_byTileRoomNum;
};
