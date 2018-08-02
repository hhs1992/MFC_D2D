#pragma once
#include "afxwin.h"


// CMonsterTool ��ȭ �����Դϴ�.

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonsterTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	/* MFC Ctrl */
	CButton m_RadioType[3];
	CListBox m_ListBox;
	CListBox m_SetBox;
	float m_fAttSpd;
	float m_fBulletSpd;

	/* MFC Func */
	afx_msg void OnBnClickedSetBtn();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnInitDialog();

	/* User */
	int i = 0;

	/* User Func */
	void Release();
};
