#pragma once


// CTriggerTool ��ȭ �����Դϴ�.

class CTriggerTool : public CDialog
{
	DECLARE_DYNAMIC(CTriggerTool)

public:
	CTriggerTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTriggerTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIGGERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_byRoomNumer;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BYTE m_byCursorRoomNum;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnChangeRoomNumber();
};
