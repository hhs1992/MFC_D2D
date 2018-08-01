#pragma once
#include "afxwin.h"


// CSubTileTool ��ȭ �����Դϴ�.

class CSubTileTool : public CDialog
{
	DECLARE_DYNAMIC(CSubTileTool)

public:
	CSubTileTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubTileTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBTILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	/* Func */
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedSubTileListSave();
	afx_msg void OnBnClickedSubTileListLoad();
	afx_msg void OnLbnSelectSubTileBox();
	afx_msg void OnBnClickedCancel();

	/* Ctrl */
	CStatic		m_PictureCtrl;
	CListBox	m_SubTileBox;

	/* User */
	void Release();

	/* Value */
	map<CString, CString>	m_mapTilePath;
	CImage*					m_pImage;
	int						m_iDrawID;
	
	afx_msg void OnBnClickedSubTileSave();
	afx_msg void OnBnClickedSubTileLoad();
};
