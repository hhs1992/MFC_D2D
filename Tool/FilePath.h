#pragma once
#include "afxwin.h"


// CFilePath ��ȭ �����Դϴ�.

class CFilePath : public CDialog
{
	DECLARE_DYNAMIC(CFilePath)

public:
	CFilePath(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFilePath();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

	list<IMGPATH*>	m_PathInfoLst;
	CListBox m_ListBox;
};
