#pragma once


// CBossTool ��ȭ �����Դϴ�.

class CBossTool : public CDialog
{
	DECLARE_DYNAMIC(CBossTool)

public:
	CBossTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBossTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOSSTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_byRoom;
	afx_msg void OnEnChangeRoom();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
};
